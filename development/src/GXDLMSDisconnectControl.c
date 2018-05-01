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
#include "../include/GXDLMSDisconnectControl.h"
#include "../include/GXDLMSConverter.h"
#include "../include/Optimize.h"

static void CGXDLMSDisconnectControl__(CGXDLMSDisconnectControl *p)
{
    p->GetAttributeCount = CGXDLMSDisconnectControl_GetAttributeCount;
    p->GetMethodCount = CGXDLMSDisconnectControl_GetMethodCount;
    p->GetValue = CGXDLMSDisconnectControl_GetValue;
    p->SetValue = CGXDLMSDisconnectControl_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSDisconnectControl_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSDisconnectControl_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSDisconnectControl_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSDisconnectControl_GetAttributeIndexToRead;
}

//Constructor.
//CGXDLMSDisconnectControl::CGXDLMSDisconnectControl() :
  //  CGXDLMSDisconnectControl("", 0)
void CGXDLMSDisconnectControl_1(CGXDLMSDisconnectControl *p)
{
    String t_Str;
    String_3(&t_Str, "");
    CGXDLMSDisconnectControl_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
//CGXDLMSDisconnectControl::CGXDLMSDisconnectControl(std::string ln, unsigned short sn) :
  //  CGXDLMSObject(DLMS_OBJECT_TYPE_DISCONNECT_CONTROL, ln, sn)
void CGXDLMSDisconnectControl_2(CGXDLMSDisconnectControl *p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_DISCONNECT_CONTROL, &ln, sn);

    CGXDLMSDisconnectControl__(p);
}

//LN Constructor.
//CGXDLMSDisconnectControl::CGXDLMSDisconnectControl(std::string ln) :
  //  CGXDLMSDisconnectControl(ln, 0)
void CGXDLMSDisconnectControl_3(CGXDLMSDisconnectControl *p, String ln)
{
    CGXDLMSDisconnectControl_2(p, ln, 0);
}

// Returns amount of attributes.
int CGXDLMSDisconnectControl_GetAttributeCount(CGXDLMSDisconnectControl *p)
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSDisconnectControl_GetMethodCount(CGXDLMSDisconnectControl *p)
{
    return 2;
}

//void CGXDLMSDisconnectControl::GetValues(std::vector<std::string>& values)
void CGXDLMSDisconnectControl_GetValues(CGXDLMSDisconnectControl *p, Vector* values)
{
    //values.clear();
    //std::string ln;
    //GetLogicalName(ln);
    //values.push_back(ln);
    //values.push_back(CGXDLMSVariant(m_OutputState).ToString());
    //values.push_back(CGXDLMSConverter::ToString(m_ControlState));
    //values.push_back(CGXDLMSConverter::ToString(m_ControlMode));

    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_7(values, p->m_OutputState);

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_5(p->m_ControlState));

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_6(p->m_ControlMode));
}

//void CGXDLMSDisconnectControl::GetAttributeIndexToRead(std::vector<int>& attributes)
void CGXDLMSDisconnectControl_GetAttributeIndexToRead(CGXDLMSDisconnectControl *p, Vector* attributes)
{
    int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //OutputState
    if (CGXDLMSDisconnectControl_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //ControlState
    if (CGXDLMSDisconnectControl_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //ControlMode
    if (CGXDLMSDisconnectControl_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSDisconnectControl_GetDataType(CGXDLMSDisconnectControl *p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSDisconnectControl_GetValue(CGXDLMSDisconnectControl *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        CGXDLMSValueEventArg_SetValue_7(e, p->m_OutputState);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_ControlState);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_ControlMode);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSDisconnectControl_SetValue(CGXDLMSDisconnectControl *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        p->m_OutputState = CGXDLMSValueEventArg_GetValue(e)->st.un.boolVal;
    }
    else if (e_index == 3)
    {
        p->m_ControlState = (DLMS_CONTROL_STATE)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
        
    }
    else if (e_index == 4)
    {
        p->m_ControlMode = (DLMS_CONTROL_MODE)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSDisconnectControl_d(CGXDLMSDisconnectControl *p)
{
    CGXDLMSObject_d((CGXDLMSObject*) p);
}

