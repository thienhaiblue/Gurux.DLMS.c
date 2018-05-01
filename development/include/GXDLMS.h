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

#ifndef GXDLMS_H
#define GXDLMS_H

#include "GXDLMSLimits.h"
#include "GXDLMSObject.h"
#include "GXDLMSObjectCollection.h"
#include "GXBytebuffer.h"
#include "GXDLMSSettings.h"
#include "GXDLMSVariant.h"
#include "GXCipher.h"
#include "GXReplyData.h"
#include "GXDLMSLNParameters.h"
#include "GXDLMSSNParameters.h"

extern unsigned short CGXDLMS_CountFCS16(CGXByteBuffer* buff, int index, int count);

    /////////////////////////////////////////////////////////////////////////////
    // Get adress as GXDLMSVariant.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_GetAddress(long value, unsigned long* address, int* size);

    /////////////////////////////////////////////////////////////////////////////
    // Get address as an byte array.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_GetAddressBytes(unsigned long value, CGXByteBuffer* bytes);

    /////////////////////////////////////////////////////////////////////////////
    // Returns true if executed command is reply.
    /////////////////////////////////////////////////////////////////////////////
    // cmd : Executed command.
    // Returns Is command reply.
    /////////////////////////////////////////////////////////////////////////////
extern bool CGXDLMS_IsReplyMessage(DLMS_COMMAND cmd);

    /////////////////////////////////////////////////////////////////////////////
    // Check LLC bytes.
    /////////////////////////////////////////////////////////////////////////////
    // server : Is server.
    // data : Received data.
    /////////////////////////////////////////////////////////////////////////////
extern void CGXDLMS_GetLLCBytes(bool server, CGXByteBuffer* data);

    /////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_CheckWrapperAddress(CGXDLMSSettings* settings, CGXByteBuffer* buff);

    /////////////////////////////////////////////////////////////////////////////
    // Get value from data.
    /////////////////////////////////////////////////////////////////////////////
    // settings : DLMS settings.
    // reply : Received data.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_GetValueFromData(CGXDLMSSettings* settings, CGXReplyData* reply);

    /////////////////////////////////////////////////////////////////////////////
    // Get data from HDLC or wrapper frame.
    /////////////////////////////////////////////////////////////////////////////
    // reply : Received data that includes HDLC frame.
    // info : Reply data.
    /////////////////////////////////////////////////////////////////////////////
extern void CGXDLMS_GetDataFromFrame(CGXByteBuffer* reply, CGXReplyData* info);

    /**
    * Handle read response data block result.
    *
    * @param settings
    *            DLMS settings.
    * @param reply
    *            Received reply.
    * @param index
    *            Starting index.
    */
extern int CGXDLMS_ReadResponseDataBlockResult(CGXDLMSSettings* settings,
                                               CGXReplyData* reply, int index);

extern int CGXDLMS_HandledGloRequest(CGXDLMSSettings* settings, CGXReplyData* data);

extern int CGXDLMS_HandledGloResponse(CGXDLMSSettings* settings,
                                      CGXReplyData* data, int index);


    /////////////////////////////////////////////////////////////////////////////
    // Check client and server addresses. Reserved for internal use.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_CheckInit(CGXDLMSSettings* settings);

    /**
     * Get all Logical name messages. Client uses this to generate messages.
     *
     * @param p
     *            LN settings.
     * @param reply
     *            Generated messages.
     * @return    Status code.
     */
extern int CGXDLMS_GetLnMessages(CGXDLMSLNParameters* p,
                                 Vector* reply); // std::vector<CGXByteBuffer>&

    /**
    * Get all Short Name messages. Client uses this to generate messages.
    *
    * @param p
    *            DLMS SN parameters.
    * @param reply
    *            Generated messages.
    * @return    Status code.
    */
extern int CGXDLMS_GetSnMessages(CGXDLMSSNParameters* p,
                                 Vector* reply); // std::vector<CGXByteBuffer>&

    /**
    * Handle General block transfer message.
    *
    * @param settings
    *            DLMS settings.
    * @param data
    *            received data.
    */
extern int CGXDLMS_HandleGbt(CGXDLMSSettings* settings, CGXReplyData* data);

    /**
     * Split DLMS PDU to wrapper frames.
     *
     * @param settings
     *            DLMS settings.
     * @param data
     *            Wrapped data.
     * @return Wrapper frames.
    */
extern int CGXDLMS_GetWrapperFrame(CGXDLMSSettings* settings,
                                   CGXByteBuffer* data,
                                   CGXByteBuffer* reply);

    /**
    * Get next logical name PDU.
    *
    * @param p
    *            LN parameters.
    * @param reply
    *            Generated message.
    */
extern int CGXDLMS_GetLNPdu(CGXDLMSLNParameters* p, CGXByteBuffer* reply);

    /**
    * @param p
    * @param reply
    */
