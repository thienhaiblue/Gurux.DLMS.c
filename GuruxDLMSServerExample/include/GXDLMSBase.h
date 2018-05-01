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

#ifndef GXDLMSBASE_H_
#define GXDLMSBASE_H_

#if defined(_WIN32) || defined(_WIN64)//Windows includes
#include <Winsock.h> //Add support for sockets	
#endif

#include "../../development/include/GXDLMSSecureServer.h"
#if defined(_WIN32) || defined(_WIN64)//Windows
extern TCHAR DATAFILE[FILENAME_MAX];
extern TCHAR IMAGEFILE[FILENAME_MAX];
#else
extern char DATAFILE[FILENAME_MAX];
extern char IMAGEFILE[FILENAME_MAX];
#endif

typedef struct CGXDLMSBase // class CGXDLMSBase : public CGXDLMSSecureServer
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
    ///////////////////////////////////////////////////////////////////////////

// private:
#if defined(_WIN32) || defined(_WIN64)//If Windows 
    SOCKET m_ServerSocket;
    HANDLE m_ReceiverThread;
#else //If Linux.
    int m_ServerSocket;
    pthread_t m_ReceiverThread;
#endif

// public:
    GX_TRACE_LEVEL m_Trace;
} CGXDLMSBase;

#define CGXDLMSBase_SetMaxReceivePDUSize(p, value)  CGXDLMSServer_SetMaxReceivePDUSize((CGXDLMSServer*) (p), (value))
#define CGXDLMSBase_Reset_2(p)                      CGXDLMSServer_Reset_2((CGXDLMSServer*) (p))
#define CGXDLMSBase_HandleRequest_1(p, data, reply) CGXDLMSServer_HandleRequest_1((CGXDLMSServer*) p, (data), (reply))
#define CGXDLMSBase_GetItems(p)                     CGXDLMSServer_GetItems((CGXDLMSServer*) (p))
#define CGXDLMSBase_Initialize(p)                   CGXDLMSServer_Initialize((CGXDLMSServer*) (p))
#define CGXDLMSBase_GetUseLogicalNameReferencing(p) CGXDLMSServer_GetUseLogicalNameReferencing((CGXDLMSServer*) (p))

/////////////////////////////////////////////////////////////////////////
//Constructor.
/////////////////////////////////////////////////////////////////////////
extern void CGXDLMSBase_2(CGXDLMSBase* p,
                          CGXDLMSAssociationLogicalName* ln,
                          CGXDLMSIecHdlcSetup* hdlc);

extern void CGXDLMSBase_3(CGXDLMSBase* p,
                          CGXDLMSAssociationLogicalName* ln,
                          CGXDLMSTcpUdpSetup* wrapper);

extern void CGXDLMSBase_4(CGXDLMSBase* p,
                          CGXDLMSAssociationShortName* sn,
                          CGXDLMSIecHdlcSetup* hdlc);

extern void CGXDLMSBase_5(CGXDLMSBase* p,
                          CGXDLMSAssociationShortName* sn,
                          CGXDLMSTcpUdpSetup* wrapper);

/////////////////////////////////////////////////////////////////////////
//Destructor.
/////////////////////////////////////////////////////////////////////////
extern void CGXDLMSBase_d(CGXDLMSBase* p);

extern bool CGXDLMSBase_IsConnected(CGXDLMSBase* p);

extern int CGXDLMSBase_GetSocket(CGXDLMSBase* p);

extern int CGXDLMSBase_StartServer(CGXDLMSBase* p, int port);

extern int CGXDLMSBase_StopServer(CGXDLMSBase* p);

extern int CGXDLMSBase_Init(CGXDLMSBase* p, int port, GX_TRACE_LEVEL trace);

extern CGXDLMSObject* CGXDLMSBase_FindObject(
		CGXDLMSBase* p,
        DLMS_OBJECT_TYPE objectType,
        int sn,
        String* ln);

extern void CGXDLMSBase_PreRead(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

extern void CGXDLMSBase_PreWrite(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

extern void CGXDLMSBase_PreAction(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

extern void CGXDLMSBase_PostRead(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

extern void CGXDLMSBase_PostWrite(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

extern void CGXDLMSBase_PostAction(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

extern bool CGXDLMSBase_IsTarget(CGXDLMSBase* p, unsigned long int serverAddress, unsigned long clientAddress);

extern DLMS_SOURCE_DIAGNOSTIC CGXDLMSBase_ValidateAuthentication(
		CGXDLMSBase* p,
        DLMS_AUTHENTICATION authentication,
        CGXByteBuffer* password);

    /**
    * Get attribute access mode.
    *
    * @param arg
    *            Value event argument.
    * @return Access mode.
    * @throws Exception
    *             Server handler occurred exceptions.
    */
extern DLMS_ACCESS_MODE CGXDLMSBase_GetAttributeAccess(CGXDLMSBase* p, CGXDLMSValueEventArg* arg);

    /**
    * Get method access mode.
    *
    * @param arg
    *            Value event argument.
    * @return Method access mode.
    * @throws Exception
    *             Server handler occurred exceptions.
    */
extern DLMS_METHOD_ACCESS_MODE CGXDLMSBase_GetMethodAccess(CGXDLMSBase* p, CGXDLMSValueEventArg* arg);

    /**
    * Accepted connection is made for the server. All initialization is done
    * here.
    */
extern void CGXDLMSBase_Connected(CGXDLMSBase* p, CGXDLMSConnectionEventArgs* connectionInfo);

    /**
     * Client has try to made invalid connection. Password is incorrect.
     *
     * @param connectionInfo
     *            Connection information.
     */
extern void CGXDLMSBase_InvalidConnection(CGXDLMSBase* p, CGXDLMSConnectionEventArgs* connectionInfo);
    /**
     * Server has close the connection. All clean up is made here.
     */
extern void CGXDLMSBase_Disconnected(CGXDLMSBase* p, CGXDLMSConnectionEventArgs* connectionInfo);

    /**
    * Get selected value(s). This is called when example profile generic
    * request current value.
    *
    * @param type
    *            Update type.
    * @param args
    *            Value event arguments.
    */
extern void CGXDLMSBase_PreGet(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

    /**
    * Get selected value(s). This is called when example profile generic
    * request current value.
    *
    * @param type
    *            Update type.
    * @param args
    *            Value event arguments.
    */
extern void CGXDLMSBase_PostGet(CGXDLMSBase* p, Vector* args); // std::vector<CGXDLMSValueEventArg*>&

#endif
