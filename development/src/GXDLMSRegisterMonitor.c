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

#include "../include/GXDLMSRegisterMonitor.h"
#include "../include/GXDLMSClient.h"
#include "../include/Optimize.h"

static void CGXDLMSRegisterMonitor__(CGXDLMSRegisterMonitor* p)
{
    p->GetAttributeCount = CGXDLMSRegisterMonitor_GetAttributeCount;
    p->GetMethodCount = CGXDLMSRegisterMonitor_GetMethodCount;
    p->GetValue = CGXDLMSRegisterMonitor_GetValue;
    p->SetValue = CGXDLMSRegisterMonitor_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
    p->d = CGXDLMSRegisterMonitor_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSRegisterMonitor_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSRegisterMonitor_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSRegisterMonitor_GetAttributeIndexToRead;

    Vector_(&p->m_Actions, sizeof(CGXDLMSActionSet*), NULL, NULL); //std::vector<CGXDLMSActionSet*>
    CGXDLMSMonitoredValue_(&p->m_MonitoredValue);
    Vector_(&p->m_Thresholds, sizeof(CGXDLMSVariant), CGXDLMSVariant_v_c, CGXDLMSVariant_v_d); //std::vector<CGXDLMSVariant>
}
void CGXDLMSRegisterMonitor_1(CGXDLMSRegisterMonitor* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSRegisterMonitor_3(p, t_Str, 0);

    String_d(&t_Str);
}


void CGXDLMSRegisterMonitor_2(CGXDLMSRegisterMonitor* p, String ln)
{
	CGXDLMSRegisterMonitor_3(p, ln, 0);
}

void CGXDLMSRegisterMonitor_3(CGXDLMSRegisterMonitor* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_REGISTER_MONITOR, &ln, sn);

	CGXDLMSRegisterMonitor__(p);
}

void CGXDLMSRegisterMonitor_d(CGXDLMSRegisterMonitor* p)
{
	//for (std_vector<CGXDLMSActionSet*>_iterator it = p->m_Actions.begin(); it != p->m_Actions.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_Actions);
    		i != Vector_end(&p->m_Actions); ++i)
    {
        CGXDLMSActionSet** it = Vector_at(&(p->m_Actions), i);

        CGXDLMSActionSet_d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_Actions);
    Vector_clear(&p->m_Thresholds);

    CGXDLMSMonitoredValue_d(&p->m_MonitoredValue);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}

Vector* CGXDLMSRegisterMonitor_GetThresholds(CGXDLMSRegisterMonitor* p) //std::vector<CGXDLMSVariant>
{
    return &p->m_Thresholds;
}
void CGXDLMSRegisterMonitor_SetThresholds(CGXDLMSRegisterMonitor* p, Vector value) //std::vector<CGXDLMSVariant>
{
	Vector_copy_1(&p->m_Thresholds, &value);
}

CGXDLMSMonitoredValue* CGXDLMSRegisterMonitor_GetMonitoredValue(CGXDLMSRegisterMonitor* p)
{
    return &p->m_MonitoredValue;
}
void CGXDLMSRegisterMonitor_SetMonitoredValue(CGXDLMSRegisterMonitor* p, CGXDLMSMonitoredValue* value)
{
	// CGXDLMSRegisterMonitor_copy(&p->m_MonitoredValue, value);

	p->m_MonitoredValue.m_AttributeIndex = value->m_AttributeIndex;
	p->m_MonitoredValue.m_ObjectType = value->m_ObjectType;
	String_copy_1(&(p->m_MonitoredValue.m_LogicalName), &value->m_LogicalName);
}

Vector* CGXDLMSRegisterMonitor_GetActions(CGXDLMSRegisterMonitor* p) //std::vector<CGXDLMSActionSet*>&
{
    return &p->m_Actions;
}

// Returns amount of attributes.
int CGXDLMSRegisterMonitor_GetAttributeCount(CGXDLMSRegisterMonitor* p)
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSRegisterMonitor_GetMethodCount(CGXDLMSRegisterMonitor* p)
{
    return 0;
}

