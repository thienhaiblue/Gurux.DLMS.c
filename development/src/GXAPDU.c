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

#include "../include/GXAPDU.h"

const unsigned char LOGICAL_NAME_OBJECT_ID[7] = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01 };
const unsigned char SHORT_NAME_OBJECT_ID[7] = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x02 };
const unsigned char LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING[7] = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x03 };
const unsigned char SHORT_NAME_OBJECT_ID_WITH_CIPHERING[7] = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x04 };

/**
 * Retrieves the string that indicates the level of authentication, if any.
 */
int CGXAPDU_GetAuthenticationString(
    CGXDLMSSettings* settings,
    CGXByteBuffer* data)
{
    // If authentication is used.
    if (settings->m_Authentication != DLMS_AUTHENTICATION_NONE)
    {
        // Add sender ACSE-requirements field component.
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT
            | PDU_TYPE_SENDER_ACSE_REQUIREMENTS);
        CGXByteBuffer_SetUInt8_1(data, 2);
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_BIT_STRING
            | BER_TYPE_OCTET_STRING);
        CGXByteBuffer_SetUInt8_1(data, 0x80);

        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT
            | PDU_TYPE_MECHANISM_NAME);
        // Len
        CGXByteBuffer_SetUInt8_1(data, 7);
        // OBJECT IDENTIFIER
        unsigned char p[] = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, (unsigned char)settings->m_Authentication };
        CGXByteBuffer_Set_1(data, p, 7);
        // Add Calling authentication information.
        CGXByteBuffer *callingAuthenticationValue;
        if (settings->m_Authentication == DLMS_AUTHENTICATION_LOW)
        {
            callingAuthenticationValue = CGXDLMSSettings_GetPassword(settings);
        }
        else
        {
            callingAuthenticationValue = CGXDLMSSettings_GetCtoSChallenge(settings);
        }
        // 0xAC
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLING_AUTHENTICATION_VALUE);
        // Len
        GXHelpers_SetObjectCount(2 + callingAuthenticationValue->m_Size, data);
        // Add authentication information.
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT);
        // Len.
        GXHelpers_SetObjectCount(callingAuthenticationValue->m_Size, data);
        if (callingAuthenticationValue->m_Size != 0)
        {
            CGXByteBuffer_Set_2(data, callingAuthenticationValue, 0, -1);
        }
    }
    return 0;
}

/**
* Code application context name.
*
* @param settings
*            DLMS settings.
* @param data
*            Byte buffer where data is saved.
* @param cipher
*            Is ciphering settings.
*/
int CGXAPDU_GenerateApplicationContextName(
    CGXDLMSSettings* settings,
    CGXByteBuffer* data,
    CGXCipher* cipher)
{
    // Application context name tag
    CGXByteBuffer_SetUInt8_1(data, (BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_APPLICATION_CONTEXT_NAME));
    // Len
    CGXByteBuffer_SetUInt8_1(data, 0x09);
    CGXByteBuffer_SetUInt8_1(data, BER_TYPE_OBJECT_IDENTIFIER);
    // Len
    CGXByteBuffer_SetUInt8_1(data, 0x07);
    bool ciphered = cipher != NULL && CGXCipher_IsCiphered(cipher);
    if (settings->m_UseLogicalNameReferencing)
    {
        if (ciphered)
        {
            CGXByteBuffer_Set_1(data, LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING, sizeof(LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING));
        }
        else
        {
            CGXByteBuffer_Set_1(data, LOGICAL_NAME_OBJECT_ID, sizeof(LOGICAL_NAME_OBJECT_ID));
        }
    }
    else
    {
        if (ciphered)
        {
            CGXByteBuffer_Set_1(data, SHORT_NAME_OBJECT_ID_WITH_CIPHERING, sizeof(SHORT_NAME_OBJECT_ID_WITH_CIPHERING));
        }
        else
        {
            CGXByteBuffer_Set_1(data, SHORT_NAME_OBJECT_ID, sizeof(SHORT_NAME_OBJECT_ID));
        }
    }
    // Add system title.
    if (!settings->m_Server &&
        (ciphered || settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_GMAC))
    {
        if (CGXCipher_GetSystemTitle(cipher)->m_Size == 0)
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        // Add calling-AP-title
        CGXByteBuffer_SetUInt8_1(data, (BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | 6));
        // LEN
        GXHelpers_SetObjectCount(2 + CGXCipher_GetSystemTitle(cipher)->m_Size, data);
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_OCTET_STRING);
        // LEN
        GXHelpers_SetObjectCount(CGXCipher_GetSystemTitle(cipher)->m_Size, data);
        CGXByteBuffer_Set_1(data, CGXCipher_GetSystemTitle(cipher)->m_Data, CGXCipher_GetSystemTitle(cipher)->m_Size);
    }
    return 0;
}

