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

#include <stdlib.h>
#include <stdio.h>

#include "../include/errorcodes.h"
#include "../include/GXBytebuffer.h"
#include "../include/GXHelpers.h"
#include "../include/DLMSPort.h"
#include <stdbool.h>

const unsigned char VECTOR_CAPACITY = 50;

//Constructor.
void CGXByteBuffer_1(CGXByteBuffer *p)
{
    p->m_Capacity = 0;
    p->m_Data = NULL;
    p->m_Position = 0;
    p->m_Size = 0;
}

//Constructor.
void CGXByteBuffer_2(CGXByteBuffer *p, int capacity)
{
    p->m_Capacity = 0;
    p->m_Data = NULL;
    p->m_Position = 0;
    p->m_Size = 0;
    CGXByteBuffer_Capacity_2(p, capacity);
}

//Copy constructor.
void CGXByteBuffer_3(CGXByteBuffer *p, const CGXByteBuffer* value)
{
    p->m_Capacity = 0;
    p->m_Data = NULL;
    p->m_Position = 0;
    p->m_Size = 0;
    if (value->m_Size - value->m_Position != 0)
    {
        CGXByteBuffer_Set_1(p, value->m_Data + value->m_Position, value->m_Size - value->m_Position);
    }
}

//Destructor.
void CGXByteBuffer_d(CGXByteBuffer *p)
{
    CGXByteBuffer_Clear(p);
}

unsigned long CGXByteBuffer_Available(CGXByteBuffer *p)
{
    return p->m_Size - p->m_Position;
}

void CGXByteBuffer_SetSize(CGXByteBuffer *p, unsigned long value)
{
    assert(!(value > p->m_Capacity));
    p->m_Size = value;
    if (p->m_Position > p->m_Size)
    {
        p->m_Position = p->m_Size;
    }
}

int CGXByteBuffer_IncreaseSize(CGXByteBuffer *p, unsigned long size)
{
    if (size > 1)
    {
        return -1;
    }
    p->m_Size += size;
    return p->m_Size;
}

//Sets position of the buffer.
void CGXByteBuffer_SetPosition(CGXByteBuffer *p, unsigned long value)
{
    assert(!(value > p->m_Size));
    p->m_Position = value;
}

// Allocate new size for the array in bytes.
void CGXByteBuffer_Capacity_2(CGXByteBuffer *p, unsigned long capacity)
{
    p->m_Capacity = capacity;
    if (capacity == 0)
    {
        if (p->m_Data != NULL)
        {
            DLMSPort_free(p->m_Data);
            p->m_Data = NULL;
        }
        p->m_Size = 0;
        p->m_Position = 0;
    }
    else
    {
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
        if (p->m_Size > capacity)
        {
            p->m_Size = capacity;
        }
    }
}

// Fill buffer it with zeros.
void CGXByteBuffer_Zero(CGXByteBuffer *p, unsigned long index, unsigned long count)
{
    if (index + count > p->m_Capacity)
    {
        CGXByteBuffer_Capacity_2(p, index + count);
    }
    if (p->m_Size < index + count)
    {
        p->m_Size = index + count;
    }
    memset(p->m_Data + index, 0, count);
}

// Push new data to the byteArray.
void CGXByteBuffer_SetUInt8_1(CGXByteBuffer *p, unsigned char item)
{
    CGXByteBuffer_SetUInt8_2(p, p->m_Size, item);
    ++(p->m_Size);
}

void CGXByteBuffer_SetUInt8_2(CGXByteBuffer *p, unsigned long index, unsigned char item)
{
    if (p->m_Capacity == 0 || index + 1 > p->m_Capacity)
    {
        p->m_Capacity += VECTOR_CAPACITY;
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
    }
    p->m_Data[index] = item;
}

void CGXByteBuffer_SetUInt16(CGXByteBuffer *p, unsigned short item)
{

    if (p->m_Capacity == 0 || p->m_Size + 2 > p->m_Capacity)
    {
        p->m_Capacity += VECTOR_CAPACITY;
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
    }
    p->m_Data[p->m_Size] = (item >> 8) & 0xFF;
    p->m_Data[p->m_Size + 1] = item & 0xFF;
    p->m_Size += 2;
}

