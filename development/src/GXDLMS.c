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

#include "../include/GXDLMS.h"
#include "../include/GXAPDU.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXBytebuffer.h"

static unsigned char CIPHERING_HEADER_SIZE = 7 + 12 + 3;
//CRC table.
static unsigned short FCS16Table[256] =
{
    0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF,
    0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7,
    0x1081, 0x0108, 0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E,
    0x9CC9, 0x8D40, 0xBFDB, 0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876,
    0x2102, 0x308B, 0x0210, 0x1399, 0x6726, 0x76AF, 0x4434, 0x55BD,
    0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E, 0xFAE7, 0xC87C, 0xD9F5,
    0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E, 0x54B5, 0x453C,
    0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD, 0xC974,
    0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB,
    0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3,
    0x5285, 0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A,
    0xDECD, 0xCF44, 0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72,
    0x6306, 0x728F, 0x4014, 0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9,
    0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5, 0xA96A, 0xB8E3, 0x8A78, 0x9BF1,
    0x7387, 0x620E, 0x5095, 0x411C, 0x35A3, 0x242A, 0x16B1, 0x0738,
    0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862, 0x9AF9, 0x8B70,
    0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E, 0xF0B7,
    0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF,
    0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036,
    0x18C1, 0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E,
    0xA50A, 0xB483, 0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5,
    0x2942, 0x38CB, 0x0A50, 0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD,
    0xB58B, 0xA402, 0x9699, 0x8710, 0xF3AF, 0xE226, 0xD0BD, 0xC134,
    0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7, 0x6E6E, 0x5CF5, 0x4D7C,
    0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1, 0xA33A, 0xB2B3,
    0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72, 0x3EFB,
    0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232,
    0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A,
    0xE70E, 0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1,
    0x6B46, 0x7ACF, 0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9,
    0xF78F, 0xE606, 0xD49D, 0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330,
    0x7BC7, 0x6A4E, 0x58D5, 0x495C, 0x3DE3, 0x2C6A, 0x1EF1, 0x0F78
};

bool CGXDLMS_IsReplyMessage(DLMS_COMMAND cmd)
{
    return cmd == DLMS_COMMAND_GET_RESPONSE ||
        cmd == DLMS_COMMAND_SET_RESPONSE ||
        cmd == DLMS_COMMAND_METHOD_RESPONSE;
}

