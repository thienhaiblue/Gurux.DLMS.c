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
#include "../include/GXDLMSConverter.h"
#include "../include/GXDLMSDemandRegister.h"
#include "../include/Optimize.h"

bool CGXDLMSDemandRegister_IsRead(CGXDLMSDemandRegister* p, int index)
{
    if (index == 4)
    {
        return p->m_Unit != 0;
    }
    return CGXDLMSObject_IsRead((CGXDLMSObject*) p, index);
}

static void CGXDLMSDemandRegister__(CGXDLMSDemandRegister* p)
{
    p->GetAttributeCount = CGXDLMSDemandRegister_GetAttributeCount;
    p->GetMethodCount = CGXDLMSDemandRegister_GetMethodCount;
    p->GetValue = CGXDLMSDemandRegister_GetValue;
    p->SetValue = CGXDLMSDemandRegister_SetValue;
    p->Invoke = CGXDLMSDemandRegister_Invoke;

    p->d = CGXDLMSDemandRegister_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSDemandRegister_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSDemandRegister_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSDemandRegister_GetAttributeIndexToRead;

    CGXDLMSVariant_1(&p->m_CurrentAvarageValue);
    CGXDLMSVariant_1(&p->m_LastAvarageValue);
    CGXDLMSVariant_1(&p->m_Status);
    CGXDateTime_1(&p->m_CaptureTime);
    CGXDateTime_1(&p->m_StartTimeCurrent);
}

/**
 Constructor.
*/
//CGXDLMSDemandRegister::CGXDLMSDemandRegister() :
  //  CGXDLMSDemandRegister("", 0)
void CGXDLMSDemandRegister_1(CGXDLMSDemandRegister* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSDemandRegister_3(p, t_Str, 0);

    String_d(&t_Str);
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
//CGXDLMSDemandRegister::CGXDLMSDemandRegister(std::string ln) :
  //  CGXDLMSDemandRegister(ln, 0)
void CGXDLMSDemandRegister_2(CGXDLMSDemandRegister* p, String ln)
{
    CGXDLMSDemandRegister_3(p, ln, 0);
}

//CGXDLMSDemandRegister::CGXDLMSDemandRegister(std::string ln, unsigned short sn) :
  //  CGXDLMSObject(DLMS_OBJECT_TYPE_DEMAND_REGISTER, ln, sn)
void CGXDLMSDemandRegister_3(CGXDLMSDemandRegister* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_DEMAND_REGISTER, &ln, sn);

    CGXDLMSDemandRegister__(p);

    p->m_Period = p->m_NumberOfPeriods = p->m_Unit = p->m_Scaler = 0;
}

/**
 Current avarage value of COSEM Data object.
*/
CGXDLMSVariant CGXDLMSDemandRegister_GetCurrentAvarageValue(CGXDLMSDemandRegister* p)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, &(p->m_CurrentAvarageValue));

    return tmp; // =copy cons + des
}
void CGXDLMSDemandRegister_SetCurrentAvarageValue(CGXDLMSDemandRegister* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&(p->m_CurrentAvarageValue), &value);
}

/**
 Last avarage value of COSEM Data object.
*/
CGXDLMSVariant CGXDLMSDemandRegister_GetLastAvarageValue(CGXDLMSDemandRegister* p)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, &(p->m_LastAvarageValue));

    return tmp; // =copy cons + des
}
void CGXDLMSDemandRegister_SetLastAvarageValue(CGXDLMSDemandRegister* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&(p->m_LastAvarageValue), &value);
}

/**
 Scaler of COSEM Register object.
*/
double CGXDLMSDemandRegister_GetScaler(CGXDLMSDemandRegister* p)
{
    return pow((float)10, p->m_Scaler);
}

void CGXDLMSDemandRegister_SetScaler(CGXDLMSDemandRegister* p, double value)
{
    p->m_Scaler = (signed char)log10(value);
}

/**
 Scaler of COSEM Register object.
*/
CGXDLMSVariant CGXDLMSDemandRegister_GetStatus(CGXDLMSDemandRegister* p)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, &(p->m_Status));

    return tmp; // =copy cons + des
}
void CGXDLMSDemandRegister_SetStatus(CGXDLMSDemandRegister* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&(p->m_Status), &value);
}

/*
 * Reset e.GetValue().
 */
