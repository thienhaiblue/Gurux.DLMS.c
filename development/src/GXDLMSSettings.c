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

#include "../include/GXDLMSSettings.h"

void CGXDLMSSettings_(CGXDLMSSettings* p, bool isServer)
{
    CGXByteBuffer_1(&p->m_CtoSChallenge);
    CGXByteBuffer_1(&p->m_StoCChallenge);
    CGXByteBuffer_1(&p->m_SourceSystemTitle);
    CGXByteBuffer_1(&p->m_Password);
    CGXByteBuffer_1(&p->m_Kek);
    CGXDLMSLimits_(&p->m_Limits);
    CGXDLMSObjectCollection_(&p->m_Objects);

    p->m_CustomChallenges = false;
    p->m_BlockIndex = 1;
    p->m_Connected = false;
    p->m_DlmsVersionNumber = DLMS_VERSION;
    p->m_Server = isServer;
    CGXDLMSSettings_ResetFrameSequence(p);
    p->m_InvokeID = 1;
    p->m_LongInvokeID = 1;
    p->m_Priority = DLMS_PRIORITY_HIGH;
    p->m_ServiceClass = DLMS_SERVICE_CLASS_UN_CONFIRMED;
    p->m_ClientAddress = 0;
    p->m_ServerAddress = 0;
    p->m_InterfaceType = DLMS_INTERFACE_TYPE_HDLC;
    p->m_Authentication = DLMS_AUTHENTICATION_NONE;
    p->m_MaxServerPDUSize = p->m_MaxReceivePDUSize = 0xFFFF;
    p->m_Cipher = NULL;
    CGXByteBuffer_Clear(&(p->m_SourceSystemTitle));
    p->m_Index = 0;
    p->m_Count = 0;
    p->m_ProposedConformance = p->m_NegotiatedConformance = (DLMS_CONFORMANCE)0;
}

//Destructor.
void CGXDLMSSettings_d(CGXDLMSSettings* p)
{
    CGXDLMSObjectCollection_Free(&(p->m_Objects));

    CGXByteBuffer_d(&p->m_CtoSChallenge);
    CGXByteBuffer_d(&p->m_StoCChallenge);
    CGXByteBuffer_d(&p->m_SourceSystemTitle);
    CGXByteBuffer_d(&p->m_Password);
    CGXByteBuffer_d(&p->m_Kek);

    CGXDLMSObjectCollection_d(&p->m_Objects);
}

CGXByteBuffer* CGXDLMSSettings_GetCtoSChallenge(CGXDLMSSettings* p)
{
    return &(p->m_CtoSChallenge);
}


void CGXDLMSSettings_SetCtoSChallenge(CGXDLMSSettings* p, CGXByteBuffer* value)
{
    if (!(p->m_CustomChallenges) || p->m_CtoSChallenge.m_Size == 0)
    {
        CGXByteBuffer_copy(&(p->m_CtoSChallenge), value);
    }
}

CGXByteBuffer* CGXDLMSSettings_GetStoCChallenge(CGXDLMSSettings* p)
{
    return &(p->m_StoCChallenge);
}

void CGXDLMSSettings_SetStoCChallenge(CGXDLMSSettings* p, CGXByteBuffer* value)
{
    if (!(p->m_CustomChallenges) || p->m_StoCChallenge.m_Size == 0)
    {
        CGXByteBuffer_copy(&(p->m_StoCChallenge), value);
    }
}

CGXByteBuffer* CGXDLMSSettings_GetPassword(CGXDLMSSettings* p)
{
    return &(p->m_Password);
}

void CGXDLMSSettings_SetPassword(CGXDLMSSettings* p, CGXByteBuffer* value)
{
    CGXByteBuffer_copy(&(p->m_Password), value);
}

void CGXDLMSSettings_ResetFrameSequence(CGXDLMSSettings* p)
{
    if (p->m_Server)
    {
        p->m_SenderFrame = SERVER_START_SENDER_FRAME_SEQUENCE;
        p->m_ReceiverFrame = SERVER_START_RECEIVER_FRAME_SEQUENCE;
    }
    else
    {
        p->m_SenderFrame = CLIENT_START_SENDER_FRAME_SEQUENCE;
        p->m_ReceiverFrame = CLIENT_START_RCEIVER_FRAME_SEQUENCE;
    }
}

