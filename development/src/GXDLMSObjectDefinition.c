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

#include "../include/GXDLMSObjectDefinition.h"
#include "../include/GXDLMSObjectFactory.h"

static void CGXDLMSObjectDefinition__(CGXDLMSObjectDefinition* p)
{
    String_(&p->m_LogicalName);
}

void CGXDLMSObjectDefinition_1(CGXDLMSObjectDefinition* p)
{
    CGXDLMSObjectDefinition__(p);
}

/*
 * Constructor
 */
void CGXDLMSObjectDefinition_2(CGXDLMSObjectDefinition* p, DLMS_OBJECT_TYPE classId, String logicalName)
{
    CGXDLMSObjectDefinition__(p);

    p->m_ClassId = classId;
    String_copy_1(&(p->m_LogicalName), &logicalName);
}

String CGXDLMSObjectDefinition_ToString(CGXDLMSObjectDefinition* p)
{
    String sb;
    String_(&sb);

    String t_Str = CGXDLMSObjectFactory_ObjectTypeToString(p->m_ClassId);
    String_append_3(&sb, &t_Str);

    String_append_1(&sb, " ");

    String_append_3(&sb, &(p->m_LogicalName));

    String_d(&t_Str);

    return sb; // = copy cons + des
}

String CGXDLMSObjectDefinition_GetLogicalName(CGXDLMSObjectDefinition* p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_LogicalName));

    return t_Str; // = copy cons + des
}
void CGXDLMSObjectDefinition_SetLogicalName(CGXDLMSObjectDefinition* p, String value)
{
	String_copy_1(&(p->m_LogicalName), &value);
}

void CGXDLMSObjectDefinition_d(CGXDLMSObjectDefinition* p)
{
    String_d(&p->m_LogicalName);
}

void CGXDLMSObjectDefinition_v_c(void *p1, const void* p2)
{
    CGXDLMSObjectDefinition* t_p1 = (CGXDLMSObjectDefinition*) p1;
    CGXDLMSObjectDefinition* t_p2 = (CGXDLMSObjectDefinition*) p2;

    t_p1->m_ClassId = t_p2->m_ClassId;
    String_copy_1(&t_p1->m_LogicalName, &t_p2->m_LogicalName);
}

void CGXDLMSObjectDefinition_v_d(void *p)
{
    CGXDLMSObjectDefinition_d((CGXDLMSObjectDefinition*) p);
}
