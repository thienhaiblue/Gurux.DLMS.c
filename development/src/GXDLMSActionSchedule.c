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
#include "../include/GXDLMSActionSchedule.h"

#include "../include/GXDLMSObject.h"
#include "../include/Optimize.h"

/**
 Constructor.
*/

static void CGXDLMSActionSchedule__(CGXDLMSActionSchedule* p)
{
    p->GetAttributeCount = CGXDLMSActionSchedule_GetAttributeCount;
    p->GetMethodCount = CGXDLMSActionSchedule_GetMethodCount;
    p->GetValue = CGXDLMSActionSchedule_GetValue;
    p->SetValue = CGXDLMSActionSchedule_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSActionSchedule_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSActionSchedule_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSActionSchedule_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSActionSchedule_GetAttributeIndexToRead;

    String_(&p->m_ExecutedScriptLogicalName);
    Vector_(&p->m_ExecutionTime, sizeof(CGXDateTime), NULL, NULL); // std::vector<CGXDateTime> m_ExecutionTime;
}

void CGXDLMSActionSchedule_1(CGXDLMSActionSchedule* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSActionSchedule_3(p, t_Str, 0);

    String_d(&t_Str);
}

void CGXDLMSActionSchedule_2(CGXDLMSActionSchedule* p, String ln)
{
    CGXDLMSActionSchedule_3(p, ln, 0);
}

void CGXDLMSActionSchedule_3(CGXDLMSActionSchedule* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_ACTION_SCHEDULE, &ln, sn);

    CGXDLMSActionSchedule__(p);

    p->m_ExecutedScriptSelector = 0;
    p->m_Type = DLMS_SINGLE_ACTION_SCHEDULE_TYPE1;
}

String CGXDLMSActionSchedule_GetExecutedScriptLogicalName(CGXDLMSActionSchedule* p)
{
    String resultStr;
    String_2(&resultStr, &(p->m_ExecutedScriptLogicalName));

    return resultStr; // = copy cons + des
}
void CGXDLMSActionSchedule_SetExecutedScriptLogicalName(CGXDLMSActionSchedule* p, String value)
{
    String_copy_1(&(p->m_ExecutedScriptLogicalName), &value);
}

//std::vector<CGXDateTime> CGXDLMSActionSchedule::GetExecutionTime()
Vector* CGXDLMSActionSchedule_GetExecutionTime(CGXDLMSActionSchedule* p)
{
    return &(p->m_ExecutionTime);
}
// void CGXDLMSActionSchedule::SetExecutionTime(std::vector<CGXDateTime> value)
void CGXDLMSActionSchedule_SetExecutionTime(CGXDLMSActionSchedule* p, Vector value)
{
    Vector_copy_1(&(p->m_ExecutionTime), &value);
}

// Returns amount of attributes.
int CGXDLMSActionSchedule_GetAttributeCount(CGXDLMSActionSchedule* p)
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSActionSchedule_GetMethodCount(CGXDLMSActionSchedule* p)
{
    return 0;
}

//void CGXDLMSActionSchedule::GetValues(std::vector<std::string>& values)
void CGXDLMSActionSchedule_GetValues(CGXDLMSActionSchedule* p, Vector* values)
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String str;
    String_2(&str, &(p->m_ExecutedScriptLogicalName));

    String_append_1(&str, " ");

    String_append_var_int(&str, p->m_ExecutedScriptSelector);

    Vector_push_back(values, &str);

    String_d(&str);

    Vector_push_back_Str_2(values, p->m_Type);

    String sb;
    String_3(&sb, "[");

    bool empty = true;
    for (unsigned int it = Vector_begin(&(p->m_ExecutionTime)); it != Vector_end(&(p->m_ExecutionTime)); it++)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String out = CGXDateTime_ToString((CGXDateTime*) Vector_at(&p->m_ExecutionTime, it));
        String_append_3(&sb, &out);
        String_d(&out);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);
}

