//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXDLMSCLIENT_H
#define GXDLMSCLIENT_H

#include "GXDLMS.h"
#include "GXStandardObisCodeCollection.h"
#include "GXDLMSProfileGeneric.h"
#include "GXSecure.h"
#include "GXDateTime.h"
#include "stdbool.h"
#include "Vector.h"
#include "String.h"

typedef struct CGXDLMSClient
{
    CGXDLMSSettings m_Settings;
    bool m_IsAuthenticationRequired;
} CGXDLMSClient;

//public
/////////////////////////////////////////////////////////////////////////////
//Constructor
/////////////////////////////////////////////////////////////////////////////
// Default parameter: bool UseLogicalNameReferencing = true,
//                    int ClientAddress = 16,
//                    int ServerAddress = 1,
//                    DLMS_AUTHENTICATION authentication = DLMS_AUTHENTICATION_NONE,
//                    const char* password = NULL,
//                    DLMS_INTERFACE_TYPE intefaceType = DLMS_INTERFACE_TYPE_HDLC
extern void CGXDLMSClient_(
    CGXDLMSClient *p,
    bool UseLogicalNameReferencing,
    int ClientAddress,
    int ServerAddress,
    //Authentication type.
    DLMS_AUTHENTICATION authentication,
    //Password if authentication is used.
    const char* password,
    DLMS_INTERFACE_TYPE intefaceType);

/////////////////////////////////////////////////////////////////////////////
//Destructor.
/////////////////////////////////////////////////////////////////////////////
extern void CGXDLMSClient_d(CGXDLMSClient *p);

extern bool CGXDLMSClient_GetUseLogicalNameReferencing(CGXDLMSClient *p);

extern DLMS_INTERFACE_TYPE CGXDLMSClient_GetInterfaceType(CGXDLMSClient *p);

/**
 * @return Used Priority.
 */
extern DLMS_PRIORITY CGXDLMSClient_GetPriority(CGXDLMSClient *p);

/**
 * @param value
 *            Used Priority.
 */
extern void CGXDLMSClient_SetPriority(CGXDLMSClient *p, DLMS_PRIORITY value);

/**
 * @return Used service class.
 */
extern DLMS_SERVICE_CLASS CGXDLMSClient_GetServiceClass(CGXDLMSClient *p);

/**
 * @param value
 *            Used service class.
 */
extern void CGXDLMSClient_SetServiceClass(CGXDLMSClient *p, DLMS_SERVICE_CLASS value);

extern CGXDLMSLimits* CGXDLMSClient_GetLimits(CGXDLMSClient *p);

// Collection of the objects.
extern CGXDLMSObjectCollection* CGXDLMSClient_GetObjects(CGXDLMSClient *p);

/////////////////////////////////////////////////////////////////////////////
// Returns SNRMRequest query as byte array.
/////////////////////////////////////////////////////////////////////////////
// packets: Packets to send.
// Returns: 0 if succeed. Otherwise error number.
/////////////////////////////////////////////////////////////////////////////
extern int CGXDLMSClient_SNRMRequest(
    CGXDLMSClient *p,
    Vector* packets);//std::vector<CGXByteBuffer>&

/////////////////////////////////////////////////////////////////////////////
// Parses UAResponse.
/////////////////////////////////////////////////////////////////////////////
// data: Byte array containing the data from the meter.
// Returns: 0 if succeed. Otherwise error number.
extern int CGXDLMSClient_ParseUAResponse(
    CGXDLMSClient *p,
    CGXByteBuffer* data);

/////////////////////////////////////////////////////////////////////////////
// Returns AARQRequest query as byte array.
/////////////////////////////////////////////////////////////////////////////
// Packets: Packets to send.
// Returns: 0 if succeed. Otherwise error number.
/////////////////////////////////////////////////////////////////////////////
extern int CGXDLMSClient_AARQRequest(
    CGXDLMSClient *p,
    Vector* packets);//std::vector<CGXByteBuffer>&