int CGXDLMS_GetAddress(long value, unsigned long* address, int* size)
{
    if (value < 0x80)
    {
        *address = (unsigned char)(value << 1 | 1);
        *size = 1;
        return 0;
    }
    else if (value < 0x4000)
    {
        *address = (unsigned short)((value & 0x3F80) << 2 | (value & 0x7F) << 1 | 1);
        *size = 2;
    }
    else if (value < 0x10000000)
    {
        *address = (unsigned long)((value & 0xFE00000) << 4 | (value & 0x1FC000) << 3
            | (value & 0x3F80) << 2 | (value & 0x7F) << 1 | 1);
        *size = 4;
    }
    else
    {
        //Invalid address
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_CheckInit(CGXDLMSSettings* settings)
{
    if (settings->m_ClientAddress == 0)
    {
        return DLMS_ERROR_CODE_INVALID_CLIENT_ADDRESS;
    }
    if (settings->m_ServerAddress == 0)
    {
        return DLMS_ERROR_CODE_INVALID_SERVER_ADDRESS;
    }
    return DLMS_ERROR_CODE_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Get data from Block.
/////////////////////////////////////////////////////////////////////////////
// data : Stored data block.
// index : Position where data starts.
// Returns : Amount of removed bytes.
/////////////////////////////////////////////////////////////////////////////
int CGXDLMS_GetDataFromBlock(CGXByteBuffer* data, int index)
{
    if (data->m_Size == data->m_Position)
    {
        CGXByteBuffer_Clear(data);
        return 0;
    }
    int len = data->m_Position - index;
    if (len < 0)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    unsigned long pos = data->m_Position;
    CGXByteBuffer_SetPosition(data, pos - len);
    CGXByteBuffer_Move(data, pos, pos - len, data->m_Size - pos);
    return 0;
}

int CGXDLMS_ReceiverReady(CGXDLMSSettings* settings,
                          DLMS_DATA_REQUEST_TYPES type,
                          CGXCipher* cipher,
                          CGXByteBuffer* reply)
{
    int ret;
    CGXByteBuffer_Clear(reply);
    if (type == DLMS_DATA_REQUEST_TYPES_NONE)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    // Get next frame.
    if ((type & DLMS_DATA_REQUEST_TYPES_FRAME) != 0)
    {
        if ((ret = CGXDLMS_GetHdlcFrame(settings, CGXDLMSSettings_GetReceiverReady(settings),
                                        NULL, reply)) != 0)
        {
            return ret;
        }
        return ret;
    }
    // Get next block.
    DLMS_COMMAND cmd;

    CGXByteBuffer bb;
    CGXByteBuffer_2(&bb, 6);

    Vector tmp;// std::vector<CGXByteBuffer> tmp;
    Vector_(&tmp, sizeof(CGXByteBuffer), CGXByteBuffer_v_c, CGXByteBuffer_v_d);

    if (settings->m_UseLogicalNameReferencing)
    {
        if (settings->m_Server)
        {
            cmd = DLMS_COMMAND_GET_RESPONSE;
        }
        else
        {
            cmd = DLMS_COMMAND_GET_REQUEST;
        }
    }
    else
    {
        if (settings->m_Server)
        {
            cmd = DLMS_COMMAND_READ_RESPONSE;
        }
        else
        {
            cmd = DLMS_COMMAND_READ_REQUEST;
        }
    }
    if (settings->m_UseLogicalNameReferencing)
    {
        CGXByteBuffer_SetUInt32(&bb, settings->m_BlockIndex);
    }
    else
    {
        CGXByteBuffer_SetUInt16(&bb, (unsigned short)settings->m_BlockIndex);
    }
    settings->m_BlockIndex += 1;
    if (settings->m_UseLogicalNameReferencing)
    {
        CGXDLMSLNParameters p;
        CGXDLMSLNParameters_(&p, settings, 0, cmd,
                             DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK, &bb, NULL, 0xff);


        ret = CGXDLMS_GetLnMessages(&p, &tmp);

        //CGXDLMSLNParameters_d(&p);
    }
    else
    {
        CGXDLMSSNParameters p;
        CGXDLMSSNParameters_(&p, settings, cmd, 1,
                             DLMS_VARIABLE_ACCESS_SPECIFICATION_BLOCK_NUMBER_ACCESS,
                             &bb, NULL);

        ret = CGXDLMS_GetSnMessages(&p, &tmp);
    }
    CGXByteBuffer_Set_2(reply, Vector_at(&tmp, 0), 0, -1);

    Vector_d(&tmp);
    CGXByteBuffer_d(&bb);
    return ret;
}

/**
     * Split DLMS PDU to wrapper frames.
     *
     * @param settings
     *            DLMS settings.
     * @param data
     *            Wrapped data.
     * @return Wrapper frames.
*/
int CGXDLMS_GetWrapperFrame(CGXDLMSSettings* settings,
                            CGXByteBuffer* data,
                            CGXByteBuffer* reply)
{
    CGXByteBuffer_Clear(reply);
    // Add version.
    CGXByteBuffer_SetUInt16(reply, 1);
    if (settings->m_Server)
    {
        CGXByteBuffer_SetUInt16(reply, (unsigned short)settings->m_ServerAddress);
        CGXByteBuffer_SetUInt16(reply, (unsigned short)settings->m_ClientAddress);
    }
    else
    {
        CGXByteBuffer_SetUInt16(reply, (unsigned short)settings->m_ClientAddress);
        CGXByteBuffer_SetUInt16(reply, (unsigned short)settings->m_ServerAddress);
    }
    // Data length.
    CGXByteBuffer_SetUInt16(reply, (unsigned short)data->m_Size);
    // Data
    CGXByteBuffer_Set_2(reply, data, data->m_Position, -1);

    // Remove sent data in server side.
    if (settings->m_Server)
    {
        if (data->m_Size == data->m_Position)
        {
            CGXByteBuffer_Clear(data);
        }
        else
        {
            CGXByteBuffer_Move(data, data->m_Position, 0,
                               data->m_Size - data->m_Position);
            CGXByteBuffer_SetPosition(data, 0);
        }
    }
    return DLMS_ERROR_CODE_OK;
}

/**
 * Get HDLC frame for data.
 *
 * @param settings
 *            DLMS settings.
 * @param frame
 *            Frame ID. If zero new is generated.
 * @param data
 *            Data to add.
 * @return HDLC frame.
 */
int CGXDLMS_GetHdlcFrame(CGXDLMSSettings* settings,
                         unsigned char frame,
                         CGXByteBuffer* data,
                         CGXByteBuffer* reply)
{
    CGXByteBuffer_Clear(reply);
    unsigned short frameSize;
    int ret, len = 0;

    CGXByteBuffer primaryAddress, secondaryAddress;
    CGXByteBuffer_1(&primaryAddress);
    CGXByteBuffer_1(&secondaryAddress);

    if (settings->m_Server)
    {
        if ((ret = CGXDLMS_GetAddressBytes(settings->m_ClientAddress,
                                           &primaryAddress)) != 0)
        {
            CGXByteBuffer_d(&primaryAddress);
            CGXByteBuffer_d(&secondaryAddress);
            return ret;
        }
        if ((ret = CGXDLMS_GetAddressBytes(settings->m_ServerAddress,
                                           &secondaryAddress)) != 0)
        {
            CGXByteBuffer_d(&primaryAddress);
            CGXByteBuffer_d(&secondaryAddress);
            return ret;
        }
    }
    else
    {
        if ((ret = CGXDLMS_GetAddressBytes(settings->m_ServerAddress,
                                           &primaryAddress)) != 0)
        {
            CGXByteBuffer_d(&primaryAddress);
            CGXByteBuffer_d(&secondaryAddress);
            return ret;
        }
        if ((ret = CGXDLMS_GetAddressBytes(settings->m_ClientAddress,
                                           &secondaryAddress)) != 0)
        {
            CGXByteBuffer_d(&primaryAddress);
            CGXByteBuffer_d(&secondaryAddress);
            return ret;
        }
    }

    // Add BOP
    CGXByteBuffer_SetUInt8_1(reply, HDLC_FRAME_START_END);
    frameSize = CGXDLMSSettings_GetLimits(settings)->m_MaxInfoTX;
    frameSize -= 11;
    // If no data
    if (data == NULL || data->m_Size == 0)
    {
        CGXByteBuffer_SetUInt8_1(reply, 0xA0);
    }
    else if (data->m_Size - data->m_Position <= frameSize)
    {
        len = data->m_Size - data->m_Position;
        // Is last packet.
        CGXByteBuffer_SetUInt8_1(reply, 0xA0 | (((7 + primaryAddress.m_Size +
            secondaryAddress.m_Size + len) >> 8) & 0x7));
    }
    else
    {
        len = frameSize;
        // More data to left.
        CGXByteBuffer_SetUInt8_1(reply, 0xA8 | ((len >> 8) & 0x7));
    }
    // Frame len.
    if (len == 0)
    {
        CGXByteBuffer_SetUInt8_1(reply, (unsigned char)(5 + primaryAddress.m_Size +
            secondaryAddress.m_Size + len));
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(reply, (unsigned char)(7 + primaryAddress.m_Size +
            secondaryAddress.m_Size + len));
    }
    // Add primary address.
    CGXByteBuffer_Set_2(reply, &primaryAddress, 0, -1);
    // Add secondary address.
    CGXByteBuffer_Set_2(reply, &secondaryAddress, 0, -1);

    // Add frame ID.
    if (frame == 0)
    {
        CGXByteBuffer_SetUInt8_1(reply, CGXDLMSSettings_GetNextSend(settings, 1));
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(reply, frame);
    }
    // Add header CRC.
    int crc = CGXDLMS_CountFCS16(reply, 1, reply->m_Size - 1);
    CGXByteBuffer_SetUInt16(reply, crc);
    if (len != 0)
    {
        // Add data.
        CGXByteBuffer_Set_2(reply, data, data->m_Position, len);
        // Add data CRC.
        crc = CGXDLMS_CountFCS16(reply, 1, reply->m_Size - 1);
        CGXByteBuffer_SetUInt16(reply, crc);
    }
    // Add EOP
    CGXByteBuffer_SetUInt8_1(reply, HDLC_FRAME_START_END);
    // Remove sent data in server side.
    if (settings->m_Server)
    {
        if (data != NULL)
        {
            if (data->m_Size == data->m_Position)
            {
                CGXByteBuffer_Clear(data);
            }
            else
            {
                CGXByteBuffer_Move(data, data->m_Position, 0,
                                   data->m_Size - data->m_Position);
                CGXByteBuffer_SetPosition(data, 0);
            }
        }
    }

    CGXByteBuffer_d(&primaryAddress);
    CGXByteBuffer_d(&secondaryAddress);
    return DLMS_ERROR_CODE_OK;
}

/**
* Get used glo message.
*
* @param command
*            Executed DLMS_COMMAND_
* @return Integer value of glo message.
*/
unsigned char CGXDLMS_GetGloMessage(DLMS_COMMAND command)
{
    unsigned char cmd;
    switch (command)
    {
    case DLMS_COMMAND_READ_REQUEST:
        cmd = DLMS_COMMAND_GLO_READ_REQUEST;
        break;
    case DLMS_COMMAND_GET_REQUEST:
        cmd = DLMS_COMMAND_GLO_GET_REQUEST;
        break;
    case DLMS_COMMAND_WRITE_REQUEST:
        cmd = DLMS_COMMAND_GLO_WRITE_REQUEST;
        break;
    case DLMS_COMMAND_SET_REQUEST:
        cmd = DLMS_COMMAND_GLO_SET_REQUEST;
        break;
    case DLMS_COMMAND_METHOD_REQUEST:
        cmd = DLMS_COMMAND_GLO_METHOD_REQUEST;
        break;
    case DLMS_COMMAND_READ_RESPONSE:
        cmd = DLMS_COMMAND_GLO_READ_RESPONSE;
        break;
    case DLMS_COMMAND_GET_RESPONSE:
        cmd = DLMS_COMMAND_GLO_GET_RESPONSE;
        break;
    case DLMS_COMMAND_WRITE_RESPONSE:
        cmd = DLMS_COMMAND_GLO_WRITE_RESPONSE;
        break;
    case DLMS_COMMAND_SET_RESPONSE:
        cmd = DLMS_COMMAND_GLO_SET_RESPONSE;
        break;
    case DLMS_COMMAND_METHOD_RESPONSE:
        cmd = DLMS_COMMAND_GLO_METHOD_RESPONSE;
        break;
    case DLMS_COMMAND_DATA_NOTIFICATION:
        cmd = DLMS_COMMAND_GENERAL_GLO_CIPHERING;
        break;
    case DLMS_COMMAND_RELEASE_REQUEST:
        cmd = DLMS_COMMAND_RELEASE_REQUEST;
        break;
    case DLMS_COMMAND_RELEASE_RESPONSE:
        cmd = DLMS_COMMAND_RELEASE_RESPONSE;
        break;
    default:
        cmd = DLMS_COMMAND_NONE;
    }
    return cmd;
}

unsigned char CGXDLMS_GetInvokeIDPriority(CGXDLMSSettings* settings)
{
    unsigned char value = 0;
    if (settings->m_Priority == DLMS_PRIORITY_HIGH)
    {
        value = 0x80;
    }
    if (settings->m_ServiceClass == DLMS_SERVICE_CLASS_CONFIRMED)
    {
        value |= 0x40;
    }
    value |= settings->m_InvokeID & 0xF;
    return value;
}

/**
     * Generates Invoke ID and priority.
     *
     * @param settings
     *            DLMS settings.
     * @return Invoke ID and priority.
     */
long CGXDLMS_GetLongInvokeIDPriority(CGXDLMSSettings* settings)
{
    long value = 0;
    if (settings->m_Priority == DLMS_PRIORITY_HIGH)
    {
        value = 0x80000000;
    }
    if (settings->m_ServiceClass == DLMS_SERVICE_CLASS_CONFIRMED)
    {
        value |= 0x40000000;
    }
    value |= ((settings->m_LongInvokeID) & 0xFFFFFF);
    CGXDLMSSettings_SetLongInvokeID(settings, settings->m_LongInvokeID + 1);
    return value;
}

/**
     * Add LLC bytes to generated message.
     *
     * @param settings
     *            DLMS settings.
     * @param data
     *            Data where bytes are added.
     */
void CGXDLMS_AddLLCBytes(CGXDLMSSettings* settings, CGXByteBuffer* data)
{
    if (settings->m_Server)
    {
        CGXByteBuffer_Set_1(data, LLC_REPLY_BYTES, 3);
    }
    else
    {
        CGXByteBuffer_Set_1(data, LLC_SEND_BYTES, 3);
    }
}

/**
     * Check is all data fit to one data block.
     *
     * @param p
     *            LN parameters.
     * @param reply
     *            Generated reply.
     */
void CGXDLMS_MultipleBlocks(CGXDLMSLNParameters* p,
                    CGXByteBuffer* reply,
                    unsigned char ciphering)
{
    // Check is all data fit to one message if data is given.
    int len = p->m_Data->m_Size
              - p->m_Data->m_Position;
    if (p->m_AttributeDescriptor != NULL)
    {
        len += p->m_AttributeDescriptor->m_Size;
    }
    if (ciphering)
    {
        len += CIPHERING_HEADER_SIZE;
    }
    if (!p->m_MultipleBlocks)
    {
        // Add command type and invoke and priority.
        p->m_MultipleBlocks = 2 + reply->m_Size + len
                                    > p->m_Settings->m_MaxReceivePDUSize;
    }
    if (p->m_MultipleBlocks)
    {
        // Add command type and invoke and priority.
        p->m_LastBlock = !(8 + reply->m_Size + len
                > p->m_Settings->m_MaxReceivePDUSize);
    }
    if (p->m_LastBlock)
    {
        // Add command type and invoke and priority.
        p->m_LastBlock = !(8 + reply->m_Size + len
                > p->m_Settings->m_MaxReceivePDUSize);
    }
}

int CGXDLMS_GetLNPdu(CGXDLMSLNParameters* p, CGXByteBuffer* reply)
{
    int ret;
    unsigned char ciphering = p->m_Command != DLMS_COMMAND_AARQ
                           && p->m_Command != DLMS_COMMAND_AARE
                           && p->m_Settings->m_Cipher != NULL
                           && p->m_Settings->m_Cipher->m_Security != DLMS_SECURITY_NONE;
    int len = 0;
    if (!ciphering && p->m_Settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
    {
        CGXDLMS_AddLLCBytes(p->m_Settings, reply);
    }
    if (p->m_Command == DLMS_COMMAND_AARQ)
    {
        CGXByteBuffer_Set_2(reply, p->m_AttributeDescriptor, 0, -1);
    }
    else
    {
        if ((p->m_Settings->m_NegotiatedConformance & DLMS_CONFORMANCE_GENERAL_BLOCK_TRANSFER) != 0)
        {
            CGXByteBuffer_SetUInt8_1(reply, DLMS_COMMAND_GENERAL_BLOCK_TRANSFER);
            CGXDLMS_MultipleBlocks(p, reply, ciphering);
            // Is last block
            if (!p->m_LastBlock)
            {
                CGXByteBuffer_SetUInt8_1(reply, 0);
            }
            else
            {
                CGXByteBuffer_SetUInt8_1(reply, 0x80);
            }
            // Set block number sent.
            CGXByteBuffer_SetUInt8_1(reply, 0);
            // Set block number acknowledged
            CGXByteBuffer_SetUInt8_1(reply, (unsigned char)(p->m_BlockIndex));
            p->m_BlockIndex = p->m_BlockIndex + 1;
            // Add APU tag.
            CGXByteBuffer_SetUInt8_1(reply, 0);
            // Add Addl fields
            CGXByteBuffer_SetUInt8_1(reply, 0);
        }
        // Add command.
        CGXByteBuffer_SetUInt8_1(reply, (unsigned char)p->m_Command);

        if (p->m_Command == DLMS_COMMAND_EVENT_NOTIFICATION ||
            p->m_Command == DLMS_COMMAND_DATA_NOTIFICATION ||
            p->m_Command == DLMS_COMMAND_ACCESS_REQUEST ||
            p->m_Command == DLMS_COMMAND_ACCESS_RESPONSE)
        {
            // Add Long-Invoke-Id-And-Priority
            if (p->m_Command != DLMS_COMMAND_EVENT_NOTIFICATION)
            {
                if (p->m_InvokeId != 0)
                {
                    CGXByteBuffer_SetUInt32(reply, p->m_InvokeId);
                }
                else
                {
                    CGXByteBuffer_SetUInt32(reply, CGXDLMS_GetLongInvokeIDPriority(p->m_Settings));
                }
            }

            // Add date time.
            if (p->m_Time == NULL)
            {
                CGXByteBuffer_SetUInt8_1(reply, DLMS_DATA_TYPE_NONE);
            }
            else
            {
                // Data is send in octet string. Remove data type.
                int pos = reply->m_Size;
                CGXDLMSVariant tmp;
                CGXDLMSVariant_12(&tmp, p->m_Time);

                if ((ret = GXHelpers_SetData(reply, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
                {
                    CGXDLMSVariant_d(&tmp);
                    return ret;
                }
                CGXByteBuffer_Move(reply, pos + 1, pos, reply->m_Size - pos - 1);

                CGXDLMSVariant_d(&tmp);
            }
        }
        else if (p->m_Command != DLMS_COMMAND_RELEASE_REQUEST)
        {
            // Get request size can be bigger than PDU size.
            if (p->m_Command != DLMS_COMMAND_GET_REQUEST
                && p->m_Data != NULL
                && p->m_Data->m_Size != 0)
            {
                CGXDLMS_MultipleBlocks(p, reply, ciphering);
            }
            // Change Request type if Set request and multiple blocks is
            // needed.
            if (p->m_Command == DLMS_COMMAND_SET_REQUEST)
            {
                if (p->m_MultipleBlocks)
                {
                    if (p->m_RequestType == 1)
                    {
                        p->m_RequestType = 2;
                    }
                    else if (p->m_RequestType == 2)
                    {
                        p->m_RequestType = 3;
                    }
                }
            }
            // Change request type If get response and multiple blocks is
            // needed.
            if (p->m_Command == DLMS_COMMAND_GET_RESPONSE)
            {
                if (p->m_MultipleBlocks)
                {
                    if (p->m_RequestType == 1)
                    {
                        p->m_RequestType = 2;
                    }
                }
            }
            CGXByteBuffer_SetUInt8_1(reply, p->m_RequestType);
            // Add Invoke Id And Priority.
            if (p->m_InvokeId != 0)
            {
                CGXByteBuffer_SetUInt8_1(reply, (unsigned char)(p->m_InvokeId));
            }
            else
            {
                CGXByteBuffer_SetUInt8_1(reply, CGXDLMS_GetInvokeIDPriority(p->m_Settings));
            }
        }

        // Add attribute descriptor.
        CGXByteBuffer_Set_2(reply, p->m_AttributeDescriptor, 0, -1);
        if (p->m_Command != DLMS_COMMAND_EVENT_NOTIFICATION &&
            p->m_Command != DLMS_COMMAND_DATA_NOTIFICATION &&
            (p->m_Settings->m_NegotiatedConformance & DLMS_CONFORMANCE_GENERAL_BLOCK_TRANSFER) == 0)
        {
            // If multiple blocks.
            if (p->m_MultipleBlocks)
            {
                // Is last block.
                if (p->m_LastBlock)
                {
                    CGXByteBuffer_SetUInt8_1(reply, 1);
                    p->m_Settings->m_Count = 0;
                    p->m_Settings->m_Index = 0;
                }
                else
                {
                    CGXByteBuffer_SetUInt8_1(reply, 0);
                }
                // Block index.
                CGXByteBuffer_SetUInt32(reply, p->m_BlockIndex);
                p->m_BlockIndex = p->m_BlockIndex + 1;
                // Add status if reply.CGXByteBuffer_
                if (p->m_Status != 0xFF)
                {
                    if (p->m_Status != 0
                     && p->m_Command == DLMS_COMMAND_GET_RESPONSE)
                    {
                        CGXByteBuffer_SetUInt8_1(reply, 1);
                    }
                    CGXByteBuffer_SetUInt8_1(reply, p->m_Status);
                }
                // Block size.
                if (p->m_Data != NULL)
                {
                    len = p->m_Data->m_Size
                          - p->m_Data->m_Position;
                }
                else
                {
                    len = 0;
                }
                int totalLength = len + reply->m_Size;
                if (ciphering)
                {
                    totalLength += CIPHERING_HEADER_SIZE;
                }

                if (totalLength > p->m_Settings->m_MaxReceivePDUSize)
                {
                    len = p->m_Settings->m_MaxReceivePDUSize - reply->m_Size;
                    if (ciphering)
                    {
                        len -= CIPHERING_HEADER_SIZE;
                    }
                    len -= GXHelpers_GetObjectCountSizeInBytes(len);
                }
                GXHelpers_SetObjectCount(len, reply);
                CGXByteBuffer_Set_2(reply, p->m_Data, 0, len);
            }
        }
        // Add data that fits to one block.
        if (len == 0)
        {
            // Add status if reply.CGXByteBuffer_
            if (p->m_Status != 0xFF)
            {
                if (p->m_Status != 0
                    && p->m_Command == DLMS_COMMAND_GET_RESPONSE)
                {
                    CGXByteBuffer_SetUInt8_1(reply, 1);
                }
                CGXByteBuffer_SetUInt8_1(reply, p->m_Status);
            }
            if (p->m_Data != NULL
                    && p->m_Data->m_Size != 0)
            {
                len = p->m_Data->m_Size - p->m_Data->m_Position;
                // Get request size can be bigger than PDU size.
                if (p->m_Command != DLMS_COMMAND_GET_REQUEST && len
                    + reply->m_Size > p->m_Settings->m_MaxReceivePDUSize)
                {
                    len = p->m_Settings->m_MaxReceivePDUSize - reply->m_Size
                        - p->m_Data->m_Position;
                }
                CGXByteBuffer_Set_2(reply, p->m_Data, p->m_Data->m_Position, len);
            }
        }
        if (ciphering)
        {
            p->m_Settings->m_Cipher->m_FrameCounter = p->m_Settings->m_Cipher->m_FrameCounter + 1;
            CGXByteBuffer tmp;
            CGXByteBuffer_1(&tmp);

            unsigned char cmd;
            if ((p->m_Settings->m_NegotiatedConformance & DLMS_CONFORMANCE_GENERAL_PROTECTION) == 0)
            {
                cmd = CGXDLMS_GetGloMessage(p->m_Command);
            }
            else
            {
                cmd = (unsigned char)DLMS_COMMAND_GENERAL_GLO_CIPHERING;
            }
            ret = CGXCipher_Encrypt(p->m_Settings->m_Cipher,
                                    p->m_Settings->m_Cipher->m_Security,
                                    DLMS_COUNT_TYPE_PACKET,
                                    p->m_Settings->m_Cipher->m_FrameCounter,
                                    cmd,
                                    CGXCipher_GetSystemTitle(p->m_Settings->m_Cipher),
                                    reply, &tmp);
            if (ret != 0)
            {
                CGXByteBuffer_d(&tmp);
                return ret;
            }
            CGXByteBuffer_SetSize(reply, 0);
            if (p->m_Settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
            {
                CGXDLMS_AddLLCBytes(p->m_Settings, reply);
            }
            if (p->m_Command == DLMS_COMMAND_DATA_NOTIFICATION
            || (p->m_Settings->m_NegotiatedConformance & DLMS_CONFORMANCE_GENERAL_PROTECTION) != 0)
            {
                // Add command.
                CGXByteBuffer_SetUInt8_1(reply, tmp.m_Data[0]);
                // Add system title.
                GXHelpers_SetObjectCount(CGXCipher_GetSystemTitle(p->m_Settings->m_Cipher)->m_Size, reply);
                CGXByteBuffer_Set_2(reply, CGXCipher_GetSystemTitle(p->m_Settings->m_Cipher), 0, -1);
                // Add data.
                CGXByteBuffer_Set_2(reply, &tmp, 1, tmp.m_Size - 1);
            }
            else
            {
                CGXByteBuffer_Set_2(reply, &tmp, 0, tmp.m_Size);
            }

            CGXByteBuffer_d(&tmp);
        }
    }
    return 0;
}

int CGXDLMS_GetLnMessages(CGXDLMSLNParameters* p,
                          Vector* messages)
{
    int ret;

    CGXByteBuffer reply, tmp;
    CGXByteBuffer_1(&reply);
    CGXByteBuffer_1(&tmp);

    unsigned char frame = 0;
    if (p->m_Command == DLMS_COMMAND_AARQ)
    {
        frame = 0x10;
    }
    else if (p->m_Command == DLMS_COMMAND_DATA_NOTIFICATION
          || p->m_Command == DLMS_COMMAND_EVENT_NOTIFICATION)
    {
        frame = 0x13;
    }
    do
    {
        if ((ret = CGXDLMS_GetLNPdu(p, &reply)) != 0)
        {
            CGXByteBuffer_d(&reply);
            CGXByteBuffer_d(&tmp);
            return ret;
        }
        p->m_LastBlock = true;
        if (p->m_AttributeDescriptor == NULL)
        {
            p->m_Settings->m_BlockIndex += 1;
        }
        while (reply.m_Position != reply.m_Size)
        {
            if (p->m_Settings->m_InterfaceType
                                                                == DLMS_INTERFACE_TYPE_WRAPPER)
            {
                ret = CGXDLMS_GetWrapperFrame(p->m_Settings, &reply, &tmp);
            }
            else
            {
                ret = CGXDLMS_GetHdlcFrame(p->m_Settings, frame, &reply, &tmp);
                if (ret == 0 && reply.m_Position != reply.m_Size)
                {
                    if (p->m_Settings->m_Server
                     || p->m_Command == DLMS_COMMAND_SET_REQUEST
                     || p->m_Command == DLMS_COMMAND_METHOD_REQUEST)
                    {
                        frame = 0;
                    }
                    else
                    {
                        frame = CGXDLMSSettings_GetNextSend(p->m_Settings, 0);
                    }
                }
            }
            if (ret != 0)
            {
                break;
            }
            Vector_push_back(messages, &tmp);
            CGXByteBuffer_Clear(&tmp);
        }
        CGXByteBuffer_Clear(&reply);
    } while (ret == 0 && p->m_Data != NULL
          && p->m_Data->m_Position != p->m_Data->m_Size);

    CGXByteBuffer_d(&reply);
    CGXByteBuffer_d(&tmp);

    return ret;
}

int CGXDLMS_AppendMultipleSNBlocks(CGXDLMSSNParameters* p, CGXByteBuffer* reply)
{
    bool ciphering = p->m_Settings->m_Cipher != NULL
                  && p->m_Settings->m_Cipher->m_Security != DLMS_SECURITY_NONE;
    unsigned long hSize = reply->m_Size + 3;
    // Add LLC bytes.
    if (p->m_Command == DLMS_COMMAND_WRITE_REQUEST
     || p->m_Command == DLMS_COMMAND_READ_REQUEST)
    {
        hSize += 1 + GXHelpers_GetObjectCountSizeInBytes(p->m_Count);
    }
    unsigned long maxSize = p->m_Settings->m_MaxReceivePDUSize - hSize;
    if (ciphering)
    {
        maxSize -= CIPHERING_HEADER_SIZE;
        if (p->m_Settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
        {
            maxSize -= 3;
        }
    }
    maxSize -= GXHelpers_GetObjectCountSizeInBytes(maxSize);
    if (p->m_Data->m_Size
            - p->m_Data->m_Position > maxSize)
    {
        // More blocks.
        CGXByteBuffer_SetUInt8_1(reply, 0);
    }
    else
    {
        // Last block.
        CGXByteBuffer_SetUInt8_1(reply, 1);
        maxSize = p->m_Data->m_Size
                - p->m_Data->m_Position;
    }
    // Add block index.
    CGXByteBuffer_SetUInt16(reply, p->m_BlockIndex);
    if (p->m_Command == DLMS_COMMAND_WRITE_REQUEST)
    {
        p->m_BlockIndex = p->m_BlockIndex + 1;
        GXHelpers_SetObjectCount(p->m_Count, reply);
        CGXByteBuffer_SetUInt8_1(reply, DLMS_DATA_TYPE_OCTET_STRING);
    }
    else if (p->m_Command == DLMS_COMMAND_READ_REQUEST)
    {
        p->m_BlockIndex = p->m_BlockIndex + 1;
    }

    GXHelpers_SetObjectCount(maxSize, reply);
    return maxSize;
}

int CGXDLMS_GetSNPdu(CGXDLMSSNParameters* p, CGXByteBuffer* reply)
{
    int ret;
    unsigned char ciphering = p->m_Command != DLMS_COMMAND_AARQ
                           && p->m_Command != DLMS_COMMAND_AARE
                           && p->m_Settings->m_Cipher != NULL
                           && p->m_Settings->m_Cipher->m_Security != DLMS_SECURITY_NONE;
    if (!ciphering
        && p->m_Settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
    {
        CGXDLMS_AddLLCBytes(p->m_Settings, reply);
    }
    int cnt = 0, cipherSize = 0;
    if (ciphering)
    {
        cipherSize = CIPHERING_HEADER_SIZE;
    }
    if (p->m_Data != NULL)
    {
        cnt = p->m_Data->m_Size - p->m_Data->m_Position;
    }
    // Add command.
    if (p->m_Command == DLMS_COMMAND_INFORMATION_REPORT)
    {
        CGXByteBuffer_SetUInt8_1(reply, p->m_Command);
        // Add date time.
        if (p->m_Time == NULL)
        {
            CGXByteBuffer_SetUInt8_1(reply, DLMS_DATA_TYPE_NONE);
        }
        else
        {
            // Data is send in octet string. Remove data type.
            int pos = reply->m_Size;
            CGXDLMSVariant tmp;
            CGXDLMSVariant_12(&tmp, p->m_Time);

            if ((ret = GXHelpers_SetData(reply, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                return ret;
            }
            CGXByteBuffer_Move(reply, pos + 1, pos, reply->m_Size - pos - 1);

            CGXDLMSVariant_d(&tmp);
        }
        GXHelpers_SetObjectCount(p->m_Count, reply);
        CGXByteBuffer_Set_2(reply, p->m_AttributeDescriptor, 0, -1);
    }
    else if (p->m_Command != DLMS_COMMAND_AARQ
          && p->m_Command != DLMS_COMMAND_AARE)
    {
        CGXByteBuffer_SetUInt8_1(reply, (unsigned char)p->m_Command);
        if (p->m_Count != 0xFF)
        {
            GXHelpers_SetObjectCount(p->m_Count, reply);
        }
        if (p->m_RequestType != 0xFF)
        {
            CGXByteBuffer_SetUInt8_1(reply, p->m_RequestType);
        }
        CGXByteBuffer_Set_2(reply, p->m_AttributeDescriptor, 0, -1);

        if (!p->m_MultipleBlocks)
        {
            p->m_MultipleBlocks = reply->m_Size + cipherSize + cnt
                                                            > p->m_Settings->m_MaxReceivePDUSize;
            // If reply data is not fit to one PDU.
            if (p->m_MultipleBlocks)
            {
                CGXByteBuffer_SetSize(reply, 0);
                if (!ciphering
                  && p->m_Settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
                {
                    CGXDLMS_AddLLCBytes(p->m_Settings, reply);
                }
                if (p->m_Command == DLMS_COMMAND_WRITE_REQUEST)
                {
                    p->m_RequestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_WRITE_DATA_BLOCK_ACCESS;
                }
                else if (p->m_Command == DLMS_COMMAND_READ_REQUEST)
                {
                    p->m_RequestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_READ_DATA_BLOCK_ACCESS;
                }
                else if (p->m_Command == DLMS_COMMAND_READ_RESPONSE)
                {
                    p->m_RequestType = DLMS_SINGLE_READ_RESPONSE_DATA_BLOCK_RESULT;
                }
                else
                {
                    //Invalid command.
                    return DLMS_ERROR_CODE_INVALID_COMMAND;
                }
                CGXByteBuffer_SetUInt8_1(reply, (unsigned char)p->m_Command);
                // Set object count.
                CGXByteBuffer_SetUInt8_1(reply, 1);
                if (p->m_RequestType != 0xFF)
                {
                    CGXByteBuffer_SetUInt8_1(reply, p->m_RequestType);
                }
                cnt = CGXDLMS_AppendMultipleSNBlocks(p, reply);
            }
        }
        else
        {
            cnt = CGXDLMS_AppendMultipleSNBlocks(p, reply);
        }
    }
    // Add data.
    if (p->m_Data != NULL)
    {
        CGXByteBuffer_Set_2(reply, p->m_Data,
                            p->m_Data->m_Position, cnt);
    }
    // If all data is transfered.
    if (p->m_Data != NULL && p->m_Data->m_Position == p->m_Data->m_Size)
    {
        p->m_Settings->m_Index = 0;
        p->m_Settings->m_Count = 0;
    }
    // If Ciphering is used.
    if (ciphering && p->m_Command != DLMS_COMMAND_AARQ
        && p->m_Command != DLMS_COMMAND_AARE)
    {
        CGXByteBuffer tmp;
        CGXByteBuffer_1(&tmp);

        ret = CGXCipher_Encrypt(p->m_Settings->m_Cipher,
                                p->m_Settings->m_Cipher->m_Security,
                                DLMS_COUNT_TYPE_PACKET,
                                p->m_Settings->m_Cipher->m_FrameCounter,
                                CGXDLMS_GetGloMessage(p->m_Command),
                                CGXCipher_GetSystemTitle(p->m_Settings->m_Cipher),
                                reply, &tmp);
        if (ret != 0)
        {
            CGXByteBuffer_d(&tmp);
            return ret;
        }
        CGXByteBuffer_SetSize(reply, 0);
        if (p->m_Settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
        {
            CGXDLMS_AddLLCBytes(p->m_Settings, reply);
        }
        CGXByteBuffer_Set_2(reply, &tmp, 0, tmp.m_Size);

        CGXByteBuffer_d(&tmp);
    }
    return 0;
}

int CGXDLMS_GetSnMessages(CGXDLMSSNParameters* p, Vector* messages)
{
    int ret;
    CGXByteBuffer data, reply;
    CGXByteBuffer_1(&data);
    CGXByteBuffer_1(&reply);

    unsigned char frame = 0x0;
    if (p->m_Command == DLMS_COMMAND_AARQ)
    {
        frame = 0x10;
    }
    else if (p->m_Command == DLMS_COMMAND_INFORMATION_REPORT)
    {
        frame = 0x13;
    }
    else if (p->m_Command == DLMS_COMMAND_NONE)
    {
        frame = CGXDLMSSettings_GetNextSend(p->m_Settings, 1);
    }
    do
    {
        ret = CGXDLMS_GetSNPdu(p, &data);
        // Command is not add to next PDUs.
        while (data.m_Position != data.m_Size)
        {
            if (p->m_Settings->m_InterfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
            {
                ret = CGXDLMS_GetWrapperFrame(p->m_Settings, &data, &reply);
            }
            else
            {
                ret = CGXDLMS_GetHdlcFrame(p->m_Settings, frame, &data, &reply);
                if (data.m_Position != data.m_Size)
                {
                    if (p->m_Settings->m_Server)
                    {
                        frame = 0;
                    }
                    else
                    {
                        frame = CGXDLMSSettings_GetNextSend(p->m_Settings, 0);
                    }
                }
            }
            if (ret != 0)
            {
                break;
            }
            Vector_push_back(messages, &reply);
            CGXByteBuffer_Clear(&reply);
        }
        CGXByteBuffer_Clear(&reply);
    } while (ret == 0 && p->m_Data != NULL
          && p->m_Data->m_Position != p->m_Data->m_Size);

    CGXByteBuffer_d(&data);
    CGXByteBuffer_d(&reply);

    return 0;
}

int CGXDLMS_GetHdlcData(bool server,
                        CGXDLMSSettings* settings,
                        CGXByteBuffer* reply,
                        CGXReplyData* data,
                        unsigned char* frame)
{
    unsigned long packetStartID = reply->m_Position, frameLen = 0;
    unsigned long pos;
    unsigned char ch;
    int ret;
    unsigned short crc, crcRead;
    // If whole frame is not received yet.
    if (reply->m_Size - reply->m_Position < 9)
    {
        data->m_Complete = false;
        return 0;
    }
    data->m_Complete = true;
    // Find start of HDLC frame.
    for (pos = reply->m_Position; pos < reply->m_Size; ++pos)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(reply, &ch)) != 0)
        {
            return ret;
        }
        if (ch == HDLC_FRAME_START_END)
        {
            packetStartID = pos;
            break;
        }
    }
    // Not a HDLC frame.
    // Sometimes meters can send some strange data between DLMS frames.
    if (reply->m_Position == reply->m_Size)
    {
        data->m_Complete = false;
        // Not enough data to parse;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(reply, frame)) != 0)
    {
        return ret;
    }
    if (((*frame) & 0xF0) != 0xA0)
    {
        // If same data.
        return CGXDLMS_GetHdlcData(server, settings, reply, data, frame);
    }
    // Check frame length.
    if (((*frame) & 0x7) != 0)
    {
        frameLen = (((*frame) & 0x7) << 8);
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(reply, &ch)) != 0)
    {
        return ret;
    }
    // If not enough data.
    frameLen += ch;
    if (reply->m_Size - reply->m_Position + 1 < frameLen)
    {
        data->m_Complete = false;
        CGXByteBuffer_SetPosition(reply, packetStartID);
        // Not enough data to parse;
        return 0;
    }
    int eopPos = frameLen + packetStartID + 1;
    if ((ret = CGXByteBuffer_GetUInt8_2(reply, eopPos, &ch)) != 0)
    {
        return ret;
    }
    if (ch != HDLC_FRAME_START_END)
    {
        return DLMS_ERROR_CODE_NOT_REPLY;
    }

    // Check addresses.
    ret = CGXDLMS_CheckHdlcAddress(server, settings, reply, eopPos);
    if (ret != 0)
    {
        if (ret == DLMS_ERROR_CODE_FALSE)
        {
            // If echo,
            return CGXDLMS_GetHdlcData(server, settings, reply, data, frame);
        }
        return ret;
    }

    // Is there more data available.
    if (((*frame) & 0x8) != 0)
    {
        data->m_MoreData = (DLMS_DATA_REQUEST_TYPES)(data->m_MoreData | DLMS_DATA_REQUEST_TYPES_FRAME);
    }
    else
    {
        data->m_MoreData = (DLMS_DATA_REQUEST_TYPES)(data->m_MoreData & ~DLMS_DATA_REQUEST_TYPES_FRAME);
    }
    // Get frame type.
    if ((ret = CGXByteBuffer_GetUInt8_1(reply, frame)) != 0)
    {
        return ret;
    }
    if (!CGXDLMSSettings_CheckFrame(settings, *frame))
    {
        CGXByteBuffer_SetPosition(reply, eopPos + 1);
        return CGXDLMS_GetHdlcData(server, settings, reply, data, frame);
    }
    // Check that header CRC is correct.
    crc = CGXDLMS_CountFCS16(reply, packetStartID + 1,
                             reply->m_Position - packetStartID - 1);

    if ((ret = CGXByteBuffer_GetUInt16_1(reply, &crcRead)) != 0)
    {
        return ret;
    }
    if (crc != crcRead)
    {
        return DLMS_ERROR_CODE_WRONG_CRC;
    }
    // Check that packet CRC match only if there is a data part.
    if (reply->m_Position != packetStartID + frameLen + 1)
    {
        crc = CGXDLMS_CountFCS16(reply, packetStartID + 1, frameLen - 2);
        if ((ret = CGXByteBuffer_GetUInt16_2(reply, packetStartID + frameLen - 1, &crcRead)) != 0)
        {
            return ret;
        }
        if (crc != crcRead)
        {
            return DLMS_ERROR_CODE_WRONG_CRC;
        }
        // Remove CRC and EOP from packet length.
        data->m_PacketLength = eopPos - 2;
    }
    else
    {
        data->m_PacketLength = reply->m_Position + 1;
    }

    if ((*frame) != 0x13 && ((*frame) & HDLC_FRAME_TYPE_U_FRAME) == HDLC_FRAME_TYPE_U_FRAME)
    {
        // Get Eop if there is no data.
        if (reply->m_Position == packetStartID + frameLen + 1)
        {
            // Get EOP.
            if ((ret = CGXByteBuffer_GetUInt8_1(reply, &ch)) != 0)
            {
                return ret;
            }
        }
        if ((*frame) == 0x97)
        {
            return DLMS_ERROR_CODE_UNACCEPTABLE_FRAME;
        }
        data->m_Command = (DLMS_COMMAND)(*frame);
    }
    else if ((*frame) != 0x13 && ((*frame) & HDLC_FRAME_TYPE_S_FRAME) == HDLC_FRAME_TYPE_S_FRAME)
    {
        // If S-frame
        int tmp = ((*frame) >> 2) & 0x3;
        // If frame is rejected.
        if (tmp == HDLC_CONTROL_FRAME_REJECT)
        {
            return DLMS_ERROR_CODE_REJECTED;
        }
        else if (tmp == HDLC_CONTROL_FRAME_RECEIVE_NOT_READY)
        {
            return DLMS_ERROR_CODE_REJECTED;
        }
        else if (tmp == HDLC_CONTROL_FRAME_RECEIVE_READY)
        {
            // Get next frame.
        }
        // Get Eop if there is no data.
        if (reply->m_Position == packetStartID + frameLen + 1)
        {
            // Get EOP.
            if ((ret = CGXByteBuffer_GetUInt8_1(reply, &ch)) != 0)
            {
                return ret;
            }
        }
    }
    else
    {
        // I-frame
        // Get Eop if there is no data.
        if (reply->m_Position == packetStartID + frameLen + 1)
        {
            // Get EOP.
            if ((ret = CGXByteBuffer_GetUInt8_1(reply, &ch)) != 0)
            {
                return ret;
            }
            if (((*frame) & 0x1) == 0x1)
            {
                data->m_MoreData = DLMS_DATA_REQUEST_TYPES_FRAME;
            }
        }
        else
        {
            CGXDLMS_GetLLCBytes(server, reply);
        }
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_GetHDLCAddress(CGXByteBuffer* buff, unsigned long* address)
{
    unsigned char ch;
    unsigned short s;
    unsigned long l;
    int ret, size = 0;
    *address = 0;
    for (unsigned long pos = buff->m_Position;
         pos != buff->m_Size; ++pos)
    {
        ++size;
        if ((ret = CGXByteBuffer_GetUInt8_2(buff, pos, &ch)) != 0)
        {
            return ret;
        }
        if ((ch & 0x1) == 1)
        {
            break;
        }
    }
    if (size == 1)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
        {
            return ret;
        }
        *address = ((ch & 0xFE) >> 1);
    }
    else if (size == 2)
    {
        if ((ret = CGXByteBuffer_GetUInt16_1(buff, &s)) != 0)
        {
            return ret;
        }
        *address = ((s & 0xFE) >> 1) | ((s & 0xFE00) >> 2);
    }
    else if (size == 4)
    {
        if ((ret = CGXByteBuffer_GetUInt32_1(buff, &l)) != 0)
        {
            return ret;
        }
        *address = ((l & 0xFE) >> 1) | ((l & 0xFE00) >> 2)
                 | ((l & 0xFE0000) >> 3) | ((l & 0xFE000000) >> 4);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

static void GetServerAddress(int address, int* logical, int* physical)
{
    if (address < 0x4000)
    {
        *logical = address >> 7;
        *physical = address & 0x7F;
    }
    else
    {
        *logical = address >> 14;
        *physical = address & 0x3FFF;
    }
}

int CGXDLMS_CheckHdlcAddress(bool server,
                             CGXDLMSSettings* settings,
                             CGXByteBuffer* reply,
                             int index)
{
    unsigned char ch;
    unsigned long source, target;
    int ret;
    // Get destination and source addresses.
    if ((ret = CGXDLMS_GetHDLCAddress(reply, &target)) != 0)
    {
        return ret;
    }
    if ((ret = CGXDLMS_GetHDLCAddress(reply, &source)) != 0)
    {
        return ret;
    }
    if (server)
    {
        // Check that server addresses match.
        if (settings->m_ServerAddress != 0
         && settings->m_ServerAddress != target)
        {
            // Get frame command.
            if (CGXByteBuffer_GetUInt8_2(reply, reply->m_Position, &ch) != 0)
            {
                return DLMS_ERROR_CODE_INVALID_SERVER_ADDRESS;
            }
            //If SNRM and client has not call disconnect and changes client ID.
            if (ch == DLMS_COMMAND_SNRM)
            {
                settings->m_ServerAddress = target;
            }
            else
            {
                return DLMS_ERROR_CODE_INVALID_SERVER_ADDRESS;
            }
        }
        else
        {
            settings->m_ServerAddress = target;
        }

        // Check that client addresses match.
        if (settings->m_ClientAddress != 0
         && settings->m_ClientAddress != source)
        {
            // Get frame command.
            if (CGXByteBuffer_GetUInt8_2(reply, reply->m_Position, &ch) != 0)
            {
                return DLMS_ERROR_CODE_INVALID_CLIENT_ADDRESS;
            }
            //If SNRM and client has not call disconnect and changes client ID.
            if (ch == DLMS_COMMAND_SNRM)
            {
                settings->m_ClientAddress = source;
            }
            else
            {
                return DLMS_ERROR_CODE_INVALID_CLIENT_ADDRESS;
            }
        }
        else
        {
            settings->m_ClientAddress = source;
        }
    }
    else
    {
        // Check that client addresses match.
        if (settings->m_ClientAddress != target)
        {
            // If echo.
            if (settings->m_ClientAddress == source
             && settings->m_ServerAddress == target)
            {
                CGXByteBuffer_SetPosition(reply, index + 1);
            }
            return DLMS_ERROR_CODE_FALSE;
        }
        // Check that server addresses match.
        if (settings->m_ServerAddress != source)
        {
            //Check logical and physical address separately.
            //This is done because some meters might send four bytes
            //when only two bytes is needed.
            int readLogical, readPhysical, logical, physical;
            GetServerAddress(source, &readLogical, &readPhysical);
            GetServerAddress(settings->m_ServerAddress, &logical, &physical);
            if (readLogical != logical || readPhysical != physical)
            {
                return DLMS_ERROR_CODE_FALSE;
            }
        }
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_HandleMethodResponse(CGXDLMSSettings* settings, CGXReplyData* data)
{
    int ret;
    unsigned char ch, type;
    // Get type.
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&type)) != 0)
    {
        return ret;
    }
    // Get invoke ID and priority.
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
    {
        return ret;
    }
    //Action-Response-Normal
    if (type == 1)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
        {
            return ret;
        }
        if (ch != 0)
        {
            return ch;
        }
        // Response normal. Get data if exists.
        if (CGXReplyData_GetData(data)->m_Position < CGXReplyData_GetData(data)->m_Size)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
            {
                return ret;
            }
            if (ch == 0)
            {
            	CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(data), 0);
            }
            else if (ch == 1)
            {
                //Get Data-Access-Result
                if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
                {
                    return ret;
                }
                if (ch != 0)
                {

                    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&type)) != 0)
                    {
                        return ret;
                    }
                    //Handle Texas Instrument missing byte here.
                    if (ch == 9 && type == 16)
                    {
                    	CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position-2);
                    }
                    else
                    {
                        return type;
                    }
                }
                CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(data), 0);
            }
            else
            {
                //Invalid tag.
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
        }
    }
    else if (type == 2)
    {
        //Action-Response-With-Pblock
        return DLMS_ERROR_CODE_INVALID_COMMAND;
    }
    else if (type == 3)
    {
        // Action-Response-With-List.
        return DLMS_ERROR_CODE_INVALID_COMMAND;
    }
    else if (type == 4)
    {
        //Action-Response-Next-Pblock
        return DLMS_ERROR_CODE_INVALID_COMMAND;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_COMMAND;
    }
    return DLMS_ERROR_CODE_OK;
}

/**
    * Handle data notification get data from block and/or update error status.
    *
    * @param settings
    *            DLMS settings.
    * @param reply
    *            Received data from the client.
    */
int CGXDLMS_HandleDataNotification(CGXDLMSSettings* settings, CGXReplyData* reply)
{
    unsigned long id;
    int ret;
    int start = CGXReplyData_GetData(reply)->m_Position - 1;
    // Get invoke id.
    if ((ret = CGXByteBuffer_GetUInt32_1(CGXReplyData_GetData(reply), &id)) != 0)
    {
        return ret;
    }
    // Get date time.
    CGXReplyData_SetTime(reply, NULL);
    unsigned char len;
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(reply),&len)) != 0)
    {
        return ret;
    }
    if (len != 0)
    {
        CGXByteBuffer tmp;
        CGXByteBuffer_1(&tmp);

        CGXDLMSVariant t;
        CGXDLMSVariant_1(&t);

        CGXByteBuffer_Set_2(&tmp,CGXReplyData_GetData(reply),CGXReplyData_GetData(reply)->m_Position, len);

        if ((ret = CGXDLMSClient_ChangeType_1(&tmp, DLMS_DATA_TYPE_DATETIME, &t)) != 0)
        {
            CGXByteBuffer_d(&tmp);
            CGXDLMSVariant_d(&t);
            return ret;
        }
        CGXReplyData_SetTime(reply, &(t.dateTime.m_Value));

        CGXByteBuffer_d(&tmp);
        CGXDLMSVariant_d(&t);
    }
    if ((ret = CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(reply), start)) != 0)
    {
        return ret;
    }
    return CGXDLMS_GetValueFromData(settings, reply);
}

int CGXDLMS_HandleSetResponse(CGXDLMSSettings* settings, CGXReplyData* data)
{
    unsigned char ch, type, invokeId;
    int ret;
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&type)) != 0)
    {
        return ret;
    }
    //Invoke ID and priority.
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&invokeId)) != 0)
    {
        return ret;
    }

    // SetResponseNormal
    if (type == DLMS_SET_RESPONSE_TYPE_NORMAL)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
        {
            return ret;
        }
        if (ch != 0)
        {
            return ch;
        }
    }
    else if (type == DLMS_SET_RESPONSE_TYPE_DATA_BLOCK || type == DLMS_SET_RESPONSE_TYPE_LAST_DATA_BLOCK)
    {
        unsigned long  tmp;
        if ((ret = CGXByteBuffer_GetUInt32_1(CGXReplyData_GetData(data),&tmp)) != 0)
        {
            return ret;
        }
    }
    else
    {
        //Invalid data type.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_HandleGbt(CGXDLMSSettings* settings, CGXReplyData* data)
{
    int ret;
    unsigned char ch, bn, bna;
    data->m_Gbt = true;
    int index = CGXReplyData_GetData(data)->m_Position - 1;
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
    {
        return ret;
    }
    // Is streaming active.
    //TODO: bool streaming = (ch & 0x40) == 1;
    unsigned char window = (ch & 0x3F);
    // Block number.
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&bn)) != 0)
    {
        return ret;
    }
    // Block number acknowledged.
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&bna)) != 0)
    {
        return ret;
    }
    // Get APU tag.
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
    {
        return ret;
    }
    if (ch != 0)
    {
        //Invalid APU.
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    // Get Addl tag.
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
    {
        return ret;
    }
    if (ch != 0)
    {
        //Invalid APU.
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
    {
        return ret;
    }
    if (ch != 0)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    data->m_Command = DLMS_COMMAND_NONE;
    if (window != 0)
    {
        unsigned long len;
        if ((ret = GXHelpers_GetObjectCount(CGXReplyData_GetData(data), &len)) != 0)
        {
            return ret;
        }
        if (len != (unsigned long)(CGXReplyData_GetData(data)->m_Size - CGXReplyData_GetData(data)->m_Position))
        {
            data->m_Complete = false;
            return 0;
        }
    }

    if ((ret = CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(data), index)) != 0 ||
        (ret = CGXDLMS_GetPdu(settings, data)) != 0)
    {
        return ret;
    }
    // Is Last block,
    if ((ch & 0x80) == 0)
    {
        data->m_MoreData = (DLMS_DATA_REQUEST_TYPES)(data->m_MoreData  | DLMS_DATA_REQUEST_TYPES_BLOCK);
    }
    else
    {
        data->m_MoreData = (DLMS_DATA_REQUEST_TYPES)(data->m_MoreData  & ~DLMS_DATA_REQUEST_TYPES_BLOCK);
    }
    // Get data if all data is read or we want to peek data.
    if (CGXReplyData_GetData(data)->m_Position != CGXReplyData_GetData(data)->m_Size
        && (data->m_Command == DLMS_COMMAND_READ_RESPONSE
            || data->m_Command == DLMS_COMMAND_GET_RESPONSE)
        && (data->m_MoreData  == DLMS_DATA_REQUEST_TYPES_NONE
            || data->m_Peek))
    {
    	CGXByteBuffer_SetPosition(CGXReplyData_GetData(data), 0);
        ret = CGXDLMS_GetValueFromData(settings, data);
    }
    return ret;
}

