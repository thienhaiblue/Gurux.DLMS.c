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

#include "../include/GXDLMSPushObject.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

String CGXDLMSPushObject_GetLogicalName(CGXDLMSPushObject *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_LogicalName));

    return t_Str; // = copy cons + des
}
void CGXDLMSPushObject_SetLogicalName(CGXDLMSPushObject *p, String value)
{
	String_copy_1(&(p->m_LogicalName), &value );
}

String CGXDLMSPushObject_ToString(CGXDLMSPushObject *p)
{
    String sb;
    String_(&sb);

    String_append_int(&sb, (int) p->m_Type);

    String_append_1(&sb, " ");

    String_append_3(&sb, &(p->m_LogicalName));

    String_append_1(&sb, " ");

    String_append_int(&sb, p->m_AttributeIndex);

    String_append_1(&sb, " ");

    String_append_int(&sb, p->m_DataIndex);

    return sb; // = copy cons + des
}

void CGXDLMSPushObject_(CGXDLMSPushObject *p)
{
    String_(&p->m_LogicalName);
}

void CGXDLMSPushObject_d(CGXDLMSPushObject *p)
{
    String_d(&p->m_LogicalName);
}