/**
 * Generate User information initiate request.
 *
 * @param settings
 *            DLMS settings.
 * @param cipher
 * @param data
 */
int CGXAPDU_GetInitiateRequest(
    CGXDLMSSettings* settings,
    CGXCipher* cipher, CGXByteBuffer* data)
{
    // Tag for xDLMS-Initiate request
    CGXByteBuffer_SetUInt8_1(data, DLMS_COMMAND_INITIATE_REQUEST);
    // Usage field for the response allowed component.

    // Usage field for dedicated-key component. Not used
    CGXByteBuffer_SetUInt8_1(data, 0x00);

    // encoding of the response-allowed component (bool DEFAULT TRUE)
    // usage flag (FALSE, default value TRUE conveyed)
    CGXByteBuffer_SetUInt8_1(data, 0);

    // Usage field of the proposed-quality-of-service component. Not used
    CGXByteBuffer_SetUInt8_1(data, 0x00);
    CGXByteBuffer_SetUInt8_1(data, settings->m_DlmsVersionNumber);
    // Tag for conformance block
    CGXByteBuffer_SetUInt8_1(data, 0x5F);
    CGXByteBuffer_SetUInt8_1(data, 0x1F);
    // length of the conformance block
    CGXByteBuffer_SetUInt8_1(data, 0x04);
    // encoding the number of unused bits in the bit string
    CGXByteBuffer_SetUInt8_1(data, 0x00);
    //Add conformance block.
    CGXByteBuffer bb;
    CGXByteBuffer_2(&bb, 4);

    CGXByteBuffer_SetUInt32(&bb, (unsigned long)(settings->m_ProposedConformance));
    CGXByteBuffer_Set_2(data, &bb, 1, 3);
    CGXByteBuffer_SetUInt16(data, settings->m_MaxReceivePDUSize);

    CGXByteBuffer_d(&bb);
    return 0;
}

int CGXAPDU_GenerateUserInformation(
    CGXDLMSSettings* settings,
    CGXCipher* cipher,
    CGXByteBuffer* encryptedData,
    CGXByteBuffer* data)
{
    int ret;
    CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_USER_INFORMATION);
    if (cipher == NULL || !CGXCipher_IsCiphered(cipher))
    {
        // Length for AARQ user field
        CGXByteBuffer_SetUInt8_1(data, 0x10);
        // Coding the choice for user-information (Octet STRING, universal)
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_OCTET_STRING);
        // Length
        CGXByteBuffer_SetUInt8_1(data, 0x0E);
        if ((ret = CGXAPDU_GetInitiateRequest(settings, cipher, data)) != 0)
        {
            return ret;
        }
    }
    else
    {
        if (encryptedData != NULL && encryptedData->m_Size != 0)
        {
            //Length for AARQ user field
            CGXByteBuffer_SetUInt8_1(data, (unsigned char)(4 + encryptedData->m_Size));
            //Tag
            CGXByteBuffer_SetUInt8_1(data, BER_TYPE_OCTET_STRING);
            CGXByteBuffer_SetUInt8_1(data, (unsigned char)(2 + encryptedData->m_Size));
            //Coding the choice for user-information (Octet STRING, universal)
            CGXByteBuffer_SetUInt8_1(data, DLMS_COMMAND_GLO_INITIATE_REQUEST);
            CGXByteBuffer_SetUInt8_1(data, (unsigned char)encryptedData->m_Size);
            CGXByteBuffer_Set_2(data, encryptedData, 0, -1);
        }
        else
        {
            CGXByteBuffer tmp, crypted;
            CGXByteBuffer_1(&tmp);
            CGXByteBuffer_1(&crypted);

            if ((ret = CGXAPDU_GetInitiateRequest(settings, cipher, &tmp)) != 0)
            {
                CGXByteBuffer_d(&tmp);
                CGXByteBuffer_d(&crypted);
                return ret;
            }
            if ((ret = CGXCipher_Encrypt(cipher, cipher->m_Security,
                DLMS_COUNT_TYPE_PACKET,
                settings->m_Cipher->m_FrameCounter,
                DLMS_COMMAND_GLO_INITIATE_REQUEST,
                CGXCipher_GetSystemTitle(cipher),
                &tmp,
                &crypted)) != 0)
            {
                CGXByteBuffer_d(&tmp);
                CGXByteBuffer_d(&crypted);
                return ret;
            }
            // Length for AARQ user field
            GXHelpers_SetObjectCount(2 + crypted.m_Size, data);
            // Coding the choice for user-information (Octet string, universal)
            CGXByteBuffer_SetUInt8_1(data, BER_TYPE_OCTET_STRING);
            GXHelpers_SetObjectCount(crypted.m_Size, data);
            CGXByteBuffer_Set_2(data, &crypted, 0, -1);

            CGXByteBuffer_d(&tmp);
            CGXByteBuffer_d(&crypted);
        }
    }
    return 0;
}