int CGXDLMS_HandledGloRequest(CGXDLMSSettings* settings, CGXReplyData* data)
{
    if (settings->m_Cipher == NULL)
    {
        //Secure connection is not supported.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    DLMS_SECURITY security;
    //If all frames are read.
    if ((data->m_MoreData  & DLMS_DATA_REQUEST_TYPES_FRAME) == 0)
    {
        int ret;
        unsigned char ch;
        CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position - 1 );

        if ((ret = CGXCipher_Decrypt(settings->m_Cipher, CGXDLMSSettings_GetSourceSystemTitle(settings), CGXReplyData_GetData(data), &security)) != 0)
        {
            return ret;
        }
        // Get command.
        CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch);
        data->m_Command = (DLMS_COMMAND)ch;
    }
    else
    {
    	CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position - 1 );
    }
    return 0;
}

int CGXDLMS_HandledGloResponse(CGXDLMSSettings* settings,
                               CGXReplyData* data, int index)
{
    if (settings->m_Cipher == NULL)
    {
        //Secure connection is not supported.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    //If all frames are read.
    if ((data->m_MoreData  & DLMS_DATA_REQUEST_TYPES_FRAME) == 0)
    {
        DLMS_SECURITY security;
        CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position - 1 );

        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer* tmp = CGXReplyData_GetData(data);
        CGXByteBuffer_Set_2(&bb, tmp, CGXReplyData_GetData(data)->m_Position, CGXReplyData_GetData(data)->m_Size - CGXReplyData_GetData(data)->m_Position );
        CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),index );

        CGXByteBuffer_SetSize(CGXReplyData_GetData(data), index);
        CGXCipher_Decrypt(settings->m_Cipher, CGXDLMSSettings_GetSourceSystemTitle(settings), &bb, &security);

        CGXByteBuffer_Set_2(CGXReplyData_GetData(data), &bb, 0, -1);
        data->m_Command = DLMS_COMMAND_NONE;
        CGXDLMS_GetPdu(settings, data);
        data->m_CipherIndex = (unsigned short)CGXReplyData_GetData(data)->m_Size;

        CGXByteBuffer_d(&bb);
    }
    return 0;
}


