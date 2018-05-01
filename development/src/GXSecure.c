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

#include "../include/GXSecure.h"
#include "../include/GXDLMSMd5.h"
#include "../include/GXDLMSSha1.h"
#include "../include/GXDLMSSha256.h"

#include <stdlib.h> //rand

int CGXSecure_GenerateChallenge(DLMS_AUTHENTICATION authentication, CGXByteBuffer* challenge)
{
    // Random challenge is 8 to 64 bytes.
    // Texas Instruments accepts only 16 byte long challenge.
    // For this reason challenge size is 16 bytes at the moment.
    int len = 16;
    //int len = rand() % 58 + 8;
    unsigned char val;
    for (int pos = 0; pos != len; ++pos)
    {
        val = rand();
        CGXByteBuffer_SetUInt8_1(challenge, val);
    }
    return 0;
}

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
int CGXSecure_Secure(
    CGXDLMSSettings* settings,
    CGXCipher* cipher,
    unsigned long ic,
    CGXByteBuffer* data,
    CGXByteBuffer* secret,
    CGXByteBuffer* reply)
{
    int ret = 0, pos;
    CGXByteBuffer_Clear(reply);
    if (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH)
    {
        CGXByteBuffer s;
        CGXByteBuffer_1(&s);

        int len = data->m_Size;
        if (len % 16 != 0)
        {
            len += (16 - (data->m_Size % 16));
        }
        if (secret->m_Size > data->m_Size)
        {
            len = secret->m_Size;
            if (len % 16 != 0)
            {
                len += (16 - (secret->m_Size % 16));
            }
        }
        CGXByteBuffer_Set_2(&s, secret, 0, -1);
        CGXByteBuffer_Zero(&s, s.m_Size, len - s.m_Size);
        CGXByteBuffer_Set_2(reply, data, 0, -1);
        CGXByteBuffer_Zero(reply, reply->m_Size, len - reply->m_Size);
        for (pos = 0; pos < len / 16; ++pos)
        {
            CGXCipher_Aes1Encrypt(reply, pos * 16, &s);
        }

        CGXByteBuffer_d(&s);
        return 0;
    }

    // Get server Challenge.
    CGXByteBuffer challenge;
    CGXByteBuffer_1(&challenge);

    int t_res;
    // Get shared secret
    if (settings->m_Authentication != DLMS_AUTHENTICATION_HIGH_GMAC)
    {
        CGXByteBuffer_Set_2(&challenge, data, 0, -1);
        CGXByteBuffer_Set_2(&challenge, secret, 0, -1);
    }
    if (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_MD5)
    {
        t_res = CGXDLMSMD5_Encrypt(&challenge, reply);

        CGXByteBuffer_d(&challenge);
        return t_res;
    }
    else if (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_SHA1)
    {
        t_res = CGXDLMSSha1_Encrypt(&challenge, reply);

        CGXByteBuffer_d(&challenge);
        return t_res;
    }
    else if (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_SHA256)
    {
        t_res = CGXDLMSSha256_Encrypt(&challenge, reply);

        CGXByteBuffer_d(&challenge);
        return t_res;
    }
    else if (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_GMAC)
    {
        CGXByteBuffer tmp;
        CGXByteBuffer_1(&tmp);

        ret = CGXCipher_Encrypt(cipher, DLMS_SECURITY_AUTHENTICATION,
            DLMS_COUNT_TYPE_TAG, ic, 0, secret, data, &tmp);
        if (ret == 0)
        {
            CGXByteBuffer_SetUInt8_1(reply, DLMS_SECURITY_AUTHENTICATION);
            CGXByteBuffer_SetUInt32(reply, ic);
            CGXByteBuffer_Set_2(reply, &tmp, 0, -1);
        }

        CGXByteBuffer_d(&tmp);
    }

    CGXByteBuffer_d(&challenge);
    return ret;
}
