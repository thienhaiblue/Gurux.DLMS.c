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
// and/or modify it under the terms of the GNU General License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXDLMSSERVER_H
#define GXDLMSSERVER_H

#include "GXDLMSLongTransaction.h"
#include "GXReplyData.h"
#include "GXDLMSSettings.h"
#include "GXSNInfo.h"
#include "GXDLMSSNParameters.h"
#include "GXDLMSLNParameters.h"
#include "GXDLMSConnectionEventArgs.h"
#include "GXDLMSHdlcSetup.h"
#include "GXDLMSTcpUdpSetup.h"
#include "GXDLMSAssociationLogicalName.h"
#include "GXDLMSAssociationShortName.h"
#include "GXDLMSPushSetup.h"

#include <stdbool.h>

typedef struct CGXDLMSProfileGeneric CGXDLMSProfileGeneric;

typedef bool (*IsTarget_FuncPtr)(void* p, unsigned long int serverAddress, unsigned long clientAddress);
typedef DLMS_SOURCE_DIAGNOSTIC (*ValidateAuthentication_FuncPtr)(void* p, DLMS_AUTHENTICATION authentication, CGXByteBuffer* password);

typedef CGXDLMSObject* (*FindObject_FuncPtr)(void* p, DLMS_OBJECT_TYPE objectType, int sn, String* ln);

typedef void (*PreRead_FuncPtr)(void* p, Vector* args);

typedef void (*PreWrite_FuncPtr)(void* p, Vector* args);

typedef void (*Connected_FuncPtr)(void* p, CGXDLMSConnectionEventArgs* connectionInfo);

typedef void (*InvalidConnection_FuncPtr)(void* p, CGXDLMSConnectionEventArgs* connectionInfo);

typedef void (*Disconnected_FuncPtr)(void* p, CGXDLMSConnectionEventArgs* connectionInfo);

typedef DLMS_ACCESS_MODE (*GetAttributeAccess_FuncPtr)(void* p, CGXDLMSValueEventArg* arg);

typedef DLMS_METHOD_ACCESS_MODE (*GetMethodAccess_FuncPtr)(void* p, CGXDLMSValueEventArg* arg);

typedef void (*PreAction_FuncPtr)(void* p, Vector* args); //std::vector<CGXDLMSValueEventArg*>&

typedef void (*PostRead_FuncPtr)(void* p, Vector* args); //std::vector<CGXDLMSValueEventArg*>&

typedef void (*PostWrite_FuncPtr)(void* p, Vector* args); //std::vector<CGXDLMSValueEventArg*>&

typedef void (*PostAction_FuncPtr)(void* p, Vector* args); //std::vector<CGXDLMSValueEventArg*>&

typedef void (*PreGet_FuncPtr)(void* p, Vector* args); //std::vector<CGXDLMSValueEventArg*>&

typedef void (*PostGet_FuncPtr)(void* p, Vector* args); //std::vector<CGXDLMSValueEventArg*>&

