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

#include "../include/GXStandardObisCode.h"

static void CGXStandardObisCode__(CGXStandardObisCode *p)
{
    Vector_(&p->m_OBIS, sizeof(String), String_v_c, String_v_d); // std::vector< std::string >
    String_(&p->m_DataType);
    String_(&p->m_Interfaces);
    String_(&p->m_Description);
}

void CGXStandardObisCode_1(CGXStandardObisCode *p)
{
    CGXStandardObisCode__(p);
}

void CGXStandardObisCode_2(CGXStandardObisCode *p,
                           Vector obis, String* desc,
                           String* interfaces, String* dataType)
{
    CGXStandardObisCode__(p);

	Vector_clear(&(p->m_OBIS));

//	m_OBIS.insert(m_OBIS.end(), obis.begin(), obis.end());
	for (unsigned int it = Vector_begin(&obis); it != Vector_end(&obis); ++it)
	{
	    Vector_push_back(&(p->m_OBIS), Vector_at(&obis, it));
	}

	CGXStandardObisCode_SetDescription(p, *desc);
	CGXStandardObisCode_SetInterfaces(p, *interfaces);
	CGXStandardObisCode_SetDataType(p, *dataType);
}

Vector* CGXStandardObisCode_GetOBIS(CGXStandardObisCode *p)
{
    return &(p->m_OBIS);
}

void CGXStandardObisCode_SetOBIS(CGXStandardObisCode *p, Vector* value)
{
	Vector_clear(&(p->m_OBIS));
//    m_OBIS.insert(m_OBIS.end(), value.begin(), value.end());
    for (unsigned int it = Vector_begin(value); it != Vector_end(value); ++it)
    {
        Vector_push_back(&(p->m_OBIS), Vector_at(value, it));
    }
}

/**
 m_OBIS code description.
*/
String* CGXStandardObisCode_GetDescription(CGXStandardObisCode *p)
{
    return &(p->m_Description);
}
void CGXStandardObisCode_SetDescription(CGXStandardObisCode *p, String value)
{
    String_copy_1(&(p->m_Description), &value);
}

/**
 m_Interfaces that are using this m_OBIS code.
*/
String* CGXStandardObisCode_GetInterfaces(CGXStandardObisCode *p)
{
    return &(p->m_Interfaces);
}
void CGXStandardObisCode_SetInterfaces(CGXStandardObisCode *p, String value)
{
    String_copy_1(&(p->m_Interfaces), &value);
}

/**
 Standard data types.
*/
String* CGXStandardObisCode_GetDataType(CGXStandardObisCode *p)
{
    return &(p->m_DataType);
}

void CGXStandardObisCode_SetDataType(CGXStandardObisCode *p, String value)
{
    String_copy_1(&(p->m_DataType), &value);
}

void CGXStandardObisCode_d(CGXStandardObisCode *p)
{
    Vector_d(&p->m_OBIS);
    String_d(&p->m_DataType);
    String_d(&p->m_Interfaces);
    String_d(&p->m_Description);
}

void CGXStandardObisCode_v_c(void* p1, const void* p2)
{
    CGXStandardObisCode* t_p1 = (CGXStandardObisCode*) p1;
    CGXStandardObisCode* t_p2 = (CGXStandardObisCode*) p2;

    Vector_copy_1(&t_p1->m_OBIS, &t_p2->m_OBIS);
    String_copy_1(&t_p1->m_DataType, &t_p2->m_DataType);
    String_copy_1(&t_p1->m_Interfaces, &t_p2->m_Interfaces);
    String_copy_1(&t_p1->m_Description, &t_p2->m_Description);
}

void CGXStandardObisCode_v_d(void* p)
{
    CGXStandardObisCode_d((CGXStandardObisCode*) p);
}
