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

#ifndef GXDLMSSECURECLIENT_H
#define GXDLMSSECURECLIENT_H

#include "GXDLMSClient.h"
#include <stdbool.h>

typedef struct// class CGXDLMSSecureClient : public CGXDLMSClient
{
    ///////////////////////////////////////////////////////////////////////////
    // (CGXDLMSServer)
    CGXDLMSSettings m_Settings;
    bool m_IsAuthenticationRequired;
    ///////////////////////////////////////////////////////////////////////////

    CGXCipher m_Cipher;

} CGXDLMSSecureClient;

    /////////////////////////////////////////////////////////////////////////////
    //Constructor
    /////////////////////////////////////////////////////////////////////////////
    // Default parameter: bool UseLogicalNameReferencing = true,
    //                    int ClientAddress = 16,
    //                    int ServerAddress = 1,
    //                    DLMS_AUTHENTICATION authentication = DLMS_AUTHENTICATION_NONE,
    //                    const char* password = NULL,
    //                    DLMS_INTERFACE_TYPE intefaceType = DLMS_INTERFACE_TYPE_HDLC
    extern void CGXDLMSSecureClient_(
        CGXDLMSSecureClient* p,
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
    extern void CGXDLMSSecureClient_d(CGXDLMSSecureClient* p);

    /**
     * @return Ciphering settings.
     */
    extern CGXCipher* CGXDLMSSecureClient_GetCiphering(CGXDLMSSecureClient* p);

    /**
    * Encrypt data using Key Encrypting Key.
    *
    * @param kek
    *            Key Encrypting Key, also known as Master key.
    * @param data
    *            Data to encrypt.
    * @return Encrypt data.
    */
    extern int CGXDLMSSecureClient_Encrypt(
        CGXByteBuffer* kek,
        CGXByteBuffer* data,
        CGXByteBuffer* reply);

    /**
    * Decrypt data using Key Encrypting Key.
    *
    * @param kek
    *            Key Encrypting Key, also known as Master key.
    * @param data
    *            Data to decrypt.
    * @return Decrypted data.
    */
    extern int CGXDLMSSecureClient_Decrypt(
        CGXByteBuffer* kek,
        CGXByteBuffer* data,
        CGXByteBuffer* reply);

#endif //GXDLMSCLIENT_H
