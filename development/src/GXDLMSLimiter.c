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

#include "../include/GXDLMSLimiter.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSActionSet.h"
#include "../include/Optimize.h"

static void CGXDLMSLimiter__(CGXDLMSLimiter* p)
{
    p->GetAttributeCount = CGXDLMSLimiter_GetAttributeCount;
    p->GetMethodCount = CGXDLMSLimiter_GetMethodCount;
    p->GetValue = CGXDLMSLimiter_GetValue;
    p->SetValue = CGXDLMSLimiter_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSLimiter_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSLimiter_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSLimiter_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSLimiter_GetAttributeIndexToRead;

    CGXDLMSVariant_1(&p->m_ThresholdActive);
    CGXDLMSVariant_1(&p->m_ThresholdNormal);
    CGXDLMSVariant_1(&p->m_ThresholdEmergency);
    CGXDLMSEmergencyProfile_(&p->m_EmergencyProfile);
    Vector_(&p->m_EmergencyProfileGroupIDs, sizeof(int), NULL, NULL); // std::vector<int>
    CGXDLMSActionItem_(&p->m_ActionOverThreshold);
    CGXDLMSActionItem_(&p->m_ActionUnderThreshold);
}

//Constructor.
//CGXDLMSLimiter::CGXDLMSLimiter() :
  //  CGXDLMSLimiter("", 0)
void CGXDLMSLimiter_1(CGXDLMSLimiter* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSLimiter_2(p, t_Str, 0);
    String_d(&t_Str);
}

//SN Constructor.
//CGXDLMSLimiter::CGXDLMSLimiter(std::string ln, unsigned short sn) :
  //  CGXDLMSObject(DLMS_OBJECT_TYPE_LIMITER, ln, sn)
void CGXDLMSLimiter_2(CGXDLMSLimiter* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_LIMITER, &ln, sn);

    CGXDLMSLimiter__(p);

    p->m_MonitoredValue = NULL;
    p->m_MinOverThresholdDuration = 0;
    p->m_MinUnderThresholdDuration = 0;
    p->m_EmergencyProfileActive = false;
    p->m_MonitoredAttributeIndex = 0;
}

//LN Constructor.
//CGXDLMSLimiter::CGXDLMSLimiter(std::string ln) : CGXDLMSLimiter(ln, 0)
void CGXDLMSLimiter_3(CGXDLMSLimiter* p, String ln)
{
    CGXDLMSLimiter_2(p, ln, 0);
}

/**
 Provides the active threshold value to which the attribute monitored is compared.
*/
CGXDLMSVariant* CGXDLMSLimiter_GetThresholdActive(CGXDLMSLimiter* p)
{
    return &p->m_ThresholdActive;
}
void CGXDLMSLimiter_SetThresholdActive(CGXDLMSLimiter* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&p->m_ThresholdActive, &value);
}

/**
 Provides the threshold value to which the attribute monitored
 is compared when in normal operation.
*/
CGXDLMSVariant* CGXDLMSLimiter_GetThresholdNormal(CGXDLMSLimiter* p)
{
    return &p->m_ThresholdNormal;
}
void CGXDLMSLimiter_SetThresholdNormal(CGXDLMSLimiter* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&p->m_ThresholdNormal, &value);
}

/**
 Provides the threshold value to which the attribute monitored
 is compared when an emergency profile is active.
*/
CGXDLMSVariant* CGXDLMSLimiter_GetThresholdEmergency(CGXDLMSLimiter* p)
{
    return &p->m_ThresholdEmergency;
}
void CGXDLMSLimiter_SetThresholdEmergency(CGXDLMSLimiter* p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&p->m_ThresholdEmergency, &value);
}

CGXDLMSEmergencyProfile* CGXDLMSLimiter_GetEmergencyProfile(CGXDLMSLimiter* p)
{
    return &p->m_EmergencyProfile;
}
void CGXDLMSLimiter_SetEmergencyProfile(CGXDLMSLimiter* p, CGXDLMSEmergencyProfile value)
{
    p->m_EmergencyProfile = value;
}

