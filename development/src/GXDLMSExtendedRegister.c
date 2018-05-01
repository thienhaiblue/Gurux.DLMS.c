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
#include "../include/GXDLMSExtendedRegister.h"
#include "../include/GXDLMSRegister.h"
#include "../include/Optimize.h"

bool CGXDLMSExtendedRegister_IsRead(CGXDLMSExtendedRegister* p, int index)
{
    if (index == 3)
    {
        return p->m_Unit != 0;
    }
    return CGXDLMSObject_IsRead((CGXDLMSObject*) p, index);
}

static void CGXDLMSExtendedRegister__(CGXDLMSExtendedRegister *p)
{
    p->GetAttributeCount = CGXDLMSExtendedRegister_GetAttributeCount;
    p->GetMethodCount = CGXDLMSExtendedRegister_GetMethodCount;
    p->GetValue = CGXDLMSExtendedRegister_GetValue;
    p->SetValue = CGXDLMSExtendedRegister_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSExtendedRegister_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSExtendedRegister_GetDataType;
    p->GetUIDataType = CGXDLMSExtendedRegister_GetUIDataType;
    p->GetValues = CGXDLMSExtendedRegister_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSExtendedRegister_GetAttributeIndexToRead;

    CGXDateTime_1(&p->m_CaptureTime);
    CGXDLMSVariant_1(&p->m_Status);
}

//Constructor.
//CGXDLMSExtendedRegister::CGXDLMSExtendedRegister() :
  //  CGXDLMSExtendedRegister("", 0)
void CGXDLMSExtendedRegister_1(CGXDLMSExtendedRegister* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSExtendedRegister_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
//CGXDLMSExtendedRegister::CGXDLMSExtendedRegister(std::string ln, unsigned short sn) :
  //  CGXDLMSRegister(DLMS_OBJECT_TYPE_EXTENDED_REGISTER, ln, sn)
void CGXDLMSExtendedRegister_2(CGXDLMSExtendedRegister* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_EXTENDED_REGISTER, &ln, sn);

    CGXDLMSExtendedRegister__(p);
}

//LN Constructor.
//CGXDLMSExtendedRegister::CGXDLMSExtendedRegister(std::string ln) :
  //  CGXDLMSExtendedRegister(ln, 0)
void CGXDLMSExtendedRegister_3(CGXDLMSExtendedRegister* p, String ln)
{
    CGXDLMSExtendedRegister_2(p, ln, 0);
}

/**
 Status of COSEM Extended Register object.
*/
CGXDLMSVariant CGXDLMSExtendedRegister_GetStatus(CGXDLMSExtendedRegister* p)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, &(p->m_Status));

    return tmp; // = copy cons + des
}
void CGXDLMSExtendedRegister_SetStatus(CGXDLMSExtendedRegister* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&(p->m_Status), &value);
}

int CGXDLMSExtendedRegister_GetUIDataType(CGXDLMSExtendedRegister* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_DATETIME;
    }
    else
    {
        return CGXDLMSObject_GetUIDataType((CGXDLMSObject*) p, index, type);
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns amount of attributes.
int CGXDLMSExtendedRegister_GetAttributeCount(CGXDLMSExtendedRegister* p)
{
    return 5;
}

// Returns amount of methods.
int CGXDLMSExtendedRegister_GetMethodCount(CGXDLMSExtendedRegister* p)
{
    return 1;
}

void CGXDLMSExtendedRegister_GetValues(CGXDLMSExtendedRegister* p, Vector* values)
{
    CGXDLMSRegister_GetValues((CGXDLMSRegister*) p, values);
    //values.push_back(m_Status.ToString());
    //values.push_back(m_CaptureTime.ToString());

    Vector_push_back_Str_1(values, &(p->m_Status));

    String str = CGXDateTime_ToString(&(p->m_CaptureTime));
    Vector_push_back(values, &str);

    String_d(&str);
}

void CGXDLMSExtendedRegister_GetAttributeIndexToRead(CGXDLMSExtendedRegister* p, Vector* attributes)
{
    CGXDLMSRegister_GetAttributeIndexToRead((CGXDLMSRegister*) p, attributes);
    int tmp;
    //Status
    if (!CGXDLMSExtendedRegister_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //CaptureTime
    if (CGXDLMSExtendedRegister_CanRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSExtendedRegister_GetDataType(CGXDLMSExtendedRegister* p, int index, DLMS_DATA_TYPE* type)
{
    if (index < 4)
    {
        return CGXDLMSRegister_GetDataType((CGXDLMSRegister*) p, index, type);
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSExtendedRegister_GetValue(CGXDLMSExtendedRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
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
        //e.GetValue().Clear();
        //e.GetValue().vt = DLMS_DATA_TYPE_STRUCTURE;
        //e.GetValue().Arr.push_back(m_Scaler);
        //e.GetValue().Arr.push_back(m_Unit);

        CGXDLMSVariant* p_var = CGXDLMSValueEventArg_GetValue(e);

        CGXDLMSVariant_Clear(p_var);
        p_var->st.vt = DLMS_DATA_TYPE_STRUCTURE;

        CGXDLMSVariant var1;
        CGXDLMSVariant_8(&var1, p->m_Scaler);

        Vector_push_back(&(p_var->Arr), &var1);

        CGXDLMSVariant var2;

        CGXDLMSVariant_19(&var2, p->m_Unit);
        Vector_push_back(&(p_var->Arr), &var2);

        CGXDLMSVariant_d(&var1);
        CGXDLMSVariant_d(&var2);

        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSExtendedRegister_SetValue(CGXDLMSExtendedRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index < 4)
    {
        return CGXDLMSRegister_SetValue_2((CGXDLMSRegister*) p, settings, e);
    }
    else if (e_index == 4)
    {
        //m_Status = e.GetValue();
        CGXDLMSVariant_copy_1(&(p->m_Status), CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 5)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_DATETIME, &tmp);
            p->m_CaptureTime = tmp.dateTime;

            CGXDLMSVariant_d(&tmp);
        }
        else
        {
            p->m_CaptureTime = CGXDLMSValueEventArg_GetValue(e)->dateTime;
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSExtendedRegister_d(CGXDLMSExtendedRegister* p)
{
    CGXDLMSVariant_d(&p->m_Status);

    CGXDLMSRegister_d((CGXDLMSRegister*) p);
}
