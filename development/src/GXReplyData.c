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

#include "../include/GXReplyData.h"
#include "../include/DLMSPort.h"

static void CGXReplyData__(CGXReplyData* p)
{
    CGXByteBuffer_1(&p->m_Data);
    CGXDLMSVariant_1(&p->m_DataValue);
}

void CGXReplyData_1(
	CGXReplyData* p,
    DLMS_DATA_REQUEST_TYPES more,
    DLMS_COMMAND cmd,
    CGXByteBuffer* buff,
    bool complete)
{
    CGXReplyData__(p);

    CGXReplyData_Clear(p);
    p->m_DataType = DLMS_DATA_TYPE_NONE;
    p->m_MoreData = more;
    p->m_Command = cmd;
    p->m_CommandType = 0;
    CGXByteBuffer_copy(&(p->m_Data), buff);
    p->m_Complete = complete;
    p->m_Time = NULL;
}

void CGXReplyData_2(CGXReplyData* p)
{
    CGXReplyData__(p);

    CGXReplyData_Clear(p);
}

CGXDLMSVariant* CGXReplyData_GetValue(CGXReplyData* p)
{
    return &(p->m_DataValue);
}

void CGXReplyData_SetValue(CGXReplyData* p, CGXDLMSVariant* value)
{
    CGXDLMSVariant_copy_1(&(p->m_DataValue), value);
}

void CGXReplyData_SetData(CGXReplyData* p, CGXByteBuffer* value)
{
    CGXByteBuffer_copy(&(p->m_Data), value);
}

void CGXReplyData_Clear(CGXReplyData* p)
{
    p->m_Time = NULL;
    p->m_MoreData = DLMS_DATA_REQUEST_TYPES_NONE;
    p->m_Command = DLMS_COMMAND_NONE;
    CGXByteBuffer_Clear(&(p->m_Data));
    p->m_Complete = false;
    p->m_Peek = false;
    p->m_TotalCount = 0;
    CGXDLMSVariant_Clear(&(p->m_DataValue));
    p->m_ReadPosition = 0;
    p->m_PacketLength = 0;
    p->m_DataType = DLMS_DATA_TYPE_NONE;
    p->m_CipherIndex = 0;
    p->m_Gbt = false;
}

bool CGXReplyData_IsMoreData(CGXReplyData* p)
{
    return p->m_MoreData != DLMS_DATA_REQUEST_TYPES_NONE;
}

CGXByteBuffer* CGXReplyData_GetData(CGXReplyData* p)
{
    return &(p->m_Data);
}

int CGXReplyData_GetCount(CGXReplyData* p)
{
    if (p->m_DataValue.st.vt == DLMS_DATA_TYPE_ARRAY)
    {
        return (int) Vector_size(&(p->m_DataValue.Arr));
    }
    return 0;
}

void CGXReplyData_SetTime(CGXReplyData* p, struct tm* value)
{
    if (value == NULL)
    {
        if (p->m_Time != NULL)
        {
            DLMSPort_free(p->m_Time);
        }
        p->m_Time = value;
    }
    else
    {
        if (p->m_Time == NULL)
        {
            p->m_Time = (struct tm*) DLMSPort_malloc(sizeof(struct tm));
        }
        memcpy(p->m_Time, value, sizeof(struct tm));
    }
}

void CGXReplyData_d(CGXReplyData* p)
{
    CGXByteBuffer_d(&p->m_Data);
    CGXDLMSVariant_d(&p->m_DataValue);
}
