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

#ifndef GXDLMSSETTINGS_H
#define GXDLMSSETTINGS_H

#include "enums.h"
#include "GXBytebuffer.h"
#include "GXDLMSLimits.h"
#include "GXDLMSObjectCollection.h"
#include "GXCipher.h"

//typedef struct CGXDLMSObjectCollection CGXDLMSObjectCollection;

// Server sender frame sequence starting number.
static const unsigned char SERVER_START_SENDER_FRAME_SEQUENCE = 0x1E;

// Server receiver frame sequence starting number.
static const unsigned char SERVER_START_RECEIVER_FRAME_SEQUENCE = 0xFE;

// Client sender frame sequence starting number.
static const unsigned char CLIENT_START_SENDER_FRAME_SEQUENCE = 0x10;

// Client receiver frame sequence starting number.
static const unsigned char CLIENT_START_RCEIVER_FRAME_SEQUENCE = 0xE;
// DLMS version number.
static const unsigned char DLMS_VERSION = 6;

static const unsigned short MAX_RECEIVE_PDU_SIZE = 0xFFFF;

// This class includes DLMS communication Settings.
typedef struct CGXDLMSSettings
{
    //Is connection made for the server.
    bool m_Connected;

    // Is custom challenges used. If custom challenge is used new challenge is
    // not generated if it is Set. This is for debugging purposes.
    bool m_CustomChallenges;

    // Client to server challenge.
    CGXByteBuffer m_CtoSChallenge;

    // Server to Client challenge.
    CGXByteBuffer m_StoCChallenge;

    CGXByteBuffer m_SourceSystemTitle;

    // Invoke ID.
    unsigned char m_InvokeID;
    //Long Invoke ID.
    int m_LongInvokeID;

    // Priority.
    DLMS_PRIORITY m_Priority;

    // Service class.
    DLMS_SERVICE_CLASS m_ServiceClass;

    // Client address.
    unsigned long m_ClientAddress;

    // Server address.
    unsigned long m_ServerAddress;

    // Is Logical Name referencing used.
    bool m_UseLogicalNameReferencing;

    // Interface type.
    DLMS_INTERFACE_TYPE m_InterfaceType;

    // User authentication.
    DLMS_AUTHENTICATION m_Authentication;

    // User password.
    CGXByteBuffer m_Password;

    /**
     * Key Encrypting Key, also known as Master key.
     */
    CGXByteBuffer m_Kek;

    /**
     * Long data count.
     */
    unsigned short m_Count;

    /**
     * Long data index.
     */
    unsigned short m_Index;

    // DLMS version number.
    unsigned char m_DlmsVersionNumber;

    // Maximum receivers PDU size.
    unsigned short m_MaxReceivePDUSize;

    // Maximum server PDU size.
    unsigned short m_MaxServerPDUSize;

    // HDLC sender frame sequence number.
    unsigned char m_SenderFrame;

    // HDLC receiver block sequence number.
    unsigned char m_ReceiverFrame;

    // Is this server or client.
    bool m_Server;

    // Information from the connection size that server can handle.
    CGXDLMSLimits m_Limits;

    // Block packet index.
    unsigned long m_BlockIndex;

    // List of server or client objects.
    CGXDLMSObjectCollection m_Objects;

    /**
     * Cipher interface that is used to cipher PDU.
     */
    CGXCipher* m_Cipher;

    /**
    * Proposed conformance block. Client asks this funtionality.
    */
    DLMS_CONFORMANCE m_ProposedConformance;

    /**
    * Server tells what functionality is available and client will know it.
    */
    DLMS_CONFORMANCE m_NegotiatedConformance;
} CGXDLMSSettings;

// Constructor.
extern void CGXDLMSSettings_(CGXDLMSSettings* p, bool isServer);

//Destructor.
extern void CGXDLMSSettings_d(CGXDLMSSettings* p);

// Client to Server challenge.
extern CGXByteBuffer* CGXDLMSSettings_GetCtoSChallenge(CGXDLMSSettings* p);

// Client to Server challenge.
extern void CGXDLMSSettings_SetCtoSChallenge(CGXDLMSSettings* p, CGXByteBuffer* value);

// Get server to Client challenge.
extern CGXByteBuffer* CGXDLMSSettings_GetStoCChallenge(CGXDLMSSettings* p);

// Set server to Client challenge.
extern void CGXDLMSSettings_SetStoCChallenge(CGXDLMSSettings* p, CGXByteBuffer* value);