typedef struct CGXDLMSServer
{
    ///////////////////////////////////////////////////////////////////////////
//private:
    long m_DataReceived;
    CGXDLMSIecHdlcSetup* m_Hdlc;
    CGXDLMSTcpUdpSetup* m_Wrapper;
    CGXReplyData m_Info;
    /**
     * Received data.
     */
    CGXByteBuffer m_ReceivedData;

    /**
     * Reply data.
     */
    CGXByteBuffer m_ReplyData;

    /**
     * Long get or read transaction information.
     */
    CGXDLMSLongTransaction* m_Transaction;

    /**
     * Is server initialized.
     */
    bool m_Initialized;

//protected:
    /**
     * Server Settings.
     */
    CGXDLMSSettings m_Settings;

    /**
        * Check is data sent to this server.
        *
        * @param serverAddress
        *            Server address.
        * @param clientAddress
        *            Client address.
        * @return True, if data is sent to this server.
        */
    IsTarget_FuncPtr IsTarget;

    /**
     * Check whether the authentication and password are correct.
     *
     * @param authentication
     *            Authentication level.
     * @param password
     *            Password.
     * @return Source diagnostic.
     */
    ValidateAuthentication_FuncPtr ValidateAuthentication;

    /**
     * Find object.
     *
     * @param objectType
     *            Object type.
     * @param sn
     *            Short Name. In Logical name referencing this is not used.
     * @param ln
     *            Logical Name. In Short Name referencing this is not used.
     * @return Found object or NULL if object is not found.
     */
    FindObject_FuncPtr FindObject;

    /**
     * Read selected item(s).
     *
     * @param args
     *            Handled read requests.
     */
    PreRead_FuncPtr PreRead;

    /**
     * Write selected item(s).
     *
     * @param args
     *            Handled write requests.
     */
    PreWrite_FuncPtr PreWrite;

    /**
     * Accepted connection is made for the server. All initialization is done
     * here.
     */
    Connected_FuncPtr Connected;

    /**
     * Client has try to made invalid connection. Password is incorrect.
     *
     * @param connectionInfo
     *            Connection information.
     */
    InvalidConnection_FuncPtr InvalidConnection;

    /**
     * Server has close the connection. All clean up is made here.
     */
    Disconnected_FuncPtr Disconnected;

    /**
    * Get attribute access mode.
    *
    * @param arg
    *            Value event argument.
    * @return Access mode.
    * @throws Exception
    *             Server handler occurred exceptions.
    */
    GetAttributeAccess_FuncPtr GetAttributeAccess;

    /**
    * Get method access mode.
    *
    * @param arg
    *            Value event argument.
    * @return Method access mode.
    * @throws Exception
    *             Server handler occurred exceptions.
    */
    GetMethodAccess_FuncPtr GetMethodAccess;

    /**
     * Action is occurred.
     *
     * @param args
     *            Handled action requests.
     */
    PreAction_FuncPtr PreAction;

    /**
    * Read selected item(s).
    *
    * @param args
    *            Handled read requests.
    */
    PostRead_FuncPtr PostRead;
    /**
    * Write selected item(s).
    *
    * @param args
    *            Handled write requests.
    */
    PostWrite_FuncPtr PostWrite;

    /**
    * Action is occurred.
    *
    * @param args
    *            Handled action requests.
    */
    PostAction_FuncPtr PostAction;

    /**
    * Get selected value(s). This is called when example profile generic
    * request current value.
    *
    * @param args
    *            Value event arguments.
    */
    PreGet_FuncPtr PreGet;

    /**
    * Get selected value(s). This is called when example profile generic
    * request current value.
    *
    * @param args
    *            Value event arguments.
    */
    PostGet_FuncPtr PostGet;
    ///////////////////////////////////////////////////////////////////////////

} CGXDLMSServer;

/**
* Parse SNRM Request. If server do not accept client empty byte array is
* returned.
*
* @return Returns returned UA packet.
*/
extern int CGXDLMSServer_HandleSnrmRequest(CGXDLMSServer* p, CGXDLMSSettings* settings, CGXByteBuffer* data, CGXByteBuffer* reply);

/**
* Handle get request normal command.
*
* @param data
*            Received data.
*/
extern int CGXDLMSServer_GetRequestNormal(CGXDLMSServer* p, CGXByteBuffer* data, unsigned char invokeID);

/**
* Handle get request next data block command.
*
* @param data
*            Received data.
*/
extern int CGXDLMSServer_GetRequestNextDataBlock(CGXDLMSServer* p, CGXByteBuffer* data, unsigned char invokeID);

/**
 * Handle get request with list command.
 *
 * @param data
 *            Received data.
 */
extern int CGXDLMSServer_GetRequestWithList(CGXDLMSServer* p, CGXByteBuffer* data, unsigned char invokeID);

extern int CGXDLMSServer_HandleSetRequest_1(
    CGXDLMSServer* ptr,
    CGXByteBuffer* data,
    short type,
    CGXDLMSLNParameters* p);

extern int CGXDLMSServer_HanleSetRequestWithDataBlock(
    CGXDLMSServer* ptr,
    CGXByteBuffer* data,
    CGXDLMSLNParameters* p);

/**
* Handle read Block in blocks.
*
* @param data
*            Received data.
*/
extern int CGXDLMSServer_HandleReadBlockNumberAccess(
    CGXDLMSServer* p,
    CGXByteBuffer* data);

