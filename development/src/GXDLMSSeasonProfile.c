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

#include "../include/GXDLMSSeasonProfile.h"

static void CGXDLMSSeasonProfile__(CGXDLMSSeasonProfile* p)
{
    String_(&p->m_Name);
    CGXDateTime_1(&p->m_Start);
    String_(&p->m_WeekName);
}

/**
 Constructor.
*/
void CGXDLMSSeasonProfile_1(CGXDLMSSeasonProfile* p)
{
    CGXDLMSSeasonProfile__(p);
}

/**
 Constructor.
*/
void CGXDLMSSeasonProfile_2(CGXDLMSSeasonProfile* p, String name, CGXDateTime start, String weekName)
{
    CGXDLMSSeasonProfile__(p);

	CGXDLMSSeasonProfile_SetName(p, name);
	p->m_Start = start;
	CGXDLMSSeasonProfile_SetWeekName(p, weekName);
}

/**
 Name of season profile.
*/
String CGXDLMSSeasonProfile_GetName(CGXDLMSSeasonProfile* p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_Name));

    return t_Str; // copy cons + des
}

void CGXDLMSSeasonProfile_SetName(CGXDLMSSeasonProfile* p, String value)
{
	String_copy_1(&(p->m_Name), &value);
}

/**
 Week name of season profile.
*/
String CGXDLMSSeasonProfile_GetWeekName(CGXDLMSSeasonProfile* p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_WeekName));

    return t_Str; // copy cons + des
}
void CGXDLMSSeasonProfile_SetWeekName(CGXDLMSSeasonProfile* p, String value)
{
	String_copy_1(&(p->m_WeekName), &value);
}

String CGXDLMSSeasonProfile_ToString(CGXDLMSSeasonProfile* p)
{
	String sb;
	String_(&sb);
	String_append_3(&sb, &(p->m_Name));
	String_append_1(&sb, " ");

	String t_Str = CGXDateTime_ToString(&(p->m_Start));
	String_append_3(&sb, &t_Str);
	String_d(&t_Str);

	return sb; // copy cons + des
}

void CGXDLMSSeasonProfile_d(CGXDLMSSeasonProfile* p)
{
    String_d(&p->m_Name);
    String_d(&p->m_WeekName);
}
