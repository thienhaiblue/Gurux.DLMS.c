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

#include "../include/GXDateTime.h"
#include "../include/GXDate.h"
#include "../include/GXTime.h"
#include "../include/GXHelpers.h"
#include "../include/DLMSPort.h"
#include "../include/String.h"
//#include <locale>
//#include <vector>
#include <assert.h>

//Get UTC offset in minutes.
static void GetUtcOffset(int* hours, int* minutes)
{
    time_t zero = 24 * 60 * 60L;
    struct tm tm;

    // local time for Jan 2, 1900 00:00 UTC
#if _MSC_VER > 1000
    localtime_s(&tm, &zero);
#else
    tm = *localtime(&zero);
#endif
    *hours = tm.tm_hour;

    //If the local time is the "day before" the UTC, subtract 24 hours from the hours to get the UTC offset
    if (tm.tm_mday < 2)
    {
        *hours -= 24;
    }
    *minutes = tm.tm_min;
}

static time_t GetUtcTime(struct tm * timeptr)
{
    /* gets the epoch time relative to the local time zone,
    and then adds the appropriate number of seconds to make it UTC */
    int hours, minutes;
    GetUtcOffset(&hours, &minutes);
    return mktime(timeptr) + (hours * 3600) + (minutes * 60);
}


// Constructor.
void CGXDateTime_1(CGXDateTime* p)
{
    int hours, minutes;
    GetUtcOffset(&hours, &minutes);
    p->m_Deviation = -(hours * 60 + minutes);
    p->m_Skip = DATETIME_SKIPS_NONE;
    memset(&(p->m_Value), 0xFF, sizeof(p->m_Value));
    p->m_DaylightSavingsBegin = p->m_DaylightSavingsEnd = false;
    p->m_Status = DLMS_CLOCK_STATUS_OK;
}

// Constructor.
void CGXDateTime_2(CGXDateTime* p, struct tm* value)
{
    CGXDateTime_3(p, value);
}

// Constructor.
void CGXDateTime_3(CGXDateTime* p, struct tm* value)
{
    int hours, minutes;
    GetUtcOffset(&hours, &minutes);
    p->m_Deviation = -(hours * 60 + minutes);
    p->m_Value = *value;
    p->m_Skip = DATETIME_SKIPS_NONE;
    p->m_DaylightSavingsBegin = p->m_DaylightSavingsEnd = false;
    p->m_Status = DLMS_CLOCK_STATUS_OK;
}

void CGXDateTime_4(CGXDateTime* p, int year, int month, int day, int hour, int minute, int second, int millisecond)
{
    int hours, minutes;
    GetUtcOffset(&hours, &minutes);
    CGXDateTime_Init(p, year, month, day, hour, minute, second, millisecond, -(hours * 60 + minutes));
}

// Constructor.
void CGXDateTime_5(CGXDateTime* p, int year, int month, int day, int hour, int minute, int second, int millisecond, int devitation)
{
    CGXDateTime_Init(p, year, month, day, hour, minute, second, millisecond, devitation);
}

// Constructor.
void CGXDateTime_Init(CGXDateTime* p, int year, int month, int day, int hour, int minute, int second, int millisecond, int devitation)
{
    memset(&(p->m_Value), 0, sizeof(p->m_Value));
    p->m_DaylightSavingsBegin = p->m_DaylightSavingsEnd = false;
    p->m_Status = DLMS_CLOCK_STATUS_OK;
    int skip = DATETIME_SKIPS_NONE;
    if (year < 1 || year == 0xFFFF)
    {
        skip |= DATETIME_SKIPS_YEAR;
        year = 1900 + CGXDateTime_Now(p).m_Value.tm_year;
    }
    if (month < 1 || month == 0xFF)
    {
        skip |= DATETIME_SKIPS_MONTH;
        month = 0;
    }
    else
    {
        --month;
    }
    if (day < 1 || day == 0xFF)
    {
        skip |= DATETIME_SKIPS_DAY;
        day = 1;
    }
    else if (day == 0xFD)
    {
        day = CGXDateTime_DaysInMonth(year, month) - 1;
    }
    else if (day == 0xFE)
    {
        day = CGXDateTime_DaysInMonth(year, month);
    }
    if (hour == -1 || hour == 0xFF)
    {
        skip |= DATETIME_SKIPS_HOUR;
        hour = 1;
    }
    if (minute == -1 || minute == 0xFF)
    {
        skip |= DATETIME_SKIPS_MINUTE;
        minute = 0;
    }
    if (second == -1 || second == 0xFF)
    {
        skip |= DATETIME_SKIPS_SECOND;
        second = 0;
    }
    if (millisecond < 1 || millisecond == 0xFF)
    {
        skip |= DATETIME_SKIPS_MS;
        millisecond = 0;
    }
    p->m_Skip = (DATETIME_SKIPS)skip;
    if (year != 0)
    {
        p->m_Value.tm_year = year - 1900;
    }
    p->m_Value.tm_mon = month;
    p->m_Value.tm_mday = day;
    p->m_Value.tm_hour = hour;
    p->m_Value.tm_min = minute;
    p->m_Value.tm_sec = second;
    p->m_Deviation = devitation;
}

