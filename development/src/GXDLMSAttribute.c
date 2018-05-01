/*
 * GXDLMSAttribute.c
 *
 *  Created on: Feb 26, 2018
 *      Author: son
 */

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

#include "../include/GXDLMSAttribute.h"

static void CGXDLMSAttribute_Initialize(CGXDLMSAttribute *p, int index, DLMS_DATA_TYPE Type, DLMS_DATA_TYPE UiType, DLMS_ACCESS_MODE Access, int MinimumVersion)
{
    p->m_Access = Access;
    p->m_Static = false;
    p->m_Order = 0;
    p->m_Index = index;
    p->m_Type = Type;
    p->m_UIType = UiType;
    p->m_MethodAccess = DLMS_METHOD_ACCESS_MODE_NONE;
    p->m_MinimumVersion = MinimumVersion;
}
//Constructor
// Default parameter: Type = DLMS_DATA_TYPE_NONE, UiType = DLMS_DATA_TYPE_NONE, Access = DLMS_ACCESS_MODE_READ, MinimumVersion = 1
void CGXDLMSAttribute_(CGXDLMSAttribute *p, int index, DLMS_DATA_TYPE Type, DLMS_DATA_TYPE UiType, DLMS_ACCESS_MODE Access, int MinimumVersion)
{
    CGXDLMSAttribute_Initialize(p, index, Type, UiType, Access, MinimumVersion);
}