void CGXByteBuffer_SetUInt32(CGXByteBuffer *p, unsigned long item)
{

    CGXByteBuffer_SetUInt32ByIndex(p, p->m_Size, item);
    p->m_Size += 4;
}

void CGXByteBuffer_SetUInt32ByIndex(CGXByteBuffer *p, unsigned long index, unsigned long item)
{
    if (p->m_Capacity == 0 || index + 4 > p->m_Capacity)
    {
        p->m_Capacity += VECTOR_CAPACITY;
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
    }
    p->m_Data[index] = (item >> 24) & 0xFF;
    p->m_Data[index + 1] = (item >> 16) & 0xFF;
    p->m_Data[index + 2] = (item >> 8) & 0xFF;
    p->m_Data[index + 3] = item & 0xFF;
}

void CGXByteBuffer_SetUInt64(CGXByteBuffer *p, unsigned long long item)
{
    if (p->m_Capacity == 0 || p->m_Size + 8 > p->m_Capacity)
    {
        p->m_Capacity += VECTOR_CAPACITY;
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
    }
    p->m_Data[p->m_Size] = (unsigned char)((item >> 56) & 0xFF);
    p->m_Data[p->m_Size + 1] = (item >> 48) & 0xFF;
    p->m_Data[p->m_Size + 2] = (item >> 40) & 0xFF;
    p->m_Data[p->m_Size + 3] = (item >> 32) & 0xFF;
    p->m_Data[p->m_Size + 4] = (item >> 24) & 0xFF;
    p->m_Data[p->m_Size + 5] = (item >> 16) & 0xFF;
    p->m_Data[p->m_Size + 6] = (item >> 8) & 0xFF;
    p->m_Data[p->m_Size + 7] = item & 0xFF;
    p->m_Size += 8;
}

void CGXByteBuffer_SetFloat(CGXByteBuffer *p, float value)
{
    typedef union
    {
        float value;
        char b[sizeof(float)];
    } HELPER;

    HELPER tmp;
    tmp.value = value;
    if (p->m_Capacity == 0 || p->m_Size + 4 > p->m_Capacity)
    {
        p->m_Capacity += VECTOR_CAPACITY;
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
    }
    p->m_Data[p->m_Size] = tmp.b[3];
    p->m_Data[p->m_Size + 1] = tmp.b[2];
    p->m_Data[p->m_Size + 2] = tmp.b[1];
    p->m_Data[p->m_Size + 3] = tmp.b[0];
    p->m_Size += 4;
}

void CGXByteBuffer_SetDouble(CGXByteBuffer *p, double value)
{
    typedef union
    {
        double value;
        char b[sizeof(double)];
    } HELPER;

    HELPER tmp;
    tmp.value = value;
    if (p->m_Capacity == 0 || p->m_Size + 8 > p->m_Capacity)
    {
        p->m_Capacity += VECTOR_CAPACITY;
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
    }
    p->m_Data[p->m_Size] = tmp.b[7];
    p->m_Data[p->m_Size + 1] = tmp.b[6];
    p->m_Data[p->m_Size + 2] = tmp.b[5];
    p->m_Data[p->m_Size + 3] = tmp.b[4];
    p->m_Data[p->m_Size + 4] = tmp.b[3];
    p->m_Data[p->m_Size + 5] = tmp.b[2];
    p->m_Data[p->m_Size + 6] = tmp.b[1];
    p->m_Data[p->m_Size + 7] = tmp.b[0];
    p->m_Size += 8;
}

void CGXByteBuffer_SetInt8(CGXByteBuffer *p, char item)
{
    CGXByteBuffer_SetUInt8_1(p, (unsigned char)item);
}

void CGXByteBuffer_SetInt16(CGXByteBuffer *p, short item)
{
    CGXByteBuffer_SetUInt16(p, (unsigned short)item);
}

void CGXByteBuffer_SetInt32(CGXByteBuffer *p, long item)
{
    CGXByteBuffer_SetUInt32(p, (unsigned long)item);
}

void CGXByteBuffer_SetInt64(CGXByteBuffer *p, long long item)
{
    CGXByteBuffer_SetUInt64(p, (unsigned long long) item);
}

