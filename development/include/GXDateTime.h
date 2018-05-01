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

#ifndef GXDATETIME_H
#define GXDATETIME_H

#include <stdbool.h>

#include "enums.h"

#include "String.h"

// DataType enumerates skipped fields from date time.
typedef enum
{
    // Nothing is skipped from date time.
    DATETIME_SKIPS_NONE = 0x0,
    // Year part of date time is skipped.
    DATETIME_SKIPS_YEAR = 0x1,
    // Month part of date time is skipped.
    DATETIME_SKIPS_MONTH = 0x2,
    // Day part is skipped.
    DATETIME_SKIPS_DAY = 0x4,
    // Day of week part of date time is skipped.
    DATETIME_SKIPS_DAYOFWEEK = 0x8,
    // Hours part of date time is skipped.
    DATETIME_SKIPS_HOUR = 0x10,
    // Minute part of date time is skipped.
    DATETIME_SKIPS_MINUTE = 0x20,
    // Seconds part of date time is skipped.
    DATETIME_SKIPS_SECOND = 0x40,
    // Hundreds of seconds part of date time is skipped.
    DATETIME_SKIPS_MS = 0x80,
    //Devitation is skipped on write.
    DATETIME_SKIPS_DEVITATION = 0x100
} DATETIME_SKIPS;

// This class is used because in COSEM object model some fields from date time can be ignored.
// Default behavior of DateTime do not allow this.
typedef struct
{
    short m_Deviation;
    DATETIME_SKIPS m_Skip;
    struct tm m_Value;
    bool m_DaylightSavingsBegin;
    bool m_DaylightSavingsEnd;
    DLMS_CLOCK_STATUS m_Status;
} CGXDateTime;

extern void CGXDateTime_Init(CGXDateTime* p, int year, int month, int day, int hour, int minute, int second, int millisecond, int devitation);

// Constructor.
extern void CGXDateTime_1(CGXDateTime* p);
extern void CGXDateTime_2(CGXDateTime* p, struct tm* value);
extern void CGXDateTime_3(CGXDateTime* p, struct tm* value);
extern void CGXDateTime_4(CGXDateTime* p, int year, int month, int day, int hour, int minute, int second, int millisecond);
extern void CGXDateTime_5(CGXDateTime* p, int year, int month, int day, int hour, int minute, int second, int millisecond, int devitation);

// Used date time value.
extern struct tm* CGXDateTime_GetValue(CGXDateTime* p);
extern void CGXDateTime_SetValue(CGXDateTime* p, const struct tm* value);

// Skip selected date time fields.
extern DATETIME_SKIPS CGXDateTime_GetSkip(CGXDateTime* p);
extern void CGXDateTime_SetSkip(CGXDateTime* p, DATETIME_SKIPS value);
extern String CGXDateTime_ToString(CGXDateTime* p);

//Get currect time.
extern CGXDateTime CGXDateTime_Now();

// Daylight savings begin.
extern bool CGXDateTime_GetDaylightSavingsBegin(CGXDateTime* p);
extern void CGXDateTime_SetDaylightSavingsBegin(CGXDateTime* p, bool value);

// Daylight savings end.
extern bool CGXDateTime_GetDaylightSavingsEnd(CGXDateTime* p);
extern void CGXDateTime_SetDaylightSavingsEnd(CGXDateTime* p, bool value);

// Get deviation.
extern int CGXDateTime_GetDeviation(CGXDateTime* p);

// Set deviation.
extern void CGXDateTime_SetDeviation(CGXDateTime* p, int value);

// Status of the clock.
extern DLMS_CLOCK_STATUS CGXDateTime_GetStatus(CGXDateTime* p);
extern void CGXDateTime_SetStatus(CGXDateTime* p, DLMS_CLOCK_STATUS value);

/**
* Set time to midnight.
*/
extern void CGXDateTime_ResetTime(CGXDateTime* p);
/**
* Add hours to current time.
*/
extern int CGXDateTime_AddHours(CGXDateTime* p, int hours);

/**
* Add minutes to current time.
*/
extern int CGXDateTime_AddMinutes(CGXDateTime* p, int minutes);

/**
* Add seconds to current time.
*/
extern int CGXDateTime_AddSeconds(CGXDateTime* p, int seconds);

/**
* Add days to current time.
*/
extern int CGXDateTime_AddDays(CGXDateTime* p, int hours);

/**
* Compare current time to another time.
*/
extern int CGXDateTime_CompareTo(CGXDateTime* p, CGXDateTime* antherDate);

/**
* Get amount of days in given month.
*/
extern unsigned char CGXDateTime_DaysInMonth(int year, short month);

/**
* Get difference between given time and run time in ms.
*
* @param start
*            Start date time.
* @param to
*            Compared time.
* @return Difference in milliseconds.
*/
extern long CGXDateTime_GetDifference(struct tm* start, CGXDateTime* to);

// Convert value to local time.
extern int CGXDateTime_ToLocalTime(CGXDateTime* p, struct tm* localTime);

#endif //GXDATETIME_H
