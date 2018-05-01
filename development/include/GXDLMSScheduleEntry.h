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

#ifndef GXDLMSSCHEDULEENTRY_H
#define GXDLMSSCHEDULEENTRY_H

#include "GXDLMSObject.h"
#include "String.h"

/**
* Executed scripts.
*/
typedef struct
{
    /**
    * Schedule entry index.
    */
    unsigned char m_Index;

    /**
     * Is Schedule entry enabled.
     */
    bool m_Enable;

    /**
     * Logical name of the Script table object.
     */
    String m_LogicalName;

    /**
     * Script identifier of the script to be executed.
     */
    unsigned char m_ScriptSelector;

    /**
    *
    */
    CGXDateTime m_SwitchTime;

    /**
     * Defines a period in minutes, in which an entry shall be processed after
     * power fail.
     */
    unsigned char m_ValidityWindow;

    /**
     * Days of the week on which the entry is valid.
     */
    String m_ExecWeekdays;

    /**
     * Perform the link to the IC �Special days table�, day_id.
     */
    String m_ExecSpecDays;

    /**
     * Date starting period in which the entry is valid.
     */
    CGXDateTime m_BeginDate;

    /**
     * Date starting period in which the entry is valid.
     */
    CGXDateTime m_EndDate;

} CGXDLMSScheduleEntry;

/**
 * Get schedule entry index.
 *
 * @return Entry index.
 */
extern unsigned char CGXDLMSScheduleEntry_GetIndex(CGXDLMSScheduleEntry *p);

/**
 * Set schedule entry index.
 *
 * @param value
 *            Entry index.
 */
extern void CGXDLMSScheduleEntry_SetIndex(CGXDLMSScheduleEntry *p, unsigned char value);

/**
 * Is Schedule entry enabled.
 *
 * @return True, if schedule entry is enabled.
 */
extern bool CGXDLMSScheduleEntry_GetEnable(CGXDLMSScheduleEntry *p);

/**
 * Enable schedule entry.
 *
 * @param value
 *            Is Schedule entry enabled.
 */
extern void CGXDLMSScheduleEntry_SetEnable(CGXDLMSScheduleEntry *p, bool value);

/**
 * Returns logical name of the Script table object.
 *
 * @return Logical name of the Script table object.
 */
extern String CGXDLMSScheduleEntry_GetLogicalName(CGXDLMSScheduleEntry *p);

extern void CGXDLMSScheduleEntry_SetLogicalName(CGXDLMSScheduleEntry *p, String value);

/**
 * Get script identifier of the script to be executed.
 *
 * @return Script identifier.
 */
extern unsigned char CGXDLMSScheduleEntry_GetScriptSelector(CGXDLMSScheduleEntry *p);

/**
 * Set script identifier of the script to be executed.
 *
 * @param value
 *            Script identifier.
 */
extern void CGXDLMSScheduleEntry_SetScriptSelector(CGXDLMSScheduleEntry *p, unsigned char value);

/**
 * @return
 */
extern CGXDateTime CGXDLMSScheduleEntry_GetSwitchTime(CGXDLMSScheduleEntry *p);

/**
 * @param value
 */
extern void CGXDLMSScheduleEntry_SetSwitchTime(CGXDLMSScheduleEntry *p, CGXDateTime value);

/**
 * Defines a period in minutes, in which an entry shall be processed after
 * power fail.
 *
 * @return Validity period in minutes.
 */
extern unsigned char CGXDLMSScheduleEntry_GetValidityWindow(CGXDLMSScheduleEntry *p);

/**
 * Defines a period in minutes, in which an entry shall be processed after
 * power fail.
 *
 * @param value
 *            Validity period in minutes.
 */
extern void CGXDLMSScheduleEntry_SetValidityWindow(CGXDLMSScheduleEntry *p, unsigned char value);

/**
 * Get days of the week on which the entry is valid.
 *
 * @return Bit array of valid week days.
 */
extern String CGXDLMSScheduleEntry_GetExecWeekdays(CGXDLMSScheduleEntry *p);

/**
 * Set days of the week on which the entry is valid.
 *
 * @param value
 *            Bit array of valid week days.
 */
extern void CGXDLMSScheduleEntry_SetExecWeekdays(CGXDLMSScheduleEntry *p, String value);

/**
 * Perform the link to the IC Special days table.
 *
 * @return day_id.
 */
extern String CGXDLMSScheduleEntry_GetExecSpecDays(CGXDLMSScheduleEntry *p);

/**
 * Perform the link to the IC Special days table.
 *
 * @param value
 *            day_id
 */
extern void CGXDLMSScheduleEntry_SetExecSpecDays(CGXDLMSScheduleEntry *p, String value);

/**
 * Date starting period in which the entry is valid.
 *
 * @return Begin date.
 */
extern CGXDateTime CGXDLMSScheduleEntry_GetBeginDate(CGXDLMSScheduleEntry *p);

/**
 * Date starting period in which the entry is valid.
 *
 * @param value
 *            Begin date.
 */
extern void CGXDLMSScheduleEntry_SetBeginDate(CGXDLMSScheduleEntry *p, CGXDateTime value);

/**
 * Get date starting period in which the entry is valid.
 *
 * @return End date.
 */
extern CGXDateTime CGXDLMSScheduleEntry_GetEndDate(CGXDLMSScheduleEntry *p);

/**
 * Set date starting period in which the entry is valid.
 *
 * @param value
 *            End date.
 */
extern void CGXDLMSScheduleEntry_SetEndDate(CGXDLMSScheduleEntry *p, CGXDateTime value);

extern void CGXDLMSScheduleEntry_(CGXDLMSScheduleEntry *p);
extern void CGXDLMSScheduleEntry_d(CGXDLMSScheduleEntry *p);

extern void CGXDLMSScheduleEntry_v_c(void* p1, const void* p2);
extern void CGXDLMSScheduleEntry_v_d(void* p);

#endif //GXDLMSSCHEDULEENTRY_H