int CGXDLMS_GetPdu(CGXDLMSSettings* settings, CGXReplyData* data)
{
    int ret = DLMS_ERROR_CODE_OK;
    unsigned char ch;
    DLMS_COMMAND cmd = data->m_Command;
    // If header is not read yet or GBT message.
    if (cmd == DLMS_COMMAND_NONE || data->m_Gbt)
    {
        // If PDU is missing.
        if (CGXReplyData_GetData(data)->m_Size - CGXReplyData_GetData(data)->m_Position == 0)
        {
            // Invalid PDU.
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        int index = CGXReplyData_GetData(data)->m_Position;
        // Get Command.
        if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
        {
            return ret;
        }
        cmd = (DLMS_COMMAND)ch;
        data->m_Command = cmd;
        switch (cmd)
        {
        case DLMS_COMMAND_READ_RESPONSE:
            if ((ret = CGXDLMS_HandleReadResponse(settings, data, index)) != 0)
            {
                if (ret == DLMS_ERROR_CODE_FALSE)
                {
                    return 0;
                }
                return ret;
            }
            break;
        case DLMS_COMMAND_GET_RESPONSE:
            if ((ret = CGXDLMS_HandleGetResponse(settings, data, index)) != 0)
            {
                if (ret == DLMS_ERROR_CODE_FALSE)
                {
                    return 0;
                }
                return ret;
            }
            break;
        case DLMS_COMMAND_SET_RESPONSE:
            ret = CGXDLMS_HandleSetResponse(settings, data);
            break;
        case DLMS_COMMAND_WRITE_RESPONSE:
            ret = CGXDLMS_HandleWriteResponse(data);
            break;
        case DLMS_COMMAND_METHOD_RESPONSE:
            ret = CGXDLMS_HandleMethodResponse(settings, data);
            break;
        case DLMS_COMMAND_GENERAL_BLOCK_TRANSFER:
            ret = CGXDLMS_HandleGbt(settings, data);
            break;
        case DLMS_COMMAND_AARQ:
        case DLMS_COMMAND_AARE:
            // This is parsed later.
            CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position - 1 );
            break;
        case DLMS_COMMAND_RELEASE_RESPONSE:
            break;
        case DLMS_COMMAND_EXCEPTION_RESPONSE:
            /* TODO:
            throw new GXDLMSException(
                StateError.values()[data.getData().getUInt8() - 1],
                ServiceError.values()[data.getData().getUInt8() - 1]);
                */
        case DLMS_COMMAND_GET_REQUEST:
        case DLMS_COMMAND_READ_REQUEST:
        case DLMS_COMMAND_WRITE_REQUEST:
        case DLMS_COMMAND_SET_REQUEST:
        case DLMS_COMMAND_METHOD_REQUEST:
        case DLMS_COMMAND_RELEASE_REQUEST:
            // Server handles this.
            if ((data->m_MoreData  & DLMS_DATA_REQUEST_TYPES_FRAME) != 0)
            {
                break;
            }
            break;
        case DLMS_COMMAND_GLO_READ_REQUEST:
        case DLMS_COMMAND_GLO_WRITE_REQUEST:
        case DLMS_COMMAND_GLO_GET_REQUEST:
        case DLMS_COMMAND_GLO_SET_REQUEST:
        case DLMS_COMMAND_GLO_METHOD_REQUEST:
            if (settings->m_Cipher == NULL)
            {
                //Secure connection is not supported.
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
            // If all frames are read.
            if ((data->m_MoreData  & DLMS_DATA_REQUEST_TYPES_FRAME) == 0)
            {
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position - 1 );
                DLMS_SECURITY security;
                if ((ret = CGXCipher_Decrypt(settings->m_Cipher, CGXDLMSSettings_GetSourceSystemTitle(settings), CGXReplyData_GetData(data), &security)) != 0)
                {
                    return ret;
                }
                // Get command
                if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
                {
                    return ret;
                }
                cmd = (DLMS_COMMAND)ch;
                data->m_Command = cmd;
            }
            else
            {
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position - 1 );
            }
            // Server handles this.
            break;
        case DLMS_COMMAND_GLO_READ_RESPONSE:
        case DLMS_COMMAND_GLO_WRITE_RESPONSE:
        case DLMS_COMMAND_GLO_GET_RESPONSE:
        case DLMS_COMMAND_GLO_SET_RESPONSE:
        case DLMS_COMMAND_GLO_METHOD_RESPONSE:
            if (settings->m_Cipher == NULL)
            {
                //Secure connection is not supported.
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
            // If all frames are read.
            if ((data->m_MoreData  & DLMS_DATA_REQUEST_TYPES_FRAME) == 0)
            {
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data),CGXReplyData_GetData(data)->m_Position - 1 );

                CGXByteBuffer bb;
                CGXByteBuffer_3(&bb, CGXReplyData_GetData(data));

                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data), index );
                CGXByteBuffer_SetSize(CGXReplyData_GetData(data), index);
                DLMS_SECURITY security;
                if ((ret = CGXCipher_Decrypt(settings->m_Cipher, CGXDLMSSettings_GetSourceSystemTitle(settings), &bb, &security)) != 0)
                {
                    CGXByteBuffer_d(&bb);
                    return ret;
                }
                CGXByteBuffer_Set_2(CGXReplyData_GetData(data), &bb, bb.m_Position, bb.m_Size - bb.m_Position );

                data->m_Command = DLMS_COMMAND_NONE;
                ret = CGXDLMS_GetPdu(settings, data);
                data->m_CipherIndex = (unsigned short)CGXReplyData_GetData(data)->m_Size;

                CGXByteBuffer_d(&bb);
            }
            break;
        case DLMS_COMMAND_GLO_GENERAL_CIPHERING:
            if (settings->m_Server)
            {
                CGXDLMS_HandledGloRequest(settings, data);
            }
            else
            {
                CGXDLMS_HandledGloResponse(settings, data, index);
            }
            break;
        case DLMS_COMMAND_DATA_NOTIFICATION:
            ret = CGXDLMS_HandleDataNotification(settings, data);
            // Client handles this.
            break;
        case DLMS_COMMAND_EVENT_NOTIFICATION:
            // Client handles this.
            break;
        case DLMS_COMMAND_INFORMATION_REPORT:
            // Client handles this.
            break;
        default:
            // Invalid DLMS_COMMAND_
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    else if ((data->m_MoreData  & DLMS_DATA_REQUEST_TYPES_FRAME) == 0)
    {
        // Is whole block is read and if last packet and data is not try to
        // peek.
        if (!data->m_Peek && data->m_MoreData  == DLMS_DATA_REQUEST_TYPES_NONE)
        {
            if (data->m_Command == DLMS_COMMAND_AARE
                || data->m_Command == DLMS_COMMAND_AARQ)
            {
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data), 0);
            }
            else
            {
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data), 1);
            }
            settings->m_BlockIndex = 1;
        }
        // Get command if operating as a server.
        if (settings->m_Server)
        {
            // Ciphered messages are handled after whole PDU is received.
            switch (cmd)
            {
            case DLMS_COMMAND_GLO_READ_REQUEST:
            case DLMS_COMMAND_GLO_WRITE_REQUEST:
            case DLMS_COMMAND_GLO_GET_REQUEST:
            case DLMS_COMMAND_GLO_SET_REQUEST:
            case DLMS_COMMAND_GLO_METHOD_REQUEST:
                data->m_Command = DLMS_COMMAND_NONE;
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data), data->m_CipherIndex);
                ret = CGXDLMS_GetPdu(settings, data);
                break;
            default:
                break;
            }
        }
        else
        {
            // Client do not need a command any more.
            data->m_Command = DLMS_COMMAND_NONE;
            // Ciphered messages are handled after whole PDU is received.
            switch (cmd)
            {
            case DLMS_COMMAND_GLO_READ_RESPONSE:
            case DLMS_COMMAND_GLO_WRITE_RESPONSE:
            case DLMS_COMMAND_GLO_GET_RESPONSE:
            case DLMS_COMMAND_GLO_SET_RESPONSE:
            case DLMS_COMMAND_GLO_METHOD_RESPONSE:
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(data), data->m_CipherIndex);
                ret = CGXDLMS_GetPdu(settings, data);
                break;
            default:
                break;
            }
        }
    }

    // Get data only blocks if SN is used. This is faster.
    if (cmd == DLMS_COMMAND_READ_RESPONSE
        && data->m_CommandType == DLMS_SINGLE_READ_RESPONSE_DATA_BLOCK_RESULT
        && (data->m_MoreData  &  DLMS_DATA_REQUEST_TYPES_FRAME) != 0) {
        return 0;
    }

    // Get data if all data is read or we want to peek data.
    if (CGXReplyData_GetData(data)->m_Position != CGXReplyData_GetData(data)->m_Size
        && (cmd == DLMS_COMMAND_READ_RESPONSE || cmd == DLMS_COMMAND_GET_RESPONSE)
        && (data->m_MoreData  == DLMS_DATA_REQUEST_TYPES_NONE
            || data->m_Peek))
    {
        ret = CGXDLMS_GetValueFromData(settings, data);
    }
    return ret;
}

