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

#include "../include/GXDLMSSecureServer.h"

//CGXDLMSSecureServer::CGXDLMSSecureServer(bool UseLogicalNameReferencing,
//    DLMS_INTERFACE_TYPE intefaceType) :
//    CGXDLMSServer(
//        UseLogicalNameReferencing,
//        intefaceType), m_Cipher("ABCDEFGH")
void CGXDLMSSecureServer_1(CGXDLMSSecureServer* p,
                           bool UseLogicalNameReferencing,
                           DLMS_INTERFACE_TYPE intefaceType)
{
    CGXDLMSServer_1((CGXDLMSServer*) p, UseLogicalNameReferencing, intefaceType);

    CGXCipher_2(&p->m_Cipher, "ABCDEFGH");

    p->m_Settings.m_Cipher = &p->m_Cipher;
}

//CGXDLMSSecureServer::CGXDLMSSecureServer(
//    CGXDLMSAssociationLogicalName* ln,
//    CGXDLMSIecHdlcSetup* hdlc) :
//    CGXDLMSServer(
//        ln,
//        hdlc), m_Cipher("ABCDEFGH")
void CGXDLMSSecureServer_2(CGXDLMSSecureServer* p,
                           CGXDLMSAssociationLogicalName* ln,
                           CGXDLMSIecHdlcSetup* hdlc)
{
    CGXDLMSServer_2((CGXDLMSServer*) p, ln, hdlc);

    CGXCipher_2(&p->m_Cipher, "ABCDEFGH");

    p->m_Settings.m_Cipher = &p->m_Cipher;
}

//CGXDLMSSecureServer::CGXDLMSSecureServer(
//    CGXDLMSAssociationLogicalName* ln,
//    CGXDLMSTcpUdpSetup* wrapper) :
//    CGXDLMSServer(
//        ln,
//        wrapper), m_Cipher("ABCDEFGH")
void CGXDLMSSecureServer_3(CGXDLMSSecureServer* p,
                           CGXDLMSAssociationLogicalName* ln,
                           CGXDLMSTcpUdpSetup* wrapper)
{
    CGXDLMSServer_3((CGXDLMSServer*) p, ln, wrapper);

    CGXCipher_2(&p->m_Cipher, "ABCDEFGH");

    p->m_Settings.m_Cipher = &p->m_Cipher;
}

//CGXDLMSSecureServer::CGXDLMSSecureServer(
//    CGXDLMSAssociationShortName* sn,
//    CGXDLMSIecHdlcSetup* hdlc) :
//    CGXDLMSServer(
//        sn,
//        hdlc), m_Cipher("ABCDEFGH")
void CGXDLMSSecureServer_4(CGXDLMSSecureServer* p,
                           CGXDLMSAssociationShortName* sn,
                           CGXDLMSIecHdlcSetup* hdlc)
{
    CGXDLMSServer_4((CGXDLMSServer*) p, sn, hdlc);

    CGXCipher_2(&p->m_Cipher, "ABCDEFGH");

    p->m_Settings.m_Cipher = &p->m_Cipher;
}

//CGXDLMSSecureServer::CGXDLMSSecureServer(
//    CGXDLMSAssociationShortName* sn,
//    CGXDLMSTcpUdpSetup* wrapper) :
//    CGXDLMSServer(
//        sn,
//        wrapper), m_Cipher("ABCDEFGH")
void CGXDLMSSecureServer_5(CGXDLMSSecureServer* p,
                           CGXDLMSAssociationShortName* sn,
                           CGXDLMSTcpUdpSetup* wrapper)
{
    CGXDLMSServer_5((CGXDLMSServer*) p, sn, wrapper);

    CGXCipher_2(&p->m_Cipher, "ABCDEFGH");

    p->m_Settings.m_Cipher = &p->m_Cipher;
}

//CGXDLMSSecureServer::~CGXDLMSSecureServer()
void CGXDLMSSecureServer_d(CGXDLMSSecureServer* p)
{
    CGXCipher_d(&p->m_Cipher);

    CGXDLMSServer_d((CGXDLMSServer*) p);
}

//CGXCipher* CGXDLMSSecureServer::GetCiphering()
CGXCipher* CGXDLMSSecureServer_GetCiphering(CGXDLMSSecureServer* p)
{
    return p->m_Settings.m_Cipher;
}