/**
 * Parse User Information from PDU.
 */
int CGXAPDU_ParseUserInformation(
    CGXDLMSSettings* settings,
    CGXCipher* cipher,
    CGXByteBuffer* data)
{
    int ret;
    unsigned short pduSize;
    unsigned char ch, len, tag;
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
    {
        return ret;
    }
    if (data->m_Size - data->m_Position < len)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    // Encoding the choice for user information
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
    {
        return ret;
    }
    if (tag != 0x4)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
    {
        return ret;
    }
    // Tag for xDLMS-Initate.response
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
    {
        return ret;
    }
    if (tag == DLMS_COMMAND_GLO_INITIATE_RESPONSE)
    {
        CGXByteBuffer_SetPosition(data, data->m_Position - 1);
        DLMS_SECURITY security = DLMS_SECURITY_NONE;
        if ((ret = CGXCipher_Decrypt(cipher, CGXDLMSSettings_GetSourceSystemTitle(settings), data, &security)) != 0)
        {
            return ret;
        }
        cipher->m_Security = security;
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
        {
            return ret;
        }
    }
    else if (tag == DLMS_COMMAND_GLO_INITIATE_REQUEST)
    {
        CGXByteBuffer_SetPosition(data, data->m_Position - 1);
        // InitiateRequest
        DLMS_SECURITY security = DLMS_SECURITY_NONE;
        if ((ret = CGXCipher_Decrypt(cipher, CGXDLMSSettings_GetSourceSystemTitle(settings), data, &security)) != 0)
        {
            return ret;
        }
        cipher->m_Security = security;
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
        {
            return ret;
        }
    }
    bool response = tag == DLMS_COMMAND_INITIATE_RESPONSE;
    if (response)
    {
        // Optional usage field of the negotiated quality of service
        // component
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
        {
            return ret;
        }
        if (tag != 0)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
            {
                return ret;
            }
            CGXByteBuffer_SetPosition(data, data->m_Position + len);
        }
    }
    else if (tag == DLMS_COMMAND_INITIATE_REQUEST)
    {
        // Optional usage field of the negotiated quality of service
        // component
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
        {
            return ret;
        }
        // CtoS.
        if (tag != 0)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
            {
                return ret;
            }
            CGXByteBuffer tmp;
            CGXByteBuffer_1(&tmp);

            CGXByteBuffer_Set_2(&tmp, data, data->m_Position, -1);
            CGXDLMSSettings_SetCtoSChallenge(settings, &tmp);

            CGXByteBuffer_d(&tmp);
        }
        // Optional usage field of the negotiated quality of service
        // component
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
        {
            return ret;
        }
        // Skip if used.
        if (tag != 0)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
            {
                return ret;
            }
            CGXByteBuffer_SetPosition(data, data->m_Position + len);
        }
        // Optional usage field of the proposed quality of service component
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
        {
            return ret;
        }
        // Skip if used.
        if (tag != 0)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
            {
                return ret;
            }
            CGXByteBuffer_SetPosition(data, data->m_Position + len);
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    // Get DLMS version number.
    if (settings->m_Server)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            return ret;
        }
        settings->m_DlmsVersionNumber = ch;
    }
    else
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            return ret;
        }
        if (ch != 6)
        {
            //Invalid DLMS version number.
            return DLMS_ERROR_CODE_INVALID_VERSION_NUMBER;
        }
    }

    // Tag for conformance block
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
    {
        return ret;
    }
    if (tag != 0x5F)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    // Old Way...
    if ((ret = CGXByteBuffer_GetUInt8_2(data, data->m_Position, &tag)) != 0)
    {
        return ret;
    }
    if (tag == 0x1F)
    {
        CGXByteBuffer_SetPosition(data, data->m_Position + 1);
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
    {
        return ret;
    }
    // The number of unused bits in the bit string.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &tag)) != 0)
    {
        return ret;
    }
    unsigned long v;
    unsigned char tmp[3];

    CGXByteBuffer bb;
    CGXByteBuffer_2(&bb, 4);

    CGXByteBuffer_Get(data, tmp, 3);
    CGXByteBuffer_SetUInt8_1(&bb, 0);
    CGXByteBuffer_Set_1(&bb, tmp, 3);
    CGXByteBuffer_GetUInt32_1(&bb, &v);

    CGXByteBuffer_d(&bb);

    if (settings->m_Server)
    {
        v &= settings->m_ProposedConformance;
        settings->m_NegotiatedConformance = (DLMS_CONFORMANCE)v;
    }
    else
    {
        settings->m_NegotiatedConformance = (DLMS_CONFORMANCE)v;
    }

    if (settings->m_Server)
    {
        if ((ret = CGXByteBuffer_GetUInt16_1(data, &pduSize)) != 0)
        {
            return ret;
        }
        //If client asks too high PDU.
        if (pduSize > settings->m_MaxServerPDUSize)
        {
            pduSize = settings->m_MaxServerPDUSize;
        }
        CGXDLMSSettings_SetMaxReceivePDUSize(settings, pduSize);
    }
    else
    {
        if ((ret = CGXByteBuffer_GetUInt16_1(data, &pduSize)) != 0)
        {
            return ret;
        }
        CGXDLMSSettings_SetMaxReceivePDUSize(settings, pduSize);
    }
    if (response)
    {
        // VAA Name
        unsigned short vaa;
        if ((ret = CGXByteBuffer_GetUInt16_1(data, &vaa)) != 0)
        {
            return ret;
        }
        if (vaa == 0x0007)
        {
            // If LN
            if (!settings->m_UseLogicalNameReferencing)
            {
                //Invalid VAA.
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
        }
        else if (vaa == 0xFA00)
        {
            // If SN
            if (settings->m_UseLogicalNameReferencing)
            {
                //Invalid VAA.
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
        }
        else
        {
            // Unknown VAA.
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    return 0;
}

/**
 * Parse application context name.
 *
 * @param settings
 *            DLMS settings.
 * @param buff
 *            Received data.
 */
int CGXAPDU_ParseApplicationContextName(
    CGXDLMSSettings* settings,
    CGXByteBuffer* buff)
{
    int ret;
    unsigned char len, ch;
    // Get length.
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
    {
        return ret;
    }
    if (buff->m_Size - buff->m_Position < len)
    {
        //Encoding failed. Not enough data.
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x6)
    {
        //Encoding failed. Not an Object ID.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (settings->m_Server && settings->m_Cipher != NULL)
    {
        settings->m_Cipher->m_Security = DLMS_SECURITY_NONE;
    }
    // Object ID length.
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
    {
        return ret;
    }
    if (settings->m_UseLogicalNameReferencing)
    {
        if (CGXByteBuffer_Compare(buff, (unsigned char*)LOGICAL_NAME_OBJECT_ID, sizeof(LOGICAL_NAME_OBJECT_ID)))
        {
            return 0;
        }
        // If ciphering is used.
        if (!CGXByteBuffer_Compare(buff, (unsigned char*)LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING, sizeof(LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING)))
        {
            return DLMS_ERROR_CODE_FALSE;
        }
        else
        {
            return 0;
        }
    }
    if (CGXByteBuffer_Compare(buff, (unsigned char*)SHORT_NAME_OBJECT_ID, sizeof(SHORT_NAME_OBJECT_ID)))
    {
        return 0;
    }
    // If ciphering is used.
    if (!CGXByteBuffer_Compare(buff, (unsigned char*)SHORT_NAME_OBJECT_ID_WITH_CIPHERING, sizeof(SHORT_NAME_OBJECT_ID_WITH_CIPHERING)))
    {
        return DLMS_ERROR_CODE_FALSE;
    }
    return 0;
}

int CGXAPDU_ValidateAare(
    CGXDLMSSettings* settings,
    CGXByteBuffer* buff)
{
    int ret;
    unsigned char tag;
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
    {
        return ret;
    }
    if (settings->m_Server)
    {
        if (tag != (BER_TYPE_APPLICATION
            | BER_TYPE_CONSTRUCTED
            | PDU_TYPE_PROTOCOL_VERSION))
        {
            return DLMS_ERROR_CODE_INVALID_TAG;
        }
    }
    else
    {
        if (tag != (BER_TYPE_APPLICATION
            | BER_TYPE_CONSTRUCTED
            | PDU_TYPE_APPLICATION_CONTEXT_NAME))
        {
            return DLMS_ERROR_CODE_INVALID_TAG;
        }
    }
    return 0;
}

int CGXAPDU_UpdatePassword(
    CGXDLMSSettings* settings,
    CGXByteBuffer* buff)
{
    CGXByteBuffer tmp;
    CGXByteBuffer_1(&tmp);

    int ret;
    unsigned char ch, len;
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
    {
        CGXByteBuffer_d(&tmp);
        return ret;
    }

    // Get authentication information.
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        CGXByteBuffer_d(&tmp);
        return ret;
    }
    if (ch != 0x80)
    {
        CGXByteBuffer_d(&tmp);
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
    {
        CGXByteBuffer_d(&tmp);
        return ret;
    }
    CGXByteBuffer_Set_2(&tmp, buff, buff->m_Position, len);
    if (settings->m_Authentication == DLMS_AUTHENTICATION_LOW)
    {
        CGXDLMSSettings_SetPassword(settings, &tmp);
    }
    else
    {
        CGXDLMSSettings_SetCtoSChallenge(settings, &tmp);
    }

    CGXByteBuffer_d(&tmp);
    return 0;
}

int CGXAPDU_UpdateAuthentication(
    CGXDLMSSettings* settings,
    CGXByteBuffer* buff)
{
    int ret;
    unsigned char ch;
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }

    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x60)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x85)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x74)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x05)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x08)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x02)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch > DLMS_AUTHENTICATION_HIGH_SHA256)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    settings->m_Authentication = (DLMS_AUTHENTICATION)ch;
    return 0;
}

