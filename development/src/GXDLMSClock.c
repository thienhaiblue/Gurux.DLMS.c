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
#include "../include/GXDLMSClock.h"
#include "../include/GXDLMSConverter.h"
#include "../include/Optimize.h"

static void CGXDLMSClock__(CGXDLMSClock* p)
{
    p->GetAttributeCount = CGXDLMSClock_GetAttributeCount;
    p->GetMethodCount = CGXDLMSClock_GetMethodCount;
    p->GetValue = CGXDLMSClock_GetValue;
    p->SetValue = CGXDLMSClock_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSClock_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSClock_GetDataType;
    p->GetUIDataType = CGXDLMSClock_GetUIDataType;
    p->GetValues = CGXDLMSClock_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSClock_GetAttributeIndexToRead;

    CGXDateTime_1(&p->m_End);
    CGXDateTime_1(&p->m_Begin);
    CGXDateTime_1(&p->m_Time);
}

//CGXDLMSClock::CGXDLMSClock() :
  //  CGXDLMSClock("0.0.1.0.0.255", 0)
void CGXDLMSClock_1(CGXDLMSClock *p)
{
    String t_Str;
    String_3(&t_Str, "0.0.1.0.0.255");

    CGXDLMSClock_3(p, t_Str, 0);

    String_d(&t_Str);
}

//CGXDLMSClock::CGXDLMSClock(std::string ln) :
  //  CGXDLMSClock(ln, 0)
void CGXDLMSClock_2(CGXDLMSClock *p, String ln)
{
    CGXDLMSClock_3(p, ln, 0);
}

//CGXDLMSClock::CGXDLMSClock(std::string ln, unsigned short sn) :
  //  CGXDLMSObject(DLMS_OBJECT_TYPE_CLOCK, ln, sn)
void CGXDLMSClock_3(CGXDLMSClock *p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_CLOCK, &ln, sn);

    CGXDLMSClock__(p);

    p->m_Deviation = p->m_ClockBase = DLMS_CLOCK_BASE_NONE;
    p->m_Enabled = false;
    p->m_TimeZone = 0;
    p->m_Status = DLMS_CLOCK_STATUS_OK;
}

void CGXDLMSClock_d(CGXDLMSClock *p)
{
    CGXDLMSObject_d((CGXDLMSObject*) p);
}

// Returns amount of attributes.
int CGXDLMSClock_GetAttributeCount(CGXDLMSClock *p)
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSClock_GetMethodCount(CGXDLMSClock *p)
{
    return 6;
}

//void CGXDLMSClock::GetValues(std::vector<std::string>& values)
void CGXDLMSClock_GetValues(CGXDLMSClock *p, Vector* values)
{
    Vector_clear(values);

    //GetLogicalName(tmp);
    //values.push_back(tmp);
    String tmp;
    String_(&tmp);

    CGXDLMSClock_GetLogicalName_2(p, &tmp);

    Vector_push_back(values, &tmp);

    //values.push_back(m_Time.ToString());
    String out = CGXDateTime_ToString(&p->m_Time);

    Vector_push_back(values, &out);

    String_d(&out);

    //values.push_back(CGXDLMSVariant(m_TimeZone).ToString());
    CGXDLMSVariant var1;
    CGXDLMSVariant_9(&var1, p->m_TimeZone);

    Vector_push_back_Str_1(values, &var1);

    CGXDLMSVariant_d(&var1);

    //tmp.append(CGXDLMSConverter::ToString(m_Status));
    //values.push_back(tmp);
    String_append_1(&tmp, CGXDLMSConverter_ToString_3(p->m_Status));
    Vector_push_back(values, &tmp);

    String_d(&tmp);

    //values.push_back(m_Begin.ToString());
    out = CGXDateTime_ToString(&(p->m_Begin));
    Vector_push_back(values, &out);

    String_d(&out);

    //values.push_back(m_End.ToString());
    out = CGXDateTime_ToString(&(p->m_End));
    Vector_push_back(values, &out);

    String_d(&out);

    //values.push_back(CGXDLMSVariant(m_Deviation).ToString());
    CGXDLMSVariant var2;
    CGXDLMSVariant_8(&var2, p->m_Deviation);

    Vector_push_back_Str_1(values, &var2);

    CGXDLMSVariant_d(&var2);

    //values.push_back(CGXDLMSVariant(m_Enabled).ToString());
    Vector_push_back_Str_7(values, p->m_Enabled);

    //values.push_back(CGXDLMSConverter::ToString(m_ClockBase));
    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_2(p->m_ClockBase));
}