/**
* Parses the AARE response. Parse method will update the following data:
* <ul>
* <li>DLMSVersion</li>
* <li>MaxReceivePDUSize</li>
* <li>UseLogicalNameReferencing</li>
* <li>LNSettings or SNSettings</li>
* </ul>
* LNSettings or SNSettings will be updated, depending on the referencing,
* Logical name or Short name.
*
* reply
*            Received data.
* @see GXDLMSClient#aarqRequest
* @see GXDLMSClient#GetUseLogicalNameReferencing
* @see GXDLMSClient#GetLNSettings
* @see GXDLMSClient#GetSNSettings
*/
extern int CGXDLMSClient_ParseAAREResponse(
    CGXDLMSClient *p,
    CGXByteBuffer* data);

/**
* @return Is authentication Required.
*/
extern bool CGXDLMSClient_IsAuthenticationRequired(CGXDLMSClient *p);

/**
 * @return Get challenge request if HLS authentication is used.
 */
extern int CGXDLMSClient_GetApplicationAssociationRequest(
    CGXDLMSClient *p,
    Vector* packets);//std::vector<CGXByteBuffer>&

/**
 * Parse server's challenge if HLS authentication is used.
 *
 * @param reply
 *            Received reply from the server.
 */
extern int CGXDLMSClient_ParseApplicationAssociationResponse(
    CGXDLMSClient *p,
    CGXByteBuffer* reply);

/////////////////////////////////////////////////////////////////////////////
// Returns ReceiverReady query as byte array.
/////////////////////////////////////////////////////////////////////////////
// Type: type of the next requested packet.
// Data: Data to send.
// Returns: 0 if succeed. Otherwise error number.
/////////////////////////////////////////////////////////////////////////////
extern int CGXDLMSClient_ReceiverReady(
    CGXDLMSClient *p,
    DLMS_DATA_REQUEST_TYPES Type,
    CGXByteBuffer* Data);

/////////////////////////////////////////////////////////////////////////////
// Changes byte array received from the meter to given type.
/////////////////////////////////////////////////////////////////////////////
// value Byte array received from the meter.
// type Wanted type.
// returns Value changed by type.
extern int CGXDLMSClient_ChangeType_1(
    CGXByteBuffer* value,
    DLMS_DATA_TYPE type,
    CGXDLMSVariant* newValue);

/////////////////////////////////////////////////////////////////////////////
// Changes byte array received from the meter to given type.
/////////////////////////////////////////////////////////////////////////////
// value Byte array received from the meter.
// type Wanted type.
// returns Value changed by type.
extern int CGXDLMSClient_ChangeType_2(
    CGXDLMSVariant* value,
    DLMS_DATA_TYPE type,
    CGXDLMSVariant* newValue);

/**
* Parses the COSEM objects of the received data.
*
* data : Received data, from the device, as byte array.
* objects : Collection of COSEM objects.
* onlyKnownObjects : Only known objects are parsed.
*/
extern int CGXDLMSClient_ParseObjects(
    CGXDLMSClient *p,
    CGXByteBuffer* data,
    bool onlyKnownObjects);

/*
* Get Value from byte array received from the meter.
*/
extern int CGXDLMSClient_UpdateValue(
    CGXDLMSClient *p,
    CGXDLMSObject* target,
    int attributeIndex,
    CGXDLMSVariant* value);

/**
    * Get Value from byte array received from the meter.
    *
    * data
    *            Byte array received from the meter.
    * @return Received data.
    */
extern int CGXDLMSClient_GetValue(
    CGXDLMSClient *p,
    CGXByteBuffer* data,
    CGXDLMSVariant* value);

/**
* Update list of values.
*
* list : List of read objects and atributes.
* values :  Received values.
*/
extern int CGXDLMSClient_UpdateValues(
    CGXDLMSClient *p,
    Vector* list, //std::vector< std::pair<CGXDLMSObject*, unsigned char> >&
    Vector* values);//std::vector<CGXDLMSVariant>&

