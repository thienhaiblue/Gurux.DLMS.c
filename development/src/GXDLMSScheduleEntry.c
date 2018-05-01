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

#include "../include/GXDLMSScheduleEntry.h"

String CGXDLMSScheduleEntry_GetLogicalName(CGXDLMSScheduleEntry *p)
{
	String t_Str;
	String_2(&t_Str, &(p->m_LogicalName));

	return t_Str; // copy cons + des
}

void CGXDLMSScheduleEntry_SetLogicalName(CGXDLMSScheduleEntry *p, String value)
{
	String_copy_1(&(p->m_LogicalName), &value);
}

String CGXDLMSScheduleEntry_GetExecWeekdays(CGXDLMSScheduleEntry *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_ExecWeekdays));

    return t_Str; // copy cons + des
}

void CGXDLMSScheduleEntry_SetExecWeekdays(CGXDLMSScheduleEntry *p, String value)
{
	String_copy_1(&(p->m_ExecWeekdays), &value);
}

String CGXDLMSScheduleEntry_GetExecSpecDays(CGXDLMSScheduleEntry *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_ExecSpecDays));

    return t_Str; // copy cons + des
}

void CGXDLMSScheduleEntry_SetExecSpecDays(CGXDLMSScheduleEntry *p, String value)
{
	String_copy_1(&(p->m_ExecSpecDays), &value);
}

void CGXDLMSScheduleEntry_(CGXDLMSScheduleEntry *p)
{
    String_(&p->m_LogicalName);
    CGXDateTime_1(&p->m_SwitchTime);
    String_(&p->m_ExecWeekdays);
    String_(&p->m_ExecSpecDays);
    CGXDateTime_1(&p->m_BeginDate);
    CGXDateTime_1(&p->m_EndDate);
}

void CGXDLMSScheduleEntry_d(CGXDLMSScheduleEntry *p)
{
    String_d(&p->m_LogicalName);
    String_d(&p->m_ExecWeekdays);
    String_d(&p->m_ExecSpecDays);
}

void CGXDLMSScheduleEntry_v_c(void* p1, const void* p2)
{
	CGXDLMSScheduleEntry* t_p1 = (CGXDLMSScheduleEntry*) p1;
	CGXDLMSScheduleEntry* t_p2 = (CGXDLMSScheduleEntry*) p2;

	*t_p1 = *t_p2;

    String_2(&t_p1->m_LogicalName, &t_p2->m_LogicalName);
    String_2(&t_p1->m_ExecWeekdays, &t_p2->m_ExecWeekdays);
    String_2(&t_p1->m_ExecSpecDays, &t_p2->m_ExecSpecDays);
}

void CGXDLMSScheduleEntry_v_d(void* p)
{
	CGXDLMSScheduleEntry_d((CGXDLMSScheduleEntry*) p);
}
