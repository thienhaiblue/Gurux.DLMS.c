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

#include "../include/GXDate.h"
#include "../include/GXTime.h"
#include "../include/GXHelpers.h"
#include "../include/GXBytebuffer.h"
#include "../include/GXDataInfo.h"
#include "../include/WString.h"

/**
    * Get array from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * index
    *            starting index.
    * Returns  CGXDLMSVariant array.
    */
static int GetArray(CGXByteBuffer *buff, CGXDataInfo *info, int index, CGXDLMSVariant *value)
{
    int ret;
    unsigned long cnt = 0;
    CGXDataInfo info2;
    CGXDataInfo_(&info2);

    CGXDLMSVariant tmp;
    CGXDLMSVariant_1(&tmp);

    if (info->m_Count == 0)
    {
        if ((ret = GXHelpers_GetObjectCount(buff, &cnt)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            return ret;
        }
        info->m_Count = cnt;
    }
    int size = buff->m_Size - buff->m_Position;
    if (info->m_Count != 0 && size < 1)
    {
        info->m_Compleate = false;

        CGXDLMSVariant_d(&tmp);
        return 0;
    }
    int startIndex = index;
    value->st.vt = DLMS_DATA_TYPE_ARRAY;
    // Position where last row was found. Cache uses this info.
    int pos = info->m_Index;
    for (; pos != info->m_Count; ++pos)
    {
        CGXDataInfo_Clear(&info2);
        CGXDLMSVariant_Clear(&tmp);
        if ((ret = GXHelpers_GetData(buff, &info2, &tmp)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            return ret;
        }
        if (!info2.m_Compleate)
        {
            CGXByteBuffer_SetPosition(buff, startIndex);
            info->m_Compleate = false;
            break;
        }
        else
        {
            if (info2.m_Count == info2.m_Index)
            {
                startIndex = buff->m_Position;
                Vector_push_back(&(value->Arr), &tmp);
            }
        }
    }
    info->m_Index = pos;

    CGXDLMSVariant_d(&tmp);
    return 0;
}

/**
    * Get time from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  Parsed time.
    */
int GetTime(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    unsigned char hour, minute, second, ms;
    if (buff->m_Size - buff->m_Position < 4)
    {
        // If there is not enough data available.
        info->m_Compleate = false;
        return 0;
    }
    // Get time.
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &hour)) != 0)
    {
        return ret;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &minute)) != 0)
    {
        return ret;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &second)) != 0)
    {
        return ret;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ms)) != 0)
    {
        return ret;
    }
    CGXTime dt;
    CGXTime_3(&dt, hour, minute, second, ms);

    CGXDLMSVariant_copy_20(value, &dt);

    return 0;
}

/**
    * Get date from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  Parsed date.
    */
int GetDate(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    unsigned short year;
    int ret;
    unsigned char ch, month, day;
    if (buff->m_Size - buff->m_Position < 5)
    {
        // If there is not enough data available.
        info->m_Compleate = false;
        return 0;
    }
    // Get year.
    if ((ret = CGXByteBuffer_GetUInt16_1(buff, &year)) != 0)
    {
        return ret;
    }
    // Get month
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &month)) != 0)
    {
        return ret;
    }
    // Get day
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &day)) != 0)
    {
        return ret;
    }

    CGXDate dt;
    CGXDate_3(&dt, year, month, day);

    // Skip week day
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch == 0xFF)
    {
        dt.m_Skip = (DATETIME_SKIPS)(dt.m_Skip | DATETIME_SKIPS_DAYOFWEEK);
    }
    CGXDLMSVariant_copy_19(value, &dt);
    return 0;
}

/**
* Get date and time from DLMS data.
*
* buff
*            Received DLMS data.
* info
*            Data info.
* Returns  Parsed date and time.
*/
int GetDateTime(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    struct tm tm = { 0 };
    unsigned short year;
    short deviation;
    int ret, ms, status;
    unsigned char ch;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 12)
    {
        info->m_Compleate = false;
        return 0;
    }
    // Get year.
    if ((ret = CGXByteBuffer_GetUInt16_1(buff, &year)) != 0)
    {
        return ret;
    }
    tm.tm_year = year;
    // Get month
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    tm.tm_mon = ch;
    // Get day
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    tm.tm_mday = ch;
    // Skip week day
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    tm.tm_wday = ch;
    // Get time.
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    tm.tm_hour = ch;
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    tm.tm_min = ch;
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    tm.tm_sec = ch;
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    ms = ch;
    if (ms != 0xFF)
    {
        ms *= 10;
    }
    else
    {
        ms = 0;
    }
    if ((ret = CGXByteBuffer_GetInt16(buff, &deviation)) != 0)
    {
        return ret;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    status = ch;
    CGXDateTime dt;
    CGXDateTime_1(&dt);

    dt.m_Status = (DLMS_CLOCK_STATUS)status;
    DATETIME_SKIPS skip = DATETIME_SKIPS_NONE;
    if (year < 1 || year == 0xFFFF)
    {
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_YEAR);
        tm.tm_year = 0;
    }
    else
    {
        tm.tm_year -= 1900;
    }
    if (tm.tm_wday < 0 || tm.tm_wday > 7)
    {
        tm.tm_wday = 0;
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_DAYOFWEEK);
    }
    dt.m_DaylightSavingsBegin = (tm.tm_mon == 0xFE);
    dt.m_DaylightSavingsEnd = (tm.tm_mon == 0xFD);
    if (tm.tm_mon < 1 || tm.tm_mon > 12)
    {
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_MONTH);
        tm.tm_mon = 0;
    }
    else
    {
        tm.tm_mon -= 1;
    }
    if (tm.tm_mday == -1 || tm.tm_mday == 0 || tm.tm_mday > 31)
    {
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_DAY);
        tm.tm_mday = 1;
    }
    else if (tm.tm_mday < 0)
    {
        tm.tm_mday = CGXDateTime_DaysInMonth(year, tm.tm_mon + 1) + tm.tm_mday + 3;
    }
    if (tm.tm_hour < 0 || tm.tm_hour > 24)
    {
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_HOUR);
        tm.tm_hour = 0;
    }
    if (tm.tm_min < 0 || tm.tm_min > 60)
    {
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_MINUTE);
        tm.tm_min = 0;
    }
    if (tm.tm_sec < 0 || tm.tm_sec > 60)
    {
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_SECOND);
        tm.tm_sec = 0;
    }
    // If ms is Zero it's skipped.
    if (ms < 1 || ms > 1000)
    {
        skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_MS);
        ms = 0;
    }
    tm.tm_isdst = (status & DLMS_CLOCK_STATUS_DAYLIGHT_SAVE_ACTIVE) != 0;
    dt.m_Value = tm;
    dt.m_Deviation = deviation;
    dt.m_Skip = skip;
    CGXDLMSVariant_copy_21(value, &dt);
    return 0;
}