extern int CGXDLMSServer_HandleReadDataBlockAccess(
    CGXDLMSServer* p,
    DLMS_COMMAND command,
    CGXByteBuffer* data,
    int cnt);

extern int CGXDLMSServer_ReturnSNError(
    CGXDLMSServer* p,
    DLMS_COMMAND cmd,
    DLMS_ERROR_CODE error);

extern int CGXDLMSServer_HandleRead(
    CGXDLMSServer* p,
    DLMS_VARIABLE_ACCESS_SPECIFICATION type,
    CGXByteBuffer* data,
    CGXDLMSValueEventCollection* list,
    Vector* reads, //std::vector<CGXDLMSValueEventArg*>&
    Vector* actions); //std::vector<CGXDLMSValueEventArg*>&

/**
* Reset settings when connection is made or close.
*
* @param connected
*            Is co3nnected.
*/
extern void CGXDLMSServer_Reset_1(CGXDLMSServer* p, bool connected);

/**
* Handle received command.
*/
extern int CGXDLMSServer_HandleCommand(
    CGXDLMSServer* p,
    CGXDLMSConnectionEventArgs* connectionInfo,
    DLMS_COMMAND cmd,
    CGXByteBuffer* data,
    CGXByteBuffer* reply);

/**
* Parse AARQ request that client send and returns AARE request.
*
* @return Reply to the client.
*/
extern int CGXDLMSServer_HandleAarqRequest(
    CGXDLMSServer* p,
    CGXByteBuffer* data,
    CGXDLMSConnectionEventArgs* connectionInfo);

/**
 * Handle Set request.
 *
 * @return Reply to the client.
 */
extern int CGXDLMSServer_HandleSetRequest_2(
    CGXDLMSServer* p,
    CGXByteBuffer* data);

/**
* Handle Get request.
*
* @return Reply to the client.
*/
extern int CGXDLMSServer_HandleGetRequest(
    CGXDLMSServer* p,
    CGXByteBuffer* data);

/**
* Handle read request.
*/
extern int CGXDLMSServer_HandleReadRequest(
    CGXDLMSServer* p,
    CGXByteBuffer* data);

/**
* Handle write request.
*
* @param reply
*            Received data from the client.
* @return Reply.
*/
extern int CGXDLMSServer_HandleWriteRequest(
    CGXDLMSServer* p,
    CGXByteBuffer* data);

/**
* Handle action request.
*
* @param reply
*            Received data from the client.
* @return Reply.
*/
extern int CGXDLMSServer_HandleMethodRequest(
    CGXDLMSServer* p,
    CGXByteBuffer* data,
    CGXDLMSConnectionEventArgs* connectionInfo);

/**
* Count how many rows can fit to one PDU.
*
* @param pg
*            Read profile generic.
* @return Rows to fit one PDU.
*/
extern unsigned short CGXDLMSServer_GetRowsToPdu(
    CGXDLMSServer* p,
    CGXDLMSProfileGeneric* pg);

/**
* Update short names.
*
* @param force
*            Force update.
*/
extern int CGXDLMSServer_UpdateShortNames_1(CGXDLMSServer* p, bool force);

/**
* Handles release request.
*
* @param data
*            Received data.
* @param connectionInfo
*            Connection info.
*/
extern int CGXDLMSServer_HandleReleaseRequest(
    CGXDLMSServer* p,
    CGXByteBuffer* data);

extern int CGXDLMSServer_AddData(
    CGXDLMSServer* p,
    CGXDLMSObject* obj,
    unsigned char index,
    CGXByteBuffer* buff);

//protected:
/**
 * Server Settings.
 */
//extern CGXDLMSSettings CGXDLMSServer_m_Settings;

/**
 * @param value
 *            Cipher interface that is used to cipher PDU.
 */
extern void CGXDLMSServer_SetCipher(CGXDLMSServer* p, CGXCipher* value);

/**
* @return Get settings.
*/
extern CGXDLMSSettings* CGXDLMSServer_GetSettings(CGXDLMSServer* p);

/**
* Update short names.
*/
extern int CGXDLMSServer_UpdateShortNames_2(CGXDLMSServer* p);