void CGXByteBuffer_Set_1(CGXByteBuffer *p, const void* pSource, unsigned long count)
{
    if (pSource != NULL && count != 0)
    {
        if (p->m_Size + count > p->m_Capacity)
        {
            //First time data is reserved only for the added data.
            if (p->m_Capacity == 0)
            {
                p->m_Capacity = count;
            }
            else
            {
                p->m_Capacity += count + VECTOR_CAPACITY;
            }
            p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
        }
        memcpy(p->m_Data + p->m_Size, pSource, count);
        p->m_Size += count;
    }
}

void CGXByteBuffer_Set_2(CGXByteBuffer *p, CGXByteBuffer* data, unsigned long index, unsigned long count)
{
    if (data != NULL)
    {
        if (count == (unsigned long)-1)
        {
            count = data->m_Size - index;
        }
        CGXByteBuffer_Set_1(p, data->m_Data + index, count);
        data->m_Position += count;
    }
}

void CGXByteBuffer_AddString_2(CGXByteBuffer *p, const char* value)
{
    if (value != NULL)
    {
        unsigned long len = (unsigned long)strlen(value);
        CGXByteBuffer_Set_1(p, value, len);
    }
}

void CGXByteBuffer_AddString_1(CGXByteBuffer *p, const String* value)
{
    CGXByteBuffer_Set_1(p, value->c, (unsigned long)String_length(value));
}

void CGXByteBuffer_AttachString(CGXByteBuffer *p, char* value)
{
    unsigned long len = (unsigned long)strlen(value);
    CGXByteBuffer_Set_1(p, value, len);
    DLMSPort_free(value);
}

void CGXByteBuffer_Clear(CGXByteBuffer *p)
{
    CGXByteBuffer_Capacity_2(p, 0);
}