//void CGXDLMSDemandRegister_Reset(CGXDLMSDemandRegister* p)
//{
//
//}

/*
 * Next period.
 */
//void CGXDLMSDemandRegister_NextPeriod(CGXDLMSDemandRegister* p)
//{
//
//}

//void CGXDLMSDemandRegister::GetValues(std::vector<std::string>& values)
void CGXDLMSDemandRegister_GetValues(CGXDLMSDemandRegister* p, Vector* values)
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_1(values, &p->m_CurrentAvarageValue);

    Vector_push_back_Str_1(values, &p->m_LastAvarageValue);

    String str;
    String_3(&str, "Scaler: ");

    //if there is no fractal part.
    double s = CGXDLMSDemandRegister_GetScaler(p);

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

    String ln = CGXDLMSVariant_ToString(&p->m_Status);

    Vector_push_back(values, &ln);

    String_d(&ln);

    ln = CGXDateTime_ToString(&p->m_CaptureTime);

    Vector_push_back(values, &ln);

    String_d(&ln);

    ln = CGXDateTime_ToString(&p->m_StartTimeCurrent);

    Vector_push_back(values, &ln);

    String_d(&ln);

    Vector_push_back_Str_5(values, p->m_Period);

    Vector_push_back_Str_2(values, p->m_NumberOfPeriods);
}