unsigned char CGXDateTime_DaysInMonth(int year, short month)
{
    if (month == 0 || month == 2 || month == 4 ||
        month == 6 || month == 7 || month == 9 || month == 11)
    {
        return 31;
    }
    else if (month == 3 || month == 5 || month == 8 || month == 10)
    {
        return 30;
    }
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return 29;
            }
            return 28;
        }
        return 29;
    }
    return 28;
}

//Constants for different orders of date components.
typedef enum
{
    GXDLMS_DATE_FORMAT_INVALID = -1,
    GXDLMS_DATE_FORMAT_DMY = 0,
    GXDLMS_DATE_FORMAT_MDY = 1,
    GXDLMS_DATE_FORMAT_YMD = 2,
    GXDLMS_DATE_FORMAT_YDM = 3
} GXDLMS_DATE_FORMAT;

int GetDateFormat(GXDLMS_DATE_FORMAT* format, char* separator)
{
    int ret = 0, value, lastPos = 0, pos;
    char buff[11];
    struct tm order = { 0 };
    order.tm_year = 0;
    order.tm_mday = 1;
    order.tm_mon = 1;//Month is zero based.
    ret = (int)strftime(buff, 11, "%x", &order);
    if (ret > 0)
    {
        for (pos = 0; pos != ret; ++pos)
        {
            //If numeric value
            if (buff[pos] >= '0' && buff[pos] <= '9')
            {

            }
            else //If date time separator.
            {
                *separator = buff[pos];
#if _MSC_VER > 1000
                if (DLMSPort_sscanf_s(buff + lastPos, "%d", &value) == 1)
#else
                if (DLMSPort_sscanf(buff + lastPos, "%d", &value) == 1)
#endif
                {
                    if (value == 1)
                    {
                        *format = (lastPos == 0) ? GXDLMS_DATE_FORMAT_DMY : GXDLMS_DATE_FORMAT_YDM;
                        break;
                    }
                    else if (value == 2)
                    {
                        *format = (lastPos == 0) ? GXDLMS_DATE_FORMAT_MDY : GXDLMS_DATE_FORMAT_YMD;
                        break;
                    }
                }
                lastPos = pos + 1;
            }
        }
    }
    return ret;
}