/**
* Get double value from DLMS data.
*
* buff
*            Received DLMS data.
* info
*            Data info.
* Returns  Parsed double value.
*/
int GetDouble(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 8)
    {
        info->m_Compleate = false;
        return 0;
    }
    value->st.vt = DLMS_DATA_TYPE_FLOAT64;
    return CGXByteBuffer_GetDouble(buff, &(value->st.un.dblVal));
}

/**
    * Get float value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  Parsed float value.
    */
int GetFloat(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 4)
    {
        info->m_Compleate = false;
        return 0;
    }
    value->st.vt = DLMS_DATA_TYPE_FLOAT32;
    return CGXByteBuffer_GetFloat(buff, &(value->st.un.fltVal));
}

/**
    * Get enumeration value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed enumeration value.
    */
int GetEnum(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    unsigned char ch;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 1)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    CGXDLMSVariant_copy_14(value, ch);
    value->st.vt = DLMS_DATA_TYPE_ENUM;
    return 0;
}

/**
    * Get UInt64 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed UInt64 value.
    */
int GetUInt64(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    unsigned long long val;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 8)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetUInt64_1(buff, &val)) != 0)
    {
        return ret;
    }
    CGXDLMSVariant_copy_7(value, val);
    return 0;
}

/**
    * Get Int64 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed Int64 value.
    */
int GetInt64(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    long long val;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 8)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetInt64(buff, &val)) != 0)
    {
        return ret;
    }
    CGXDLMSVariant_copy_8(value, val);
    return 0;
}

/**
    * Get UInt16 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed UInt16 value.
    */
int GetUInt16(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    unsigned short val;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 2)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetUInt16_1(buff, &val)) != 0)
    {
        return ret;
    }
    CGXDLMSVariant_copy_15(value, val);
    return 0;
}

/**
    * Get UInt8 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed UInt8 value.
    */
int GetUInt8(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    unsigned char val;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 1)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &val)) != 0)
    {
        return ret;
    }
    CGXDLMSVariant_copy_14(value, val);
    return 0;
}

/**
    * Get Int16 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed Int16 value.
    */
int GetInt16(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    short val;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 2)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetInt16(buff, &val)) != 0)
    {
        return ret;
    }
    CGXDLMSVariant_copy_11(value, val);
    return 0;
}

/**
    * Get Int8 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed Int8 value.
    */
int GetInt8(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    char val;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 1)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, (unsigned char*)&val)) != 0)
    {
        return ret;
    }
    CGXDLMSVariant_copy_10(value, val);
    return 0;
}

/**
* Get BCD value from DLMS data.
*
* buff
*            Received DLMS data.
* info
*            Data info.
* Returns  parsed BCD value.
*/
int GetBcd(CGXByteBuffer *buff, CGXDataInfo *info, bool knownType, CGXDLMSVariant *value)
{
    unsigned char ch;
    // If there is not enough data available.
    if (CGXByteBuffer_GetUInt8_1(buff, &ch) != 0)
    {
        info->m_Compleate = false;
        return 0;
    }
    CGXDLMSVariant_copy_14(value, ch);
    value->st.vt = DLMS_DATA_TYPE_BINARY_CODED_DESIMAL;
    return 0;
}

int GXHelpers_GetObjectCount(CGXByteBuffer* data, unsigned long* count)
{
    int ret;
    unsigned char cnt;
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &cnt)) != 0)
    {
        return ret;
    }
    if (cnt > 0x80)
    {
        if (cnt == 0x81)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &cnt)) != 0)
            {
                return ret;
            }
            *count = cnt;
            return DLMS_ERROR_CODE_OK;
        }
        else if (cnt == 0x82)
        {
            unsigned short tmp;
            if ((ret = CGXByteBuffer_GetUInt16_1(data, &tmp)) != 0)
            {
                return ret;
            }
            *count = tmp;
            return DLMS_ERROR_CODE_OK;
        }
        else if (cnt == 0x84)
        {
            unsigned long tmp;
            if ((ret = CGXByteBuffer_GetUInt32_1(data, &tmp)) != 0)
            {
                return ret;
            }
            *count = tmp;
            return DLMS_ERROR_CODE_OK;
        }
        else
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    *count = cnt;
    return DLMS_ERROR_CODE_OK;
}