extern int CGXDLMS_GetSNPdu(CGXDLMSSNParameters* p, CGXByteBuffer* reply);


    /////////////////////////////////////////////////////////////////////////////
    // Generates an acknowledgment message, with which the server is informed to
    // send next packets.
    /////////////////////////////////////////////////////////////////////////////
    // type : Frame type
    // Returns : Acknowledgment message as unsigned char array.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_ReceiverReady(CGXDLMSSettings* settings,
                                 DLMS_DATA_REQUEST_TYPES type,
                                 CGXCipher* cipher,
                                 CGXByteBuffer* reply);

    /**
    * Get HDLC frame for data.
    *
    * @param settings
    *            DLMS settings.
    * @param frame
    *            Frame ID. If zero new is generated.
    * @param data
    *            Data to add.
    * @return HDLC frame.
    */
extern int CGXDLMS_GetHdlcFrame(CGXDLMSSettings* settings,
                                unsigned char frame,
                                CGXByteBuffer* data,
                                CGXByteBuffer* reply);

extern int CGXDLMS_GetHdlcData(bool server,
                               CGXDLMSSettings* settings,
                               CGXByteBuffer* reply,
                               CGXReplyData* data,
                               unsigned char* frame);

    /**
     * Get HDLC address from byte array.
     *
     * @param buff
     *            byte array.
     * @return HDLC address.
     */
extern int CGXDLMS_GetHDLCAddress(CGXByteBuffer* buff, unsigned long* address);

    /**
     * Check that client and server address match.
     *
     * @param server
     *            Is server.
     * @param settings
     *            DLMS settings.
     * @param reply
     *            Received data.
     * @param index
     *            Position.
     * @return True, if client and server address match.
     */
extern int CGXDLMS_CheckHdlcAddress(bool server,
                                    CGXDLMSSettings* settings,
                                    CGXByteBuffer* reply,
                                    int index);

    /////////////////////////////////////////////////////////////////////////////
    // Get data from TCP/IP frame.
    /////////////////////////////////////////////////////////////////////////////
    // settings : DLMS settigns.
    // buff : Received data.
    // data : Reply information.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_GetTcpData(CGXDLMSSettings* settings,
                              CGXByteBuffer* buff,
                              CGXReplyData* data);

    /////////////////////////////////////////////////////////////////////////////
    // Handle read response and get data from block and/or update error status.
    /////////////////////////////////////////////////////////////////////////////
    // data : Received data from the client.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_HandleReadResponse(CGXDLMSSettings* settings,
                                      CGXReplyData* data,
                                      int index);

    /////////////////////////////////////////////////////////////////////////////
    // Handle method response and get data from block and/or update error status.
    /////////////////////////////////////////////////////////////////////////////
    // data : Received data from the client.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_HandleMethodResponse(CGXDLMSSettings* settings,
                                        CGXReplyData* data);

    /////////////////////////////////////////////////////////////////////////////
    // Handle push and get data from block and/or update error status.
    /////////////////////////////////////////////////////////////////////////////
    // reply : Received data from the client.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_HandlePush(CGXReplyData* reply);

    /////////////////////////////////////////////////////////////////////////////
    // Handle set response and update error status.
    /////////////////////////////////////////////////////////////////////////////
    // reply : Received data from the client.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_HandleSetResponse(CGXDLMSSettings* settings,
                                     CGXReplyData* data);

    /**
    * Handle data notification get data from block and/or update error status.
    *
    * @param settings
    *            DLMS settings.
    * @param reply
    *            Received data from the client.
    */
extern int CGXDLMS_HandleDataNotification(CGXDLMSSettings* settings,
                                          CGXReplyData* reply);

    /////////////////////////////////////////////////////////////////////////////
    // Handle write response and update error status.
    /////////////////////////////////////////////////////////////////////////////
    // reply : Received data from the client.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_HandleWriteResponse(CGXReplyData* data);

    /////////////////////////////////////////////////////////////////////////////
    // Handle get response and get data from block and/or update error status.
    /////////////////////////////////////////////////////////////////////////////
    // settings : DLMS settings.
    // reply : Received data from the client.
    // index : Block index number.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_HandleGetResponse(CGXDLMSSettings* settings,
                                     CGXReplyData* reply,
                                     int index);

    /////////////////////////////////////////////////////////////////////////////
    // Get PDU from the packet.
    /////////////////////////////////////////////////////////////////////////////
    // settings : DLMS settings.
    // data : received data.
    // cipher : Cipher interface.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_GetPdu(CGXDLMSSettings* settings,
                          CGXReplyData* data);

    /////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_GetData(CGXDLMSSettings* settings,
                           CGXByteBuffer* reply,
                           CGXReplyData* data);

    /////////////////////////////////////////////////////////////////////////////
    // Get action info.
    /////////////////////////////////////////////////////////////////////////////
    // objectType : Object type.
    // value : Starting address.
    // count : Attribute count.
    /////////////////////////////////////////////////////////////////////////////
extern int CGXDLMS_GetActionInfo(DLMS_OBJECT_TYPE objectType,
                                 unsigned char* value,
                                 unsigned char* count);


extern int CGXDLMS_AppendData(CGXDLMSObject* obj,
                              unsigned char index,
                              CGXByteBuffer* bb,
                              CGXDLMSVariant* value);

extern int CGXDLMS_ParseSnrmUaResponse(CGXByteBuffer* data,
                                       CGXDLMSLimits* limits);

    // Add HDLC parameter.
extern void CGXDLMS_AppendHdlcParameter(CGXByteBuffer* data, unsigned short value);

#endif //GXDLMS_H