int CGXDLMS_GetData(CGXDLMSSettings* settings,
                    CGXByteBuffer* reply,
                    CGXReplyData* data)
{
    int ret;
    unsigned char frame = 0;
    // If DLMS frame is generated.
    if (settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
    {
        if ((ret = CGXDLMS_GetHdlcData(settings->m_Server, settings, reply, data, &frame)) != 0)
        {
            return ret;
        }
    }
    else if (settings->m_InterfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        if ((ret = CGXDLMS_GetTcpData(settings, reply, data)) != 0)
        {
            return ret;
        }
    }
    else
    {
        // Invalid Interface type.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    // If all data is not read yet.
    if (!data->m_Complete)
    {
        return DLMS_ERROR_CODE_FALSE;
    }
    CGXDLMS_GetDataFromFrame(reply, data);
    // If keepalive or get next frame request.
    if (frame != 0x13 && (frame & 0x1) != 0)
    {
        if (settings->m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC && CGXReplyData_GetData(data)->m_Size != 0)
        {
            if (reply->m_Position != reply->m_Size) {
                CGXByteBuffer_SetPosition(reply, reply->m_Position + 3);
            }
        }
        if (data->m_Command == DLMS_COMMAND_REJECTED)
        {
            return DLMS_ERROR_CODE_REJECTED;
        }
        return DLMS_ERROR_CODE_OK;
    }
    return CGXDLMS_GetPdu(settings, data);
}

int CGXDLMS_HandleGetResponse(CGXDLMSSettings* settings,
                              CGXReplyData* reply,
                              int index)
{
    int ret;
    unsigned char ch;
    unsigned long number;
    short type;
    unsigned long count;
    CGXByteBuffer* data = CGXReplyData_GetData(reply);

    // Get type.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    type = ch;
    // Get invoke ID and priority.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    // Response normal
    if (type == 1)
    {
        // Result
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            return ret;
        }
        if (ch != 0)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
            {
                return ret;
            }
            return ch;
        }
        ret = CGXDLMS_GetDataFromBlock(data, 0);
    }
    else if (type == 2)
    {
        // GetResponsewithDataBlock
        // Is Last block.
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            return ret;
        }
        if (ch == 0)
        {
            reply->m_MoreData =
                (DLMS_DATA_REQUEST_TYPES)(reply->m_MoreData | DLMS_DATA_REQUEST_TYPES_BLOCK);
        }
        else
        {
            reply->m_MoreData =
                (DLMS_DATA_REQUEST_TYPES)(reply->m_MoreData & ~DLMS_DATA_REQUEST_TYPES_BLOCK);
        }
        // Get Block number.
        if ((ret = CGXByteBuffer_GetUInt32_1(data, &number)) != 0)
        {
            return ret;
        }
        // If meter's block index is zero based or Actaris is read.
        // Actaris SL7000 might return wrong block index sometimes.
        // It's not reseted to 1.
        if (number != 1 && settings->m_BlockIndex == 1)
        {
            settings->m_BlockIndex = number;
        }
        if (number != settings->m_BlockIndex)
        {
            return DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID;
        }
        // Get status.
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            return ret;
        }
        if (ch != 0)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
            {
                return ret;
            }
            return ch;
        }
        else
        {
            // Get data size.
            GXHelpers_GetObjectCount(data, &count);
            // if whole block is read.
            if ((reply->m_MoreData & DLMS_DATA_REQUEST_TYPES_FRAME) == 0)
            {
                // Check Block length.
                if (count > (unsigned long)(data->m_Size - data->m_Position))
                {
                    return DLMS_ERROR_CODE_OUTOFMEMORY;
                }
                reply->m_Command = DLMS_COMMAND_NONE;
            }
            if (count == 0)
            {
                // If meter sends empty data block.
                CGXByteBuffer_SetSize(data, index);
            }
            else
            {
                if ((ret = CGXDLMS_GetDataFromBlock(data, index)) != 0)
                {
                    return ret;
                }
            }
            // If last packet and data is not try to peek.
            if (reply->m_MoreData == DLMS_DATA_REQUEST_TYPES_NONE)
            {
                if (!reply->m_Peek)
                {
                    CGXByteBuffer_SetPosition(data, 0);
                    settings->m_BlockIndex = 1;
                }
            }
        }
    }
    else if (type == 3)
    {
        CGXDLMSVariant values;
        CGXDLMSVariant_1(&values);

        values.st.vt = DLMS_DATA_TYPE_ARRAY;
        // Get response with list.
        //Get count.
        if ((ret = GXHelpers_GetObjectCount(data, &count)) != 0)
        {
            CGXDLMSVariant_d(&values);
            return ret;
        }
        for (unsigned short pos = 0; pos != (unsigned short)count; ++pos) {
            // Result
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
            {
                CGXDLMSVariant_d(&values);
                return ret;
            }
            if (ch != 0)
            {
                if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
                {
                    CGXDLMSVariant_d(&values);
                    return ret;
                }
                CGXDLMSVariant_d(&values);
                return ch;
            }
            else
            {
                reply->m_ReadPosition = CGXReplyData_GetData(reply)->m_Position;
                CGXDLMS_GetValueFromData(settings, reply);
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(reply), reply->m_ReadPosition);
                Vector_push_back( &(values.Arr), CGXReplyData_GetValue(reply));
                CGXDLMSVariant_Clear(CGXReplyData_GetValue(reply));
            }
        }
        CGXReplyData_SetValue(reply, &values);

        CGXDLMSVariant_d(&values);
        return DLMS_ERROR_CODE_FALSE;
    }
    else
    {
        //Invalid Get response.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

int CGXDLMS_HandleWriteResponse(CGXReplyData* data)
{
    unsigned char ch;
    int ret;
    unsigned long count;
    if ((ret = GXHelpers_GetObjectCount(CGXReplyData_GetData(data), &count)) != 0)
    {
        return ret;
    }
    for (unsigned long pos = 0; pos != count; ++pos)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
        {
            return ret;
        }
        if (ch != 0)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(data),&ch)) != 0)
            {
                return ret;
            }
            return ch;
        }
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_ReadResponseDataBlockResult(CGXDLMSSettings* settings,
                                        CGXReplyData* reply,
                                        int index)
{
    int ret;
    unsigned short number;
    unsigned long blockLength;
    unsigned char lastBlock;
    if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(reply), &lastBlock)) != 0)
    {
        return ret;
    }
    // Get Block number.
    if ((ret = CGXByteBuffer_GetUInt16_1(CGXReplyData_GetData(reply), &number)) != 0)
    {
        return ret;
    }
    if ((ret = GXHelpers_GetObjectCount(CGXReplyData_GetData(reply), &blockLength)) != 0)
    {
        return ret;
    }
    // Is Last block.
    if (!lastBlock)
    {
        reply->m_MoreData = (DLMS_DATA_REQUEST_TYPES)(reply->m_MoreData | DLMS_DATA_REQUEST_TYPES_BLOCK);
    }
    else
    {
        reply->m_MoreData = (DLMS_DATA_REQUEST_TYPES)(reply->m_MoreData & ~DLMS_DATA_REQUEST_TYPES_BLOCK);
    }
    // If meter's block index is zero based.
    if (number != 1 && settings->m_BlockIndex == 1)
    {
        settings->m_BlockIndex = number;
    }
    int expectedIndex = settings->m_BlockIndex;
    if (number != expectedIndex)
    {
        //Invalid Block number
        return DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID;
    }
    // If whole block is not read.
    if ((reply->m_MoreData & DLMS_DATA_REQUEST_TYPES_FRAME) != 0)
    {
        CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(reply), index);
        return DLMS_ERROR_CODE_FALSE;
    }
    if (blockLength != CGXByteBuffer_Available(CGXReplyData_GetData(reply)))
    {
        //Invalid block length.
        return DLMS_ERROR_CODE_BLOCK_UNAVAILABLE;
    }
    reply->m_Command = DLMS_COMMAND_NONE;

    CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(reply), index);
    reply->m_TotalCount = 0;
    // If last packet and data is not try to peek.
    if (reply->m_MoreData == DLMS_DATA_REQUEST_TYPES_NONE)
    {
        settings->m_BlockIndex = 1;
    }
    return ret;
}