unsigned char GXHelpers_GetObjectCountSizeInBytes(unsigned long count)
{
    if (count < 0x80)
    {
        return 1;
    }
    else if (count < 0x100)
    {
        return 2;
    }
    else if (count < 0x10000)
    {
        return 3;
    }
    else
    {
        return 5;
    }
}

void GXHelpers_SetObjectCount(unsigned long count, CGXByteBuffer *buff)
{
    if (count < 0x80)
    {
        CGXByteBuffer_SetUInt8_1(buff, (unsigned char)count);
    }
    else if (count < 0x100)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0x81);
        CGXByteBuffer_SetUInt8_1(buff, (unsigned char)count);
    }
    else if (count < 0x10000)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0x82);
        CGXByteBuffer_SetUInt16(buff, (unsigned short)count);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0x84);
        CGXByteBuffer_SetUInt32(buff, count);
    }
}

Vector GXHelpers_Split_1(String* s, char separator) // std::vector< std::string >
{
    Vector items; // std::vector< std::string >
    Vector_(&items, sizeof(String), String_v_c, String_v_d);

    int last = 0;
    int pos = -1;
    while ((pos = (int)String_find_1(s, separator, pos + 1)) != -1)
    {
        String str;
        String_(&str);

        String_append_4(&str, s, last, pos - last);
        Vector_push_back(&items, &str);
        last = pos + 1;

        String_d(&str);
    }    
    int len = (int)String_length(s);
    if (last == 0 || last != len)
    {
        String str;
        String_(&str);

        String_append_4(&str, s, last, pos);
        Vector_push_back(&items, &str);

        String_d(&str);
    }

    return items; // = Copy cons + des
}

Vector GXHelpers_Split_2(String* s, String separators, bool ignoreEmpty) // std::vector< std::string >
{
    Vector items;
    Vector_(&items, sizeof(String), String_v_c, String_v_d);

    int last = 0;
    int pos = -1;
    while ((pos = (int)String_find_first_of_1(s, &separators, pos + 1)) != -1)
    {
        if (!ignoreEmpty || pos - last != 0)
        {
            String str;
            String_(&str);

            String_append_4(&str, s, last, pos - last);
            Vector_push_back(&items, &str);

            String_d(&str);
        }
        last = pos + 1;
    }
    int len = (int)String_length(s);
    if (!ignoreEmpty || len - last != 0)
    {
        String str;
        String_(&str);

        String_append_4(&str, s, last, len - last);
        Vector_push_back(&items, &str);

        String_d(&str);
    }

    return items; // = Copy cons + des
}

void GXHelpers_Replace(String* str, String oldString, String newString)
{
    int index;
    int len = (int)String_length(&oldString);
    while ((index = (int)String_rfind_1(str, &oldString, (size_t) -1)) != -1)
    {
        String_replace_1(str, index, len, &newString);
    }
}

String* GXHelpers_ltrim(String* s)
{
    int i;

    for (i = 0; i < String_length(s); i++)
    {
        char c = *String_at(s, i);
        if ((c != ' ') && (c != '\t') && (c != '\n') && (c != '\v')
         && (c != '\f') && (c != '\r'))
        {
            break;
        }
    }
    if (i == String_length(s))
    {
        i = -1;
    }

    return String_erase(s, 0, (size_t) i);
}

String GXHelpers_BytesToHex_1(unsigned char* pBytes, int count)
{
    return GXHelpers_BytesToHex_2(pBytes, count, ' ');
}