int CGXAPDU_GetUserInformation(
    CGXDLMSSettings* settings,
    CGXCipher* cipher,
    CGXByteBuffer* data)
{
    CGXByteBuffer_Clear(data);
    CGXByteBuffer_SetUInt8_1(data, DLMS_COMMAND_INITIATE_RESPONSE); // Tag for xDLMS-Initiate
    // response
    // Usage field for the response allowed component.// (not used)
    CGXByteBuffer_SetUInt8_1(data, 0x00);
    // DLMS Version Number
    CGXByteBuffer_SetUInt8_1(data, 06);
    CGXByteBuffer_SetUInt8_1(data, 0x5F);
    CGXByteBuffer_SetUInt8_1(data, 0x1F);
    // length of the conformance block
    CGXByteBuffer_SetUInt8_1(data, 0x04);
    // encoding the number of unused bits in the bit string
    CGXByteBuffer_SetUInt8_1(data, 0x00);

    CGXByteBuffer bb;
    CGXByteBuffer_2(&bb, 4);

    CGXByteBuffer_SetUInt32(&bb, (unsigned long)settings->m_NegotiatedConformance);
    CGXByteBuffer_Set_2(data, &bb, 1, 3);

    CGXByteBuffer_d(&bb);

    CGXByteBuffer_SetUInt16(data, settings->m_MaxReceivePDUSize);
    // VAA Name VAA name (0x0007 for LN referencing and 0xFA00 for SN)
    if (settings->m_UseLogicalNameReferencing)
    {
        CGXByteBuffer_SetUInt16(data, 0x0007);
    }
    else
    {
        CGXByteBuffer_SetUInt16(data, 0xFA00);
    }
    if (cipher != NULL && CGXCipher_IsCiphered(cipher))
    {
        CGXByteBuffer tmp;
        CGXByteBuffer_3(&tmp, data);

        CGXByteBuffer_Clear(data);

        int t_Res = CGXCipher_Encrypt(cipher, cipher->m_Security,
                DLMS_COUNT_TYPE_PACKET,
                settings->m_Cipher->m_FrameCounter,
                DLMS_COMMAND_GLO_INITIATE_RESPONSE,
                CGXCipher_GetSystemTitle(cipher),
                &tmp,
                data);

        CGXByteBuffer_d(&tmp);
        return t_Res;
    }
    return 0;
}

