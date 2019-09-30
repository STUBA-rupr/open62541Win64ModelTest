/*
open62541Win64ModelTest is a test project for running opc ua server with model
creted witn opc ua nodeset_compiler
*/



#ifdef UA_ENABLE_AMALGAMATION
#include "open62541.h"
#include "namespace_nucleof767ziWODI_generated.h"
#else
#include "open62541/plugin/log_stdout.h"
#include "open62541/server.h"
#include "open62541/server_config_default.h"
#include "namespace_di_generated.h"
#include "namespace_nucleof767zi_generated.h"
#pragma comment(lib, "open62541.lib")
#endif

#include <netioapi.h>

#include <signal.h>
#include <stdlib.h>

//#include "myNS.h"


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")


UA_ServerConfig *config;
UA_Server *server;

UA_Boolean running = true;
static void stopHandler(int sig) {
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
	running = false;
}

static UA_StatusCode ToggleLD3(const UA_NodeId objectId, const UA_Variant *input, UA_Variant *output) {


	return UA_STATUSCODE_GOOD;
}

static UA_StatusCode ToggleLD2(const UA_NodeId objectId, const UA_Variant *input, UA_Variant *output) {

	// read value 


	return UA_STATUSCODE_GOOD;
}

#define STM32  1

#if STM32 == 1
int main()
{
	int retval;
	UA_UInt16 ns[2];

	//Allows to set smaller buffer for the connections, which can cause problems
	UA_UInt32 sendBufferSize = 16000; //64 KB was too much for my platform
	UA_UInt32 recvBufferSize = 16000;  //64 KB was too much for my platform

	server = UA_Server_new();
	retval = UA_ServerConfig_setMinimalCustomBuffer(UA_Server_getConfig(server), 4840, 0, sendBufferSize, recvBufferSize);

	//LWIP_ASSERT("UA_ServerConfig_setMinimalCustomBuffer allocation failed", retval == UA_STATUSCODE_GOOD);

	//VERY IMPORTANT: Set the hostname with your IP before allocating the server
	UA_ServerConfig_setCustomHostname(UA_Server_getConfig(server), UA_STRING("192.168.0.9"));

	// modify publishing rates
	UA_ServerConfig *serverConfig;
	serverConfig = UA_Server_getConfig(server);

	serverConfig->publishingIntervalLimits.min = 0.0;
	serverConfig->publishingIntervalLimits.max = 3600.0 * 1000.0;

	serverConfig->samplingIntervalLimits.min = 0.0;	// zero means event/exception based based
	serverConfig->samplingIntervalLimits.max = 24.0 * 3600.0 * 1000.0;

	retval |= namespace_nucleof767ziWODI_generated(server);
	if (retval != UA_STATUSCODE_GOOD) {
		UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Adding the nucleof767zi namespace failed. Please check previous error output.");
		UA_Server_delete(server);
		return (int)UA_STATUSCODE_BADUNEXPECTEDERROR;
	}


	// Add method call backs
	ns[0] = UA_Server_addNamespace(server, "http://opcfoundation.org/UA/");
	ns[1] = UA_Server_addNamespace(server, "http://phi-ware.com/NucleoF767ZI/");

/*#if defined(UA_ENABLE_METHODCALLS) && defined(UA_ENABLE_SUBSCRIPTIONS)
	retval |= UA_Server_setMethodNode_callback(server,
		UA_NODEID_NUMERIC(ns[1], 7003), ToggleLD3);

	retval |= UA_Server_setMethodNode_callback(server,
		UA_NODEID_NUMERIC(ns[1], 7004), ToggleLD2);
#endif*/

	// let know UA sever is ready to run
	
	//retval = UA_Server_run(server, &running);

	// main loop
	retval = UA_Server_run_startup(server);
	if (retval != UA_STATUSCODE_GOOD)
		return retval;

	UA_DateTime now = UA_DateTime_nowMonotonic();
	UA_UInt16 time1 = 0;
	UA_UInt32 loopCount = 0;
	srand(now);
	int nloop = 0;

		
	while (running) {
		UA_UInt16 timeout;
		timeout = UA_Server_run_iterate(server, true);

		if ((UA_DateTime_nowMonotonic() >= (now + time1 * UA_DATETIME_MSEC)))
		{
			// time to do stuff
			now = UA_DateTime_nowMonotonic();
			time1 = rand() % 1000 + 200;
			//printf("loop: %.3d,%u\n", ++nloop, GetTickCount());
			// set node value
			ns[0] = UA_Server_addNamespace(server, "http://opcfoundation.org/UA/");
			ns[1] = UA_Server_addNamespace(server, "http://phi-ware.com/NucleoF767ZI/");
			
			UA_NodeId myIntegerNodeId = UA_NODEID_NUMERIC(ns[1], 6020);
			++loopCount;
			UA_Variant myVar;
			UA_Variant_init(&myVar);
			UA_Variant_setScalar(&myVar, &loopCount, &UA_TYPES[UA_TYPES_UINT32]);
			UA_Server_writeValue(server, myIntegerNodeId, myVar);
		}
		
		
	}
	return UA_Server_run_shutdown(server);	   	  	

	UA_Server_delete(server);
}
#else

int main(void) {
	signal(SIGINT, stopHandler);
	signal(SIGTERM, stopHandler);


	UA_Server *server = UA_Server_new();
	UA_ServerConfig_setDefault(UA_Server_getConfig(server));
	
	/* create nodes from nodeset */
#ifdef UA_ENABLE_AMALGAMATION
	UA_StatusCode retval = namespace_nucleof767ziWODI_generated(server);
	if (retval != UA_STATUSCODE_GOOD) {
		UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Adding the DI namespace failed. Please check previous error output.");
		UA_Server_delete(server);
		return (int)UA_STATUSCODE_BADUNEXPECTEDERROR;
	}
#else
	
	UA_StatusCode retval = namespace_di_generated(server);
	if (retval != UA_STATUSCODE_GOOD) {
		UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Adding the DI namespace failed. Please check previous error output.");
		UA_Server_delete(server);
		UA_ServerConfig_delete(config);
		return (int)UA_STATUSCODE_BADUNEXPECTEDERROR;
	}
	retval |= namespace_nucleof767zi_generated(server);
	if (retval != UA_STATUSCODE_GOOD) {
		UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Adding the nucleof767zi namespace failed. Please check previous error output.");
		UA_Server_delete(server);
		UA_ServerConfig_delete(config);
		return (int)UA_STATUSCODE_BADUNEXPECTEDERROR;
	}
#endif
	
	// Add method call backs
#if defined(UA_ENABLE_METHODCALLS) && defined(UA_ENABLE_SUBSCRIPTIONS)
	UA_UInt16 ns[3];
	ns[0] = UA_Server_addNamespace(server, "http://opcfoundation.org/UA/");
	ns[1] = UA_Server_addNamespace(server, "http://opcfoundation.org/UA/DI/");
	ns[2] = UA_Server_addNamespace(server, "http://yourorganisation.org/Opc.NucleoF767ZI.NodeSet/");

	retval |= UA_Server_setMethodNode_callback(server,
		UA_NODEID_NUMERIC(ns[2], 7003), ToggleLD3);

	retval |= UA_Server_setMethodNode_callback(server,
		UA_NODEID_NUMERIC(ns[2], 7004), ToggleLD2);
#endif


	retval = UA_Server_run(server, &running);

	UA_Server_delete(server);
}

#endif
