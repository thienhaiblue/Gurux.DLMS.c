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

#ifndef GXREPLYDATA_H
#define GXREPLYDATA_H

#include "GXDLMSConverter.h"
#include "GXBytebuffer.h"
#include "GXDLMSVariant.h"

typedef struct
{
    /**
     * Is more data available.
     */
    DLMS_DATA_REQUEST_TYPES m_MoreData;
    /**
     * Received command.
     */
    DLMS_COMMAND m_Command;

    /**
    * Received command type.
    */
    unsigned char m_CommandType;

    /**
     * Received data.
     */
    CGXByteBuffer m_Data;
    /**
     * Is frame complete.
     */
    bool m_Complete;

    /**
     * Read value.
     */
    CGXDLMSVariant m_DataValue;

    /**
     * Expected count of element in the array.
     */
    int m_TotalCount;

    /**
     * Last read position. This is used in peek to solve how far data is read.
     */
    unsigned long m_ReadPosition;

    /**
     * Packet Length.
     */
    int m_PacketLength;

    /**
     * Try Get value.
     */
    bool m_Peek;

    DLMS_DATA_TYPE m_DataType;

    /**
     * Cipher index is position where data is decrypted.
     */
    unsigned short m_CipherIndex;

    /**
    * Is received message General Block Transfer message.
    */
    bool m_Gbt;

    /**
     * Data notification date time.
     */
    struct tm* m_Time;
} CGXReplyData;

/**
 * Constructor.
 *
 * @param more
 *            Is more data available.
 * @param cmd
 *            Received command.
 * @param buff
 *            Received data.
 * @param forComplete
 *            Is frame complete.
 */
extern void CGXReplyData_1(
    CGXReplyData* p,
    DLMS_DATA_REQUEST_TYPES more,
    DLMS_COMMAND cmd,
    CGXByteBuffer* buff,
    bool complete);

/**
 * Constructor.
 */
extern void CGXReplyData_2(CGXReplyData* p);

extern DLMS_DATA_TYPE CGXReplyData_GetValueType(CGXReplyData* p);

extern void CGXReplyData_SetValueType(CGXReplyData* p, DLMS_DATA_TYPE value);


extern CGXDLMSVariant* CGXReplyData_GetValue(CGXReplyData* p);


extern void CGXReplyData_SetValue(CGXReplyData* p, CGXDLMSVariant* value);

extern unsigned long CGXReplyData_GetReadPosition(CGXReplyData* p);

extern void CGXReplyData_SetReadPosition(CGXReplyData* p, unsigned long value);

extern int CGXReplyData_GetPacketLength(CGXReplyData* p);

extern void CGXReplyData_SetPacketLength(CGXReplyData* p, int value);

extern void CGXReplyData_SetCommand(CGXReplyData* p, DLMS_COMMAND value);

extern void CGXReplyData_SetCommandType(CGXReplyData* p, unsigned char value);

extern unsigned char CGXReplyData_GetCommandType(CGXReplyData* p);


extern void CGXReplyData_SetData(CGXReplyData* p, CGXByteBuffer* value);

extern void CGXReplyData_SetComplete(CGXReplyData* p, bool value);

extern void CGXReplyData_SetTotalCount(CGXReplyData* p, int value);

/**
 * Reset data values to default.
 */
extern void CGXReplyData_Clear(CGXReplyData* p);

/**
 * @return Is more data available.
 */
extern bool CGXReplyData_IsMoreData(CGXReplyData* p);

/**
 * Is more data available.
 *
 * @return Return None if more data is not available or Frame or Block type.
 */
extern DLMS_DATA_REQUEST_TYPES CGXReplyData_GetMoreData(CGXReplyData* p);

extern void CGXReplyData_SetMoreData(CGXReplyData* p, DLMS_DATA_REQUEST_TYPES value);


/**
 * Get received command.
 *
 * @return Received command.
 */
extern DLMS_COMMAND CGXReplyData_GetCommand(CGXReplyData* p);

/**
 * Get received data.
 *
 * @return Received data.
 */
extern CGXByteBuffer* CGXReplyData_GetData(CGXReplyData* p);

/**
 * Is frame complete.
 *
 * @return Returns true if frame is complete or false if bytes is missing.
 */
extern bool CGXReplyData_IsComplete(CGXReplyData* p);

/**
 * Get total count of element in the array. If this method is used peek must
 * be Set true.
 *
 * @return Count of element in the array.
 * @see peek
 * @see GetCount
 */
extern int CGXReplyData_GetTotalCount(CGXReplyData* p);

/**
 * Get count of read elements. If this method is used peek must be Set true.
 *
 * @return Count of read elements.
 * @see peek
 * @see GetTotalCount
 */
extern int CGXReplyData_GetCount(CGXReplyData* p);

/**
 * Get is value try to peek.
 *
 * @return Is value try to peek.
 * @see GetCount
 * @see GetTotalCount
 */
extern bool CGXReplyData_GetPeek(CGXReplyData* p);

/**CGXReplyData__(p);
 * Set is value try to peek.
 *
 * @param value
 *            Is value try to peek.
 */
extern void CGXReplyData_SetPeek(CGXReplyData* p, bool value);

/**
 * @return Cipher index is position where data is decrypted.
 */
extern unsigned short CGXReplyData_GetCipherIndex(CGXReplyData* p);

/**
 * @param cipherIndex
 *            Cipher index is position where data is decrypted.
 */
extern void CGXReplyData_SetCipherIndex(CGXReplyData* p, unsigned short value);

/**
 * @return Is received message General Block Transfer message.
 */
extern bool CGXReplyData_GetGbt(CGXReplyData* p);

/**
 * @param Is
 *            received message General Block Transfer message.
 */
extern void CGXReplyData_SetGbt(CGXReplyData* p, bool value);

/**
 * @return Data notification date time.
 */
extern struct tm* CGXReplyData_GetTime(CGXReplyData* p);


/**
 * @param time
 *            Data notification date time.
 */
extern void CGXReplyData_SetTime(CGXReplyData* p, struct tm* value);

extern void CGXReplyData_d(CGXReplyData* p);

#endif //GXREPLYDATA_H
