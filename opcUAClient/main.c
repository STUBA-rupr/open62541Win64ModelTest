#include <stdio.h>
#include "open62541.h"
#include <signal.h>

UA_Boolean running = true;
UA_Int32 opcuaSubscriptionId = -1;
//UA_Logger logger = UA_Log_Stdout;


static void stopHandler(int sign) {
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received Ctrl-C");
	running = 0;
}

static void
handler_currentTimeChanged(UA_Client *client, UA_UInt32 subId, void *subContext,
	UA_UInt32 monId, void *monContext, UA_DataValue *value) {

	//UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "loopCount has changed!");
	if (UA_Variant_hasScalarType(&value->value, &UA_TYPES[UA_TYPES_UINT32])) {
		UA_UInt32 loopCount = *(UA_UInt32 *)value->value.data;
		/*SYSTEMTIME t;
		GetSystemTime(&t); // or GetLocalTime(&t)*/
		DWORD now = GetTickCount();
		
		printf("loop: %.3d,%u\n", loopCount, now);
	}
}

static void
deleteSubscriptionCallback(UA_Client *client, UA_UInt32 subscriptionId, void *subscriptionContext) {
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Subscription Id %u was deleted", subscriptionId);
}

static void
subscriptionInactivityCallback(UA_Client *client, UA_UInt32 subId, void *subContext) {
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Inactivity for subscription %u", subId);
}

static void
stateCallback(UA_Client *client, UA_ClientState clientState) {
	switch (clientState) {
	case UA_CLIENTSTATE_DISCONNECTED:
		UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "The client is disconnected");
		break;
	case UA_CLIENTSTATE_WAITING_FOR_ACK:
		UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Waiting for ack");
		break;
	case UA_CLIENTSTATE_CONNECTED:
		UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "A TCP connection to the server is open");
		break;
	case UA_CLIENTSTATE_SECURECHANNEL:
		UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "A SecureChannel to the server is open");
		break;
	case UA_CLIENTSTATE_SESSION: {
		UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "A session with the server is open");
		/* A new session was created. We need to create the subscription. */
		/* Create a subscription */
		UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
		UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(client, request,
			NULL, NULL, deleteSubscriptionCallback);

		if (response.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
			UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Create subscription succeeded, id %u", response.subscriptionId);
		else
			return;

		/* Add a MonitoredItem */
		UA_MonitoredItemCreateRequest monRequest =
			UA_MonitoredItemCreateRequest_default(UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME));

		UA_MonitoredItemCreateResult monResponse =
			UA_Client_MonitoredItems_createDataChange(client, response.subscriptionId,
				UA_TIMESTAMPSTORETURN_BOTH,
				monRequest, NULL, handler_currentTimeChanged, NULL);
		if (monResponse.statusCode == UA_STATUSCODE_GOOD)
			UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Monitoring UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME', id %u", monResponse.monitoredItemId);
	}
								 break;
	case UA_CLIENTSTATE_SESSION_RENEWED:
		UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "A session with the server is open (renewed)");
		/* The session was renewed. We don't need to recreate the subscription. */
		break;
	case UA_CLIENTSTATE_SESSION_DISCONNECTED:
		UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Session disconnected");
		break;
	}
	return;
}


