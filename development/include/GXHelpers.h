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

#ifndef GXHELPERS_H
#define GXHELPERS_H

#include "errorcodes.h"
#include "GXDLMSVariant.h"
#include "GXDataInfo.h"
#include "String.h"
#include "Vector.h"
#include <stdbool.h>
#include "DLMSPort.h"

    /**
    * Convert object to DLMS bytes.
    *
    * buff : Byte buffer where data is write.
    * type : Data type.
    * value : Added Value.
    */
extern int GXHelpers_SetData(CGXByteBuffer* buff, DLMS_DATA_TYPE type, CGXDLMSVariant* value);

    /**
        * Get data from DLMS frame.
        *
        * @param data
        *            received data.
        * @param info
        *            Data info.
        * @return Received data.
        */
extern int GXHelpers_GetData(CGXByteBuffer* data, CGXDataInfo* info, CGXDLMSVariant* value);

extern void GXHelpers_GetLogicalName_1(unsigned char* buff, String* ln);

extern void GXHelpers_GetLogicalName_2(CGXByteBuffer* buff, String* ln);

    /////////////////////////////////////////////////////////////////////////////
    //Set logical name from std::string.
    /////////////////////////////////////////////////////////////////////////////
extern int GXHelpers_SetLogicalName_1(const char* name, CGXDLMSVariant* value);

    /////////////////////////////////////////////////////////////////////////////
    //Set logical name from std::string.
    /////////////////////////////////////////////////////////////////////////////
extern int GXHelpers_SetLogicalName_2(const char* name, unsigned char ln[6]);

    /////////////////////////////////////////////////////////////////////////////
    // Get object count. If first byte is 0x80 or higger it will tell bytes count.
    // data ; received data.
    // Returns Object count.
    /////////////////////////////////////////////////////////////////////////////
extern int GXHelpers_GetObjectCount(CGXByteBuffer* data, unsigned long* count);

    /**
        * Return how many bytes object count takes.
        *
        * @param count
        *            Value
        * @return Value size in bytes.
        */
extern unsigned char GXHelpers_GetObjectCountSizeInBytes(unsigned long count);

    /////////////////////////////////////////////////////////////////////////////
    // Set item count.
    /////////////////////////////////////////////////////////////////////////////
    // count : Item count.
    // buff : Byte buffer.
    /////////////////////////////////////////////////////////////////////////////
extern void GXHelpers_SetObjectCount(unsigned long count, CGXByteBuffer* buff);

extern Vector GXHelpers_Split_1(String* s, char separator); // std::vector< std::string >

extern Vector GXHelpers_Split_2(String* s, String separators, bool ignoreEmpty); // std::vector< std::string >

extern void GXHelpers_Replace(String* str, String oldString, String newString);

    /////////////////////////////////////////////////////////////////////////////
    // Trim from start.
    /////////////////////////////////////////////////////////////////////////////
extern String* GXHelpers_ltrim(String* s);

    /////////////////////////////////////////////////////////////////////////////
    // Trim from end. hanchiran is waiting
    /////////////////////////////////////////////////////////////////////////////
extern String* GXHelpers_rtrim(String* s);

    /////////////////////////////////////////////////////////////////////////////
    // Trim from both ends
    /////////////////////////////////////////////////////////////////////////////
extern String* GXHelpers_trim(String* s);

extern String GXHelpers_BytesToHex_1(unsigned char* pBytes, int count);

extern String GXHelpers_BytesToHex_2(unsigned char* pBytes, int count, char separator);

    /**
     * Convert std::string to byte array.
     *
     * @param value
     *            Hex std::string.
     * @param buffer
     *            byte array.
     * @return Occurred error.
     */
extern void GXHelpers_HexToBytes(String value, CGXByteBuffer* buffer);

extern void GXHelpers_Write_1(String fileName, String data);

extern void GXHelpers_Write_2(char* fileName, char* pData, int len);

extern bool GXHelpers_GetBits(unsigned char* tmp, unsigned char BitMask);

extern bool GXHelpers_StringCompare(const char* c1, const char* c2);

    /**
    * Get data type in bytes.
    *
    * @param type
    *            Data type.
    * @return Size of data type in bytes.
    */
extern int GXHelpers_GetDataTypeSize(DLMS_DATA_TYPE type);

#endif //GXHELPERS_H
