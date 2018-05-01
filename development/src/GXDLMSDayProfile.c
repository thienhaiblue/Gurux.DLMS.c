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

#include "../include/GXDLMSDayProfile.h"
#include "../include/String.h"
#include "../include/Vector.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

static void CGXDLMSDayProfile__(CGXDLMSDayProfile *p)
{
    Vector_(&p->m_DaySchedules, sizeof(CGXDLMSDayProfileAction*), NULL, NULL); // std::vector<CGXDLMSDayProfileAction*>
}

/**
 Constructor.
*/
void CGXDLMSDayProfile_1(CGXDLMSDayProfile *p)
{
    CGXDLMSDayProfile__(p);

    p->m_DayId = 0;
}

/**
 Constructor.
*/
void CGXDLMSDayProfile_2(CGXDLMSDayProfile *p, short dayId, Vector* schedules)
{
    CGXDLMSDayProfile__(p);

	p->m_DayId = dayId;
	CGXDLMSDayProfile_SetDaySchedules(p, schedules);
}

void CGXDLMSDayProfile_d(CGXDLMSDayProfile *p)
{
    for (unsigned int it = Vector_begin(&(p->m_DaySchedules));
         it != Vector_end(&(p->m_DaySchedules)); ++it)
    {
        CGXDLMSDayProfileAction **t_temp = Vector_at(&(p->m_DaySchedules), it);

        CGXDLMSDayProfileAction_d(*t_temp);
        DLMSPort_free(*t_temp);
    }
    Vector_clear(&(p->m_DaySchedules));
}

Vector* CGXDLMSDayProfile_GetDaySchedules(CGXDLMSDayProfile *p)//std::vector<CGXDLMSDayProfileAction*>&
{
    return &(p->m_DaySchedules);
}
void CGXDLMSDayProfile_SetDaySchedules(CGXDLMSDayProfile *p, Vector* value)//std::vector<CGXDLMSDayProfileAction*>&
{
    Vector_copy_1(&(p->m_DaySchedules), value);
}

String CGXDLMSDayProfile_ToString(CGXDLMSDayProfile *p)
{
    String sb;
    String_(&sb);

    String_append_int(&sb, p->m_DayId);

    String t_tmp;
    for (unsigned int it = Vector_begin(&(p->m_DaySchedules));
         it != Vector_end(&(p->m_DaySchedules)); ++it)
    {
        String_append_1(&sb, " ");

        t_tmp = CGXDLMSDayProfileAction_ToString(Vector_at(&(p->m_DaySchedules), it));
        String_append_3(&sb, &t_tmp);
        String_d(&t_tmp);
    }

    return sb; // = copy cons + des
}