//public:
/**
* @return HDLC settings.
*/
extern CGXDLMSIecHdlcSetup* CGXDLMSServer_GetHdlc(CGXDLMSServer* p);

/**
* @param value
*            HDLC settings.
*/
extern void CGXDLMSServer_SetHdlc(CGXDLMSServer* p, CGXDLMSIecHdlcSetup* value);

/**
* @return Wrapper settings.
*/
extern CGXDLMSTcpUdpSetup* CGXDLMSServer_GetWrapper(CGXDLMSServer* p);

/**
* @param value
*            Wrapper settings.
*/
extern void CGXDLMSServer_SetWrapper(CGXDLMSServer* p, CGXDLMSTcpUdpSetup* value);

/**
 * @return Client to Server challenge.
 */
extern CGXByteBuffer* CGXDLMSServer_GetCtoSChallenge(CGXDLMSServer* p);

/**
 * @return Server to Client challenge.
 */
extern CGXByteBuffer* CGXDLMSServer_GetStoCChallenge(CGXDLMSServer* p);

/**
 * @return Interface type.
 */
extern DLMS_INTERFACE_TYPE CGXDLMSServer_GetInterfaceType(CGXDLMSServer* p);

/**
 * Server to Client custom challenge. This is for debugging purposes. Reset
 * custom challenge settings StoCChallenge to NULL.
 *
 * @param value
 *            Server to Client challenge.
 */
extern void CGXDLMSServer_SetStoCChallenge(
    CGXDLMSServer* p,
    CGXByteBuffer* value);

/**
 * Set starting packet index. Default is One based, but some meters use Zero
 * based value. Usually this is not used.
 *
 * @param value
 *            Zero based starting index.
 */
extern void CGXDLMSServer_SetStartingPacketIndex(CGXDLMSServer* p, int value);

/**
 * @return Invoke ID.
 */
extern int CGXDLMSServer_GetInvokeID(CGXDLMSServer* p);

/**
 * Constructor.
 *
 * @param logicalNameReferencing
 *            Is logical name referencing used.
 * @param type
 *            Interface type.
 */
extern void CGXDLMSServer_1(
    CGXDLMSServer* p,
    bool logicalNameReferencing,
    DLMS_INTERFACE_TYPE type);

/**
* Constructor.
*
* @param ln
*           Logical name settings..
* @param hdlc
*            HDLC settings.
*/
extern void CGXDLMSServer_2(
    CGXDLMSServer* p,
    CGXDLMSAssociationLogicalName* ln, CGXDLMSIecHdlcSetup* hdlc);

/**
* Constructor.
*
* @param ln
*           Logical name settings..
* @param wrapper
*            WRAPPER settings.
*/
extern void CGXDLMSServer_3(
    CGXDLMSServer* p,
    CGXDLMSAssociationLogicalName* ln, CGXDLMSTcpUdpSetup* wrapper);

/**
* Constructor.
*
* @param sn
*           Short name settings..
* @param hdlc
*            HDLC settings.
*/
extern void CGXDLMSServer_4(
    CGXDLMSServer* p,
    CGXDLMSAssociationShortName* sn, CGXDLMSIecHdlcSetup* hdlc);

/**
* Constructor.
*
* @param sn
*           Short name settings..
* @param wrapper
*            WRAPPER settings.
*/
extern void CGXDLMSServer_5(
    CGXDLMSServer* p,
    CGXDLMSAssociationShortName* sn, CGXDLMSTcpUdpSetup* wrapper);


/**
* Destructor.
*/
extern void CGXDLMSServer_d(CGXDLMSServer* p);

/**
 * @return List of objects that meter supports.
 */
extern CGXDLMSObjectCollection* CGXDLMSServer_GetItems(CGXDLMSServer* p);

/**
 * @return Information from the connection size that server can handle.
 */
extern CGXDLMSLimits CGXDLMSServer_GetLimits(CGXDLMSServer* p);

/**
 * Retrieves the maximum size of received PDU. PDU size tells maximum size
 * of PDU packet. Value can be from 0 to 0xFFFF. By default the value is
 * 0xFFFF.
 *
 * @return Maximum size of received PDU.
 */