int CGXAPDU_GenerateAarq(
    CGXDLMSSettings* settings,
    CGXCipher* cipher,
    CGXByteBuffer* encryptedData,
    CGXByteBuffer* data)
{
    int ret;
    // AARQ APDU Tag
    CGXByteBuffer_SetUInt8_1(data, BER_TYPE_APPLICATION | BER_TYPE_CONSTRUCTED);
    // Length is updated later.
    unsigned long offset = data->m_Size;
    CGXByteBuffer_SetUInt8_1(data, 0);
    ///////////////////////////////////////////
    // Add Application context name.
    if ((ret = CGXAPDU_GenerateApplicationContextName(settings, data, cipher)) != 0)
    {
        return ret;
    }
    if ((ret = CGXAPDU_GetAuthenticationString(settings, data)) != 0)
    {
        return ret;
    }
    if ((ret = CGXAPDU_GenerateUserInformation(settings, cipher, encryptedData, data)) != 0)
    {
        return ret;
    }
    CGXByteBuffer_SetUInt8_2(data, offset, (unsigned char)(data->m_Size - offset - 1));
    return 0;
}

int CGXAPDU_handleResultComponent(DLMS_SOURCE_DIAGNOSTIC value)
{
    int ret;
    switch ((int)value)
    {
    case DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN:
        ret = DLMS_ERROR_CODE_NO_REASON_GIVEN;
        break;
    case DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED:
        ret = DLMS_ERROR_CODE_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
        break;
    case DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_MECHANISM_NAME_NOT_RECOGNISED:
        ret = DLMS_ERROR_CODE_AUTHENTICATION_MECHANISM_NAME_NOT_RECOGNISED;
        break;
    case DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_MECHANISM_NAME_REQUIRED:
        ret = DLMS_ERROR_CODE_AUTHENTICATION_MECHANISM_NAME_REQUIRED;
        break;
    case DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE:
        ret = DLMS_ERROR_CODE_AUTHENTICATION_FAILURE;
        break;
    default:
        //OK.
        ret = 0;
        break;
    }
    return ret;
}