String CGXDateTime_ToString(CGXDateTime* p)
{
    char buff[50];
    int ret;
    if (p->m_Skip != DATETIME_SKIPS_NONE)
    {
        CGXByteBuffer ba;
        CGXByteBuffer_1(&ba);

        GXDLMS_DATE_FORMAT format;
        char separator;
        //Add year, month and date if used.
        if ((p->m_Skip & (DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY)) != (DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY))
        {
            ret = GetDateFormat(&format, &separator);
            switch (format)
            {
            case GXDLMS_DATE_FORMAT_DMY:
            {
                if (p->m_Value.tm_mday != -1 && (p->m_Skip & DATETIME_SKIPS_DAY) == 0)
                {
                    CGXByteBuffer_AddIntAsString(&ba, p->m_Value.tm_mday);
                }
                if (p->m_Value.tm_mon != -1 && (p->m_Skip & DATETIME_SKIPS_MONTH) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, 1 + p->m_Value.tm_mon);
                }
                if (p->m_Value.tm_year != -1 && (p->m_Skip & DATETIME_SKIPS_YEAR) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, 1900 + p->m_Value.tm_year);
                }
            }
            break;
            case GXDLMS_DATE_FORMAT_MDY:
            {
                if (p->m_Value.tm_mon != -1 && (p->m_Skip & DATETIME_SKIPS_MONTH) == 0)
                {
                    CGXByteBuffer_AddIntAsString(&ba, 1 + p->m_Value.tm_mon);
                }
                if (p->m_Value.tm_mday != -1 && (p->m_Skip & DATETIME_SKIPS_DAY) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, p->m_Value.tm_mday);
                }
                if (p->m_Value.tm_year != -1 && (p->m_Skip & DATETIME_SKIPS_YEAR) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, 1900 + p->m_Value.tm_year);
                }
            }
            break;
            case GXDLMS_DATE_FORMAT_YMD:
            {
                if (p->m_Value.tm_year != -1 && (p->m_Skip & DATETIME_SKIPS_YEAR) == 0)
                {
                    CGXByteBuffer_AddIntAsString(&ba, 1900 + p->m_Value.tm_year);
                }
                if (p->m_Value.tm_mon != -1 && (p->m_Skip & DATETIME_SKIPS_MONTH) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, 1 + p->m_Value.tm_mon);
                }
                if (p->m_Value.tm_mday != -1 && (p->m_Skip & DATETIME_SKIPS_DAY) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, p->m_Value.tm_mday);
                }
            }
            break;
            case GXDLMS_DATE_FORMAT_YDM:
            {
                if (p->m_Value.tm_year != -1 && (p->m_Skip & DATETIME_SKIPS_YEAR) == 0)
                {
                    CGXByteBuffer_AddIntAsString(&ba, 1900 + p->m_Value.tm_year);
                }
                if (p->m_Value.tm_mday != -1 && (p->m_Skip & DATETIME_SKIPS_DAY) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, p->m_Value.tm_mday);
                }
                if (p->m_Value.tm_mon != -1 && (p->m_Skip & DATETIME_SKIPS_MONTH) == 0)
                {
                    if (ba.m_Size != 0)
                    {
                        CGXByteBuffer_SetUInt8_1(&ba, separator);
                    }
                    CGXByteBuffer_AddIntAsString(&ba, 1 + p->m_Value.tm_mon);
                }
            }
            break;
            default:
            {
                ret = (int)strftime(buff, 50, "%X", &(p->m_Value));
                CGXByteBuffer_SetUInt8_1(&ba, ' ');
                CGXByteBuffer_Set_1(&ba, buff, ret);
                CGXByteBuffer_d(&ba);

                String t_tmp;
                t_tmp.c = NULL;
                return t_tmp;
            }
            }
        }

        //Add hours.
        if (p->m_Value.tm_hour != -1 && (p->m_Skip & DATETIME_SKIPS_HOUR) == 0)
        {
            if (ba.m_Size != 0)
            {
                CGXByteBuffer_SetUInt8_1(&ba, ' ');
            }
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 50, "%.2d", p->m_Value.tm_hour);
#else
            DLMSPort_sprintf(buff, "%.2d", p->m_Value.tm_hour);
#endif
            CGXByteBuffer_AddString_2(&ba, buff);
        }
        //Add minutes.
        if (p->m_Value.tm_min != -1 && (p->m_Skip & DATETIME_SKIPS_MINUTE) == 0)
        {
            if (ba.m_Size != 0)
            {
                CGXByteBuffer_SetUInt8_1(&ba, ':');
            }
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 50, "%.2d", p->m_Value.tm_min);
#else
            DLMSPort_sprintf(buff, "%.2d", p->m_Value.tm_min);
#endif
            CGXByteBuffer_AddString_2(&ba, buff);
        }
        //Add seconds.
        if (p->m_Value.tm_sec != -1 && (p->m_Skip & DATETIME_SKIPS_SECOND) == 0)
        {
            if (ba.m_Size != 0)
            {
                CGXByteBuffer_SetUInt8_1(&ba, ':');
            }
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 50, "%.2d", p->m_Value.tm_sec);
#else
            DLMSPort_sprintf(buff, "%.2d", p->m_Value.tm_sec);
#endif
            CGXByteBuffer_AddString_2(&ba, buff);
        }

        String t_tmp;
        CGXByteBuffer_ToString(&ba, &t_tmp);

        CGXByteBuffer_d(&ba);
        return t_tmp; // = copy cons + des
    }
    //If value is not set return empty std::string.
    if (p->m_Value.tm_year == -1)
    {
        String t_tmp;
        String_3(&t_tmp, "");

        return t_tmp; // = copy cons + des
    }

    String str;
    String_(&str);

    ret = (int)strftime(buff, 50, "%x %X", &(p->m_Value));
    String_append_2(&str, buff, ret);

    return str; // = copy cons + des
}