int CGXDLMS_HandleReadResponse(CGXDLMSSettings* settings,
                               CGXReplyData* reply,
                               int index)
{
    unsigned char ch;
    unsigned long pos, cnt = reply->m_TotalCount;
    int ret;
    // If we are reading value first time or block is handed.
    bool first = reply->m_TotalCount == 0 || reply->m_CommandType == DLMS_SINGLE_READ_RESPONSE_DATA_BLOCK_RESULT;
    if (first)
    {
        if ((ret = GXHelpers_GetObjectCount(CGXReplyData_GetData(reply), &cnt)) != 0)
        {
            return ret;
        }
        reply->m_TotalCount = cnt;
    }

    DLMS_SINGLE_READ_RESPONSE type;

    CGXDLMSVariant values;
    CGXDLMSVariant_1(&values);

    unsigned short number;

    values.st.vt = DLMS_DATA_TYPE_ARRAY;
    for (pos = 0; pos != cnt; ++pos)
    {
        if (CGXByteBuffer_Available(CGXReplyData_GetData(reply)) == 0)
        {
            if (cnt != 1)
            {
                CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(reply), 0);
                CGXReplyData_SetValue(reply, &values);
                reply->m_ReadPosition = CGXReplyData_GetData(reply)->m_Position;
            }

            CGXDLMSVariant_d(&values);
            return DLMS_ERROR_CODE_FALSE;
        }
        // Get status code. Status code is begin of each PDU.
        if (first) {
            if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(reply), &ch)) != 0)
            {
                CGXDLMSVariant_d(&values);
                return ret;
            }
            reply->m_CommandType = ch;
            type = (DLMS_SINGLE_READ_RESPONSE)ch;
        }
        else {
            type = (DLMS_SINGLE_READ_RESPONSE)reply->m_CommandType;
        }
        switch (type)
        {
        case DLMS_SINGLE_READ_RESPONSE_DATA:
            if (cnt == 1)
            {
                ret = CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(reply), 0);
            }
            else
            {
                // If read multiple items.
                reply->m_ReadPosition = CGXReplyData_GetData(reply)->m_Position;
                CGXDLMS_GetValueFromData(settings, reply);
                if (CGXReplyData_GetData(reply)->m_Position == reply->m_ReadPosition)
                {
                    // If multiple values remove command.
                    if (cnt != 1 && reply->m_TotalCount == 0) {
                        ++index;
                    }
                    reply->m_TotalCount = 0;
                    CGXByteBuffer_SetPosition(CGXReplyData_GetData(reply), index);
                    CGXDLMS_GetDataFromBlock(CGXReplyData_GetData(reply), 0);
                    CGXDLMSVariant_Clear(CGXReplyData_GetValue(reply));
                    // Ask that data is parsed after last block is received.
                    reply->m_CommandType = DLMS_SINGLE_READ_RESPONSE_DATA_BLOCK_RESULT;

                    CGXDLMSVariant_d(&values);
                    return DLMS_ERROR_CODE_FALSE;
                }
                CGXByteBuffer_SetPosition(CGXReplyData_GetData(reply), reply->m_ReadPosition);
                Vector_push_back( &(values.Arr), CGXReplyData_GetValue(reply));
                CGXDLMSVariant_Clear(CGXReplyData_GetValue(reply));
            }
            break;
        case DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR:
            // Get error code.
            if ((ret = CGXByteBuffer_GetUInt8_1(CGXReplyData_GetData(reply), &ch)) != 0)
            {
                CGXDLMSVariant_d(&values);
                return ret;
            }

            CGXDLMSVariant_d(&values);
            return ch;
            break;
        case DLMS_SINGLE_READ_RESPONSE_DATA_BLOCK_RESULT:
            if ((ret = CGXDLMS_ReadResponseDataBlockResult(settings, reply, index)) != 0)
            {
                CGXDLMSVariant_d(&values);
                return ret;
            }
            break;
        case DLMS_SINGLE_READ_RESPONSE_BLOCK_NUMBER:
            // Get Block number.
            if ((ret = CGXByteBuffer_GetUInt16_1(CGXReplyData_GetData(reply), &number)) != 0)
            {
                CGXDLMSVariant_d(&values);
                return ret;
            }
            if (number != settings->m_BlockIndex)
            {
                CGXDLMSVariant_d(&values);
                //Invalid Block number
                return DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID;
            }
            settings->m_BlockIndex += 1;
            reply->m_MoreData = (DLMS_DATA_REQUEST_TYPES)(reply->m_MoreData | DLMS_DATA_REQUEST_TYPES_BLOCK);
            break;
        default:
            CGXDLMSVariant_d(&values);
            //HandleReadResponse failed. Invalid tag.
            return DLMS_ERROR_CODE_INVALID_TAG;
        }
    }
    if (Vector_size(&(values.Arr)) != 0)
    {
        CGXReplyData_SetValue(reply, &values);
    }
    if (cnt != 1)
    {
        CGXDLMSVariant_d(&values);
        return DLMS_ERROR_CODE_FALSE;
    }

    CGXDLMSVariant_d(&values);
    return 0;
}

