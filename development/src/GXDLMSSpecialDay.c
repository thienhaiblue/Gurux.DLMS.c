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

#include "../include/GXDLMSSpecialDay.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

String CGXDLMSSpecialDay_ToString(CGXDLMSSpecialDay *p)
{
    String sb;
    String_(&sb);

    String_append_int(&sb, p->m_Index);

    String_append_1(&sb, " ");

    String t_Str = CGXDateTime_ToString(&(p->m_Date));
    String_append_3(&sb, &t_Str);
    String_d(&t_Str);
    String_append_1(&sb, " ");

    String_append_int(&sb, p->m_DayId);

    return sb; // copy cons + des
}

void CGXDLMSSpecialDay_(CGXDLMSSpecialDay *p)
{
    CGXDateTime_1(&p->m_Date);
}