// Gets used authentication.
extern DLMS_AUTHENTICATION CGXDLMSSettings_GetAuthentication(CGXDLMSSettings* p);

//Sets Used authentication.
extern void CGXDLMSSettings_SetAuthentication(CGXDLMSSettings* p, DLMS_AUTHENTICATION value);

//Gets password.
extern CGXByteBuffer* CGXDLMSSettings_GetPassword(CGXDLMSSettings* p);

    // Sets password.
extern void CGXDLMSSettings_SetPassword(CGXDLMSSettings* p, CGXByteBuffer* value);

    // Used DLMS version number.
extern unsigned char CGXDLMSSettings_GetDlmsVersionNumber(CGXDLMSSettings* p);

    // Used DLMS version number.
extern void CGXDLMSSettings_SetDlmsVersionNumber(CGXDLMSSettings* p, unsigned char value);

    // Reset frame sequence.
extern void CGXDLMSSettings_ResetFrameSequence(CGXDLMSSettings* p);

extern bool CGXDLMSSettings_CheckFrame(CGXDLMSSettings* p, unsigned char frame);

    // Generates I-frame.
extern unsigned char CGXDLMSSettings_GetNextSend(CGXDLMSSettings* p, unsigned char first);

    // Generates Receiver Ready S-frame.
extern unsigned char CGXDLMSSettings_GetReceiverReady(CGXDLMSSettings* p);

    // Generates Keep Alive S-frame.
extern unsigned char CGXDLMSSettings_GetKeepAlive(CGXDLMSSettings* p);

    // Gets current block index.
extern unsigned long CGXDLMSSettings_GetBlockIndex(CGXDLMSSettings* p);

    // Sets current block index.
extern void CGXDLMSSettings_SetBlockIndex(CGXDLMSSettings* p, unsigned long value);

    // Resets block index to default value.
extern void CGXDLMSSettings_ResetBlockIndex(CGXDLMSSettings* p);

    // Increases block index.
extern void CGXDLMSSettings_IncreaseBlockIndex(CGXDLMSSettings* p);

    //Is acting as server or client.
extern bool CGXDLMSSettings_IsServer(CGXDLMSSettings* p);

    // Information from the frame size that server can handle.
extern CGXDLMSLimits* CGXDLMSSettings_GetLimits(CGXDLMSSettings* p);

    // Used interface.
extern DLMS_INTERFACE_TYPE CGXDLMSSettings_GetInterfaceType(CGXDLMSSettings* p);

    // Used interface.
extern void CGXDLMSSettings_SetInterfaceType(CGXDLMSSettings* p, DLMS_INTERFACE_TYPE value);

    // Gets client address.
extern unsigned long CGXDLMSSettings_GetClientAddress(CGXDLMSSettings* p);

    // Sets client address.
extern void CGXDLMSSettings_SetClientAddress(CGXDLMSSettings* p, unsigned long value);

    // Server address.
extern unsigned long CGXDLMSSettings_GetServerAddress(CGXDLMSSettings* p);

    // Server address.
extern void CGXDLMSSettings_SetServerAddress(CGXDLMSSettings* p, unsigned long value);

    // DLMS version number.
extern unsigned char CGXDLMSSettings_GetDLMSVersion(CGXDLMSSettings* p);

    // DLMS version number.
extern void CGXDLMSSettings_SetDLMSVersion(CGXDLMSSettings* p,unsigned char value);

    // Maximum PDU size.
extern unsigned short CGXDLMSSettings_GetMaxPduSize(CGXDLMSSettings* p);

    // Maximum PDU size.
extern int CGXDLMSSettings_SetMaxReceivePDUSize(CGXDLMSSettings* p, unsigned short value);

    // Maximum server PDU size.
extern unsigned short CGXDLMSSettings_GetMaxServerPDUSize(CGXDLMSSettings* p);

    // Maximum server PDU size.
extern int CGXDLMSSettings_SetMaxServerPDUSize(CGXDLMSSettings* p, unsigned short value);

    // Is Logical Name Referencing used.
extern bool CGXDLMSSettings_GetUseLogicalNameReferencing(CGXDLMSSettings* p);

    // Is Logical Name Referencing used.
extern void CGXDLMSSettings_SetUseLogicalNameReferencing(CGXDLMSSettings* p, bool value);

    // Used priority.
extern DLMS_PRIORITY CGXDLMSSettings_GetPriority(CGXDLMSSettings* p);

    // Used priority.