int CGXAPDU_ParsePDU(
    CGXDLMSSettings* settings,
    CGXCipher* cipher,
    CGXByteBuffer* buff,
    DLMS_ASSOCIATION_RESULT* result,
    DLMS_SOURCE_DIAGNOSTIC* diagnostic)
{
    unsigned long len2;
    unsigned char tag, len;
    int ret;
    *diagnostic = DLMS_SOURCE_DIAGNOSTIC_NONE;
    // Get AARE tag and length
    if ((ret = CGXAPDU_ValidateAare(settings, buff)) != 0)
    {
        return ret;
    }
    if ((ret = GXHelpers_GetObjectCount(buff, &len2)) != 0)
    {
        return ret;
    }
    unsigned int size = buff->m_Size - buff->m_Position;
    if (len2 > size)
    {
        //Encoding failed. Not enough data.
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *result = DLMS_ASSOCIATION_RESULT_ACCEPTED;

    while (buff->m_Position < buff->m_Size)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
        {
            return ret;
        }

        CGXByteBuffer tmp;

        switch (tag)
        {
            //0xA1
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_APPLICATION_CONTEXT_NAME:
        {
            if ((ret = CGXAPDU_ParseApplicationContextName(settings, buff)) != 0)
            {
                return DLMS_ERROR_CODE_REJECTED_PERMAMENT;
            }
        }
        break;
        // 0xA2
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLED_AP_TITLE:
            // Get len.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            if (len != 3)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            // Choice for result (INTEGER, universal)

            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            if (tag != BER_TYPE_INTEGER)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            // Get len.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            if (len != 1)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            *result = (DLMS_ASSOCIATION_RESULT)tag;
            break;
            // 0xA3 SourceDiagnostic
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLED_AE_QUALIFIER:
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            // ACSE service user tag.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            // Result source diagnostic component.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            if (tag != BER_TYPE_INTEGER)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            if (len != 1)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            *diagnostic = (DLMS_SOURCE_DIAGNOSTIC)tag;
            break;
            // 0xA4 Result
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLED_AP_INVOCATION_ID:
            // Get len.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            if (len != 0xA)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            // Choice for result (Universal, Octet string type)
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            if (tag != BER_TYPE_OCTET_STRING)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            // responding-AP-title-field
            // Get len.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }

            CGXByteBuffer_1(&tmp);

            CGXByteBuffer_Clear(&tmp);
            CGXByteBuffer_Set_2(&tmp, buff, buff->m_Position, len);
            CGXDLMSSettings_SetSourceSystemTitle(settings, &tmp);

            CGXByteBuffer_d(&tmp);

            break;
            // 0xA6 Client system title.
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLING_AP_TITLE:
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }

            CGXByteBuffer_1(&tmp);

            CGXByteBuffer_Clear(&tmp);
            CGXByteBuffer_Set_2(&tmp, buff, buff->m_Position, len);
            CGXDLMSSettings_SetSourceSystemTitle(settings, &tmp);

            CGXByteBuffer_d(&tmp);

            break;
            // 0xAA Server system title.
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_SENDER_ACSE_REQUIREMENTS:
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }

            CGXByteBuffer_1(&tmp);

            CGXByteBuffer_Clear(&tmp);
            CGXByteBuffer_Set_2(&tmp, buff, buff->m_Position, len);
            CGXDLMSSettings_SetStoCChallenge(settings, &tmp);

            CGXByteBuffer_d(&tmp);

            break;
            //  0x8A or 0x88
        case BER_TYPE_CONTEXT | PDU_TYPE_SENDER_ACSE_REQUIREMENTS:
        case BER_TYPE_CONTEXT | PDU_TYPE_CALLING_AP_INVOCATION_ID:
            // Get sender ACSE-requirements field component.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
            {
                return ret;
            }
            if (len != 2)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            if (tag != BER_TYPE_OBJECT_DESCRIPTOR)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            //Get only value because client app is sending system title with LOW authentication.
            if ((ret = CGXByteBuffer_GetUInt8_1(buff, &tag)) != 0)
            {
                return ret;
            }
            break;
            //  0x8B or 0x89
        case BER_TYPE_CONTEXT | PDU_TYPE_MECHANISM_NAME:
        case BER_TYPE_CONTEXT | PDU_TYPE_CALLING_AE_INVOCATION_ID:
            if ((ret = CGXAPDU_UpdateAuthentication(settings, buff)) != 0)
            {
                return ret;
            }
            break;
            // 0xAC
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLING_AUTHENTICATION_VALUE:
            if ((ret = CGXAPDU_UpdatePassword(settings, buff)) != 0)
            {
                return ret;
            }
            break;
            // 0xBE
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_USER_INFORMATION:
            //Check result component. Some meters are returning invalid user-information if connection failed.
            if (*result != DLMS_ASSOCIATION_RESULT_ACCEPTED
                && *diagnostic != DLMS_SOURCE_DIAGNOSTIC_NONE)
            {
                return CGXAPDU_handleResultComponent(*diagnostic);
            }
            if ((ret = CGXAPDU_ParseUserInformation(settings, cipher, buff)) != 0)
            {
                *result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                *diagnostic = DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN;
                return 0;
            }
            break;
        default:
            // Unknown tags.
            if (buff->m_Position < buff->m_Size)
            {
                if ((ret = CGXByteBuffer_GetUInt8_1(buff, &len)) != 0)
                {
                    return ret;
                }
                CGXByteBuffer_SetPosition(buff, buff->m_Position + len);
            }
            break;
        }
    }
    //All meters don't send user-information if connection is failed.
    //For this reason result component is check again.
    return CGXAPDU_handleResultComponent(*diagnostic);
}

