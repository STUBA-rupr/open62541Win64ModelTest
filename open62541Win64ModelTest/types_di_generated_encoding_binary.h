/* Generated from Opc.Ua.Di.Types.bsd with script C:/Projects/open62541/tools/generate_datatypes.py
 * on host VM-Win16-Dev by user a2user at 2019-03-26 01:23:58 */

#ifdef UA_ENABLE_AMALGAMATION
# include "open62541.h"
#else
# include "ua_types_encoding_binary.h"
# include "types_di_generated.h"
#endif



/* DeviceHealthEnumeration */
static UA_INLINE size_t
UA_DeviceHealthEnumeration_calcSizeBinary(const UA_DeviceHealthEnumeration *src) {
    return UA_calcSizeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_DEVICEHEALTHENUMERATION]);
}
static UA_INLINE UA_StatusCode
UA_DeviceHealthEnumeration_encodeBinary(const UA_DeviceHealthEnumeration *src, UA_Byte **bufPos, const UA_Byte *bufEnd) {
    return UA_encodeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_DEVICEHEALTHENUMERATION], bufPos, &bufEnd, NULL, NULL);
}
static UA_INLINE UA_StatusCode
UA_DeviceHealthEnumeration_decodeBinary(const UA_ByteString *src, size_t *offset, UA_DeviceHealthEnumeration *dst) {
    return UA_decodeBinary(src, offset, dst, &UA_TYPES_DI[UA_TYPES_DI_DEVICEHEALTHENUMERATION], NULL);
}

/* FetchResultDataType */
static UA_INLINE size_t
UA_FetchResultDataType_calcSizeBinary(const UA_FetchResultDataType *src) {
    return UA_calcSizeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATATYPE]);
}
static UA_INLINE UA_StatusCode
UA_FetchResultDataType_encodeBinary(const UA_FetchResultDataType *src, UA_Byte **bufPos, const UA_Byte *bufEnd) {
    return UA_encodeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATATYPE], bufPos, &bufEnd, NULL, NULL);
}
static UA_INLINE UA_StatusCode
UA_FetchResultDataType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_FetchResultDataType *dst) {
    return UA_decodeBinary(src, offset, dst, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATATYPE], NULL);
}

/* FetchResultErrorDataType */
static UA_INLINE size_t
UA_FetchResultErrorDataType_calcSizeBinary(const UA_FetchResultErrorDataType *src) {
    return UA_calcSizeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE]);
}
static UA_INLINE UA_StatusCode
UA_FetchResultErrorDataType_encodeBinary(const UA_FetchResultErrorDataType *src, UA_Byte **bufPos, const UA_Byte *bufEnd) {
    return UA_encodeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE], bufPos, &bufEnd, NULL, NULL);
}
static UA_INLINE UA_StatusCode
UA_FetchResultErrorDataType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_FetchResultErrorDataType *dst) {
    return UA_decodeBinary(src, offset, dst, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE], NULL);
}

/* ParameterResultDataType */
static UA_INLINE size_t
UA_ParameterResultDataType_calcSizeBinary(const UA_ParameterResultDataType *src) {
    return UA_calcSizeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE]);
}
static UA_INLINE UA_StatusCode
UA_ParameterResultDataType_encodeBinary(const UA_ParameterResultDataType *src, UA_Byte **bufPos, const UA_Byte *bufEnd) {
    return UA_encodeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE], bufPos, &bufEnd, NULL, NULL);
}
static UA_INLINE UA_StatusCode
UA_ParameterResultDataType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_ParameterResultDataType *dst) {
    return UA_decodeBinary(src, offset, dst, &UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE], NULL);
}

/* FetchResultDataDataType */
static UA_INLINE size_t
UA_FetchResultDataDataType_calcSizeBinary(const UA_FetchResultDataDataType *src) {
    return UA_calcSizeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE]);
}
static UA_INLINE UA_StatusCode
UA_FetchResultDataDataType_encodeBinary(const UA_FetchResultDataDataType *src, UA_Byte **bufPos, const UA_Byte *bufEnd) {
    return UA_encodeBinary(src, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE], bufPos, &bufEnd, NULL, NULL);
}
static UA_INLINE UA_StatusCode
UA_FetchResultDataDataType_decodeBinary(const UA_ByteString *src, size_t *offset, UA_FetchResultDataDataType *dst) {
    return UA_decodeBinary(src, offset, dst, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE], NULL);
}
