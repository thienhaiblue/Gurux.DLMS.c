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

#include "../include/GXDLMSMonitoredValue.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/Optimize.h"

void CGXDLMSMonitoredValue_(CGXDLMSMonitoredValue *p)
{
    String_(&p->m_LogicalName);

    p->m_ObjectType = DLMS_OBJECT_TYPE_NONE;
    p->m_AttributeIndex = 0;
}

void CGXDLMSMonitoredValue_Update(CGXDLMSMonitoredValue *p, CGXDLMSObject* pObj, int attributeIndex)
{
    p->m_ObjectType = pObj->m_ObjectType;
    CGXDLMSObject_GetLogicalName_2(pObj, &(p->m_LogicalName));
    p->m_AttributeIndex = attributeIndex;
}

String CGXDLMSMonitoredValue_GetLogicalName(CGXDLMSMonitoredValue *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_LogicalName));

	return t_Str; // = copy cons + des
}
void CGXDLMSMonitoredValue_SetLogicalName(CGXDLMSMonitoredValue *p, String value)
{
	String_copy_1(&(p->m_LogicalName), &value);
}

String CGXDLMSMonitoredValue_ToString(CGXDLMSMonitoredValue *p)
{
	String sb;
	String_(&sb);

	String t_Str = CGXDLMSObjectFactory_ObjectTypeToString(p->m_ObjectType);

	String_append_3(&sb, &t_Str);
	String_append_1(&sb, " ");

	String_d(&t_Str);

	String_append_3(&sb, &(p->m_LogicalName));
	String_append_1(&sb, " ");

	String_append_int(&sb, p->m_AttributeIndex);

	return sb; // = copy cons + des
}

void CGXDLMSMonitoredValue_d(CGXDLMSMonitoredValue *p)
{
    String_d(&p->m_LogicalName);
}