Vector* CGXDLMSLimiter_GetEmergencyProfileGroupIDs(CGXDLMSLimiter* p)
{
    return &p->m_EmergencyProfileGroupIDs;
}
void CGXDLMSLimiter_SetEmergencyProfileGroupIDs(CGXDLMSLimiter* p, Vector value)
{
    Vector_copy_1(&p->m_EmergencyProfileGroupIDs, &value);
}

/**
 Defines the scripts to be executed when the monitored value
 crosses the threshold for minimal duration time.
*/
CGXDLMSActionItem* CGXDLMSLimiter_GetActionOverThreshold(CGXDLMSLimiter* p)
{
    return &p->m_ActionOverThreshold;
}
void CGXDLMSLimiter_SetActionOverThreshold(CGXDLMSLimiter* p, CGXDLMSActionItem value)
{
    CGXDLMSActionItem_copy(&p->m_ActionOverThreshold, &value);
}

/**
 Defines the scripts to be executed when the monitored value
 crosses the threshold for minimal duration time.
*/
CGXDLMSActionItem* CGXDLMSLimiter_GetActionUnderThreshold(CGXDLMSLimiter* p)
{
    return &p->m_ActionUnderThreshold;
}
void CGXDLMSLimiter_SetActionUnderThreshold(CGXDLMSLimiter* p, CGXDLMSActionItem value)
{
    CGXDLMSActionItem_copy(&p->m_ActionUnderThreshold, &value);
}

// Returns amount of attributes.
int CGXDLMSLimiter_GetAttributeCount(CGXDLMSLimiter* p)
{
    return 11;
}

// Returns amount of methods.
int CGXDLMSLimiter_GetMethodCount(CGXDLMSLimiter* p)
{
    return 0;
}

void CGXDLMSLimiter_GetValues(CGXDLMSLimiter* p, Vector* values)
{
    // values.clear();
    // std::string ln;
    // GetLogicalName(ln);
    // values.push_back(ln);
    // if (m_MonitoredValue != NULL)
    // {
    //     values.push_back(m_MonitoredValue->GetName().ToString());
    // }
    // else
    // {
    //     values.push_back("");
    // }
    // values.push_back(m_ThresholdActive.ToString());
    // values.push_back(m_ThresholdNormal.ToString());
    // values.push_back(m_ThresholdEmergency.ToString());
    // values.push_back(CGXDLMSVariant(m_MinOverThresholdDuration).ToString());
    // values.push_back(CGXDLMSVariant(m_MinUnderThresholdDuration).ToString());
    // values.push_back(m_EmergencyProfile.ToString());
    // std::stringstream sb;
    // sb << '[';
    // bool empty = true;
    // for (std::vector<int>::iterator it = m_EmergencyProfileGroupIDs.begin(); it != m_EmergencyProfileGroupIDs.end(); ++it)
    // {
    //     if (!empty)
    //     {
    //         sb << ", ";
    //     }
    //     empty = false;
    //     std::string str = CGXDLMSVariant(*it).ToString();
    //     sb.write(str.c_str(), str.size());
    // }
    // sb << ']';
    // values.push_back(sb.str());
    // values.push_back(CGXDLMSVariant(m_EmergencyProfileActive).ToString());

    // sb.str(std::string());
    // sb << m_ActionOverThreshold.ToString().c_str();
    // sb << ", ";
    // sb << m_ActionUnderThreshold.ToString().c_str();
    // values.push_back(sb.str());

    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    if (p->m_MonitoredValue != NULL)
    {
        //values.push_back(m_MonitoredValue->GetName().ToString());

        CGXDLMSVariant tmp = CGXDLMSObject_GetName(p->m_MonitoredValue);

        Vector_push_back_Str_1(values, &tmp);

        CGXDLMSVariant_d(&tmp);
    }
    else
    {
        Vector_push_back_Str_3(values, "");
    }

    Vector_push_back_Str_1(values, &p->m_ThresholdActive);

    Vector_push_back_Str_1(values, &p->m_ThresholdNormal);

    Vector_push_back_Str_1(values, &p->m_ThresholdEmergency);

    Vector_push_back_Str_6(values, p->m_MinOverThresholdDuration);

    Vector_push_back_Str_6(values, p->m_MinUnderThresholdDuration);

    String ln = CGXDLMSEmergencyProfile_ToString(&p->m_EmergencyProfile);

    Vector_push_back(values, &ln);

    String_d(&ln);

    String sb;
    String_3(&sb, "[");

    bool empty = true;
    for (unsigned int i = Vector_begin(&(p->m_EmergencyProfileGroupIDs));
         i != Vector_end(&(p->m_EmergencyProfileGroupIDs)); i++)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        int* it = Vector_at(&p->m_EmergencyProfileGroupIDs, i);

        String_append_var_int(&sb, *it);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);

    Vector_push_back_Str_7(values, p->m_EmergencyProfileActive);

    // sb.str(std::string());
    // sb << m_ActionOverThreshold.ToString().c_str();
    // sb << ", ";
    // sb << m_ActionUnderThreshold.ToString().c_str();
    // values.push_back(sb.str());

    sb = CGXDLMSActionItem_ToString(&p->m_ActionOverThreshold);

    String_append_1(&sb, ", ");

    ln = CGXDLMSActionItem_ToString(&p->m_ActionUnderThreshold);

    String_append_3(&sb, &ln);

    Vector_push_back(values, &sb);

    String_d(&sb);
    String_d(&ln);
}

