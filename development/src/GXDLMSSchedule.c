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
#include "../include/GXDLMSSchedule.h"
#include "../include/Optimize.h"

static void CGXDLMSSchedule__(CGXDLMSSchedule* p)
{
    p->GetAttributeCount = CGXDLMSSchedule_GetAttributeCount;
    p->GetMethodCount = CGXDLMSSchedule_GetMethodCount;
    p->GetValue = CGXDLMSSchedule_GetValue;
    p->SetValue = CGXDLMSSchedule_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSSchedule_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSSchedule_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSSchedule_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSSchedule_GetAttributeIndexToRead;

    Vector_(&p->m_Entries, sizeof(CGXDLMSScheduleEntry),
    		CGXDLMSScheduleEntry_v_c, CGXDLMSScheduleEntry_v_d); //std::vector<CGXDLMSScheduleEntry>
}
//Constructor.
void CGXDLMSSchedule_1(CGXDLMSSchedule* p)
{
    String t_Str;
    String_3(&t_Str, "");

	CGXDLMSSchedule_2(p, t_Str, 0);

	String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSSchedule_2(CGXDLMSSchedule* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_SCHEDULE, &ln, sn);

	CGXDLMSSchedule__(p);
}

//LN Constructor.
void CGXDLMSSchedule_3(CGXDLMSSchedule* p, String ln)
{
	CGXDLMSSchedule_2(p, ln, 0);
}

// Get value of COSEM Data object.
Vector* CGXDLMSSchedule_GetEntries(CGXDLMSSchedule* p) //std::vector<CGXDLMSScheduleEntry>&
{
    return &p->m_Entries;
}

// Set value of COSEM Data object.
void CGXDLMSSchedule_SetEntries(CGXDLMSSchedule* p, Vector* value) //std::vector<CGXDLMSScheduleEntry>&
{
    Vector_copy_1(&p->m_Entries, value);
}

// Returns amount of attributes.
int CGXDLMSSchedule_GetAttributeCount(CGXDLMSSchedule* p)
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSSchedule_GetMethodCount(CGXDLMSSchedule* p)
{
    return 3;
}

void CGXDLMSSchedule_GetValues(CGXDLMSSchedule* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_3(values, "");

    //TODO: values.push_back(p->m_Entries.ToString());
}

void CGXDLMSSchedule_GetAttributeIndexToRead(CGXDLMSSchedule* p, Vector* attributes) //std::vector<int>&
{
    int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Entries
    if (CGXDLMSSchedule_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSSchedule_GetDataType(CGXDLMSSchedule* p, int index, DLMS_DATA_TYPE* type)
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
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSSchedule_GetValue(CGXDLMSSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    if (e->m_Index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    //TODO:
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSSchedule_SetValue(CGXDLMSSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        Vector_clear(&p->m_Entries);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);

        //for (std_vector<CGXDLMSVariant >_iterator it = CGXDLMSValueEventArg_GetValue(e).Arr.begin(); it != CGXDLMSValueEventArg_GetValue(e).Arr.end(); ++it)
        for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
        {
            CGXDLMSVariant* it = Vector_at(temp, i);

            CGXDLMSScheduleEntry item;
            CGXDLMSScheduleEntry_(&item);

            item.m_Index = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 0));
            item.m_Enable = ((CGXDLMSVariant*)Vector_at(&it->Arr, 1))->st.un.boolVal;
            CGXDLMSClient_ChangeType_2((CGXDLMSVariant*)Vector_at(&it->Arr, 2), DLMS_DATA_TYPE_OCTET_STRING, &tmp);
            CGXDLMSScheduleEntry_SetLogicalName(&item, CGXDLMSVariant_ToString(&tmp));
            item.m_ScriptSelector = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 3));
            CGXDLMSClient_ChangeType_2(Vector_at(&it->Arr, 4), DLMS_DATA_TYPE_DATETIME, &tmp);
            item.m_SwitchTime = tmp.dateTime;
            item.m_ValidityWindow = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 5));
            CGXDLMSScheduleEntry_SetExecWeekdays(&item, ((CGXDLMSVariant*)Vector_at(&it->Arr, 6))->strVal);
            CGXDLMSScheduleEntry_SetExecSpecDays(&item, ((CGXDLMSVariant*)Vector_at(&it->Arr, 7))->strVal);
            CGXDLMSClient_ChangeType_2(Vector_at(&it->Arr, 8), DLMS_DATA_TYPE_DATETIME, &tmp);
            item.m_BeginDate = tmp.dateTime;
            CGXDLMSClient_ChangeType_2(Vector_at(&it->Arr, 9), DLMS_DATA_TYPE_DATETIME, &tmp);
            item.m_EndDate = tmp.dateTime;

            Vector_push_back(&p->m_Entries, &item);

            CGXDLMSScheduleEntry_d(&item);
        }

        CGXDLMSVariant_d(&tmp);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSSchedule_d(CGXDLMSSchedule* p)
{
	Vector_d(&p->m_Entries);

	CGXDLMSObject_d((CGXDLMSObject*) p);
}
