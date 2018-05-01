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

#include "../include/GXDLMSData.h"
#include "../include/Optimize.h"

static void CGXDLMSData__(CGXDLMSData *p)
{
    p->GetAttributeCount = CGXDLMSData_GetAttributeCount;
    p->GetMethodCount = CGXDLMSData_GetMethodCount;
    p->GetValue = CGXDLMSData_GetValue_2;
    p->SetValue = CGXDLMSData_SetValue_2;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSData_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSData_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSData_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSData_GetAttributeIndexToRead;

    CGXDLMSVariant_1(&p->m_Value);
}

//Constructor.
void CGXDLMSData_1(CGXDLMSData *p){
    String t_Str;
    String_3(&t_Str, "");

	CGXDLMSData_2(p, t_Str, 0);

	String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSData_2(CGXDLMSData *p, String ln, unsigned short sn){
    String t_Str;
    String_2(&t_Str, &ln);

	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_DATA, &t_Str, sn);
	CGXDLMSData__(p);

	String_d(&t_Str);
}

//LN Constructor.
void CGXDLMSData_3(CGXDLMSData *p, String ln){
	CGXDLMSData_2(p, ln, 0);
}

// Get value of COSEM Data object.
void CGXDLMSData_GetValue_1(CGXDLMSData *p, CGXDLMSVariant *out)
{
    CGXDLMSVariant_d(out);
    CGXDLMSVariant_2(out, &(p->m_Value));
}

// Set value of COSEM Data object.
void CGXDLMSData_SetValue_1(CGXDLMSData *p, CGXDLMSVariant* value)
{
    CGXDLMSVariant_copy_1(&(p->m_Value), value);
}

// Returns amount of attributes.
int CGXDLMSData_GetAttributeCount(CGXDLMSData *p)
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSData_GetMethodCount(CGXDLMSData *p)
{
    return 0;
}

void CGXDLMSData_GetValues(CGXDLMSData *p, Vector* values)//std::vector<std::string>&
{
	Vector_clear(values);

	Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

	Vector_push_back_Str_1(values, &(p->m_Value));
}

void CGXDLMSData_GetAttributeIndexToRead(CGXDLMSData *p, Vector* attributes)//std::vector<int>& attributes
{
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        int t_tmp = 1;
    	Vector_push_back(attributes, &t_tmp);
    }
    //Value
    if (CGXDLMSData_CanRead(p, 2))
    {
        int t_tmp = 2;
    	Vector_push_back(attributes, &t_tmp);
    }
}

int CGXDLMSData_GetDataType(CGXDLMSData *p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        return CGXDLMSObject_GetDataType((CGXDLMSObject*) p, index, type);
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSData_GetValue_2(CGXDLMSData *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
    	CGXDLMSValueEventArg_SetValue(e, &p->m_Value);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSData_SetValue_2(CGXDLMSData *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSData_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        CGXDLMSData_SetValue_1(p, CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSData_d(CGXDLMSData *p)
{
    CGXDLMSVariant_d(&p->m_Value);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
