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

#include "../include/GXDLMSActionItem.h"
#include "../include/String.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

//Constructor.
void CGXDLMSActionItem_(CGXDLMSActionItem* p)
{
    String_(&p->m_LogicalName);

    p->m_ScriptSelector = 0;
}

void CGXDLMSActionItem_d(CGXDLMSActionItem* p)
{
    String_clear(&(p->m_LogicalName));
}

String CGXDLMSActionItem_GetLogicalName(CGXDLMSActionItem* p)
{
    String resultStr;
    String_2(&resultStr, &(p->m_LogicalName));

    return resultStr; // = copy cons + des
}

void CGXDLMSActionItem_SetLogicalName(CGXDLMSActionItem* p, String value)
{
    String_copy_1(&(p->m_LogicalName), &value);
}

String CGXDLMSActionItem_ToString(CGXDLMSActionItem* p)
{
    String resultStr;
    String_(&resultStr);

    String_append_3(&resultStr, &(p->m_LogicalName));
    String_append_1(&resultStr, " ");

    String_append_int(&resultStr, p->m_ScriptSelector);

    return resultStr; // = copy cons + des

    //TODO
}

void CGXDLMSActionItem_copy(CGXDLMSActionItem* p, CGXDLMSActionItem* src)
{
    String_copy_1(&p->m_LogicalName, &src->m_LogicalName);
    p->m_ScriptSelector = src->m_ScriptSelector;
}
