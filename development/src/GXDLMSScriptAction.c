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

#include "../include/GXDLMSScriptAction.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

/**
 Logical name of executed object.
*/
String CGXDLMSScriptAction_GetLogicalName(CGXDLMSScriptAction* p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_LogicalName));

    return t_Str; // copy cons + des
}
void CGXDLMSScriptAction_SetLogicalName(CGXDLMSScriptAction* p, String value)
{
	String_copy_1(&(p->m_LogicalName), &value);
}

/**
 Parameter is service spesific.
*/
CGXDLMSVariant CGXDLMSScriptAction_GetParameter(CGXDLMSScriptAction* p)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, &(p->m_Parameter));

    return tmp; // copy cons + des
}
void CGXDLMSScriptAction_SetParameter(CGXDLMSScriptAction* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&(p->m_Parameter), &value);
}

String CGXDLMSScriptAction_ToString(CGXDLMSScriptAction* p)
{
	String sb;
	String_(&sb);

	String_append_int(&sb, p->m_Type);

	String_append_1(&sb, " ");

    String_append_int(&sb, p->m_ObjectType);

    String_append_1(&sb, " ");

	String_append_3(&sb, &(p->m_LogicalName));
	String_append_1(&sb, " ");

    String_append_int(&sb, p->m_Index);

    String_append_1(&sb, " ");

    String_append_var_str(&sb, &(p->m_Parameter));

	return sb; // copy cons + des
}

void CGXDLMSScriptAction_(CGXDLMSScriptAction* p)
{
    String_(&p->m_LogicalName);
    CGXDLMSVariant_1(&p->m_Parameter);
}

void CGXDLMSScriptAction_d(CGXDLMSScriptAction* p)
{
    String_d(&p->m_LogicalName);
    CGXDLMSVariant_d(&p->m_Parameter);
}