//void CGXDLMSDemandRegister::GetAttributeIndexToRead(std::vector<int>& attributes)
void CGXDLMSDemandRegister_GetAttributeIndexToRead(CGXDLMSDemandRegister* p, Vector* attributes)
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //ScalerUnit
    if (!CGXDLMSDemandRegister_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //CurrentAvarageValue
    if (CGXDLMSDemandRegister_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //LastAvarageValue
    if (CGXDLMSDemandRegister_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //Status
    if (CGXDLMSDemandRegister_CanRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //CaptureTime
    if (CGXDLMSDemandRegister_CanRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //StartTimeCurrent
    if (CGXDLMSDemandRegister_CanRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    //Period
    if (CGXDLMSDemandRegister_CanRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //NumberOfPeriods
    if (CGXDLMSDemandRegister_CanRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }
}

// Returns amount of attributes.
int CGXDLMSDemandRegister_GetAttributeCount(CGXDLMSDemandRegister* p)
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSDemandRegister_GetMethodCount(CGXDLMSDemandRegister* p)
{
    return 2;
}

//int CGXDLMSDemandRegister::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
int CGXDLMSDemandRegister_Invoke(CGXDLMSDemandRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    if (e->m_Index == 1)
    {
        //CGXDLMSDemandRegister_Reset(p);
        return DLMS_ERROR_CODE_OK;
    }
    e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    return DLMS_ERROR_CODE_OK;
}

//int CGXDLMSDemandRegister::GetDataType(int index, DLMS_DATA_TYPE& type)
int CGXDLMSDemandRegister_GetDataType(CGXDLMSDemandRegister* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        *type = (p->m_CurrentAvarageValue).st.vt;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        *type = p->m_LastAvarageValue.st.vt;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = p->m_Status.st.vt;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        *type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 9)
    {
        *type = DLMS_DATA_TYPE_UINT16;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

//int CGXDLMSDemandRegister::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
int CGXDLMSDemandRegister_GetValue(CGXDLMSDemandRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        //e.SetValue(m_CurrentAvarageValue);
        CGXDLMSValueEventArg_SetValue(e, &p->m_CurrentAvarageValue);
        
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        //e.SetValue(m_LastAvarageValue);
        CGXDLMSValueEventArg_SetValue(e, &p->m_LastAvarageValue);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        //e.GetValue().Clear();
        //e.GetValue().vt = DLMS_DATA_TYPE_STRUCTURE;
        //e.GetValue().Arr.push_back(m_Scaler);
        //e.GetValue().Arr.push_back(m_Unit);
        
        CGXDLMSVariant* var = CGXDLMSValueEventArg_GetValue(e);
        CGXDLMSVariant_Clear(var);
        var->st.vt = DLMS_DATA_TYPE_STRUCTURE;

        CGXDLMSVariant t_var1;
        CGXDLMSVariant_8(&t_var1, p->m_Scaler);

        Vector_push_back(&(var->Arr), &t_var1);

        CGXDLMSVariant_d(&t_var1);

        CGXDLMSVariant t_var2;
        CGXDLMSVariant_19(&t_var2, p->m_Unit);

        Vector_push_back(&(var->Arr), &t_var2);

        CGXDLMSVariant_d(&t_var2);

        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        //e.SetValue(m_Status);
        CGXDLMSValueEventArg_SetValue(e, &p->m_Status);

        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        //e.SetValue(m_CaptureTime);
        CGXDLMSVariant tmp;
        CGXDLMSVariant_16(&tmp, &(p->m_CaptureTime));

        CGXDLMSValueEventArg_SetValue(e, &tmp);
        
        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 7)
    {
        //e.SetValue(m_StartTimeCurrent);
        CGXDLMSVariant tmp;
        CGXDLMSVariant_16(&tmp, &(p->m_StartTimeCurrent));
        
        CGXDLMSValueEventArg_SetValue(e, &tmp);
        
        CGXDLMSVariant_d(&tmp);

        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 8)
    {
        //e.SetValue(m_Period);
        CGXDLMSValueEventArg_SetValue_5(e, p->m_Period);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 9)
    {
        //e.SetValue(m_NumberOfPeriods);
        CGXDLMSValueEventArg_SetValue_3(e, p->m_NumberOfPeriods);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

//int CGXDLMSDemandRegister::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
int CGXDLMSDemandRegister_SetValue(CGXDLMSDemandRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
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
            //SetCurrentAvarageValue(CGXDLMSVariant(e.GetValue().ToDouble() * GetScaler()));
            CGXDLMSVariant tmp;
            CGXDLMSVariant_4(&tmp, CGXDLMSVariant_ToDouble(CGXDLMSValueEventArg_GetValue(e)) * CGXDLMSDemandRegister_GetScaler(p));

            CGXDLMSDemandRegister_SetCurrentAvarageValue(p, tmp);

            CGXDLMSVariant_d(&tmp);
        }
        else
        {
            //SetCurrentAvarageValue(e.GetValue());
            CGXDLMSDemandRegister_SetCurrentAvarageValue(p, *(CGXDLMSValueEventArg_GetValue(e)));
        }
    }
    else if (e_index == 3)
    {
        if (p->m_Scaler != 0)
        {
            //SetLastAvarageValue(CGXDLMSVariant(e.GetValue().ToDouble() * GetScaler()));
            CGXDLMSVariant tmp;
            CGXDLMSVariant_4(&tmp, CGXDLMSVariant_ToDouble(CGXDLMSValueEventArg_GetValue(e)) * CGXDLMSDemandRegister_GetScaler(p));

            CGXDLMSDemandRegister_SetLastAvarageValue(p, tmp);

            CGXDLMSVariant_d(&tmp);
        }
        else
        {
            //SetLastAvarageValue(e.GetValue());
            CGXDLMSDemandRegister_SetLastAvarageValue(p, *(CGXDLMSValueEventArg_GetValue(e)));
        }
    }
    else if (e_index == 4 && CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_STRUCTURE)
    {
        //m_Scaler = e.GetValue().Arr[0].ToInteger();
        //m_Unit = e.GetValue().Arr[1].ToInteger();
        p->m_Scaler = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));
        p->m_Unit = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1));
    }
    else if (e_index == 5)
    {
        //SetStatus(e.GetValue().lVal);
        CGXDLMSVariant tmp;
        CGXDLMSVariant_11(&tmp, CGXDLMSValueEventArg_GetValue(e)->st.un.lVal);

        CGXDLMSDemandRegister_SetStatus(p, tmp);

        CGXDLMSVariant_d(&tmp);
    }
    else if (e_index == 6)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_DATETIME, &tmp);
        p->m_CaptureTime = tmp.dateTime;

        CGXDLMSVariant_d(&tmp);
    }
    else if (e_index == 7)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_DATETIME, &tmp);
        p->m_StartTimeCurrent = tmp.dateTime;
    }
    else if (e_index == 8)
    {
        p->m_Period = CGXDLMSValueEventArg_GetValue(e)->st.un.ulVal;
    }
    else if (e_index == 9)
    {
        p->m_NumberOfPeriods = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSDemandRegister_d(CGXDLMSDemandRegister* p)
{
    CGXDLMSVariant_d(&p->m_CurrentAvarageValue);
    CGXDLMSVariant_d(&p->m_LastAvarageValue);
    CGXDLMSVariant_d(&p->m_Status);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
