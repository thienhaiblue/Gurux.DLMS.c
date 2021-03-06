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

#ifndef GXSECURE_H
#define GXSECURE_H

#include "../include/enums.h"
#include "../include/GXBytebuffer.h"
#include "../include/GXDLMSSettings.h"

/**
* Generates challenge.
*
* @param authentication
*            Used authentication.
* @return Generated challenge.
*/
extern int CGXSecure_GenerateChallenge(
    DLMS_AUTHENTICATION authentication,
    CGXByteBuffer* challenge);

/**
* Chipher text.
*
* @param auth
*            Authentication level.
* @param data
*            Text to chipher.
* @param secret
*            Secret.
* @return Chiphered text.
*/
extern int CGXSecure_Secure(
    CGXDLMSSettings* settings,
    CGXCipher* cipher,
    unsigned long ic,
    CGXByteBuffer* data,
    CGXByteBuffer* secret,
    CGXByteBuffer* reply);

#endif //GXSECURE_H