void CGXDLMSRegisterMonitor_GetValues(CGXDLMSRegisterMonitor* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std_vector<CGXDLMSVariant>_iterator it = p->m_Thresholds.begin(); it != p->m_Thresholds.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_Thresholds);
            i != Vector_end(&p->m_Thresholds); ++i)
    {
    	CGXDLMSVariant* it = Vector_at(&(p->m_Thresholds), i);

        if (!empty)
        {
        	String_append_1(&sb, ", ");
        }
        empty = false;

        String_append_var_str(&sb, it);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);

    String ln = CGXDLMSMonitoredValue_ToString(&p->m_MonitoredValue);

    Vector_push_back(values, &ln);

    String_d(&ln);

    //Clear str.
    String_append_1(&sb, "[");

    empty = true;
    //for (std_vector<CGXDLMSActionSet*>_iterator it = p->m_Actions.begin(); it != p->m_Actions.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_Actions);
            i != Vector_end(&p->m_Actions); ++i)
       {
    	CGXDLMSActionSet** it = Vector_at(&(p->m_Actions), i);

        if (!empty)
        {
        	String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSActionSet_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);
}

void CGXDLMSRegisterMonitor_GetAttributeIndexToRead(CGXDLMSRegisterMonitor* p, Vector* attributes) //std::vector<std::string>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Thresholds
    if (!CGXDLMSRegisterMonitor_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //MonitoredValue
    if (!CGXDLMSRegisterMonitor_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //Actions
    if (!CGXDLMSRegisterMonitor_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSRegisterMonitor_GetDataType(CGXDLMSRegisterMonitor* p, int index, DLMS_DATA_TYPE* type)
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
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Returns value of given attribute.
 */
int CGXDLMSRegisterMonitor_GetValue(CGXDLMSRegisterMonitor* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }

    CGXByteBuffer data;
    CGXByteBuffer_1(&data);

    CGXDLMSVariant ln;
    CGXDLMSVariant_1(&ln);

    if (e_index == 2)
    {
    	e->m_ByteArray = true;
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_Thresholds), &data);

        int ret;

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        // std_vector<CGXDLMSVariant>
        for (unsigned int i = Vector_begin(&p->m_Thresholds);
                i != Vector_end(&p->m_Thresholds); ++i)
        {
            CGXDLMSVariant* it = Vector_at(&p->m_Thresholds, i);

            CGXDLMSVariant_copy_1(&tmp, it);
            if ((ret = GXHelpers_SetData(&data, it->st.vt, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&data);
                CGXDLMSVariant_d(&ln);
                return ret;
            }
        }

        CGXDLMSVariant_d(&tmp);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&ln);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
    	e->m_ByteArray = true;
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 3);

        int ret;

        String str = CGXDLMSMonitoredValue_GetLogicalName(&p->m_MonitoredValue);

        GXHelpers_SetLogicalName_1(String_c_str(&str), &ln);

        String_d(&str);

        CGXDLMSVariant type;
        CGXDLMSVariant_10(&type, p->m_MonitoredValue.m_ObjectType);

        CGXDLMSVariant index;
        CGXDLMSVariant_10(&index, p->m_MonitoredValue.m_AttributeIndex);

        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &type)) != DLMS_ERROR_CODE_OK ||  //ClassID
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != DLMS_ERROR_CODE_OK || //LN
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_INT8, &index)) != DLMS_ERROR_CODE_OK)
        {
            CGXDLMSVariant_d(&type);
            CGXDLMSVariant_d(&index);
            CGXByteBuffer_d(&data);
            CGXDLMSVariant_d(&ln);
            return ret;
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&type);
        CGXDLMSVariant_d(&index);
        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&ln);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
    	e->m_ByteArray = true;
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        int ret;
        //Add count
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_Actions), &data);

        CGXDLMSVariant selector;
        CGXDLMSVariant_1(&selector);

        // std_vector<CGXDLMSActionSet*>
        for (unsigned int i = Vector_begin(&p->m_Actions); i != Vector_end(&p->m_Actions); ++i)
        {
            CGXDLMSActionSet** it = Vector_at(&p->m_Actions, i);

            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 2);
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 2);

            String str = CGXDLMSActionItem_GetLogicalName(&((*it)->m_ActionUp));

            GXHelpers_SetLogicalName_1(String_c_str(&str), &ln);

            String_d(&str);

            CGXDLMSVariant_copy_12(&selector, (*it)->m_ActionUp.m_ScriptSelector);

            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != DLMS_ERROR_CODE_OK ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &selector)) != DLMS_ERROR_CODE_OK)
            {
                CGXDLMSVariant_d(&selector);
                CGXByteBuffer_d(&data);
                CGXDLMSVariant_d(&ln);
                return ret;
            }
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 2);

            str = CGXDLMSActionItem_GetLogicalName(&((*it)->m_ActionDown));

            GXHelpers_SetLogicalName_1(String_c_str(&str), &ln);

            String_d(&str);

            CGXDLMSVariant_copy_12(&selector, (*it)->m_ActionDown.m_ScriptSelector);

            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != DLMS_ERROR_CODE_OK ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &selector)) != DLMS_ERROR_CODE_OK)
            {
                CGXDLMSVariant_d(&selector);
                CGXByteBuffer_d(&data);
                CGXDLMSVariant_d(&ln);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&selector);
        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&ln);
        return DLMS_ERROR_CODE_OK;
    }

    CGXByteBuffer_d(&data);
    CGXDLMSVariant_d(&ln);
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSRegisterMonitor_SetValue(CGXDLMSRegisterMonitor* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    if (e_index == 2)
    {
        CGXDLMSRegisterMonitor_SetThresholds(p, CGXDLMSValueEventArg_GetValue(e)->Arr);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
    	CGXDLMSRegisterMonitor_GetMonitoredValue(p)->m_ObjectType =
    	                   (DLMS_OBJECT_TYPE) CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));

        String ln;
        String_(&ln);

        GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->st.un.byteArr, &ln);

        CGXDLMSMonitoredValue_SetLogicalName(&p->m_MonitoredValue, ln);
        p->m_MonitoredValue.m_AttributeIndex =
                CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 2));

        String_d(&ln);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        // std_vector<CGXDLMSActionSet*>
        for (unsigned int i = Vector_begin(&p->m_Actions); i != Vector_end(&p->m_Actions); ++i)
        {
            CGXDLMSActionSet** it = Vector_at(&p->m_Actions, i);

            //delete *it;
            CGXDLMSActionSet_d(*it);
            DLMSPort_free(*it);
        }
        Vector_clear(&p->m_Actions);

        String ln;
        String_(&ln);

        // std_vector<CGXDLMSVariant>
        Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
        for (unsigned iaction_set = Vector_begin(vec);
                iaction_set != Vector_end(vec); ++iaction_set)
        {
            CGXDLMSVariant* action_set = Vector_at(vec, iaction_set);

            // CGXDLMSActionSet *set = new CGXDLMSActionSet();
            CGXDLMSActionSet* set = DLMSPort_malloc(sizeof(CGXDLMSActionSet));
            CGXDLMSActionSet_(set);

            CGXDLMSVariant* up = Vector_at(&action_set->Arr, 0);

            GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&up->Arr, 0))->st.un.byteArr, &ln);

            CGXDLMSActionItem_SetLogicalName(&set->m_ActionUp, ln);
            set->m_ActionUp.m_ScriptSelector = CGXDLMSVariant_ToInteger(Vector_at(&up->Arr, 1));

            CGXDLMSVariant* down = Vector_at(&action_set->Arr, 1);

            GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&down->Arr, 0))->st.un.byteArr, &ln);

            CGXDLMSActionItem_SetLogicalName(&set->m_ActionDown, ln);
            set->m_ActionDown.m_ScriptSelector = CGXDLMSVariant_ToInteger(Vector_at(&down->Arr, 1));

            Vector_push_back(&p->m_Actions, &set);
        }

        String_d(&ln);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}