int CGXByteBuffer_GetUInt8_1(CGXByteBuffer *p, unsigned char* value)
{
    if (p->m_Position >= p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[p->m_Position];
    ++(p->m_Position);
    return 0;
}

int CGXByteBuffer_GetUInt8_2(CGXByteBuffer *p, unsigned long index, unsigned char* value)
{
    if (index >= p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[index];
    return 0;
}


int CGXByteBuffer_GetUInt16_1(CGXByteBuffer *p, unsigned short* value)
{
    if (p->m_Position + 2 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = (((p->m_Data[p->m_Position] & 0xFF) << 8) | (p->m_Data[p->m_Position + 1] & 0xFF));
    p->m_Position += 2;
    return 0;
}

int CGXByteBuffer_GetUInt32_1(CGXByteBuffer *p, unsigned long* value)
{
    if (p->m_Position + 4 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[p->m_Position] << 24 |
        p->m_Data[p->m_Position + 1] << 16 |
        p->m_Data[p->m_Position + 2] << 8 |
        p->m_Data[p->m_Position + 3];
    p->m_Position += 4;
    return 0;
}

int CGXByteBuffer_GetUInt32LE_1(CGXByteBuffer *p, unsigned long* value)
{
    if (p->m_Position + 4 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[p->m_Position + 3] << 24 |
        p->m_Data[p->m_Position + 2] << 16 |
        p->m_Data[p->m_Position + 1] << 8 |
        p->m_Data[p->m_Position];
    p->m_Position += 4;
    return 0;
}

int CGXByteBuffer_GetUInt32LE_2(CGXByteBuffer *p, unsigned long index, unsigned long* value)
{
    if (index + 4 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[index + 3] << 24 |
        p->m_Data[index + 2] << 16 |
        p->m_Data[index + 1] << 8 |
        p->m_Data[index];
    return 0;
}

void CGXByteBuffer_SetUInt32ByIndexLE(CGXByteBuffer *p, unsigned long index, unsigned long item)
{
    if (p->m_Capacity == 0 || index + 4 > p->m_Capacity)
    {
        p->m_Capacity += VECTOR_CAPACITY;
        p->m_Data = (unsigned char*)DLMSPort_realloc(p->m_Data, p->m_Capacity);
    }
    p->m_Data[index + 3] = (item >> 24) & 0xFF;
    p->m_Data[index + 2] = (item >> 16) & 0xFF;
    p->m_Data[index + 1] = (item >> 8) & 0xFF;
    p->m_Data[index] = item & 0xFF;
}


int CGXByteBuffer_GetInt16(CGXByteBuffer *p, short* value)
{
    if (p->m_Position + 2 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[p->m_Position] << 8 |
        p->m_Data[p->m_Position + 1];
    p->m_Position += 2;
    return 0;
}

int CGXByteBuffer_GetInt32(CGXByteBuffer *p, long* value)
{
    int ret = CGXByteBuffer_GetUInt32_2(p, p->m_Position, (unsigned long*)value);
    p->m_Position += 4;
    return ret;
}

int CGXByteBuffer_GetUInt32_2(CGXByteBuffer *p, unsigned long index, unsigned long* value)
{
    if (index + 4 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[index] << 24 |
        p->m_Data[index + 1] << 16 |
        p->m_Data[index + 2] << 8 |
        p->m_Data[index + 3];
    return 0;
}

int CGXByteBuffer_GetInt64(CGXByteBuffer *p, long long* value)
{
    int ret = CGXByteBuffer_GetUInt64_2(p, p->m_Position, (unsigned long long*) value);
    if (ret == 0)
    {
        p->m_Position += 8;
    }
    return ret;
}

int CGXByteBuffer_GetUInt64_1(CGXByteBuffer *p, unsigned long long* value)
{
    int ret = CGXByteBuffer_GetUInt64_2(p, p->m_Position, value);
    if (ret == 0)
    {
        p->m_Position += 8;
    }
    return ret;
}

int CGXByteBuffer_GetUInt64_2(CGXByteBuffer *p, unsigned long index, unsigned long long* value)
{
    if (index + 8 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = (unsigned long long)p->m_Data[index] << 56 |
        (unsigned long long) p->m_Data[index + 1] << 48 |
        (unsigned long long) p->m_Data[index + 2] << 40 |
        (unsigned long long) p->m_Data[index + 3] << 32 |
        (unsigned long long) p->m_Data[index + 4] << 24 |
        (unsigned long long) p->m_Data[index + 5] << 16 |
        (unsigned long long) p->m_Data[index + 6] << 8 |
        (unsigned long long) p->m_Data[index + 7];
    return 0;
}

int CGXByteBuffer_GetUInt128(CGXByteBuffer *p, unsigned long index, unsigned char* value)
{
    int ret = CGXByteBuffer_GetUInt32_2(p, index, (unsigned long*)value);
    if (ret == 0)
    {
        ret = CGXByteBuffer_GetUInt32_2(p, index + 4, (unsigned long*)value + 1);
        if (ret == 0)
        {
            ret = CGXByteBuffer_GetUInt32_2(p, index + 8, (unsigned long*)value + 2);
            if (ret == 0)
            {
                ret = CGXByteBuffer_GetUInt32_2(p, index + 12, (unsigned long*)value + 3);
            }
        }
    }
    return ret;
}

int CGXByteBuffer_GetFloat(CGXByteBuffer *p, float* value)
{
    if (p->m_Position + 4 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    typedef union
    {
        float value;
        char b[sizeof(float)];
    } HELPER;
    HELPER tmp;
    tmp.b[3] = p->m_Data[p->m_Position];
    tmp.b[2] = p->m_Data[p->m_Position + 1];
    tmp.b[1] = p->m_Data[p->m_Position + 2];
    tmp.b[0] = p->m_Data[p->m_Position + 3];
    *value = tmp.value;
    p->m_Position += 4;
    return 0;
}

int CGXByteBuffer_GetDouble(CGXByteBuffer *p, double* value)
{
    if (p->m_Position + 8 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    typedef union
    {
        double value;
        char b[sizeof(double)];
    } HELPER;
    HELPER tmp;
    tmp.b[7] = p->m_Data[p->m_Position];
    tmp.b[6] = p->m_Data[p->m_Position + 1];
    tmp.b[5] = p->m_Data[p->m_Position + 2];
    tmp.b[4] = p->m_Data[p->m_Position + 3];
    tmp.b[3] = p->m_Data[p->m_Position + 4];
    tmp.b[2] = p->m_Data[p->m_Position + 5];
    tmp.b[1] = p->m_Data[p->m_Position + 6];
    tmp.b[0] = p->m_Data[p->m_Position + 7];
    *value = tmp.value;
    p->m_Position += 8;
    return 0;
}

int CGXByteBuffer_Get(CGXByteBuffer *p, unsigned char* value, unsigned long count)
{
    if (value == NULL || p->m_Size - p->m_Position < count)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    memcpy(value, p->m_Data + p->m_Position, count);
    p->m_Position += count;
    return 0;
}

int CGXByteBuffer_GetUInt16_2(CGXByteBuffer *p, unsigned long index, unsigned short* value)
{
    if (index + 2 > p->m_Size)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    *value = p->m_Data[index] << 8 |
        p->m_Data[index + 1];
    return 0;
}

void CGXByteBuffer_ToString(CGXByteBuffer *p, String *out)
{
    if (p->m_Size != 0)
    {
        //str.append(reinterpret_cast<char const*>(m_Data), m_Size);
        String_append_2(out, (char*) p->m_Data, p->m_Size);
    }
//    return str;
}

String CGXByteBuffer_ToHexString(CGXByteBuffer *p)
{
    return GXHelpers_BytesToHex_1(p->m_Data, p->m_Size);
}

void CGXByteBuffer_AddIntAsString(CGXByteBuffer *p, int value)
{
    char buff[20];
#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 20, "%d", value);
#else
    DLMSPort_sprintf(buff, "%d", value);
#endif
    CGXByteBuffer_AddString_2(p, buff);
}

void CGXByteBuffer_AddDoubleAsString(CGXByteBuffer *p, double value)
{
    char buff[20];
    //Show as integer value if there is no fractal part.
    if (value - (long)value == 0)
    {
        CGXByteBuffer_AddIntAsString(p, (int)value);
    }
    else
    {
#if _MSC_VER > 1000
        DLMSPort_sprintf_s(buff, 20, "%lf", value);
#else
        DLMSPort_sprintf(buff, "%lf", value);
#endif
        CGXByteBuffer_AddString_2(p, buff);
    }
}

/**
    * Returns data as byte array.
    *
    * @return Byte buffer as a byte array.
    */
int CGXByteBuffer_SubArray(CGXByteBuffer *p, unsigned long index, int count, CGXByteBuffer* bb)
{
    CGXByteBuffer_Clear(bb);
    CGXByteBuffer_Set_2(bb, p, index, count);
    return 0;
}

int CGXByteBuffer_Move(CGXByteBuffer *p, unsigned long srcPos, unsigned long destPos, unsigned long count)
{
    if (p->m_Size < destPos + count)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (count != 0)
    {
        //Do not use memcpy here!
        memmove(p->m_Data + destPos, p->m_Data + srcPos, count);
        p->m_Size = (destPos + count);
        if (p->m_Position > p->m_Size)
        {
            p->m_Position = p->m_Size;
        }
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXByteBuffer_Trim(CGXByteBuffer *p)
{
    if (p->m_Size == p->m_Position)
    {
        p->m_Size = 0;
    }
    else
    {
        CGXByteBuffer_Move(p, p->m_Position, 0, p->m_Size - p->m_Position);
    }
    p->m_Position = 0;
}

/**
   * Compares, whether two given arrays are similar starting from current
   * position.
   *
   * @param arr
   *            Array to compare.
   * @return True, if arrays are similar. False, if the arrays differ.
   */
bool CGXByteBuffer_Compare(CGXByteBuffer *p, unsigned char* buff, unsigned long length)
{
    if (p->m_Size - p->m_Position < length)
    {
        return false;
    }
    bool equal = memcmp(p->m_Data + p->m_Position, buff, length) == 0;
    if (equal)
    {
        p->m_Position += length;
    }
    return equal;
}

void CGXByteBuffer_ToArray(CGXByteBuffer *p, unsigned char** value, unsigned long* count)
{
    if (value != NULL)
    {
        DLMSPort_free(value);
    }
    *count = p->m_Size;
    *value = (unsigned char*)DLMSPort_malloc(*count);
    memcpy(*value, p->m_Data, *count);
}

void CGXByteBuffer_copy(CGXByteBuffer* p, CGXByteBuffer* value)
{
    CGXByteBuffer_Capacity_2(p, value->m_Size);
    p->m_Size = 0;
    if (value->m_Size != 0)
    {
        CGXByteBuffer_Set_2(p, value, 0, (unsigned long)-1);
    }
    //return *p;
}

void CGXByteBuffer_v_c(void* p1, const void* p2)
{
    CGXByteBuffer_copy((CGXByteBuffer*) p1, (CGXByteBuffer*) p2);
}

void CGXByteBuffer_v_d(void* p)
{
    CGXByteBuffer_d((CGXByteBuffer*) p);
}
