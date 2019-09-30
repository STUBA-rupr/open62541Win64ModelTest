/* Generated from Opc.Ua.Di.Types.bsd with script C:/Projects/open62541/tools/generate_datatypes.py
 * on host VM-Win16-Dev by user a2user at 2019-03-26 01:23:58 */

#ifndef TYPES_DI_GENERATED_HANDLING_H_
#define TYPES_DI_GENERATED_HANDLING_H_

#include "types_di_generated.h"

_UA_BEGIN_DECLS

#if defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 6
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"
# pragma GCC diagnostic ignored "-Wmissing-braces"
#endif


/* DeviceHealthEnumeration */
static UA_INLINE void
UA_DeviceHealthEnumeration_init(UA_DeviceHealthEnumeration *p) {
    memset(p, 0, sizeof(UA_DeviceHealthEnumeration));
}

static UA_INLINE UA_DeviceHealthEnumeration *
UA_DeviceHealthEnumeration_new(void) {
    return (UA_DeviceHealthEnumeration*)UA_new(&UA_TYPES_DI[UA_TYPES_DI_DEVICEHEALTHENUMERATION]);
}

static UA_INLINE UA_StatusCode
UA_DeviceHealthEnumeration_copy(const UA_DeviceHealthEnumeration *src, UA_DeviceHealthEnumeration *dst) {
    *dst = *src;
    return UA_STATUSCODE_GOOD;
}

static UA_INLINE void
UA_DeviceHealthEnumeration_deleteMembers(UA_DeviceHealthEnumeration *p) {
    memset(p, 0, sizeof(UA_DeviceHealthEnumeration));
}

static UA_INLINE void
UA_DeviceHealthEnumeration_clear(UA_DeviceHealthEnumeration *p) {
    memset(p, 0, sizeof(UA_DeviceHealthEnumeration));
}

static UA_INLINE void
UA_DeviceHealthEnumeration_delete(UA_DeviceHealthEnumeration *p) {
    UA_delete(p, &UA_TYPES_DI[UA_TYPES_DI_DEVICEHEALTHENUMERATION]);
}

/* FetchResultDataType */
static UA_INLINE void
UA_FetchResultDataType_init(UA_FetchResultDataType *p) {
    memset(p, 0, sizeof(UA_FetchResultDataType));
}

static UA_INLINE UA_FetchResultDataType *
UA_FetchResultDataType_new(void) {
    return (UA_FetchResultDataType*)UA_new(&UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATATYPE]);
}

static UA_INLINE UA_StatusCode
UA_FetchResultDataType_copy(const UA_FetchResultDataType *src, UA_FetchResultDataType *dst) {
    *dst = *src;
    return UA_STATUSCODE_GOOD;
}

static UA_INLINE void
UA_FetchResultDataType_deleteMembers(UA_FetchResultDataType *p) {
    memset(p, 0, sizeof(UA_FetchResultDataType));
}

static UA_INLINE void
UA_FetchResultDataType_clear(UA_FetchResultDataType *p) {
    memset(p, 0, sizeof(UA_FetchResultDataType));
}

static UA_INLINE void
UA_FetchResultDataType_delete(UA_FetchResultDataType *p) {
    UA_delete(p, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATATYPE]);
}

/* FetchResultErrorDataType */
static UA_INLINE void
UA_FetchResultErrorDataType_init(UA_FetchResultErrorDataType *p) {
    memset(p, 0, sizeof(UA_FetchResultErrorDataType));
}

static UA_INLINE UA_FetchResultErrorDataType *
UA_FetchResultErrorDataType_new(void) {
    return (UA_FetchResultErrorDataType*)UA_new(&UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE]);
}

static UA_INLINE UA_StatusCode
UA_FetchResultErrorDataType_copy(const UA_FetchResultErrorDataType *src, UA_FetchResultErrorDataType *dst) {
    return UA_copy(src, dst, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE]);
}

static UA_INLINE void
UA_FetchResultErrorDataType_deleteMembers(UA_FetchResultErrorDataType *p) {
    UA_clear(p, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE]);
}

static UA_INLINE void
UA_FetchResultErrorDataType_clear(UA_FetchResultErrorDataType *p) {
    UA_clear(p, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE]);
}

static UA_INLINE void
UA_FetchResultErrorDataType_delete(UA_FetchResultErrorDataType *p) {
    UA_delete(p, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTERRORDATATYPE]);
}

/* ParameterResultDataType */
static UA_INLINE void
UA_ParameterResultDataType_init(UA_ParameterResultDataType *p) {
    memset(p, 0, sizeof(UA_ParameterResultDataType));
}

static UA_INLINE UA_ParameterResultDataType *
UA_ParameterResultDataType_new(void) {
    return (UA_ParameterResultDataType*)UA_new(&UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE]);
}

static UA_INLINE UA_StatusCode
UA_ParameterResultDataType_copy(const UA_ParameterResultDataType *src, UA_ParameterResultDataType *dst) {
    return UA_copy(src, dst, &UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE]);
}

static UA_INLINE void
UA_ParameterResultDataType_deleteMembers(UA_ParameterResultDataType *p) {
    UA_clear(p, &UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE]);
}

static UA_INLINE void
UA_ParameterResultDataType_clear(UA_ParameterResultDataType *p) {
    UA_clear(p, &UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE]);
}

static UA_INLINE void
UA_ParameterResultDataType_delete(UA_ParameterResultDataType *p) {
    UA_delete(p, &UA_TYPES_DI[UA_TYPES_DI_PARAMETERRESULTDATATYPE]);
}

/* FetchResultDataDataType */
static UA_INLINE void
UA_FetchResultDataDataType_init(UA_FetchResultDataDataType *p) {
    memset(p, 0, sizeof(UA_FetchResultDataDataType));
}

static UA_INLINE UA_FetchResultDataDataType *
UA_FetchResultDataDataType_new(void) {
    return (UA_FetchResultDataDataType*)UA_new(&UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE]);
}

static UA_INLINE UA_StatusCode
UA_FetchResultDataDataType_copy(const UA_FetchResultDataDataType *src, UA_FetchResultDataDataType *dst) {
    return UA_copy(src, dst, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE]);
}

static UA_INLINE void
UA_FetchResultDataDataType_deleteMembers(UA_FetchResultDataDataType *p) {
    UA_clear(p, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE]);
}

static UA_INLINE void
UA_FetchResultDataDataType_clear(UA_FetchResultDataDataType *p) {
    UA_clear(p, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE]);
}

static UA_INLINE void
UA_FetchResultDataDataType_delete(UA_FetchResultDataDataType *p) {
    UA_delete(p, &UA_TYPES_DI[UA_TYPES_DI_FETCHRESULTDATADATATYPE]);
}

#if defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 6
# pragma GCC diagnostic pop
#endif

_UA_END_DECLS

#endif /* TYPES_DI_GENERATED_HANDLING_H_ */
