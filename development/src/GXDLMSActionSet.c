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

#include "../include/GXDLMSActionSet.h"
#include "../include/String.h"

void CGXDLMSActionSet_(CGXDLMSActionSet *p)
{
    CGXDLMSActionItem_(&p->m_ActionUp);
    CGXDLMSActionItem_(&p->m_ActionDown);
}

void CGXDLMSActionSet_d(CGXDLMSActionSet *p)
{
    CGXDLMSActionItem_d(&p->m_ActionUp);
    CGXDLMSActionItem_d(&p->m_ActionDown);
}

String CGXDLMSActionSet_ToString(CGXDLMSActionSet *p)
{
    String sb;
    String_(&sb);

    String t_Str1 = CGXDLMSActionItem_ToString(&(p->m_ActionUp));
    String_append_3(&sb, &t_Str1);

    String_append_1(&sb, " ");

    String t_Str2 = CGXDLMSActionItem_ToString(&(p->m_ActionDown));
    String_append_3(&sb, &t_Str2);

    String_d(&t_Str1);
    String_d(&t_Str2);
    return sb; // = copy cons + des
}