extern unsigned short CGXDLMSServer_GetMaxReceivePDUSize(CGXDLMSServer* p);

/**
 * @param value
 *            Maximum size of received PDU.
 */
extern void CGXDLMSServer_SetMaxReceivePDUSize(
    CGXDLMSServer* p,
    unsigned short value);

/**
 * Determines, whether Logical, or Short name, referencing is used.
 * Referencing depends on the device to communicate with. Normally, a device
 * supports only either Logical or Short name referencing. The referencing
 * is defined by the device manufacturer. If the referencing is wrong, the
 * SNMR message will fail.
 *
 * @see #getMaxReceivePDUSize
 * @return Is logical name referencing used.
 */
extern bool CGXDLMSServer_GetUseLogicalNameReferencing(CGXDLMSServer* p);

/**
 * @param value
 *            Is Logical Name referencing used.
 */
extern void CGXDLMSServer_SetUseLogicalNameReferencing(
    CGXDLMSServer* p,
    bool value);

/**
 * Initialize server. This must call after server objects are set.
 */
extern int CGXDLMSServer_Initialize(CGXDLMSServer* p);

/**
 * Reset after connection is closed.
 */
extern void CGXDLMSServer_Reset_2(CGXDLMSServer* p);

/**
 * Handles client request.
 *
 * @param data
 *            Received data from the client.
 * @return Response to the request. Response is NULL if request packet is
 *         not complete.
 */
extern int CGXDLMSServer_HandleRequest_1(
    CGXDLMSServer* p,
    CGXByteBuffer* data,
    CGXByteBuffer* reply);

/**
* Handles client request.
*
* @param data
*            Received data from the client.
* @return Response to the request. Response is NULL if request packet is
*         not complete.
*/
extern int CGXDLMSServer_HandleRequest_2(
    CGXDLMSServer* p,
    CGXDLMSConnectionEventArgs* connectionInfo,
    CGXByteBuffer* data,
    CGXByteBuffer* reply);

/**
 * Handles client request.
 *
 * @param data
 *            Received data from the client.
 * @return Response to the request. Response is NULL if request packet is
 *         not complete.
 */
extern int CGXDLMSServer_HandleRequest_3(
    CGXDLMSServer* p,
    unsigned char* data,
    unsigned short size,
    CGXByteBuffer* reply);

/**
 * Handles client request.
 *
 * @param data
 *            Received data from the client.
 * @return Response to the request. Response is NULL if request packet is
 *         not complete.
 */
extern int CGXDLMSServer_HandleRequest_4(
    CGXDLMSServer* p,
    CGXDLMSConnectionEventArgs* connectionInfo,
    unsigned char* data,
    unsigned short size,
    CGXByteBuffer* reply);


/**
* Find Short Name object.
*
* @param sn
*/
extern int CGXDLMSServer_FindSNObject(CGXDLMSServer* p, int sn, CGXSNInfo* i);

/**
* Server will tell what functionality is available for the client.
* @return Available functionality.
*/
extern DLMS_CONFORMANCE CGXDLMSServer_GetConformance(CGXDLMSServer* p);

/**
* Server will tell what functionality is available for the client.
*
* @param value
*            Available functionality.
*/
extern void CGXDLMSServer_SetConformance(CGXDLMSServer* p, DLMS_CONFORMANCE value);

extern int CGXDLMSServer_GenerateDataNotificationMessages_1(
    CGXDLMSServer* p,
    struct tm* time,
    CGXByteBuffer* data,
    Vector* reply); //std::vector<CGXByteBuffer>&

extern int CGXDLMSServer_GenerateDataNotificationMessages_2(
    CGXDLMSServer* p,
    struct tm* date,
    Vector* objects, //std::vector<std::pair<CGXDLMSObject*, unsigned char> >&
    Vector* reply); //std::vector<CGXByteBuffer>&

extern int CGXDLMSServer_GeneratePushSetupMessages(
    CGXDLMSServer* p,
    struct tm* date,
    CGXDLMSPushSetup* push,
    Vector* reply); //std::vector<CGXByteBuffer>&

#endif //GXDLMSSERVER_H
