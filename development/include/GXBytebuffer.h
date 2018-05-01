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

#ifndef GXBYTEBUFFER_H
#define GXBYTEBUFFER_H

#include "errorcodes.h"
#include "enums.h"
#include <stdbool.h>
#include "String.h"

typedef struct
{
    unsigned char* m_Data;
    unsigned long m_Capacity;
    unsigned long m_Size;
    unsigned long m_Position;
} CGXByteBuffer;

//Constructor.
extern void CGXByteBuffer_1(CGXByteBuffer *p);

//Constructor.
extern void CGXByteBuffer_2(CGXByteBuffer *p, int capacity);

//Copy constructor.
extern void CGXByteBuffer_3(CGXByteBuffer *p, const CGXByteBuffer* value);

//Destructor.
extern void CGXByteBuffer_d(CGXByteBuffer *p);


//Amount of non read bytes in the buffer.
extern unsigned long CGXByteBuffer_Available(CGXByteBuffer *p);

    //Returns buffer size.
extern unsigned long CGXByteBuffer_GetSize(CGXByteBuffer *p);

    //Set buffer size.
extern void CGXByteBuffer_SetSize(CGXByteBuffer *p, unsigned long value);

    //Increase buffer size.
extern int CGXByteBuffer_IncreaseSize(CGXByteBuffer *p, unsigned long size);

    //Returns position of the buffer.
extern unsigned long CGXByteBuffer_GetPosition(CGXByteBuffer *p);

    //Returns position of the buffer.
extern void CGXByteBuffer_SetPosition(CGXByteBuffer *p, unsigned long value);

//Get buffer capacity.
extern unsigned long CGXByteBuffer_Capacity_1(CGXByteBuffer *p);

    //Allocate new size for the array in bytes.
extern void CGXByteBuffer_Capacity_2(CGXByteBuffer *p, unsigned long capacity);


    //Fill buffer it with zeros.
extern void CGXByteBuffer_Zero(CGXByteBuffer *p, unsigned long index, unsigned long count);

    //Push new data to the byteArray.
extern void CGXByteBuffer_SetUInt8_1(CGXByteBuffer *p, unsigned char item);

extern void CGXByteBuffer_SetUInt8_2(CGXByteBuffer *p, unsigned long index, unsigned char item);
extern void CGXByteBuffer_SetUInt16(CGXByteBuffer *p, unsigned short item);

extern void CGXByteBuffer_SetUInt32(CGXByteBuffer *p, unsigned long item);

extern void CGXByteBuffer_SetUInt32ByIndex(CGXByteBuffer *p, unsigned long index, unsigned long item);

extern void CGXByteBuffer_SetUInt64(CGXByteBuffer *p, unsigned long long item);

extern void CGXByteBuffer_SetInt8(CGXByteBuffer *p, char item);

extern void CGXByteBuffer_SetInt16(CGXByteBuffer *p, short item);

extern void CGXByteBuffer_SetInt32(CGXByteBuffer *p, long item);

extern void CGXByteBuffer_SetInt64(CGXByteBuffer *p, long long item);

extern void CGXByteBuffer_SetFloat(CGXByteBuffer *p, float value);

extern void CGXByteBuffer_SetDouble(CGXByteBuffer *p, double value);

extern void CGXByteBuffer_Set_1(CGXByteBuffer *p, const void* pSource, unsigned long count);

// Default parameter: index = 0, count = -1
extern void CGXByteBuffer_Set_2(CGXByteBuffer *p, CGXByteBuffer* data, unsigned long index, unsigned long count);

    //Add string to byte buffer.
extern void CGXByteBuffer_AddString_1(CGXByteBuffer *p, const String* value);

extern void CGXByteBuffer_AddString_2(CGXByteBuffer *p, const char* value);

extern void CGXByteBuffer_AttachString(CGXByteBuffer *p, char* value);

extern void CGXByteBuffer_Clear(CGXByteBuffer *p);