//void CGXDLMSActionSchedule::GetAttributeIndexToRead(std::vector<int>& attributes)
void CGXDLMSActionSchedule_GetAttributeIndexToRead(CGXDLMSActionSchedule* p, Vector* attributes)
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //ExecutedScriptLogicalName is static and read only once.
    if (!CGXDLMSActionSchedule_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //Type is static and read only once.
    if (!CGXDLMSActionSchedule_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //ExecutionTime is static and read only once.
    if (!CGXDLMSActionSchedule_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSActionSchedule_GetDataType(CGXDLMSActionSchedule* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;

}

// Returns value of given attribute.
int CGXDLMSActionSchedule_GetValue(CGXDLMSActionSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }

    CGXByteBuffer data;
    CGXByteBuffer_1(&data);

    if (e_index == 2)
    {
        e->m_ByteArray = true;
        int ret;
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 2);

        CGXDLMSVariant ln;
        CGXDLMSVariant_1(&ln);

        GXHelpers_SetLogicalName_1(String_c_str(&(p->m_ExecutedScriptLogicalName)), &ln);

        CGXDLMSVariant ss;
        CGXDLMSVariant_10(&ss, p->m_ExecutedScriptSelector);

        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &ss)) != 0)
        {
            CGXDLMSVariant_d(&ln);
            CGXDLMSVariant_d(&ss);
            CGXByteBuffer_d(&data);
            return ret;
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&ln);
        CGXDLMSVariant_d(&ss);
        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_Type);
        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        e->m_ByteArray = true;
        int ret;
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        
        Vector* t_Vec = CGXDLMSActionSchedule_GetExecutionTime(p);

        GXHelpers_SetObjectCount((unsigned long)Vector_size(t_Vec), &data);

        CGXDLMSVariant val1, val2;
        CGXDLMSVariant_1(&val1);
        CGXDLMSVariant_1(&val2);

        //for (std::vector<CGXDateTime>::iterator it = m_ExecutionTime.begin(); it != m_ExecutionTime.end(); ++it)
        for (unsigned int i = Vector_begin(&(p->m_ExecutionTime));
             i != Vector_end(&(p->m_ExecutionTime)); i++)
        {
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            //Count
            CGXByteBuffer_SetUInt8_1(&data, 2);

            CGXTime t;
            CGXTime_4(&t, (CGXDateTime*) Vector_at(&(p->m_ExecutionTime), i));

            CGXDate d;
            CGXDate_4(&d, (CGXDateTime*) Vector_at(&(p->m_ExecutionTime), i));

            CGXDLMSVariant_copy_20(&val1, &t);
            CGXDLMSVariant_copy_19(&val2, &d);

            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &val1)) != 0 ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &val2)) != 0)
            {
                CGXDLMSVariant_d(&val1);
                CGXDLMSVariant_d(&val2);
                CGXByteBuffer_d(&data);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&val1);
        CGXDLMSVariant_d(&val2);
        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }

    CGXByteBuffer_d(&data);
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSActionSchedule_SetValue(CGXDLMSActionSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr), 0))->st.un.byteArr,
                                   &(p->m_ExecutedScriptLogicalName));
        p->m_ExecutedScriptSelector = CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr), 1));
        
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 3)
    {
        p->m_Type = (DLMS_SINGLE_ACTION_SCHEDULE_TYPE)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 4)
    {
        int ret;
        Vector_clear(&(p->m_ExecutionTime));

        CGXDLMSVariant time, date;
        CGXDLMSVariant_1(&time);
        CGXDLMSVariant_1(&date);

        Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
        for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
        {
            if ((ret = CGXDLMSClient_ChangeType_2(Vector_at(temp, 0), DLMS_DATA_TYPE_TIME, &time)) != 0 ||
                (ret = CGXDLMSClient_ChangeType_2(Vector_at(temp, 1), DLMS_DATA_TYPE_DATE, &date)) != 0)
            {
                CGXDLMSVariant_d(&time);
                CGXDLMSVariant_d(&date);
                return ret;
            }

            time.dateTime.m_Skip = (DATETIME_SKIPS)(time.dateTime.m_Skip & ~(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK));
            date.dateTime.m_Skip = (DATETIME_SKIPS)(date.dateTime.m_Skip & ~(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS));
            struct tm val = time.dateTime.m_Value;
            struct tm val2 = date.dateTime.m_Value;
            val2.tm_hour = val.tm_hour;
            val2.tm_min = val.tm_min;
            val2.tm_sec = val.tm_sec;

            //m_ExecutionTime.push_back(tmp);
            CGXDateTime tmp;
            CGXDateTime_2(&tmp, &val2);

            tmp.m_Skip = (DATETIME_SKIPS)(time.dateTime.m_Skip | date.dateTime.m_Skip);
            Vector_push_back(&(p->m_ExecutionTime), &tmp);
        }

        CGXDLMSVariant_d(&time);
        CGXDLMSVariant_d(&date);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

void CGXDLMSActionSchedule_d(CGXDLMSActionSchedule* p)
{
    String_d(&p->m_ExecutedScriptLogicalName);
    Vector_d(&p->m_ExecutionTime);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