/**
 * Server generates AARE message.
 */
int CGXAPDU_GenerateAARE(
    CGXDLMSSettings* settings,
    CGXByteBuffer* data,
    DLMS_ASSOCIATION_RESULT result,
    DLMS_SOURCE_DIAGNOSTIC diagnostic,
    CGXCipher* cipher,
    CGXByteBuffer *errorData,
    CGXByteBuffer *encryptedData)
{
    int ret;
    unsigned long offset = data->m_Size;
    // Set AARE tag and length 0x61
    CGXByteBuffer_SetUInt8_1(data, BER_TYPE_APPLICATION | BER_TYPE_CONSTRUCTED | PDU_TYPE_APPLICATION_CONTEXT_NAME);
    // Length is updated later.
    CGXByteBuffer_SetUInt8_1(data, 0);
    if ((ret = CGXAPDU_GenerateApplicationContextName(settings, data, cipher)) != 0)
    {
        return ret;
    }
    // Result 0xA2
    CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | BER_TYPE_INTEGER);
    CGXByteBuffer_SetUInt8_1(data, 3); // len
    // Tag
    CGXByteBuffer_SetUInt8_1(data, BER_TYPE_INTEGER);
    // Choice for result (INTEGER, universal)
    CGXByteBuffer_SetUInt8_1(data, 1); // Len
    // ResultValue
    CGXByteBuffer_SetUInt8_1(data, result);
    // SourceDiagnostic
    CGXByteBuffer_SetUInt8_1(data, 0xA3);
    CGXByteBuffer_SetUInt8_1(data, 5); // len
    CGXByteBuffer_SetUInt8_1(data, 0xA1); // Tag
    CGXByteBuffer_SetUInt8_1(data, 3); // len
    CGXByteBuffer_SetUInt8_1(data, 2); // Tag
    // Choice for result (INTEGER, universal)
    CGXByteBuffer_SetUInt8_1(data, 1); // Len
    // diagnostic
    CGXByteBuffer_SetUInt8_1(data, diagnostic);
    // SystemTitle
    if (cipher != NULL
        && (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_GMAC
            || CGXCipher_IsCiphered(cipher)))
    {
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLED_AP_INVOCATION_ID);
        GXHelpers_SetObjectCount(2 + CGXCipher_GetSystemTitle(cipher)->m_Size, data);
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_OCTET_STRING);
        GXHelpers_SetObjectCount(CGXCipher_GetSystemTitle(cipher)->m_Size, data);
        CGXByteBuffer_Set_2(data, CGXCipher_GetSystemTitle(cipher), 0, -1);
    }
    if (settings->m_Authentication > DLMS_AUTHENTICATION_LOW)
    {
        // Add server ACSE-requirenents field component.
        CGXByteBuffer_SetUInt8_1(data, 0x88);
        CGXByteBuffer_SetUInt8_1(data, 0x02); // Len.
        CGXByteBuffer_SetUInt16(data, 0x0780);
        // Add tag.
        CGXByteBuffer_SetUInt8_1(data, 0x89);
        CGXByteBuffer_SetUInt8_1(data, 0x07); // Len
        CGXByteBuffer_SetUInt8_1(data, 0x60);
        CGXByteBuffer_SetUInt8_1(data, 0x85);
        CGXByteBuffer_SetUInt8_1(data, 0x74);
        CGXByteBuffer_SetUInt8_1(data, 0x05);
        CGXByteBuffer_SetUInt8_1(data, 0x08);
        CGXByteBuffer_SetUInt8_1(data, 0x02);
        CGXByteBuffer_SetUInt8_1(data, settings->m_Authentication);
        // Add tag.
        CGXByteBuffer_SetUInt8_1(data, 0xAA);
        GXHelpers_SetObjectCount(2 + CGXDLMSSettings_GetStoCChallenge(settings)->m_Size, data); // Len
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT);
        GXHelpers_SetObjectCount(CGXDLMSSettings_GetStoCChallenge(settings)->m_Size, data);
        CGXByteBuffer_Set_1(data, CGXDLMSSettings_GetStoCChallenge(settings)->m_Data, CGXDLMSSettings_GetStoCChallenge(settings)->m_Size);
    }
    if (result == DLMS_ASSOCIATION_RESULT_ACCEPTED || cipher == NULL || cipher->m_Security == DLMS_SECURITY_NONE)
    {
        // Add User Information. Tag 0xBE
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_USER_INFORMATION);

        CGXByteBuffer tmp;
        CGXByteBuffer_1(&tmp);

        if (encryptedData != NULL && encryptedData->m_Size != 0)
        {
            CGXByteBuffer_Capacity_2(&tmp, 2 + encryptedData->m_Size);
            CGXByteBuffer_SetUInt8_1(&tmp, DLMS_COMMAND_GLO_INITIATE_RESPONSE);
            GXHelpers_SetObjectCount(encryptedData->m_Size, &tmp);
            CGXByteBuffer_Set_2(&tmp, encryptedData, 0, -1);
        }
        else
        {
            if (errorData != NULL && errorData->m_Size != 0)
            {
                CGXByteBuffer_Set_2(&tmp, errorData, 0, -1);
            }
            else
            {
                if ((ret = CGXAPDU_GetUserInformation(settings, cipher, &tmp)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
            }
        }

        GXHelpers_SetObjectCount(2 + tmp.m_Size, data);
        // Coding the choice for user-information (Octet STRING, universal)
        CGXByteBuffer_SetUInt8_1(data, BER_TYPE_OCTET_STRING);
        // Length
        GXHelpers_SetObjectCount(tmp.m_Size, data);
        CGXByteBuffer_Set_2(data, &tmp, 0, -1);

        CGXByteBuffer_d(&tmp);
    }
    CGXByteBuffer_SetUInt8_2(data, offset + 1, (unsigned char)(data->m_Size - offset - 2));
    return 0;
}