extern int CGXByteBuffer_GetUInt8_1(CGXByteBuffer *p, unsigned char* value);

extern int CGXByteBuffer_GetUInt8_2(CGXByteBuffer *p, unsigned long index, unsigned char* value);

extern int CGXByteBuffer_GetUInt16_1(CGXByteBuffer *p, unsigned short* value);

extern int CGXByteBuffer_GetUInt32_1(CGXByteBuffer *p, unsigned long* value);

extern int CGXByteBuffer_GetInt16(CGXByteBuffer *p, short* value);

extern int CGXByteBuffer_GetInt32(CGXByteBuffer *p, long* value);

extern int CGXByteBuffer_GetInt64(CGXByteBuffer *p, long long* value);

extern int CGXByteBuffer_GetUInt64_1(CGXByteBuffer *p, unsigned long long* value);

extern int CGXByteBuffer_GetFloat(CGXByteBuffer *p, float* value);

extern int CGXByteBuffer_GetDouble(CGXByteBuffer *p, double* value);

extern int CGXByteBuffer_Get(CGXByteBuffer *p, unsigned char* value, unsigned long count);

extern unsigned char* CGXByteBuffer_GetData(CGXByteBuffer *p);

extern void CGXByteBuffer_ToArray(CGXByteBuffer *p, unsigned char** value, unsigned long* count);

    /**
     * Remove handled bytes. This can be used in debugging to remove handled
     * bytes.
     */
extern void CGXByteBuffer_Trim(CGXByteBuffer *p);


    /**
     * Compares, whether two given arrays are similar starting from current
     * position.
     *
     * @param arr
     *            Array to compare.
     * @return True, if arrays are similar. False, if the arrays differ.
     */
extern bool CGXByteBuffer_Compare(CGXByteBuffer *p, unsigned char* buff, unsigned long length);

extern int CGXByteBuffer_GetUInt16_2(CGXByteBuffer *p, unsigned long index, unsigned short* value);
extern int CGXByteBuffer_GetUInt32_2(CGXByteBuffer *p, unsigned long index, unsigned long* value);
extern int CGXByteBuffer_GetUInt64_2(CGXByteBuffer *p, unsigned long index, unsigned long long* value);
extern int CGXByteBuffer_GetUInt128(CGXByteBuffer *p, unsigned long index, unsigned char* value);

    //Get byte array as a std::string.
extern void CGXByteBuffer_ToString(CGXByteBuffer *p, String *out);

    //Get byte array as hex std::string.
extern String CGXByteBuffer_ToHexString(CGXByteBuffer *p);

    //Add integer value to byte array as a std::string.
extern void CGXByteBuffer_AddIntAsString(CGXByteBuffer *p, int value);

    //Add double value to byte array as a std::string.
extern void CGXByteBuffer_AddDoubleAsString(CGXByteBuffer *p, double value);

    /**
        * Returns data as byte array.
        *
        * @param bb Byte buffer as a byte array.
        */
extern int CGXByteBuffer_SubArray(CGXByteBuffer *p, unsigned long index, int count, CGXByteBuffer* bb);

    //Move data insize byte array.
extern int CGXByteBuffer_Move(CGXByteBuffer *p, unsigned long srcPos, unsigned long destPos, unsigned long count);

    //Little Endian methods.
extern int CGXByteBuffer_GetUInt32LE_1(CGXByteBuffer *p, unsigned long* value);
extern int CGXByteBuffer_GetUInt32LE_2(CGXByteBuffer *p, unsigned long index, unsigned long* value);
extern void CGXByteBuffer_SetUInt32ByIndexLE(CGXByteBuffer *p, unsigned long index, unsigned long item);

     // operator=
extern void CGXByteBuffer_copy(CGXByteBuffer* p, CGXByteBuffer* value);

extern void CGXByteBuffer_v_c(void* p1, const void* p2);
extern void CGXByteBuffer_v_d(void* p);

#endif //GXBYTEBUFFER_H