void CGXDLMSLimiter_GetAttributeIndexToRead(CGXDLMSLimiter* p, Vector* attributes)
{
    int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //MonitoredValue
    if (CGXDLMSLimiter_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }

    //ThresholdActive
    if (CGXDLMSLimiter_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }

    //ThresholdNormal
    if (CGXDLMSLimiter_CanRead(p, 4))
    {
       tmp = 4;
        Vector_push_back(attributes, &tmp);
    }

    //ThresholdEmergency
    if (CGXDLMSLimiter_CanRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }

    //MinOverThresholdDuration
    if (CGXDLMSLimiter_CanRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }

    //MinUnderThresholdDuration
    if (CGXDLMSLimiter_CanRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }

    //EmergencyProfile
    if (CGXDLMSLimiter_CanRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //EmergencyProfileGroup
    if (CGXDLMSLimiter_CanRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }

    //EmergencyProfileActive
    if (CGXDLMSLimiter_CanRead(p, 10))
    {
        tmp = 10;
        Vector_push_back(attributes, &tmp);
    }
    //Actions
    if (CGXDLMSLimiter_CanRead(p, 11))
    {
        tmp = 11;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSLimiter_GetDataType(CGXDLMSLimiter* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 3)
    {
        CGXDLMSObject_GetDataType((CGXDLMSObject*)p, index, type);
    }
    else if (index == 4)
    {
        CGXDLMSObject_GetDataType((CGXDLMSObject*)p, index, type);
    }
    else if (index == 5)
    {
        CGXDLMSObject_GetDataType((CGXDLMSObject*)p, index, type);
    }
    else if (index == 6)
    {
        *type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 7)
    {
        *type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 8)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 9)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 10)
    {
        *type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 11)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSLimiter_GetValue(CGXDLMSLimiter* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    else if (e_index == 2)
    {
        e->m_ByteArray = true;
        int ret;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 3);

        String ln;
        String_(&ln);

        CGXDLMSVariant type;
        CGXDLMSVariant_10(&type, 0);

        if (p->m_MonitoredValue != NULL)
        {
            CGXDLMSObject_GetLogicalName_2(p->m_MonitoredValue, &ln);
            CGXDLMSVariant_copy_12(&type, p->m_MonitoredValue->m_ObjectType);
        }

        CGXDLMSVariant index;
        CGXDLMSVariant_10(&index, p->m_MonitoredAttributeIndex);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        GXHelpers_SetLogicalName_1(String_c_str(&ln), &tmp);
        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_INT16, &type)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &index)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            CGXDLMSVariant_d(&index);
            CGXDLMSVariant_d(&type);
            String_d(&ln);
            CGXByteBuffer_d(&data);
            return ret;
        }
        //e.SetValue(data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&tmp);
        CGXDLMSVariant_d(&index);
        CGXDLMSVariant_d(&type);
        String_d(&ln);
        CGXByteBuffer_d(&data);
    }
    else if (e_index == 3)
    {
        //e.SetValue(m_ThresholdActive);        
        CGXDLMSValueEventArg_SetValue(e, &p->m_ThresholdActive);
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 4)
    {
        //e.SetValue(m_ThresholdNormal);
        CGXDLMSValueEventArg_SetValue(e, &p->m_ThresholdNormal);
    }
    else if (e_index == 5)
    {
        //e.SetValue(m_ThresholdEmergency);        
        CGXDLMSValueEventArg_SetValue(e, &p->m_ThresholdEmergency);
    }
    else if (e_index == 6)
    {
        //e.SetValue(m_MinOverThresholdDuration);
        CGXDLMSValueEventArg_SetValue_6(e, p->m_MinOverThresholdDuration);
    }
    else if (e_index == 7)
    {
        //e.SetValue(m_MinUnderThresholdDuration);
        CGXDLMSValueEventArg_SetValue_6(e, p->m_MinUnderThresholdDuration);
    }
    else if (e_index == 8)
    {
        e->m_ByteArray = true;
        int ret;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 3);

        //CGXDLMSVariant id = m_EmergencyProfile.GetID();
        //CGXDLMSVariant time = m_EmergencyProfile.GetActivationTime();
        //CGXDLMSVariant duration = m_EmergencyProfile.GetDuration();

        CGXDLMSVariant id, time, duration;
        CGXDLMSVariant_10(&id, p->m_EmergencyProfile.m_ID);
        CGXDLMSVariant_16(&time, &(p->m_EmergencyProfile.m_ActivationTime));
        CGXDLMSVariant_10(&duration, p->m_EmergencyProfile.m_Duration);

        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &id)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &time)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT32, &duration)) != 0)
        {
            CGXByteBuffer_d(&data);
            CGXDLMSVariant_d(&id);
            CGXDLMSVariant_d(&time);
            CGXDLMSVariant_d(&duration);
            return ret;
        }
        //e.SetValue(data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&id);
        CGXDLMSVariant_d(&time);
        CGXDLMSVariant_d(&duration);
    }
    else if (e_index == 9)
    {
        e->m_ByteArray = true;
        int ret;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);

        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_EmergencyProfileGroupIDs), &data);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        //for (std::vector<int>::iterator it = m_EmergencyProfileGroupIDs.begin(); it != m_EmergencyProfileGroupIDs.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_EmergencyProfileGroupIDs);
             i != Vector_end(&p->m_EmergencyProfileGroupIDs); ++i)
        {
            //tmp = *it;
            int* it = Vector_at(&p->m_EmergencyProfileGroupIDs, i);
            CGXDLMSVariant_copy_12(&tmp, *it);
            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&data);
                return ret;
            }
        }
        //e.SetValue(data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&tmp);

        CGXByteBuffer_d(&data);
    }
    else if (e_index == 10)
    {
        //e.SetValue(m_EmergencyProfileActive);
        CGXDLMSValueEventArg_SetValue_7(e, p->m_EmergencyProfileActive);
    }
    else if (e_index == 11)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 2);
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 2);

        int ret;

        CGXDLMSVariant ln;
        CGXDLMSVariant_1(&ln);

        {
        String str1 = CGXDLMSActionItem_GetLogicalName(&p->m_ActionOverThreshold);

        GXHelpers_SetLogicalName_1(String_c_str(&str1), &ln);

        String_d(&str1);
        }

        CGXDLMSVariant selector;
        CGXDLMSVariant_10(&selector, p->m_ActionOverThreshold.m_ScriptSelector);

        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &selector)) != 0)
        {
            CGXByteBuffer_d(&data);
            CGXDLMSVariant_d(&ln);
            CGXDLMSVariant_d(&selector);
            return ret;
        }
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 2);

        {
        String str2 = CGXDLMSActionItem_GetLogicalName(&p->m_ActionUnderThreshold);

        GXHelpers_SetLogicalName_1(String_c_str(&str2), &ln);

        String_d(&str2);
        }

        CGXDLMSVariant_copy_12(&selector, p->m_ActionUnderThreshold.m_ScriptSelector);
        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &selector)) != 0)
        {
            CGXByteBuffer_d(&data);
            CGXDLMSVariant_d(&ln);
            CGXDLMSVariant_d(&selector);
            return ret;
        }
        //e.SetValue(data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&ln);
        CGXDLMSVariant_d(&selector);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSLimiter_SetValue(CGXDLMSLimiter* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        //(CGXDLMSVariant*)Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 0);
        //DLMS_OBJECT_TYPE ot = (DLMS_OBJECT_TYPE)e.GetValue().Arr[0].ToInteger();
        DLMS_OBJECT_TYPE ot = (DLMS_OBJECT_TYPE) CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));

        String ln;
        String_(&ln);

        GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->st.un.byteArr, &ln);

        //m_MonitoredValue = settings.GetObjects().FindByLN(ot, ln);
        p->m_MonitoredValue = CGXDLMSObjectCollection_FindByLN_1(CGXDLMSSettings_GetObjects(settings), ot, &ln);
        p->m_MonitoredAttributeIndex = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 2));

        String_d(&ln);
    }
    else if (e_index == 3)
    {
        CGXDLMSVariant_copy_1(&p->m_ThresholdActive, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 4)
    {
        CGXDLMSVariant_copy_1(&p->m_ThresholdNormal, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 5)
    {
        CGXDLMSVariant_copy_1(&p->m_ThresholdEmergency, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 6)
    {
        p->m_MinOverThresholdDuration = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 7)
    {
        p->m_MinUnderThresholdDuration = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 8)
    {
        //m_EmergencyProfile.SetID(e.GetValue().Arr[0].ToInteger());
        p->m_EmergencyProfile.m_ID = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        CGXDLMSClient_ChangeType_2((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1), DLMS_DATA_TYPE_DATETIME, &tmp);
        //m_EmergencyProfile.SetActivationTime(tmp.dateTime);
        p->m_EmergencyProfile.m_ActivationTime = tmp.dateTime;
        //m_EmergencyProfile.SetDuration(e.GetValue().Arr[2].ToInteger());
        p->m_EmergencyProfile.m_Duration = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 2));

        CGXDLMSVariant_d(&tmp);
    }
    else if (e_index == 9)
    {
        //m_EmergencyProfileGroupIDs.clear();
        Vector_clear(&p->m_EmergencyProfileGroupIDs);

        Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
        //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
        {
            CGXDLMSVariant* it = Vector_at(temp, i);
            //m_EmergencyProfileGroupIDs.push_back((*it).ToInteger());

            int tmp = CGXDLMSVariant_ToInteger(it);

            Vector_push_back(&p->m_EmergencyProfileGroupIDs, &tmp);
        }
    }
    else if (e_index == 10)
    {
        p->m_EmergencyProfileActive = CGXDLMSValueEventArg_GetValue(e)->st.un.boolVal;
    }
    else if (e_index == 11)
    {
        String ln;
        String_(&ln);

        //GXHelpers_GetLogicalName(e.GetValue().Arr[0].Arr[0].byteArr, ln);
        GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0))->Arr, 0))->st.un.byteArr, &ln);

        //m_ActionOverThreshold.SetLogicalName(ln);
        CGXDLMSActionItem_SetLogicalName(&p->m_ActionOverThreshold, ln);

        //m_ActionOverThreshold.SetScriptSelector(e.GetValue().Arr[0].Arr[1].ToInteger());
        p->m_ActionOverThreshold.m_ScriptSelector = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0))->Arr, 1));


        //GXHelpers::GetLogicalName(e.GetValue().Arr[1].Arr[0].byteArr, ln);
        GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->Arr, 0))->st.un.byteArr, &ln);

        //m_ActionUnderThreshold.SetLogicalName(ln);
        CGXDLMSActionItem_SetLogicalName(&p->m_ActionUnderThreshold, ln);

        //m_ActionUnderThreshold.SetScriptSelector(e.GetValue().Arr[1].Arr[1].ToInteger());
        p->m_ActionUnderThreshold.m_ScriptSelector = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->Arr, 1));

        String_d(&ln);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSLimiter_d(CGXDLMSLimiter* p)
{
    CGXDLMSVariant_d(&p->m_ThresholdActive);
    CGXDLMSVariant_d(&p->m_ThresholdNormal);
    CGXDLMSVariant_d(&p->m_ThresholdEmergency);
    Vector_d(&p->m_EmergencyProfileGroupIDs);
    CGXDLMSActionItem_d(&p->m_ActionOverThreshold);
    CGXDLMSActionItem_d(&p->m_ActionUnderThreshold);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
