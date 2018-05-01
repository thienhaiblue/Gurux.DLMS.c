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

#include "../include/GXApplicationContextName.h"
#include "../include/GXDLMSVariant.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

String CGXApplicationContextName_GetLogicalName(CGXApplicationContextName *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_LogicalName));

    return t_Str; // = copy cons + des
}

void CGXApplicationContextName_SetLogicalName(CGXApplicationContextName *p, String value)
{
    String_copy_1(&(p->m_LogicalName), &value);
}

String CGXApplicationContextName_ToString(CGXApplicationContextName *p)
{
    String t_Str;
    String_(&t_Str);

    String_append_3(&t_Str, &(p->m_LogicalName));

    String_append_1(&t_Str, " ");

    String_append_int(&t_Str, p->m_JointIsoCtt);

    String_append_1(&t_Str, " ");

    String_append_int(&t_Str, p->m_Country);

    String_append_1(&t_Str, " ");

    String_append_int(&t_Str, p->m_CountryName);

    String_append_1(&t_Str, " ");

    String_append_int(&t_Str, p->m_IdentifiedOrganization);

    String_append_1(&t_Str, " ");

    String_append_int(&t_Str, p->m_DlmsUA);

    String_append_1(&t_Str, " ");

    String_append_int(&t_Str, p->m_ApplicationContext);

    String_append_1(&t_Str, " ");

    String_append_int(&t_Str, p->m_ContextId);

    return t_Str; // = copy cons + des
}

void CGXApplicationContextName_(CGXApplicationContextName *p)
{
    String_(&p->m_LogicalName);
}

void CGXApplicationContextName_d(CGXApplicationContextName *p)
{
    String_d(&p->m_LogicalName);
}
