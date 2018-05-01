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

#ifndef GXDLMSSERVERLN_H_
#define GXDLMSSERVERLN_H_

#include "GXDLMSBase.h"

typedef struct CGXDLMSServerLN // class CGXDLMSServerLN : public CGXDLMSBase
{
    ///////////////////////////////////////////////////////////////////////////
    // (CGXDLMSServer)
    long m_DataReceived;
    CGXDLMSIecHdlcSetup* m_Hdlc;
    CGXDLMSTcpUdpSetup* m_Wrapper;
    CGXReplyData m_Info;
    CGXByteBuffer m_ReceivedData;
    CGXByteBuffer m_ReplyData;
    CGXDLMSLongTransaction* m_Transaction;
    bool m_Initialized;
    CGXDLMSSettings m_Settings;

    // Override CGXDLMSServer
    IsTarget_FuncPtr IsTarget;
    ValidateAuthentication_FuncPtr ValidateAuthentication;
    FindObject_FuncPtr FindObject;
    PreRead_FuncPtr PreRead;
    PreWrite_FuncPtr PreWrite;
    Connected_FuncPtr Connected;
    InvalidConnection_FuncPtr InvalidConnection;
    Disconnected_FuncPtr Disconnected;
    GetAttributeAccess_FuncPtr GetAttributeAccess;
    GetMethodAccess_FuncPtr GetMethodAccess;
    PreAction_FuncPtr PreAction;
    PostRead_FuncPtr PostRead;
    PostWrite_FuncPtr PostWrite;
    PostAction_FuncPtr PostAction;
    PreGet_FuncPtr PreGet;
    PostGet_FuncPtr PostGet;

    // (CGXDLMSSecureServer)
    CGXCipher m_Cipher;

    // (CGXDLMSBase)
#if defined(_WIN32) || defined(_WIN64)//If Windows
    SOCKET m_ServerSocket;
    HANDLE m_ReceiverThread;
#else //If Linux.
    int m_ServerSocket;
    pthread_t m_ReceiverThread;
#endif

    GX_TRACE_LEVEL m_Trace;
    ///////////////////////////////////////////////////////////////////////////
} CGXDLMSServerLN;

#define CGXDLMSServerLN_Init(p, port, trace) CGXDLMSBase_Init((CGXDLMSBase*) (p), (port), (trace))
#define CGXDLMSServerLN_d(p)                 CGXDLMSBase_d((CGXDLMSBase*) (p))

//Constructor.
extern void CGXDLMSServerLN_(CGXDLMSServerLN* p,
                             CGXDLMSAssociationLogicalName* ln,
                             CGXDLMSIecHdlcSetup* hdlc)
{
    CGXDLMSBase_2((CGXDLMSBase*) p, ln, hdlc);
}

#endif