String GXHelpers_BytesToHex_2(unsigned char* pBytes, int count, char separator)
{
    const char hexArray[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    String hexChars;
    String_4(&hexChars, 3 * count, 0);

    int tmp;
    for (int pos = 0; pos != count; ++pos)
    {
        tmp = pBytes[pos] & 0xFF;
        *String_at(&hexChars, pos * 3) = hexArray[tmp >> 4];
        *String_at(&hexChars, pos * 3 + 1) = hexArray[tmp & 0x0F];
        *String_at(&hexChars, pos * 3 + 2) = separator;
    }
    //Remove last separator.
    if (count != 0)
    {
        String_resize(&hexChars, String_size(&hexChars) - 1);
    }
    return hexChars; // = Copy cons + des
}
/**
* Get UTF string value from DLMS data.
*
* buff
*            Received DLMS data.
* info
*            Data info.
* Returns  parsed UTF string value.
*/
int GetUtfString(CGXByteBuffer *buff, CGXDataInfo *info, bool knownType, CGXDLMSVariant *value)
{
    int ret;
    unsigned long len = 0;
    wchar_t *tmp;
    if (knownType)
    {
        len = buff->m_Size;
    }
    else
    {
        if ((ret = GXHelpers_GetObjectCount(buff, &len)) != 0)
        {
            return ret;
        }
        // If there is not enough data available.
        if (buff->m_Size - buff->m_Position < len)
        {
            info->m_Compleate = false;
            return 0;
        }
    }
    if (len > 0)
    {
        tmp = DLMSPort_malloc(len * sizeof(wchar_t));
        CGXByteBuffer_Get(buff, (unsigned char*)tmp, 2 * len);
        WString_append_2(&(value->strUtfVal), tmp, len);
        DLMSPort_free(tmp);
    }
    else
    {
        CGXDLMSVariant_copy_3(value, "");
    }
    return 0;
}

/**
    * Get octect string value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed octet string value.
    */
int GetOctetString(CGXByteBuffer *buff, CGXDataInfo *info, bool knownType, CGXDLMSVariant *value)
{
    int ret;
    unsigned long len = 0;
    if (knownType)
    {
        len = buff->m_Size;
    }
    else
    {
        if ((ret = GXHelpers_GetObjectCount(buff, &len)) != 0)
        {
            return ret;
        }
        // If there is not enough data available.
        if (buff->m_Size - buff->m_Position < len)
        {
            info->m_Compleate = false;
            return 0;
        }
    }
    value->size = (unsigned short)len;
    if (len == 0)
    {
        value->st.un.byteArr = NULL;
    }
    else
    {
        value->st.un.byteArr = (unsigned char*) DLMSPort_malloc(len);
        if ((ret = CGXByteBuffer_Get(buff, value->st.un.byteArr, len)) != 0)
        {
            return ret;
        }
    }
    value->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    return 0;
}

/**
    * Get string value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed string value.
    */
int GetString(CGXByteBuffer *buff, CGXDataInfo *info, bool knownType, CGXDLMSVariant *value)
{
    int ret;
    unsigned long len = 0;
    char *tmp;
    if (knownType)
    {
        len = buff->m_Size;
    }
    else
    {
        if ((ret = GXHelpers_GetObjectCount(buff, &len)) != 0)
        {
            return ret;
        }
        // If there is not enough data available.
        if (buff->m_Size - buff->m_Position < len)
        {
            info->m_Compleate = false;
            return 0;
        }
    }
    if (len > 0)
    {
        tmp = (char*) DLMSPort_malloc(len + 1);
        tmp[len] = '\0';
        if ((ret = CGXByteBuffer_Get(buff, (unsigned char*)tmp, len)) != 0)
        {
            DLMSPort_free(tmp);
            return ret;
        }
        CGXDLMSVariant_copy_3(value, tmp);
        DLMSPort_free(tmp);
    }
    else
    {
        CGXDLMSVariant_copy_3(value, "");
    }
    return 0;
}

/**
    * Get UInt32 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed UInt32 value.
    */
int GetUInt32(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 4)
    {
        info->m_Compleate = false;
        return 0;
    }
    value->st.vt = DLMS_DATA_TYPE_UINT32;
    return CGXByteBuffer_GetUInt32_1(buff, &(value->st.un.ulVal));
}

/**
    * Get Int32 value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed Int32 value.
    */
int GetInt32(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 4)
    {
        info->m_Compleate = false;
        return 0;
    }
    value->st.vt = DLMS_DATA_TYPE_INT32;
    return CGXByteBuffer_GetInt32(buff, &(value->st.un.lVal));
}


//Reserved for internal use.
static void ToBitString(CGXByteBuffer *sb, unsigned char value, int count)
{
    if (count > 0) {
        if (count > 8) {
            count = 8;
        }
        for (int pos = 7; pos != 8 - count - 1; --pos) {
            if ((value & (1 << pos)) != 0) {
                CGXByteBuffer_SetInt8(sb, '1');
            }
            else {
                CGXByteBuffer_SetInt8(sb, '0');
            }
        }
    }
}

/**
* Get bit string value from DLMS data.
*
* buff : Received DLMS data.
* info : Data info.
* Returns parsed bit string value.
*/
static int GetBitString(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    unsigned long cnt = 0;
    int ret;
    unsigned char ch;
    if ((ret = GXHelpers_GetObjectCount(buff, &cnt)) != 0)
    {
        return ret;
    }
    double t = cnt;
    t /= 8;
    if (cnt % 8 != 0)
    {
        ++t;
    }
    unsigned int byteCnt = (unsigned int)t;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < byteCnt)
    {
        info->m_Compleate = false;
        return 0;
    }

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    while (cnt > 0)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
        {
            CGXByteBuffer_d(&bb);
            return ret;
        }
        ToBitString(&bb, ch, cnt);
        if (cnt < 8)
        {
            break;
        }
        cnt -= 8;
    }

    String str;
    CGXByteBuffer_ToString(&bb, &str);

    CGXDLMSVariant_copy_2(value, str);

    value->st.vt = DLMS_DATA_TYPE_BIT_STRING;

    String_d(&str);
    CGXByteBuffer_d(&bb);
    return 0;
}

/**
    * Get bool value from DLMS data.
    *
    * buff
    *            Received DLMS data.
    * info
    *            Data info.
    * Returns  parsed bool value.
    */
static int GetBool(CGXByteBuffer *buff, CGXDataInfo *info, CGXDLMSVariant *value)
{
    int ret;
    unsigned char ch;
    // If there is not enough data available.
    if (buff->m_Size - buff->m_Position < 1)
    {
        info->m_Compleate = false;
        return 0;
    }
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    value->st.vt = DLMS_DATA_TYPE_BOOLEAN;
    value->st.un.boolVal = ch != 0;
    return 0;
}

