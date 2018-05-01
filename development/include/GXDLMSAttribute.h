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
#ifndef CGXDLMSATTRIBUTE_H
#define CGXDLMSATTRIBUTE_H

#include <stdbool.h>

#include "enums.h"

typedef struct
{
    DLMS_ACCESS_MODE	m_Access;
    int					m_Index;
    DLMS_DATA_TYPE		m_Type;
    DLMS_DATA_TYPE		m_UIType;
    int					m_MinimumVersion;
    DLMS_METHOD_ACCESS_MODE	m_MethodAccess;
    bool				m_Static;
    int					m_Order;
} CGXDLMSAttribute;

//Constructor
// Default parameter: Type = DLMS_DATA_TYPE_NONE, UiType = DLMS_DATA_TYPE_NONE, Access = DLMS_ACCESS_MODE_READ, MinimumVersion = 1
extern void CGXDLMSAttribute_(CGXDLMSAttribute *p, int index, DLMS_DATA_TYPE Type, DLMS_DATA_TYPE UiType, DLMS_ACCESS_MODE Access, int MinimumVersion);

/// <summary>
/// Attribute Index.
/// </summary>
extern int CGXDLMSAttribute_GetIndex(CGXDLMSAttribute *p);

/// <summary>
/// Attribute data type.
/// </summary>
extern DLMS_DATA_TYPE CGXDLMSAttribute_GetDataType(CGXDLMSAttribute *p);

extern void CGXDLMSAttribute_SetDataType(CGXDLMSAttribute *p, DLMS_DATA_TYPE type);

/// <summary>
/// Data type that user want's to see.
/// </summary>
extern DLMS_DATA_TYPE CGXDLMSAttribute_GetUIDataType(CGXDLMSAttribute *p);

extern void CGXDLMSAttribute_SetUIDataType(CGXDLMSAttribute *p, DLMS_DATA_TYPE type);

extern DLMS_ACCESS_MODE CGXDLMSAttribute_GetAccess(CGXDLMSAttribute *p);

extern void CGXDLMSAttribute_SetAccess(CGXDLMSAttribute *p, DLMS_ACCESS_MODE value);

extern DLMS_METHOD_ACCESS_MODE CGXDLMSAttribute_GetMethodAccess(CGXDLMSAttribute *p);

extern void CGXDLMSAttribute_SetMethodAccess(CGXDLMSAttribute *p, DLMS_METHOD_ACCESS_MODE value);

extern bool CGXDLMSAttribute_GetStatic(CGXDLMSAttribute *p);

extern void CGXDLMSAttribute_SetStatic(CGXDLMSAttribute *p, bool value);

/*
/// <summary>
/// Attribute values.
/// </summary>
[Browsable(false)]
[XmlIgnore]
public GXObisValueItemCollection Values
{
    get;
    set;
}
*/

/// <summary>
/// Read order.
/// </summary>
extern int CGXDLMSAttribute_GetOrder(CGXDLMSAttribute *p);

/// <summary>
/// Minimum version vhere this attribute is implemented.
/// </summary>
extern int CGXDLMSAttribute_GetMinimumVersion(CGXDLMSAttribute *p);

#endif //CGXDLMSATTRIBUTE_H