CGXDateTime CGXDateTime_Now()
{
    time_t tm1 = time(NULL);
#if _MSC_VER > 1000
    struct tm dt;
    localtime_s(&dt, &tm1);
#else
    struct tm dt = *localtime(&tm1);
#endif
    CGXDateTime now;
    CGXDateTime_2(&now, &dt);
    return now;
}

void CGXDateTime_ResetTime(CGXDateTime* p)
{
    p->m_Value.tm_hour = p->m_Value.tm_min = p->m_Value.tm_sec = 0;
}

int CGXDateTime_AddDays(CGXDateTime* p, int days)
{
    p->m_Value.tm_mday += days;
    if ((int)mktime(&(p->m_Value)) == -1)
    {
        return DLMS_ERROR_CODE_INVALID_DATE_TIME;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDateTime_AddHours(CGXDateTime* p, int hours)
{
    p->m_Value.tm_hour += hours;
    if ((int)mktime(&(p->m_Value)) == -1)
    {
        return DLMS_ERROR_CODE_INVALID_DATE_TIME;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDateTime_AddMinutes(CGXDateTime* p, int minutes)
{
    p->m_Value.tm_min += minutes;
    if ((int)mktime(&(p->m_Value)) == -1)
    {
        return DLMS_ERROR_CODE_INVALID_DATE_TIME;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDateTime_AddSeconds(CGXDateTime* p, int seconds)
{
    p->m_Value.tm_sec += seconds;
    if ((int)mktime(&(p->m_Value)) == -1)
    {
        return DLMS_ERROR_CODE_INVALID_DATE_TIME;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDateTime_CompareTo(CGXDateTime* p, CGXDateTime* antherDate)
{
    time_t time1 = mktime(&(p->m_Value));
    time_t time2 = mktime(&antherDate->m_Value);
    if (time1 < time2)
    {
        return -1;
    }
    if (time1 > time2)
    {
        return 1;
    }
    return 0;
}

int CGXDateTime_ToLocalTime(CGXDateTime* p, struct tm* localTime)
{
    *localTime = p->m_Value;
    if (p->m_Deviation != -32768)//0x8000
    {
        (*localTime).tm_min += p->m_Deviation;
        time_t t = GetUtcTime(localTime);
        if (t == -1)
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
#if _MSC_VER > 1000
        localtime_s(localTime, &t);
#else
        *localTime = *localtime(&t);
#endif
    }
    return 0;
}

long CGXDateTime_GetDifference(struct tm* start, CGXDateTime* to)
{
    long diff = 0;
    // Compare seconds.
    if ((to->m_Skip & DATETIME_SKIPS_SECOND) != 0)
    {
        if (start->tm_sec < to->m_Value.tm_sec)
        {
            diff += (to->m_Value.tm_sec - start->tm_sec) * 1000L;
        }
        else
        {
            diff -= (start->tm_sec - to->m_Value.tm_sec) * 1000L;
        }
    }
    else if (diff < 0)
    {
        diff = 60000 + diff;
    }
    // Compare minutes.
    if ((to->m_Skip & DATETIME_SKIPS_MINUTE) != 0)
    {
        if (start->tm_min < to->m_Value.tm_min)
        {
            diff += (to->m_Value.tm_min - start->tm_min) * 60000L;
        }
        else
        {
            diff -= (start->tm_min - to->m_Value.tm_min) * 60000L;
        }
    }
    else if (diff < 0)
    {
        diff = 60 * 60000 + diff;
    }
    // Compare hours.
    if ((to->m_Skip & DATETIME_SKIPS_HOUR) != 0)
    {
        if (start->tm_hour < to->m_Value.tm_hour)
        {
            diff += (to->m_Value.tm_hour - start->tm_hour) * 60 * 60000L;
        }
        else
        {
            diff -= (start->tm_hour - to->m_Value.tm_hour) * 60 * 60000L;
        }
    }
    else if (diff < 0)
    {
        diff = 60 * 60000 + diff;
    }
    // Compare days.
    if ((to->m_Skip & DATETIME_SKIPS_DAY) != 0)
    {
        if (start->tm_mday < to->m_Value.tm_mday)
        {
            diff += (to->m_Value.tm_mday - start->tm_mday) * 24 * 60 * 60000;
        }
        else if (start->tm_mday != to->m_Value.tm_mday)
        {
            if ((to->m_Skip & DATETIME_SKIPS_DAY) == 0)
            {
                diff += (to->m_Value.tm_mday - start->tm_mday) * 24 * 60 * 60000L;
            }
            else {
                diff = ((CGXDateTime_DaysInMonth(start->tm_year, start->tm_mon) - start->tm_mday
                       + to->m_Value.tm_mday) * 24 * 60 * 60000L) + diff;
            }
        }
    }
    else if (diff < 0)
    {
        diff = 24 * 60 * 60000 + diff;
    }
    // Compare months.
    if ((to->m_Skip & DATETIME_SKIPS_MONTH) != 0)
    {
        if (start->tm_mon < to->m_Value.tm_mon)
        {
            for (int m = start->tm_mon; m != to->m_Value.tm_mon; ++m)
            {
                diff += CGXDateTime_DaysInMonth(start->tm_year, m) * 24 * 60 * 60000L;
            }
        }
        else
        {
            for (int m = to->m_Value.tm_mon; m != start->tm_mon; ++m)
            {
                diff += -CGXDateTime_DaysInMonth(start->tm_year, m) * 24 * 60 * 60000L;
            }
        }
    }
    else if (diff < 0)
    {
        diff = CGXDateTime_DaysInMonth(start->tm_year, start->tm_mon) * 24 * 60 * 60000L + diff;
    }
    return diff;
}

////////////////////////////////////////////////////////////////////////////////////////////////
/* CGXDate */
// Constructor.
void CGXDate_1(CGXDate* p)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_1(t_p);
    t_p->m_Skip = (DATETIME_SKIPS)(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS);
};

// Constructor.
void CGXDate_2(CGXDate* p, struct tm value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_2(t_p, &value);

    t_p->m_Skip = (DATETIME_SKIPS)(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS);
}

// Constructor.
void CGXDate_3(CGXDate* p, int year, int month, int day)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_4(t_p, year, month, day, -1, -1, -1, -1);
}

/**
* Constructor.
*
* @param forvalue
*            Date value.
*/
/// <summary>
/// Constructor.
/// </summary>
void CGXDate_4(CGXDate* p, CGXDateTime* value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_2(t_p, &value->m_Value);
    t_p->m_Skip = (DATETIME_SKIPS)(value->m_Skip | DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS);
}

// operator=
void CGXDate_copy_1(CGXDate* p, const CGXDateTime* value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    t_p->m_Value = value->m_Value;
    t_p->m_Skip = (DATETIME_SKIPS)(value->m_Skip | DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS);
}

void CGXDate_copy_2(CGXDate* p, CGXDateTime value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    t_p->m_Value = value.m_Value;
    t_p->m_Skip = (DATETIME_SKIPS)(value.m_Skip | DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS);
}
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/* CGXTime */
// Constructor.
extern void CGXTime_1(CGXTime* p)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_1(t_p);
    t_p->m_Skip = (DATETIME_SKIPS)(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK);
}

// Constructor.
extern void CGXTime_2(CGXTime* p, struct tm value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_2(t_p, &value);
    t_p->m_Skip = (DATETIME_SKIPS)(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK);
}

// Constructor.
extern void CGXTime_3(CGXTime* p, int hour, int minute, int second, int millisecond)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_4(t_p, -1, -1, -1, hour, minute, second, millisecond);
    t_p->m_Skip = (DATETIME_SKIPS)(t_p->m_Skip | DATETIME_SKIPS_DAYOFWEEK);
}

/**
* Constructor.
*
* @param value
*            Date value.
*/
extern void CGXTime_4(CGXTime* p, CGXDateTime* value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    CGXDateTime_2(t_p, &value->m_Value);
    t_p->m_Skip = (DATETIME_SKIPS)(value->m_Skip | DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK);
}

// operator=
extern void CGXTime_copy_1(CGXTime* p, const CGXDateTime* value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    t_p->m_Value = value->m_Value;
    t_p->m_Skip = (DATETIME_SKIPS)(value->m_Skip | DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK);
}

extern void CGXTime_copy_2(CGXTime* p, CGXDateTime value)
{
    CGXDateTime* t_p = (CGXDateTime*) p;

    t_p->m_Value = value.m_Value;
    t_p->m_Skip = (DATETIME_SKIPS)(value.m_Skip | DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK);
}
////////////////////////////////////////////////////////////////////////////////////////////////