bool CGXDLMSSettings_CheckFrame(CGXDLMSSettings* p, unsigned char frame)
{
    // If U frame.
    if ((frame & 0x3) == 3)
    {
        CGXDLMSSettings_ResetFrameSequence(p);
        return true;
    }
    // If S -frame
    if ((frame & 0x3) == 1)
    {
        if ((frame & 0xE0) == ((p->m_ReceiverFrame) & 0xE0))
        {
            p->m_ReceiverFrame = frame;
            return true;
        }
        return true;
    }

    // If I frame sent.
    if ((p->m_SenderFrame & 0x1) == 0)
    {
        if ((frame & 0xE0) == ((p->m_ReceiverFrame + 0x20) & 0xE0)
            && (frame & 0xE) == ((p->m_ReceiverFrame + 2) & 0xE))
        {
            p->m_ReceiverFrame = frame;
            return true;
        }
    }
    else if (frame == p->m_ReceiverFrame
        || ((frame & 0xE0) == (p->m_ReceiverFrame & 0xE0)
            && (frame & 0xE) == ((p->m_ReceiverFrame + 2) & 0xE)))
    {
        // If S-frame sent.
        p->m_ReceiverFrame = frame;
        return true;
    }
    return true;
}

// Increase receiver sequence.
//
// @param value
//            Frame value.
// Increased receiver frame sequence.
static unsigned char IncreaseReceiverSequence(unsigned char value)
{
    return ((value + 0x20) | 0x10 | (value & 0xE));
}

// Increase sender sequence.
//
// @param value
//            Frame value.
// Increased sender frame sequence.
static unsigned char IncreaseSendSequence(unsigned char value)
{
    return (unsigned char)((value & 0xF0) | ((value + 0x2) & 0xE));
}

unsigned char CGXDLMSSettings_GetNextSend(CGXDLMSSettings* p, unsigned char first)
{
    if (first)
    {
        p->m_SenderFrame = IncreaseReceiverSequence(IncreaseSendSequence(p->m_SenderFrame));
    }
    else
    {
        p->m_SenderFrame = IncreaseSendSequence(p->m_SenderFrame);
    }
    return p->m_SenderFrame;
}

unsigned char CGXDLMSSettings_GetReceiverReady(CGXDLMSSettings* p)
{
    p->m_SenderFrame = IncreaseReceiverSequence((unsigned char)(p->m_SenderFrame | 1));
    return (unsigned char)(p->m_SenderFrame & 0xF1);
}

unsigned char CGXDLMSSettings_GetKeepAlive(CGXDLMSSettings* p)
{
    p->m_SenderFrame = (unsigned char)(p->m_SenderFrame | 1);
    return (unsigned char)(p->m_SenderFrame & 0xF1);
}

CGXDLMSLimits* CGXDLMSSettings_GetLimits(CGXDLMSSettings* p)
{
    return &(p->m_Limits);
}

int CGXDLMSSettings_SetMaxReceivePDUSize(CGXDLMSSettings* p, unsigned short value)
{
    if ((value < 64) && !(p->m_Server))
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    p->m_MaxReceivePDUSize = value;
    return 0;
}

int CGXDLMSSettings_SetMaxServerPDUSize(CGXDLMSSettings* p, unsigned short value)
{
    if (value < 64)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    p->m_MaxServerPDUSize = value;
    return 0;
}

int CGXDLMSSettings_SetLongInvokeID(CGXDLMSSettings* p, unsigned long value)
{
    if (value > 0xFFFFFF)
    {
        //Invalid InvokeID.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    p->m_LongInvokeID = value;
    return 0;
}
CGXDLMSObjectCollection* CGXDLMSSettings_GetObjects(CGXDLMSSettings* p)
{
    return &(p->m_Objects);
}

/**
     * @return Source system title.
     */
CGXByteBuffer* CGXDLMSSettings_GetSourceSystemTitle(CGXDLMSSettings* p)
{
    return &(p->m_SourceSystemTitle);
}

/**
 * @param value
 *            Source system title.
 */
int CGXDLMSSettings_SetSourceSystemTitle(CGXDLMSSettings* p, CGXByteBuffer* value)
{
    if (value->m_Size != 8)
    {
        //Invalid client system title.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    CGXByteBuffer_copy(&(p->m_SourceSystemTitle), value);
    return DLMS_ERROR_CODE_OK;
}

/**
 * @return Key Encrypting Key, also known as Master key.
 */
CGXByteBuffer* CGXDLMSSettings_GetKek(CGXDLMSSettings* p)
{
    return &(p->m_Kek);
}

/**
 * @param value
 *            Key Encrypting Key, also known as Master key.
 */
void CGXDLMSSettings_SetKek(CGXDLMSSettings* p, CGXByteBuffer* value)
{
    CGXByteBuffer_copy(&(p->m_Kek), value);
}