int main(int argc, char *argv[])
{
	signal(SIGINT, stopHandler);
	signal(SIGTERM, stopHandler);

	UA_Client *client = UA_Client_new();
	UA_ClientConfig *config = UA_Client_getConfig(client);
	UA_StatusCode retval;

	// set up endpoint security policy
	UA_ClientConfig_setDefault(config);

	// pozriet
	//https://github.com/open62541/open62541/issues/2777

	// Configuration for monitoring
	//UA_MonitoringMode monitoringMode = UA_MONITORINGMODE_REPORTING;
	UA_MonitoringMode monitoringMode = UA_MONITORINGMODE_REPORTING;
	UA_TimestampsToReturn timestampsToReturn = UA_TIMESTAMPSTORETURN_BOTH;
	UA_Double samplingInterval = 50;
	UA_Int32 queueSize = 0;
	// Configuration for subscription
	UA_Double requestedPublishingInterval = 100;
	UA_Byte priority = 1;

	/* Endless loop runAsync */
	while (running) {
		/* if already connected, this will return GOOD and do nothing */
		/* if the connection is closed/errored, the connection will be reset and then reconnected */
		/* Alternatively you can also use UA_Client_getState to get the current state */
		retval = UA_Client_connect(client, "opc.tcp://192.168.0.9:4840");
		if (retval != UA_STATUSCODE_GOOD) {
			UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Not connected. Retrying to connect in 1 second");
			/* The connect may timeout after 1 second (see above) or it may fail immediately on network errors */
			/* E.g. name resolution errors or unreachable network. Thus there should be a small sleep here */
			UA_sleep_ms(1000);
			continue;
		}
		else
		{
			if (opcuaSubscriptionId < 0)
			{
				UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
				request.requestedPublishingInterval = requestedPublishingInterval;
				request.priority = priority;

				UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(client, request,
					NULL, NULL, deleteSubscriptionCallback);

				if (response.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
				{
					opcuaSubscriptionId = response.subscriptionId;
					printf("Create subscription succeeded, id %u", response.subscriptionId);
				}
				else
				{
					printf("Create subscription failed, id %u", response.responseHeader.serviceResult);
					retval = response.responseHeader.serviceResult;
				}

				/* Add a MonitoredItem */
				UA_MonitoredItemCreateRequest monRequest =
					UA_MonitoredItemCreateRequest_default(UA_NODEID_NUMERIC(2, 6020));
				monRequest.monitoringMode = monitoringMode;
				monRequest.requestedParameters.queueSize = queueSize;
				monRequest.requestedParameters.samplingInterval = samplingInterval;


				UA_MonitoredItemCreateResult monResponse =
					UA_Client_MonitoredItems_createDataChange(client, response.subscriptionId, timestampsToReturn,
						monRequest, NULL, handler_currentTimeChanged, NULL);
				if (monResponse.statusCode == UA_STATUSCODE_GOOD)
					printf("Monitoring NUCLEOF767ZIDevice01.LD2', id %u", monResponse.monitoredItemId);
				else
				{
					retval |= monResponse.statusCode;
				}
				// indicate state
				if (retval == UA_STATUSCODE_GOOD)
				{					

					printf("\nrevisedSamplingInterval: %d\n", (int)monResponse.revisedSamplingInterval);
					printf("\nrevisedQueueSize: %d\n", monResponse.revisedQueueSize);
					printf("\revisedPublishingInterval: %d\n", (int)response.revisedPublishingInterval);
				}
			}

			UA_Client_run_iterate(client, 0);
		}
	};

	/* Clean up */
	UA_Client_delete(client); /* Disconnects the client internally */
	return 0 ;


	///* Create a client and connect */

	//UA_Client *client = UA_Client_new();
	//UA_ClientConfig_setDefault(UA_Client_getConfig(client));



	//UA_StatusCode status = UA_Client_connect(client, "opc.tcp://localhost:4840");
	//if (status != UA_STATUSCODE_GOOD) {
	//	UA_Client_delete(client);
	//	return status;
	//}

	///* Create a subscription */
	//UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
	//UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(client, request,
	//	NULL, NULL, deleteSubscriptionCallback);

	//if (response.responseHeader.serviceResult == UA_STATUSCODE_GOOD)
	//	printf("Create subscription succeeded, id %u", response.subscriptionId);
	//else
	//	return;

	///* Add a MonitoredItem */
	//UA_MonitoredItemCreateRequest monRequest =
	//	UA_MonitoredItemCreateRequest_default(UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME));

	//UA_MonitoredItemCreateResult monResponse =
	//	UA_Client_MonitoredItems_createDataChange(client, response.subscriptionId,
	//		UA_TIMESTAMPSTORETURN_BOTH,
	//		monRequest, NULL, handler_currentTimeChanged, NULL);
	//if (monResponse.statusCode == UA_STATUSCODE_GOOD)
	//	printf("Monitoring UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME', id %u", monResponse.monitoredItemId);


	///* Read the value attribute of the node. UA_Client_readValueAttribute is a
	// * wrapper for the raw read service available as UA_Client_Service_read. */
	//UA_Variant value; /* Variants can hold scalar values and arrays of any type */
	//UA_Variant_init(&value);
	//status = UA_Client_readValueAttribute(client, UA_NODEID_STRING(1, "the.answer"), &value);
	//if (status == UA_STATUSCODE_GOOD &&
	//	UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32])) {
	//	printf("the value is: %i\n", *(UA_Int32*)value.data);
	//}



	///* Clean up */
	//UA_Variant_deleteMembers(&value);
	//UA_Client_delete(client); /* Disconnects the client internally */
	//return status;
}