int GXHelpers_GetData(
    CGXByteBuffer* data,
    CGXDataInfo* info,
    CGXDLMSVariant* value)
{
    int ret;
    unsigned char ch;
    int startIndex = data->m_Position;
    CGXDLMSVariant_Clear(value);
    if (data->m_Position == data->m_Size)
    {
        info->m_Compleate = false;
        return 0;
    }
    info->m_Compleate = true;
    bool knownType = info->m_Type != DLMS_DATA_TYPE_NONE;
    // Get data type if it is unknown.
    if (!knownType)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            return ret;
        }
        info->m_Type = (DLMS_DATA_TYPE)ch;
    }
    if (info->m_Type == DLMS_DATA_TYPE_NONE)
    {
        return 0;
    }
    if (data->m_Position == data->m_Size)
    {
        info->m_Compleate = false;
        return 0;
    }
    switch (info->m_Type)
    {
    case DLMS_DATA_TYPE_ARRAY:
    case DLMS_DATA_TYPE_STRUCTURE:
        ret = GetArray(data, info, startIndex, value);
        value->st.vt = info->m_Type;
        break;
    case DLMS_DATA_TYPE_BOOLEAN:
        ret = GetBool(data, info, value);
        break;
    case DLMS_DATA_TYPE_BIT_STRING:
        ret = GetBitString(data, info, value);
        break;
    case DLMS_DATA_TYPE_INT32:
        ret = GetInt32(data, info, value);
        break;
    case DLMS_DATA_TYPE_UINT32:
        ret = GetUInt32(data, info, value);
        break;
    case DLMS_DATA_TYPE_STRING:
        ret = GetString(data, info, knownType, value);
        break;
    case DLMS_DATA_TYPE_STRING_UTF8:
        ret = GetUtfString(data, info, knownType, value);
        break;
    case DLMS_DATA_TYPE_OCTET_STRING:
        ret = GetOctetString(data, info, knownType, value);
        break;
    case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
        ret = GetBcd(data, info, knownType, value);
        break;
    case DLMS_DATA_TYPE_INT8:
        ret = GetInt8(data, info, value);
        break;
    case DLMS_DATA_TYPE_INT16:
        ret = GetInt16(data, info, value);
        break;
    case DLMS_DATA_TYPE_UINT8:
        ret = GetUInt8(data, info, value);
        break;
    case DLMS_DATA_TYPE_UINT16:
        ret = GetUInt16(data, info, value);
        break;
    case DLMS_DATA_TYPE_COMPACT_ARRAY:
        assert(0);
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    case DLMS_DATA_TYPE_INT64:
        ret = GetInt64(data, info, value);
        break;
    case DLMS_DATA_TYPE_UINT64:
        ret = GetUInt64(data, info, value);
        break;
    case DLMS_DATA_TYPE_ENUM:
        ret = GetEnum(data, info, value);
        break;
    case DLMS_DATA_TYPE_FLOAT32:
        ret = GetFloat(data, info, value);
        break;
    case DLMS_DATA_TYPE_FLOAT64:
        ret = GetDouble(data, info, value);
        break;
    case DLMS_DATA_TYPE_DATETIME:
        ret = GetDateTime(data, info, value);
        break;
    case DLMS_DATA_TYPE_DATE:
        ret = GetDate(data, info, value);
        break;
    case DLMS_DATA_TYPE_TIME:
        ret = GetTime(data, info, value);
        break;
    default:
        assert(0);
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return ret;
}

/**
    * Convert time to DLMS bytes.
    *
    * buff
    *            Byte buffer where data is write.
    * value
    *            Added value.
    */
static int SetTime(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    DATETIME_SKIPS skip = value->dateTime.m_Skip;
    struct tm *dt = &(value->dateTime.m_Value);
    // Add time.
    if ((skip & DATETIME_SKIPS_HOUR) != 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_hour);
    }
    if ((skip & DATETIME_SKIPS_MINUTE) != 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_min);
    }
    if ((skip & DATETIME_SKIPS_SECOND) != 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_sec);
    }
    if ((skip & DATETIME_SKIPS_MS) != 0)
    {
        // Hundredths of second is not used.
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0);
    }
    return 0;
}

/**
* Convert date to DLMS bytes.
*
* buff
*            Byte buffer where data is write.
* value
*            Added value.
*/
static int SetDate(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    struct tm *dt = &(value->dateTime.m_Value);
    DATETIME_SKIPS skip = value->dateTime.m_Skip;
    // Add year.
    if ((skip & DATETIME_SKIPS_YEAR) != 0)
    {
        CGXByteBuffer_SetUInt16(buff, 0xFFFF);
        
    }
    else
    {
        CGXByteBuffer_SetUInt16(buff, 1900 + dt->tm_year);
    }
    // Add month
    if (value->dateTime.m_DaylightSavingsBegin)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFE);
    }
    else if (value->dateTime.m_DaylightSavingsEnd)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFD);
    }
    else if ((skip & DATETIME_SKIPS_MONTH) != 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_mon + 1);
    }
    // Add day
    if ((skip & DATETIME_SKIPS_DAY) != 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_mday);
    }
    //Add week day
    if ((skip & DATETIME_SKIPS_DAYOFWEEK) != 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        int val = dt->tm_wday;
        //If Sunday.
        if (val == 0)
        {
            val = 8;
        }
        CGXByteBuffer_SetUInt8_1(buff, val - 1);
    }
    return 0;
}