/**
* Generates a release request.
*
* reply : Generated release message(s).
* Returns error status.
*/
extern int CGXDLMSClient_ReleaseRequest(
    CGXDLMSClient *p,
    Vector* packets);//    std::vector<CGXByteBuffer>&

/**
* Generates a disconnect request.
*
* reply : Generated disconnect message(s).
* Returns error status.
*/
extern int CGXDLMSClient_DisconnectRequest(
    CGXDLMSClient *p,
    Vector* packets);//std::vector<CGXByteBuffer>&

extern int CGXDLMSClient_GetData(
    CGXDLMSClient *p,
    CGXByteBuffer* reply,
    CGXReplyData* data);

extern String CGXDLMSClient_ObjectTypeToString(
    DLMS_OBJECT_TYPE type);

/**
* Reads the Association view from the device. This method is used to get
* all objects in the device.
*
* reply : Generated read message(s).
* Returns error status.
*/
extern int CGXDLMSClient_GetObjectsRequest(
    CGXDLMSClient *p,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Generates a read message.
*
* name : Short or Logical Name.
* objectType : COSEM object type.
* attributeOrdinal : Attribute index of the object.
* reply : Generated read message(s).
* Returns error status.
*/
extern int CGXDLMSClient_Read_1(
    CGXDLMSClient *p,
    CGXDLMSVariant* name,
    DLMS_OBJECT_TYPE objectType,
    int attributeOrdinal,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Generates a read message.
*
* @param pObject
*            COSEM object to write.
* @param attributeOrdinal
*            Attribute index of the object.
* @param reply
*            Generated read message(s).
* Returns error status.
*/
extern int CGXDLMSClient_Read_2(
    CGXDLMSClient *p,
    CGXDLMSObject* pObject,
    int attributeOrdinal,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Read list of COSEM objects.
*
* @param list
*            DLMS objects to read.
* @return Read request as byte array.
*/
extern int CGXDLMSClient_ReadList(
    CGXDLMSClient *p,
    Vector* list,//std::vector<std::pair<CGXDLMSObject*, unsigned char> >&
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Generates a write message.
*
* @param name
*            Short or Logical Name.
* @param objectType
*            Object type.
* @param index
*            Attribute index where data is write.
* @param value
*            Data to Write.
* @param reply
*             Generated write message(s).
* Returns error status.
*/
extern int CGXDLMSClient_Write_1(
    CGXDLMSClient *p,
    CGXDLMSVariant* name,
    DLMS_OBJECT_TYPE objectType,
    int index,
    CGXDLMSVariant* data,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
 * Generates a write message.
 *
 * @param pObject
 *            COSEM object to write.
 * @param index
 *            Attribute index where data is write.
 * @param data
 *            Data to Write.
 * @param reply
 *            Generated write message(s).
 * Returns error status.
 */
extern int CGXDLMSClient_Write_2(
    CGXDLMSClient *p,
    CGXDLMSObject* pObject,
    int index,
    CGXDLMSVariant* data,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Generates a write message.
*
* @param pObject
*            COSEM object to write.
* @param index
*            Attribute index where data is write.
* @param reply
*            Generated write message(s).
* Returns error status.
*/
extern int CGXDLMSClient_Write_3(
    CGXDLMSClient *p,
    CGXDLMSObject* pObject,
    int index,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Generate Method (Action) request.
*
* @param item
*            Method object short name or Logical Name.
* @param index
*            Method index.
* @param data
*            Method data.
* @param type
*            Data type.
* @return DLMS action message.
*/
extern int CGXDLMSClient_Method_1(
    CGXDLMSClient *p,
    CGXDLMSObject* item,
    int index,
    CGXDLMSVariant* data,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Generate Method (Action) request..
*
* @param name
*            Method object short name or Logical Name.
* @param objectType
*            Object type.
* @param methodIndex
*            Method index.
* @param value
*            Method data.
* @param dataType
*            Data type.
* @return DLMS action message.
*/
extern int CGXDLMSClient_Method_2(
    CGXDLMSClient *p,
    CGXDLMSVariant name,
    DLMS_OBJECT_TYPE objectType,
    int methodIndex,
    CGXDLMSVariant* data,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Read rows by entry.
*
* @param pg
*            Profile generic object to read.
* @param index
*            Zero bases start index.
* @param count
*            Rows count to read.
* @return Read message as byte array.
*/
extern int CGXDLMSClient_ReadRowsByEntry_1(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    int index,
    int count,
    Vector* reply);//std::vector<CGXByteBuffer>&


/**
* Read rows by entry.
*
* @param pg
*            Profile generic object to read.
* @param index
*            Zero bases start index.
* @param count
*            Rows count to read.
* @return Read message as byte array.
*/
extern int CGXDLMSClient_ReadRowsByEntry_2(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    int index,
    int count,
    Vector* columns,//std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
    Vector* reply);//std::vector<CGXByteBuffer>&


/**
* Read rows by range. Use this method to read Profile Generic table between
* dates.
*
* @param pg
*            Profile generic object to read.
* @param start
*            Start time.
* @param end
*            End time.
* @return Generated read message.
*/
extern int CGXDLMSClient_ReadRowsByRange_1(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pObject,
    CGXDateTime* start,
    CGXDateTime* end,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
 * Read rows by range. Use this method to read Profile Generic table between
 * dates.
 *
 * @param pg
 *            Profile generic object to read.
 * @param start
 *            Start time.
 * @param end
 *            End time.
 * @return Generated read message.
 */
extern int CGXDLMSClient_ReadRowsByRange_2(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    struct tm* start,
    struct tm* end,
    Vector* reply);//std::vector<CGXByteBuffer>&

/**
* Read rows by range. Use this method to read Profile Generic table between
* dates.
*
* @param pg
*            Profile generic object to read.
* @param start
*            Start time.
* @param end
*            End time.
* @return Generated read message.
*/
extern int CGXDLMSClient_ReadRowsByRange_3(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    struct tm* start,
    struct tm* end,
    Vector* columns,//std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
    Vector* reply);//std::vector<CGXByteBuffer>&


/**
*  Client will know what functionality server offers.
*
* @return Functionality.
*/
extern DLMS_CONFORMANCE CGXDLMSClient_GetNegotiatedConformance(CGXDLMSClient *p);

/**
* Negotiated functionality for the server. Client can set this if meter report error value.
*
* @param value
*            Proposed functionality.
*/
extern void CGXDLMSClient_SetNegotiatedConformance(CGXDLMSClient *p, DLMS_CONFORMANCE value);

/**
* Proposed functionality for the server.
* @return Proposed functionality.
*/
extern DLMS_CONFORMANCE CGXDLMSClient_GetProposedConformance(CGXDLMSClient *p);

/**
* Proposed functionality for the server.
*
* @param value
*            Proposed functionality.
*/
extern void CGXDLMSClient_SetProposedConformance(CGXDLMSClient *p, DLMS_CONFORMANCE value);

/**
 * Converts meter serial number to server address. Default formula is used.
 * All meters do not use standard formula or support serial number
 * addressing at all.
 *
 * @param serialNumber
 *            Meter serial number
 * @param formula
 *            Formula used to convert serial number to server address.
 *            Set to NULL if standard formula is used.
 * @return Server address.
 */
// Default parameter: const char* formula = NULL
extern int CGXDLMSClient_GetServerAddress_1(
    unsigned long serialNumber,
    const char* formula);

/**
 * Convert physical address and logical address to server address.
 *
 * @param logicalAddress
 *            Server logical address.
 * @param physicalAddress
 *            Server physical address.
 * @param addressSize
 *            Address size in bytes.
 * @return Server address.
 */
// Default parameter: unsigned char addressSize = 0
extern int CGXDLMSClient_GetServerAddress_2(unsigned long logicalAddress,
    unsigned long physicalAddress,
    unsigned char addressSize);

#endif //GXDLMSCLIENT_H
