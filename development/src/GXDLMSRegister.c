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
#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSRegister.h"
#include "../include/GXDLMSConverter.h"
#include "../include/Optimize.h"

#include <math.h>

bool CGXDLMSRegister_IsRead(CGXDLMSRegister* p, int index)
{
    if (index == 3)
    {
        return p->m_Unit != 0;
    }
    return CGXDLMSObject_IsRead((CGXDLMSObject*) p, index);
}

void CGXDLMSRegister__(CGXDLMSRegister* p)
{
    p->GetAttributeCount = CGXDLMSRegister_GetAttributeCount;
    p->GetMethodCount = CGXDLMSRegister_GetMethodCount;
    p->GetValue = CGXDLMSRegister_GetValue_2;
    p->SetValue = CGXDLMSRegister_SetValue_2;
    p->Invoke = CGXDLMSRegister_Invoke;

    p->d = CGXDLMSRegister_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSRegister_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSRegister_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSRegister_GetAttributeIndexToRead;

    CGXDLMSVariant_1(&p->m_Value);
}

//Constructor.
//CGXDLMSRegister::CGXDLMSRegister() :
//    CGXDLMSRegister("", 0)
void CGXDLMSRegister_2(CGXDLMSRegister* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSRegister_3(p, t_Str, 0);

    String_d(&t_Str);
}

//CGXDLMSRegister::CGXDLMSRegister(DLMS_OBJECT_TYPE type, std::string ln, unsigned short sn) :
//    CGXDLMSObject(type, ln, sn)
void CGXDLMSRegister_1(CGXDLMSRegister* p, DLMS_OBJECT_TYPE type, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, type, &ln, sn);

    CGXDLMSRegister__(p);

    p->m_Unit = 0;
    p->m_Scaler = 0;
}

//SN Constructor.
//CGXDLMSRegister::CGXDLMSRegister(std::string ln, unsigned short sn) :
//    CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER, ln, sn)
void CGXDLMSRegister_3(CGXDLMSRegister* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_REGISTER, &ln, sn);

    CGXDLMSRegister__(p);

    p->m_Unit = 0;
    p->m_Scaler = 0;
}

//LN Constructor.
//CGXDLMSRegister::CGXDLMSRegister(std::string ln) :
//    CGXDLMSRegister(ln, 0)
void CGXDLMSRegister_4(CGXDLMSRegister* p, String ln)
{
    CGXDLMSRegister_3(p, ln, 0);
}

/// <summary>
/// Get value of COSEM Data object.
/// </summary>
CGXDLMSVariant CGXDLMSRegister_GetValue_1(CGXDLMSRegister* p)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, &(p->m_Value));

    return tmp; // = copy cons + des
}

/// <summary>
/// Set value of COSEM Data object.
/// </summary>
void CGXDLMSRegister_SetValue_1(CGXDLMSRegister* p, CGXDLMSVariant* value)
{
    CGXDLMSVariant_copy_1(&p->m_Value, value);
}

// Scaler of COSEM Register object.
double CGXDLMSRegister_GetScaler(CGXDLMSRegister* p)
{
    return pow((float)10, p->m_Scaler);
}

void CGXDLMSRegister_SetScaler(CGXDLMSRegister* p, double value)
{
    p->m_Scaler = (signed char)log10(value);
}

/*
 * Reset value.
 */

void CGXDLMSRegister_Reset(CGXDLMSRegister* p)
{
    CGXDLMSVariant_Clear(&p->m_Value);
}

// Returns amount of attributes.
int CGXDLMSRegister_GetAttributeCount(CGXDLMSRegister* p)
{
    return 3;
}

// Returns amount of methods.
int CGXDLMSRegister_GetMethodCount(CGXDLMSRegister* p)
{
    return 1;
}

int CGXDLMSRegister_Invoke(CGXDLMSRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    if (e->m_Index == 1)
    {
        CGXDLMSRegister_Reset(p);
        return DLMS_ERROR_CODE_OK;
    }
    e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSRegister_GetValues(CGXDLMSRegister* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_1(values, &p->m_Value);

    String str;
    String_3(&str, "Scaler: ");

    double s = CGXDLMSRegister_GetScaler(p);
    //if there is no fractal part.

    CGXDLMSVariant tmp;

    if (s - (long)s == 0)
    {
        // str += CGXDLMSVariant((long)s).ToString();

        CGXDLMSVariant_11(&tmp, (long)s);
    }
    else
    {
        // str += CGXDLMSVariant(s).ToString();

        CGXDLMSVariant_4(&tmp, s);
    }

    String_append_var_str(&str, &tmp);

    CGXDLMSVariant_d(&tmp);

    String_append_1(&str, " Unit: ");

    String_append_1(&str, CGXDLMSConverter_GetUnitAsString(p->m_Unit));

    Vector_push_back(values, &str);

    String_d(&str);
}

void CGXDLMSRegister_GetAttributeIndexToRead(CGXDLMSRegister* p, Vector* attributes) //std::vector<int>&
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //ScalerUnit
    if (!CGXDLMSRegister_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //Value
    if (CGXDLMSRegister_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSRegister_GetDataType(CGXDLMSRegister* p, int index, DLMS_DATA_TYPE* type)
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
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSRegister_GetValue_2(CGXDLMSRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
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
    if (e_index == 3)
    {
        CGXDLMSVariant_Clear(CGXDLMSValueEventArg_GetValue(e));
        CGXDLMSValueEventArg_GetValue(e)->st.vt = DLMS_DATA_TYPE_STRUCTURE;

        CGXDLMSVariant tmp;
        CGXDLMSVariant_8(&tmp, p->m_Scaler);

        Vector_push_back(&CGXDLMSValueEventArg_GetValue(e)->Arr, &tmp);

        CGXDLMSVariant_d(&tmp);

        CGXDLMSVariant_19(&tmp, p->m_Unit);

        Vector_push_back(&CGXDLMSValueEventArg_GetValue(e)->Arr, &tmp);

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSRegister_SetValue_2(CGXDLMSRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        if (p->m_Scaler != 0)
        {
            double val = CGXDLMSRegister_GetScaler(p);
            val *= CGXDLMSVariant_ToDouble(CGXDLMSValueEventArg_GetValue(e));

            CGXDLMSVariant tmp;
            CGXDLMSVariant_4(&tmp, val);

            CGXDLMSRegister_SetValue_1(p, &tmp);

            CGXDLMSVariant_d(&tmp);
        }
        else
        {
            CGXDLMSRegister_SetValue_1(p, CGXDLMSValueEventArg_GetValue(e));
        }
    }
    else if (e_index == 3 && CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_STRUCTURE)
    {
        p->m_Scaler = CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 0));
        p->m_Unit = CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 1));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSRegister_d(CGXDLMSRegister* p)
{
    CGXDLMSVariant_d(&p->m_Value);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
