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

#ifndef GXAUTHENTICATION_H
#define GXAUTHENTICATION_H

#include "GXDLMSVariant.h"
#include "String.h"

typedef struct
{
    CGXDLMSVariant m_ClientID;
    DLMS_AUTHENTICATION m_Type;
    String m_Password;
} GXAuthentication;

//Constructor.
extern void GXAuthentication_1(GXAuthentication *p);

//Constructor.
extern void GXAuthentication_2(GXAuthentication *p, DLMS_AUTHENTICATION type,
                               String password, CGXDLMSVariant clientID);


    /// <summary>
    /// Authentication type
    /// </summary>
    extern DLMS_AUTHENTICATION GXAuthentication_GetType(GXAuthentication *p);

    /// <summary>
    /// Authentication type
    /// </summary>
    extern void GXAuthentication_SetType(GXAuthentication *p, DLMS_AUTHENTICATION value);

    /// <summary>
    /// Client address.
    /// </summary>
    extern void GXAuthentication_GetClientID(GXAuthentication *p, CGXDLMSVariant *out);

    /// <summary>
    /// Client address.
    /// </summary>
    extern void GXAuthentication_SetClientID(GXAuthentication *p, CGXDLMSVariant value);

    /// <summary>
    /// Get Used password.
    /// </summary>
    extern void GXAuthentication_GetPassword(GXAuthentication *p, String *out);

    /// <summary>
    /// Set Used password.
    /// </summary>
    extern void GXAuthentication_SetPassword(GXAuthentication *p, String value);

    extern void GXAuthentication_d(GXAuthentication *p);

#endif //GXAUTHENTICATION_H