/**
* Convert date time to DLMS bytes.
*
* buff
*            Byte buffer where data is write.
* value
*            Added value.
*/
static int SetDateTime(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    //Add year.
    unsigned short year = 0xFFFF;
    struct tm *dt = &(value->dateTime.m_Value);
    DATETIME_SKIPS skip = value->dateTime.m_Skip;

    if (dt->tm_year != -1 && (skip & DATETIME_SKIPS_YEAR) == 0)
    {
        year = 1900 + dt->tm_year;
    }
    CGXByteBuffer_SetUInt16(buff, year);
    //Add month
    if (value->dateTime.m_DaylightSavingsBegin)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFE);
    }
    else if (value->dateTime.m_DaylightSavingsEnd)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFD);
    }
    else if (dt->tm_mon != -1 && (skip & DATETIME_SKIPS_MONTH) == 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_mon + 1);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    //Add day
    if (dt->tm_mday != -1 && (skip & DATETIME_SKIPS_DAY) == 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_mday);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    //Add week day
    if ((skip & DATETIME_SKIPS_DAYOFWEEK) != 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        int val = dt->tm_wday;
        //If Sunday.
        if (val == 0)
        {
            val = 7;
        }
        CGXByteBuffer_SetUInt8_1(buff, val);
    }
    //Add Hours
    if (dt->tm_hour != -1 && (skip & DATETIME_SKIPS_HOUR) == 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_hour);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    //Add Minutes
    if (dt->tm_min != -1 && (skip & DATETIME_SKIPS_MINUTE) == 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_min);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    //Add seconds.
    if (dt->tm_sec != -1 && (skip & DATETIME_SKIPS_SECOND) == 0)
    {
        CGXByteBuffer_SetUInt8_1(buff, dt->tm_sec);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    //Add ms.
    if ((skip & DATETIME_SKIPS_MS) != 0)
    {
        // Hundredths of second is not used.
        CGXByteBuffer_SetUInt8_1(buff, 0xFF);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0);
    }
    // devitation not used.
    if ((skip & DATETIME_SKIPS_DEVITATION) != 0)
    {
        CGXByteBuffer_SetUInt16(buff, 0x8000);
    }
    else
    {
        // Add devitation.
        CGXByteBuffer_SetUInt16(buff, value->dateTime.m_Deviation);
    }
    // Add clock_status
    if (dt->tm_isdst)
    {
        CGXByteBuffer_SetUInt8_1(buff, value->dateTime.m_Status | DLMS_CLOCK_STATUS_DAYLIGHT_SAVE_ACTIVE);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, value->dateTime.m_Status);
    }
    return 0;
}

/**
* Convert BCD to DLMS bytes.
*
* buff
*            Byte buffer where data is write.
* value
*            Added value.
*/
static int SetBcd(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    // Standard supports only size of byte.
    CGXByteBuffer_SetUInt8_1(buff, value->st.un.bVal);
    return 0;
}

/**
    * Convert Array to DLMS bytes.
    *
    * buff
    *            Byte buffer where data is write.
    * value
    *            Added value.
    */
static int SetArray(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    int ret;
    GXHelpers_SetObjectCount((unsigned long)Vector_size(&(value->Arr)), buff);

    for (unsigned int it = Vector_begin(&(value->Arr)); it != Vector_end(&(value->Arr)); ++it)
    {
        if ((ret = GXHelpers_SetData(buff,
                                     ((CGXDLMSVariant*) Vector_at(&(value->Arr), it))->st.vt,
                                     Vector_at(&(value->Arr), it))) != 0)
        {
            return ret;
        }
    }

    return 0;
}

/**
    * Convert Octetstring to DLMS bytes.
    *
    * buff
    *            Byte buffer where data is write.
    * value
    *            Added value.
    */
static int SetOctetString(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    if (value->st.vt == DLMS_DATA_TYPE_STRING)
    {
        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        GXHelpers_HexToBytes(value->strVal, &bb);
        GXHelpers_SetObjectCount(bb.m_Size, buff);
        CGXByteBuffer_Set_1(buff, bb.m_Data, bb.m_Size);

        CGXByteBuffer_d(&bb);
    }
    else if (value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        GXHelpers_SetObjectCount(value->size, buff);
        CGXByteBuffer_Set_1(buff, value->st.un.byteArr, value->size);
    }
    else if (value->st.vt == DLMS_DATA_TYPE_NONE)
    {
        GXHelpers_SetObjectCount(0, buff);
    }
    else
    {
        // Invalid data type.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

/**
* Convert UTC string to DLMS bytes.
*
* buff
*            Byte buffer where data is write.
* value
*            Added value.
*/
static int SetUtfString(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    if (value->st.vt != DLMS_DATA_TYPE_NONE)
    {
        GXHelpers_SetObjectCount((unsigned long)String_size(&(value->strVal)), buff);
        CGXByteBuffer_AddString_2(buff, String_c_str(&(value->strVal)));
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0);
    }
    return 0;
}

int GXHelpers_SetLogicalName_1(const char* name, CGXDLMSVariant* value)
{
    unsigned char ln[6];
    int ret = GXHelpers_SetLogicalName_2(name, ln);
    if (ret == 0)
    {
        CGXDLMSVariant_Clear(value);
        CGXDLMSVariant_Add_1(value, ln, 6);
    }
    return ret;
}

int GXHelpers_SetLogicalName_2(const char* name, unsigned char ln[6])
{
    int ret;
    int v1, v2, v3, v4, v5, v6;
#if _MSC_VER > 1000
    ret = DLMSPort_sscanf_s(name, "%u.%u.%u.%u.%u.%u", &v1, &v2, &v3, &v4, &v5, &v6);
#else
    ret = DLMSPort_sscanf(name, "%u.%u.%u.%u.%u.%u", &v1, &v2, &v3, &v4, &v5, &v6);
#endif
    if (ret != 6)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    ln[0] = (unsigned char)v1;
    ln[1] = (unsigned char)v2;
    ln[2] = (unsigned char)v3;
    ln[3] = (unsigned char)v4;
    ln[4] = (unsigned char)v5;
    ln[5] = (unsigned char)v6;
    return DLMS_ERROR_CODE_OK;
}

/**
* Convert ASCII string to DLMS bytes.
*
* buff
*            Byte buffer where data is write.
* value
*            Added value.
*/
static int SetString(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    if (value->st.vt != DLMS_DATA_TYPE_NONE)
    {
        GXHelpers_SetObjectCount((unsigned long)String_size(&(value->strVal)), buff);
        CGXByteBuffer_AddString_2(buff, String_c_str(&(value->strVal)));
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, 0);
    }
    return 0;
}

