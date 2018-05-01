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
#include "../include/GXDLMSWeekProfile.h"

static void CGXDLMSWeekProfile__(CGXDLMSWeekProfile* p)
{
    String_(&p->m_Name);
}

/**
 Constructor.
*/
void CGXDLMSWeekProfile_1(CGXDLMSWeekProfile* p)
{
    CGXDLMSWeekProfile__(p);

    p->m_Monday = p->m_Tuesday = p->m_Wednesday = p->m_Thursday = p->m_Friday = p->m_Saturday = p->m_Sunday = 0;
}

/**
 Constructor.
*/
void CGXDLMSWeekProfile_2(CGXDLMSWeekProfile* p, String name, int monday, int tuesday, int wednesday, int thursday, int friday, int saturday, int sunday)
{
    CGXDLMSWeekProfile__(p);

	CGXDLMSWeekProfile_SetName(p, name);
	p->m_Monday = monday;
	p->m_Tuesday = tuesday;
	p->m_Wednesday = wednesday;
	p->m_Thursday = thursday;
	p->m_Friday = friday;
	p->m_Saturday = saturday;
	p->m_Sunday = sunday;
}

String CGXDLMSWeekProfile_GetName(CGXDLMSWeekProfile* p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_Name));

    return t_Str; // = copy cons + des
}
void CGXDLMSWeekProfile_SetName(CGXDLMSWeekProfile* p, String value)
{
    String_copy_1(&(p->m_Name), &value);
}

String CGXDLMSWeekProfile_ToString(CGXDLMSWeekProfile* p)
{
    String sb;
    String_2(&sb, &(p->m_Name));

    return sb; // = copy cons + des
}

void CGXDLMSWeekProfile_d(CGXDLMSWeekProfile* p)
{
    String_d(&p->m_Name);
}
