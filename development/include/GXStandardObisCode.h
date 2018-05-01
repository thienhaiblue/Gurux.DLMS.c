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
#ifndef GXSTANDARDOBISCODE_H
#define GXSTANDARDOBISCODE_H

#include "String.h"
#include "Vector.h"

typedef struct
{
    Vector m_OBIS; // std::vector< std::string >
    String m_DataType;
    String m_Interfaces;
    String m_Description;
} CGXStandardObisCode;

//public
// Constructor.
extern void CGXStandardObisCode_1(CGXStandardObisCode *p);

// Constructor.
extern void CGXStandardObisCode_2(CGXStandardObisCode *p,
                                  Vector obis, String* desc,
                                  String* interfaces, String* dataType); //std::vector< std::string >
// OBIS code.
extern Vector* CGXStandardObisCode_GetOBIS(CGXStandardObisCode *p);//std::vector< std::string >&

extern void CGXStandardObisCode_SetOBIS(CGXStandardObisCode *p, Vector* value);//std::vector< std::string >&

// OBIS code description.
extern String* CGXStandardObisCode_GetDescription(CGXStandardObisCode *p);

extern void CGXStandardObisCode_SetDescription(CGXStandardObisCode *p, String value);

// Interfaces that are using this m_OBIS code.
extern String* CGXStandardObisCode_GetInterfaces(CGXStandardObisCode *p);
extern void CGXStandardObisCode_SetInterfaces(CGXStandardObisCode *p, String value);

// Standard data types.
extern String* CGXStandardObisCode_GetDataType(CGXStandardObisCode *p);
extern void CGXStandardObisCode_SetDataType(CGXStandardObisCode *p, String value);

extern void CGXStandardObisCode_d(CGXStandardObisCode *p);

extern void CGXStandardObisCode_v_c(void* p1, const void* p2);
extern void CGXStandardObisCode_v_d(void* p);

#endif //GXSTANDARDOBISCODE_H