//void CGXDLMSClock::GetAttributeIndexToRead(std::vector<int>& attributes)
void CGXDLMSClock_GetAttributeIndexToRead(CGXDLMSClock *p, Vector* attributes)
{
    int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Time
    if (CGXDLMSClock_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //TimeZone
    if (!CGXDLMSClock_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //Status
    if (CGXDLMSClock_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //Begin
    if (!CGXDLMSClock_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //End
    if (!CGXDLMSClock_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //Deviation
    if (!CGXDLMSClock_IsRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    //Enabled
    if (!CGXDLMSClock_IsRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //ClockBase
    if (!CGXDLMSClock_IsRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }
}

//int CGXDLMSClock::GetUIDataType(int index, DLMS_DATA_TYPE& type)
int CGXDLMSClock_GetUIDataType(CGXDLMSClock *p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 2 || index == 5 || index == 6)
    {
        *type = DLMS_DATA_TYPE_DATETIME;
    }
    else
    {
        return CGXDLMSObject_GetUIDataType((CGXDLMSObject*) p, index, type);
    }
    return DLMS_ERROR_CODE_OK;
}

//int CGXDLMSClock::GetDataType(int index, DLMS_DATA_TYPE& type)
int CGXDLMSClock_GetDataType(CGXDLMSClock *p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_INT16;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 5)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 6)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 7)
    {
        *type = DLMS_DATA_TYPE_INT8;
    }
    else if (index == 8)
    {
        *type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 9)
    {
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

/*
 * Returns value of given attribute.
 */
int CGXDLMSClock_GetValue(CGXDLMSClock *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_16(&tmp, &p->m_Time);

        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return 0;
    }
    if (e_index == 3)
    {
        //e.SetValue(GetTimeZone());
        CGXDLMSVariant tmp;
        CGXDLMSVariant_9(&tmp, p->m_TimeZone);
        
        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return 0;
    }
    if (e_index == 4)
    {
        //e.SetValue((unsigned char)GetStatus());
        CGXDLMSValueEventArg_SetValue_4(e, (unsigned char)(p->m_Status));
        return 0;
    }
    if (e_index == 5)
    {
        //e.SetValue(GetBegin());
        CGXDLMSVariant tmp;
        CGXDLMSVariant_16(&tmp, &p->m_Begin);
        
        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return 0;
    }
    if (e_index == 6)
    {
        //e.SetValue(GetEnd());
        CGXDLMSVariant tmp;
        CGXDLMSVariant_16(&tmp, &p->m_End);
        
        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return 0;
    }
    if (e_index == 7)
    {
        //e.SetValue(GetDeviation());
        CGXDLMSVariant tmp;
        CGXDLMSVariant_8(&tmp, p->m_Deviation);
        
        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return 0;
    }
    if (e_index == 8)
    {
        //e.SetValue(GetEnabled());
        CGXDLMSValueEventArg_SetValue_7(e, p->m_Enabled);
        return 0;
    }
    if (e_index == 9)
    {
        //e.SetValue(GetClockBase());
        CGXDLMSValueEventArg_SetValue_3(e, p->m_ClockBase);
        return 0;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSClock_SetValue(CGXDLMSClock *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_DATETIME, &tmp);
            //SetTime(tmp.dateTime);
            p->m_Time = tmp.dateTime;

            CGXDLMSVariant_d(&tmp);
        }
        else
        {
            //SetTime(e.GetValue().dateTime);
            p->m_Time = CGXDLMSValueEventArg_GetValue(e)->dateTime;
        }
    }
    else if (e_index == 3)
    {
        //SetTimeZone(e.GetValue().ToInteger());
        p->m_TimeZone = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 4)
    {
        //SetStatus((DLMS_CLOCK_STATUS)e.GetValue().ToInteger());
        p->m_Status = (DLMS_CLOCK_STATUS)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 5)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_DATETIME, &tmp);
            p->m_Begin = tmp.dateTime;

            CGXDLMSVariant_d(&tmp);
        }
        else
        {
            //SetBegin(e.GetValue().dateTime);
            p->m_Begin = CGXDLMSValueEventArg_GetValue(e)->dateTime;
        }
    }
    else if (e_index == 6)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_DATETIME, &tmp);
            p->m_End = tmp.dateTime;

            CGXDLMSVariant_d(&tmp);
        }
        else
        {
            //SetEnd(e.GetValue().dateTime);
            p->m_End = CGXDLMSValueEventArg_GetValue(e)->dateTime;
        }
    }
    else if (e_index == 7)
    {
        //SetDeviation(e.GetValue().ToInteger());
        p->m_Deviation = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 8)
    {
        //SetEnabled(e.GetValue().boolVal);
        p->m_Enabled = CGXDLMSValueEventArg_GetValue(e)->st.un.boolVal;
    }
    else if (e_index == 9)
    {
        //SetClockBase((DLMS_CLOCK_BASE)e.GetValue().ToInteger());
        p->m_ClockBase = (DLMS_CLOCK_BASE)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