/**
* Convert Bit string to DLMS bytes.
*
* buff
*            Byte buffer where data is write.
* value
*            Added value.
*/
static int SetBitString(CGXByteBuffer *buff, CGXDLMSVariant *value)
{
    unsigned char val = 0;
    int index = 7;
    if (value->st.vt == DLMS_DATA_TYPE_STRING)
    {
        GXHelpers_SetObjectCount((unsigned long)String_size(&(value->strVal)), buff);
        for (unsigned int it = String_begin(&(value->strVal)); it != String_end(&(value->strVal)); ++it)
        {
            if (*String_at(&(value->strVal), it) == '1')
            {
                val |= (1 << index);
            }
            else if (*String_at(&(value->strVal), it) != '0')
            {
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
            --index;
            if (index == -1)
            {
                index = 7;
                CGXByteBuffer_SetUInt8_1(buff, val);
                val = 0;
            }
        }
        if (index != 7)
        {
            CGXByteBuffer_SetUInt8_1(buff, val);
        }
    }
    else if (value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        GXHelpers_SetObjectCount(8 * value->size, buff);
        CGXByteBuffer_Set_1(buff, value->st.un.byteArr, value->size);
    }
    else if (value->st.vt == DLMS_DATA_TYPE_NONE)
    {
        CGXByteBuffer_SetUInt8_1(buff, 0);
    }
    else
    {
        //BitString must give as string.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int GXHelpers_SetData(CGXByteBuffer *buff, DLMS_DATA_TYPE type, CGXDLMSVariant *value)
{
    if ((type == DLMS_DATA_TYPE_ARRAY || type == DLMS_DATA_TYPE_STRUCTURE)
        && value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        // If byte array is added do not add type.
        CGXByteBuffer_Set_1(buff, value->st.un.byteArr, value->size);
        return 0;
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(buff, type);
    }
    if (type == DLMS_DATA_TYPE_NONE)
    {
        return 0;
    }
    switch (type)
    {
    case DLMS_DATA_TYPE_BOOLEAN:
        CGXByteBuffer_SetUInt8_1(buff, value->st.un.boolVal != 0);
        break;
    case DLMS_DATA_TYPE_INT8:
    case DLMS_DATA_TYPE_UINT8:
    case DLMS_DATA_TYPE_ENUM:
        CGXByteBuffer_SetUInt8_1(buff, value->st.un.bVal);
        break;
    case DLMS_DATA_TYPE_INT16:
    case DLMS_DATA_TYPE_UINT16:
        CGXByteBuffer_SetUInt16(buff, value->st.un.iVal);
        break;
    case DLMS_DATA_TYPE_INT32:
    case DLMS_DATA_TYPE_UINT32:
        CGXByteBuffer_SetUInt32(buff, value->st.un.lVal);
        break;
    case DLMS_DATA_TYPE_INT64:
    case DLMS_DATA_TYPE_UINT64:
        CGXByteBuffer_SetUInt64(buff, value->st.un.llVal);
        break;
    case DLMS_DATA_TYPE_FLOAT32:
        CGXByteBuffer_SetFloat(buff, value->st.un.fltVal);
        break;
    case DLMS_DATA_TYPE_FLOAT64:
        CGXByteBuffer_SetDouble(buff, value->st.un.dblVal);
        break;
    case DLMS_DATA_TYPE_BIT_STRING:
        return SetBitString(buff, value);
        break;
    case DLMS_DATA_TYPE_STRING:
        return SetString(buff, value);
        break;
    case DLMS_DATA_TYPE_STRING_UTF8:
        return SetUtfString(buff, value);
        break;
    case DLMS_DATA_TYPE_OCTET_STRING:
        if (value->st.vt == DLMS_DATA_TYPE_DATE)
        {
            // Add size
            CGXByteBuffer_SetUInt8_1(buff, 5);
            SetDate(buff, value);
        }
        else if (value->st.vt == DLMS_DATA_TYPE_TIME)
        {
            // Add size
            CGXByteBuffer_SetUInt8_1(buff, 4);
            SetTime(buff, value);
        }
        else if (value->st.vt == DLMS_DATA_TYPE_DATETIME)
        {
            // Date an calendar are always written as date time.
            CGXByteBuffer_SetUInt8_1(buff, 12);
            SetDateTime(buff, value);
        }
        else
        {
            return SetOctetString(buff, value);
        }
        break;
    case DLMS_DATA_TYPE_ARRAY:
    case DLMS_DATA_TYPE_STRUCTURE:
        return SetArray(buff, value);
        break;
    case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
        return SetBcd(buff, value);
        break;
    case DLMS_DATA_TYPE_COMPACT_ARRAY:
        assert(0);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
        break;
    case DLMS_DATA_TYPE_DATETIME:
        return SetDateTime(buff, value);
        break;
    case DLMS_DATA_TYPE_DATE:
        return SetDate(buff, value);
        break;
    case DLMS_DATA_TYPE_TIME:
        return SetTime(buff, value);
        break;
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

/*
   * Convert char hex value to byte value.
   * @param c Character to convert hex.
   * @return Byte value of hex char value.
   */
static unsigned char GXHelpers_GetValue(char c)
{
    unsigned char value;
    if (c > '9')
    {
        if (c > 'Z')
        {
            value = (c - 'a' + 10);
        }
        else
        {
            value = (c - 'A' + 10);
        }
    }
    else
    {
        value = (c - '0');
    }
    return value;
}

void GXHelpers_HexToBytes(String value, CGXByteBuffer *buffer)
{
    CGXByteBuffer_Clear(buffer);
    CGXByteBuffer_Capacity_2(buffer, (unsigned long)(String_length(&value) / 2));
    int lastValue = -1;
    int index = 0;
    for (unsigned int ch = String_begin(&value); ch != String_end(&value); ++ch)
    {
        if (*String_at(&value, ch) >= '0' && *String_at(&value, ch) < 'g')
        {
            if (lastValue == -1)
            {
                lastValue = GXHelpers_GetValue(*String_at(&value, ch));
            }
            else if (lastValue != -1)
            {
                CGXByteBuffer_SetUInt8_1(buffer, lastValue << 4 | GXHelpers_GetValue(*String_at(&value, ch)));
                lastValue = -1;
                ++index;
            }
        }
        else if (lastValue != -1)
        {
            CGXByteBuffer_SetUInt8_1(buffer, GXHelpers_GetValue(*String_at(&value, ch)));
            lastValue = -1;
            ++index;
        }
    }
}

void GXHelpers_Write_2(char* fileName, char* pData, int len)
{
    if (len != 0 && pData != NULL)
    {
        DLMSPort_FILE *file;
        file = DLMSPort_fopen(fileName, DLMSPort_wa);
        DLMSPort_fwrite(file, pData, len);
        DLMSPort_fclose(file);
    }
}

void GXHelpers_Write_1(String fileName, String data)
{
    if (String_size(&data) != 0)
    {
        DLMSPort_FILE *file;
        file = DLMSPort_fopen(String_c_str(&fileName), DLMSPort_wa);
        DLMSPort_fwrite(file, String_c_str(&data), String_size(&data));
        DLMSPort_fclose(file);
    }
}

bool GXHelpers_GetBits(unsigned char *tmp, unsigned char BitMask)
{
    return (*tmp & BitMask) != 0;
}

bool GXHelpers_StringCompare(const char* c1, const char* c2)
{
    return strcmp(c1, c2) == 0;
}

int GXHelpers_GetDataTypeSize(DLMS_DATA_TYPE type)
{
    int size = -1;
    switch (type) {
    case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
        size = 1;
        break;
    case DLMS_DATA_TYPE_BOOLEAN:
        size = 1;
        break;
    case DLMS_DATA_TYPE_DATE:
        size = 5;
        break;
    case DLMS_DATA_TYPE_DATETIME:
        size = 12;
        break;
    case DLMS_DATA_TYPE_ENUM:
        size = 1;
        break;
    case DLMS_DATA_TYPE_FLOAT32:
        size = 4;
        break;
    case DLMS_DATA_TYPE_FLOAT64:
        size = 8;
        break;
    case DLMS_DATA_TYPE_INT16:
        size = 2;
        break;
    case DLMS_DATA_TYPE_INT32:
        size = 4;
        break;
    case DLMS_DATA_TYPE_INT64:
        size = 8;
        break;
    case DLMS_DATA_TYPE_INT8:
        size = 1;
        break;
    case DLMS_DATA_TYPE_NONE:
        size = 0;
        break;
    case DLMS_DATA_TYPE_TIME:
        size = 4;
        break;
    case DLMS_DATA_TYPE_UINT16:
        size = 2;
        break;
    case DLMS_DATA_TYPE_UINT32:
        size = 4;
        break;
    case DLMS_DATA_TYPE_UINT64:
        size = 8;
        break;
    case DLMS_DATA_TYPE_UINT8:
        size = 1;
        break;
    default:
        break;
    }

    return size;
}

void GXHelpers_GetLogicalName_1(unsigned char* buff, String* ln)
{
    int dataSize;
    char tmp[25];
    //If Script Action target is not set it is null
    if (buff == NULL)
    {
        String_clear(ln);
        String_append_1(ln, "0.0.0.0.0.0");
    }
    else
    {
#if _MSC_VER > 1000
        dataSize = DLMSPort_sprintf_s(tmp, 25, "%d.%d.%d.%d.%d.%d", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]) + 1;
#else
        dataSize = DLMSPort_sprintf(tmp, "%d.%d.%d.%d.%d.%d", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]) + 1;
#endif
        if (dataSize > 25)
        {
            assert(0);
        }
        String_clear(ln);
        String_append_2(ln, tmp, dataSize - 1);
    }
}

void GXHelpers_GetLogicalName_2(CGXByteBuffer* buff, String* ln)
{
    unsigned char tmp[6];
    CGXByteBuffer_Get(buff, tmp, 6);
    GXHelpers_GetLogicalName_1(tmp, ln);
}

String* GXHelpers_rtrim(String* s)
{
//        s.String_Erase(std::find_if(s.rbegin(), s.rend(),
//            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
//        return s;

    char c;
    int i;

    for (i = String_length(s) - 1; i >= 0; i--)
    {
        c = *String_at(s, i);
        if ((c != ' ') && (c != '\t') && (c != '\n') && (c != '\v')
         && (c != '\f') && (c != '\r'))
        {
            break;
        }
    }

    return String_erase(s, i + 1, String_length(s) - (i + 1));
}

String* GXHelpers_trim(String* s)
{
    return GXHelpers_ltrim(GXHelpers_rtrim(s));
}