int CGXDLMS_GetTcpData(CGXDLMSSettings* settings,
                       CGXByteBuffer* buff,
                       CGXReplyData* data)
{
    int ret;
    // If whole frame is not received yet.
    if (buff->m_Size - buff->m_Position < 8)
    {
        data->m_Complete = false;
        return DLMS_ERROR_CODE_OK;
    }
    int pos = buff->m_Position;
    unsigned short value;
    data->m_Complete = false;
    while (buff->m_Position != buff->m_Size)
    {
        // Get version
        if ((ret = CGXByteBuffer_GetUInt16_1(buff, &value)) != 0)
        {
            return DLMS_ERROR_CODE_OK;
        }
        if (value == 1)
        {
            // Check TCP/IP addresses.
            CGXDLMS_CheckWrapperAddress(settings, buff);
            // Get length.
            if ((ret = CGXByteBuffer_GetUInt16_1(buff, &value)) != 0)
            {
                return ret;
            }
            bool compleate = !((buff->m_Size - buff->m_Position) < value);
            data->m_Complete = compleate;
            if (!compleate)
            {
                CGXByteBuffer_SetPosition(buff, pos);
                return DLMS_ERROR_CODE_FALSE;
            }
            else
            {
                data->m_PacketLength = buff->m_Position + value;
            }
            break;
        }
        else
        {
            CGXByteBuffer_SetPosition(buff, buff->m_Position - 1);
        }
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_GetAddressBytes(unsigned long value, CGXByteBuffer* bytes)
{
    int ret;
    unsigned long address;
    int size;
    if ((ret = CGXDLMS_GetAddress(value, &address, &size)) != 0)
    {
        return ret;
    }
    if (size == 1)
    {
        CGXByteBuffer_Capacity_2(bytes, 1);
        CGXByteBuffer_SetUInt8_1(bytes, (unsigned char)address);
    }
    else if (size == 2)
    {
        CGXByteBuffer_Capacity_2(bytes, 2);
        CGXByteBuffer_SetUInt16(bytes, (unsigned short)address);
    }
    else if (size == 4)
    {
        CGXByteBuffer_Capacity_2(bytes, 4);
        CGXByteBuffer_SetUInt32(bytes, (unsigned long)address);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_GetValueFromData(CGXDLMSSettings* settings, CGXReplyData* reply)
{
    int ret;

    CGXDataInfo info;
    CGXDataInfo_(&info);

    if (CGXReplyData_GetValue(reply)->st.vt == DLMS_DATA_TYPE_ARRAY)
    {
        info.m_Type = DLMS_DATA_TYPE_ARRAY;
        info.m_Count = reply->m_TotalCount;
        info.m_Index = CGXReplyData_GetCount(reply);
    }

    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    int index = CGXReplyData_GetData(reply)->m_Position;
    CGXByteBuffer_SetPosition(CGXReplyData_GetData(reply), reply->m_ReadPosition);
    if ((ret = GXHelpers_GetData(CGXReplyData_GetData(reply), &info, &value)) != 0)
    {
        CGXDLMSVariant_d(&value);
        return ret;
    }
    // If new data.
    if (value.st.vt != DLMS_DATA_TYPE_NONE)
    {
        if (value.st.vt != DLMS_DATA_TYPE_ARRAY)
        {
            reply->m_DataType = info.m_Type;
            CGXReplyData_SetValue(reply, &value);
            reply->m_TotalCount = 0;
            reply->m_ReadPosition = CGXReplyData_GetData(reply)->m_Position;
        }
        else
        {
            if (Vector_size(&(value.Arr)) != 0)
            {
                if (CGXReplyData_GetValue(reply)->st.vt == DLMS_DATA_TYPE_NONE)
                {
                    CGXReplyData_SetValue(reply, &value);
                }
                else
                {
                    CGXDLMSVariant tmp;
                    CGXDLMSVariant_2(&tmp, CGXReplyData_GetValue(reply));

                    // tmp.Arr.insert(tmp.Arr.end(), value.Arr.begin(), value.Arr.end());
                    for (unsigned int it = Vector_begin(&(value.Arr));
                         it != Vector_end(&(value.Arr)); ++it)
                    {
                        Vector_push_back(&(tmp.Arr), Vector_at(&(value.Arr), it));
                    }

                    CGXReplyData_SetValue(reply, &tmp);

                    CGXDLMSVariant_d(&tmp);
                }
            }
            reply->m_ReadPosition = CGXReplyData_GetData(reply)->m_Position;
            // Element count.
            reply->m_TotalCount = info.m_Count;
        }
    }
    else if (info.m_Compleate
        && reply->m_Command == DLMS_COMMAND_DATA_NOTIFICATION)
    {
        // If last item is null. This is a special case.
        reply->m_ReadPosition = CGXReplyData_GetData(reply)->m_Position;
    }
    CGXByteBuffer_SetPosition(CGXReplyData_GetData(reply), index);

    // If last data frame of the data block is read.
    if (reply->m_Command != DLMS_COMMAND_DATA_NOTIFICATION
        && info.m_Compleate
        && reply->m_MoreData == DLMS_DATA_REQUEST_TYPES_NONE)
    {
        // If all blocks are read.
        settings->m_BlockIndex = 1;
        CGXByteBuffer_SetPosition(CGXReplyData_GetData(reply), 0);
    }

    CGXDLMSVariant_d(&value);
    return 0;
}

void CGXDLMS_GetDataFromFrame(CGXByteBuffer* reply, CGXReplyData* info)
{
    CGXByteBuffer* data = CGXReplyData_GetData(info);
    int offset = data->m_Size;
    int cnt = info->m_PacketLength - reply->m_Position;
    if (cnt != 0)
    {
        CGXByteBuffer_Capacity_2(data, offset + cnt);
        CGXByteBuffer_Set_2(data, reply, reply->m_Position, cnt);
    }
    // Set position to begin of new data.
    CGXByteBuffer_SetPosition(data, offset);
}

void CGXDLMS_GetLLCBytes(bool server, CGXByteBuffer* data)
{
    if (server)
    {
        CGXByteBuffer_Compare(data, (unsigned char*)LLC_SEND_BYTES, 3);
    }
    else
    {
        CGXByteBuffer_Compare(data, (unsigned char*)LLC_REPLY_BYTES, 3);
    }
}

int CGXDLMS_CheckWrapperAddress(CGXDLMSSettings* settings,
                                CGXByteBuffer* buff)
{
    int ret;
    unsigned short value;
    if (settings->m_Server)
    {
        if ((ret = CGXByteBuffer_GetUInt16_1(buff, &value)) != 0)
        {
            return ret;
        }
        // Check that client addresses match.
        if (settings->m_ClientAddress != 0
            && settings->m_ClientAddress != value)
        {
            return DLMS_ERROR_CODE_INVALID_CLIENT_ADDRESS;
        }
        else
        {
            settings->m_ClientAddress = value;
        }

        if ((ret = CGXByteBuffer_GetUInt16_1(buff, &value)) != 0)
        {
            return ret;
        }
        // Check that server addresses match.
        if (settings->m_ServerAddress != 0
            && settings->m_ServerAddress != value)
        {
            return DLMS_ERROR_CODE_INVALID_SERVER_ADDRESS;
        }
        else
        {
            settings->m_ServerAddress = value;
        }
    }
    else
    {
        if ((ret = CGXByteBuffer_GetUInt16_1(buff, &value)) != 0)
        {
            return ret;
        }
        // Check that server addresses match.
        if (settings->m_ServerAddress != 0
            && settings->m_ServerAddress != value)
        {
            return DLMS_ERROR_CODE_INVALID_SERVER_ADDRESS;
        }
        else
        {
            settings->m_ServerAddress = value;
        }

        if ((ret = CGXByteBuffer_GetUInt16_1(buff, &value)) != 0)
        {
            return ret;
        }
        // Check that client addresses match.
        if (settings->m_ClientAddress != 0
            && settings->m_ClientAddress != value)
        {
            return DLMS_ERROR_CODE_INVALID_CLIENT_ADDRESS;
        }
        else
        {
            settings->m_ClientAddress = value;
        }
    }
    return DLMS_ERROR_CODE_OK;
}

unsigned short CGXDLMS_CountFCS16(CGXByteBuffer* buff, int index, int count)
{
    int ret;
    unsigned char ch;
    unsigned short fcs16 = 0xFFFF;
    for (short pos = 0; pos < count; ++pos)
    {
        if ((ret = CGXByteBuffer_GetUInt8_2(buff, index + pos, &ch)) != 0)
        {
            return ret;
        }
        fcs16 = (fcs16 >> 8) ^ FCS16Table[(fcs16 ^ ch) & 0xFF];
    }
    fcs16 = ~fcs16;
    fcs16 = ((fcs16 >> 8) & 0xFF) | (fcs16 << 8);
    return fcs16;
}

int CGXDLMS_GetActionInfo(DLMS_OBJECT_TYPE objectType,
                          unsigned char* value,
                          unsigned char* count)
{
    switch (objectType)
    {
    case DLMS_OBJECT_TYPE_DATA:
    case DLMS_OBJECT_TYPE_ACTION_SCHEDULE:
    case DLMS_OBJECT_TYPE_ALL:
    case DLMS_OBJECT_TYPE_AUTO_ANSWER:
    case DLMS_OBJECT_TYPE_AUTO_CONNECT:
    case DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP:
    case DLMS_OBJECT_TYPE_GPRS_SETUP:
    case DLMS_OBJECT_TYPE_IEC_HDLC_SETUP:
    case DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP:
    case DLMS_OBJECT_TYPE_IEC_TWISTED_PAIR_SETUP:
    case DLMS_OBJECT_TYPE_MODEM_CONFIGURATION:
    case DLMS_OBJECT_TYPE_PPP_SETUP:
    case DLMS_OBJECT_TYPE_REGISTER_MONITOR:
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_STARTUP:
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_JOIN:
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_APS_FRAGMENTATION:
    case DLMS_OBJECT_TYPE_ZIG_BEE_NETWORK_CONTROL:
    case DLMS_OBJECT_TYPE_SCHEDULE:
    case DLMS_OBJECT_TYPE_SMTP_SETUP:
    case DLMS_OBJECT_TYPE_STATUS_MAPPING:
    case DLMS_OBJECT_TYPE_TCP_UDP_SETUP:
    case DLMS_OBJECT_TYPE_UTILITY_TABLES:
        *value = 00;
        *count = 0;
        break;
    case DLMS_OBJECT_TYPE_IMAGE_TRANSFER:
        *value = 0x40;
        *count = 4;
        break;
    case DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR:
        *value = 0x50;
        *count = 1;
        break;
    case DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME:
        *value = 0x60;
        *count = 4;
        break;
    case DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME:
        *value = 0x20;
        *count = 8;
        break;
    case DLMS_OBJECT_TYPE_CLOCK:
        *value = 0x60;
        *count = 6;
        break;
    case DLMS_OBJECT_TYPE_DEMAND_REGISTER:
        *value = 0x48;
        *count = 2;
        break;
    case DLMS_OBJECT_TYPE_EXTENDED_REGISTER:
        *value = 0x38;
        *count = 1;
        break;
    case DLMS_OBJECT_TYPE_IP4_SETUP:
        *value = 0x60;
        *count = 3;
        break;
    case DLMS_OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP:
        *value = 0x60;
        *count = 8;
        break;
    case DLMS_OBJECT_TYPE_PROFILE_GENERIC:
        *value = 0x58;
        *count = 4;
        break;
    case DLMS_OBJECT_TYPE_REGISTER:
        *value = 0x28;
        *count = 1;
        break;
    case DLMS_OBJECT_TYPE_REGISTER_ACTIVATION:
        *value = 0x30;
        *count = 3;
        break;
    case DLMS_OBJECT_TYPE_REGISTER_TABLE:
        *value = 0x28;
        *count = 2;
        break;
    case DLMS_OBJECT_TYPE_SAP_ASSIGNMENT:
    case DLMS_OBJECT_TYPE_SCRIPT_TABLE:
        *value = 0x20;
        *count = 1;
        break;
    case DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE:
        *value = 0x10;
        *count = 2;
        break;
    case DLMS_OBJECT_TYPE_DISCONNECT_CONTROL:
        *value = 0x20;
        *count = 2;
        break;
    case DLMS_OBJECT_TYPE_PUSH_SETUP:
        *value = 0x38;
        *count = 1;
        break;
    case DLMS_OBJECT_TYPE_DLMS_SECURITY_SETUP:
        *value = 0x30;
        *count = 8;
    break;
    default:
        *count = *value = 0;
        break;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMS_AppendData(CGXDLMSObject* obj,
                       unsigned char index,
                       CGXByteBuffer* bb,
                       CGXDLMSVariant* value)
{

    int ret;
    DLMS_DATA_TYPE tp;
    if ((ret = obj->GetDataType(obj, index, &tp)) != 0)
    {
        return ret;
    }
    if (tp == DLMS_DATA_TYPE_ARRAY)
    {
        if (value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
        	CGXByteBuffer_Set_1(bb, value->st.un.byteArr, CGXDLMSVariant_GetSize_1(value));
            return 0;
        }
    }
    else
    {
        if (tp == DLMS_DATA_TYPE_NONE)
        {
            tp = value->st.vt;
            // If data type is not defined for Date Time it is write as
            // octet string.
            if (tp == DLMS_DATA_TYPE_DATETIME)
            {
                tp = DLMS_DATA_TYPE_OCTET_STRING;
            }
        }
    }
    return GXHelpers_SetData(bb, tp, value);
}

int CGXDLMS_ParseSnrmUaResponse(CGXByteBuffer* data,
                                CGXDLMSLimits* limits)
{
    unsigned char ch, id, len;
    unsigned short ui;
    unsigned long ul;
    int ret;
    //If default settings are used.
    if (data->m_Size == 0)
    {
    	limits->m_MaxInfoRX = DEFAULT_MAX_INFO_RX;
    	limits->m_MaxInfoTX = DEFAULT_MAX_INFO_TX;
    	limits->m_WindowSizeTX = DEFAULT_WINDOWS_SIZE_RX;
    	limits->m_WindowSizeRX = DEFAULT_WINDOWS_SIZE_TX;
        return 0;
    }
    // Skip FromatID
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    // Skip Group ID.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    // Skip Group len
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }

    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    while (data->m_Position < data->m_Size)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &id)) != 0)
        {
            CGXDLMSVariant_d(&value);
            return ret;
        }
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &len)) != 0)
        {
            CGXDLMSVariant_d(&value);
            return ret;
        }
        switch (len)
        {
        case 1:
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
            {
                CGXDLMSVariant_d(&value);
                return ret;
            }
            CGXDLMSVariant_copy_14(&value, ch);
            break;
        case 2:
            if ((ret = CGXByteBuffer_GetUInt16_1(data, &ui)) != 0)
            {
                CGXDLMSVariant_d(&value);
                return ret;
            }
            CGXDLMSVariant_copy_15(&value, ui);
            break;
        case 4:
            if ((ret = CGXByteBuffer_GetUInt32_1(data, &ul)) != 0)
            {
                CGXDLMSVariant_d(&value);
                return ret;
            }
            CGXDLMSVariant_copy_17(&value, ul);
            break;
        default:
            CGXDLMSVariant_d(&value);
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        // RX / TX are delivered from the partner's point of view =>
        // reversed to ours
        switch (id)
        {
        case HDLC_INFO_MAX_INFO_TX:
        	limits->m_MaxInfoRX = (unsigned char)CGXDLMSVariant_ToInteger(&value);
            break;
        case HDLC_INFO_MAX_INFO_RX:
        	limits->m_MaxInfoTX = (unsigned char)CGXDLMSVariant_ToInteger(&value);
            break;
        case HDLC_INFO_WINDOW_SIZE_TX:
        	limits->m_WindowSizeTX = (unsigned char)CGXDLMSVariant_ToInteger(&value);
            break;
        case HDLC_INFO_WINDOW_SIZE_RX:
        	limits->m_WindowSizeRX = (unsigned char)CGXDLMSVariant_ToInteger(&value);
            break;
        default:
            ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
            break;
        }
    }

    CGXDLMSVariant_d(&value);
    return ret;
}

void CGXDLMS_AppendHdlcParameter(CGXByteBuffer* data, unsigned short value)
{
    if (value < 0x100)
    {
        CGXByteBuffer_SetUInt8_1(data, 1);
        CGXByteBuffer_SetUInt8_1(data, (unsigned char)value);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(data, 2);
        CGXByteBuffer_SetUInt16(data, value);
    }
}