extern void CGXDLMSSettings_SetPriority(CGXDLMSSettings* p, DLMS_PRIORITY value);

    // Used service class.
extern DLMS_SERVICE_CLASS CGXDLMSSettings_GetServiceClass(CGXDLMSSettings* p);

    // Used service class.
extern void CGXDLMSSettings_SetServiceClass(CGXDLMSSettings* p, DLMS_SERVICE_CLASS value);

    // Invoke ID.
extern int CGXDLMSSettings_GetInvokeID(CGXDLMSSettings* p);

    // Invoke ID.
extern void CGXDLMSSettings_SetInvokeID(CGXDLMSSettings* p, int value);

    /**
       * @return Invoke ID.
       */
extern unsigned long CGXDLMSSettings_GetLongInvokeID(CGXDLMSSettings* p);

    /**
     * @param value
     *            Invoke ID.
     */
extern int CGXDLMSSettings_SetLongInvokeID(CGXDLMSSettings* p, unsigned long value);

    // Collection of the objects.
extern CGXDLMSObjectCollection* CGXDLMSSettings_GetObjects(CGXDLMSSettings* p);

    // Get Is custom challenges used.
extern bool CGXDLMSSettings_IsCustomChallenges(CGXDLMSSettings* p);

    // Set is custom challenges used.
extern void CGXDLMSSettings_SetUseCustomChallenge(CGXDLMSSettings* p, bool value);

    //Get is connection made for the server.
extern bool CGXDLMSSettings_IsConnected(CGXDLMSSettings* p);

    //Set is connection made for the server.
extern void CGXDLMSSettings_SetConnected(CGXDLMSSettings* p, bool value);

    /**
    * Cipher interface that is used to cipher PDU.
    */
extern CGXCipher* CGXDLMSSettings_GetCipher(CGXDLMSSettings* p);

    /**
    * Cipher interface that is used to cipher PDU.
    */
extern void CGXDLMSSettings_SetCipher(CGXDLMSSettings* p, CGXCipher* value);

    /**
     * @return Source system title.
     */
extern CGXByteBuffer* CGXDLMSSettings_GetSourceSystemTitle(CGXDLMSSettings* p);

    /**
     * @param value
     *            Source system title.
     */
extern int CGXDLMSSettings_SetSourceSystemTitle(CGXDLMSSettings* p, CGXByteBuffer* value);

    /**
     * @return Key Encrypting Key, also known as Master key.
     */
extern CGXByteBuffer* CGXDLMSSettings_GetKek(CGXDLMSSettings* p);

    /**
     * @param value
     *            Key Encrypting Key, also known as Master key.
     */
extern void CGXDLMSSettings_SetKek(CGXDLMSSettings* p, CGXByteBuffer* value);

    /**
     * @return Long data count.
     */
extern unsigned short CGXDLMSSettings_GetCount(CGXDLMSSettings* p);

    /**
     * @param count
     *            Long data count.
     */
extern void CGXDLMSSettings_SetCount(CGXDLMSSettings* p, unsigned short value);

    /**
     * @return Long data index.
     */
extern unsigned short CGXDLMSSettings_GetIndex(CGXDLMSSettings* p);

    /**
     * @param index
     *            Long data index
     */
extern void CGXDLMSSettings_SetIndex(CGXDLMSSettings* p, unsigned short value);

    /**
    * Server will tell what functionality is available. Client will know what functionality server offers.
    * @return Available functionality.
    */
extern DLMS_CONFORMANCE CGXDLMSSettings_GetNegotiatedConformance(CGXDLMSSettings* p);

    /**
    * Server will tell what functionality is available. Client will know what functionality server offers from this value.
    *
    * @param value
    *            Available functionality.
    */
extern void CGXDLMSSettings_SetNegotiatedConformance(CGXDLMSSettings* p, DLMS_CONFORMANCE value);

    /**
    * Client proposes this functionality. Server checks what it can offer from Conformance and updates it to proposed conformance.
    * @return Functionality.
    */
extern DLMS_CONFORMANCE CGXDLMSSettings_GetProposedConformance(CGXDLMSSettings* p);

    /**
    * Client proposes this functionality. Server checks what it can offer from Conformance and updates it to proposed conformance.
    *
    * @param value
    *            Functionality.
    */
extern void CGXDLMSSettings_SetProposedConformance(CGXDLMSSettings* p, DLMS_CONFORMANCE value);

#endif //GXDLMSSETTINGS_H
