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

#include "../include/GXDLMSScriptTable.h"
#include "../include/GXHelpers.h"
#include "../include/Optimize.h"

static void CGXDLMSScriptTable__(CGXDLMSScriptTable* p)
{
    p->GetAttributeCount = CGXDLMSScriptTable_GetAttributeCount;
    p->GetMethodCount = CGXDLMSScriptTable_GetMethodCount;
    p->GetValue = CGXDLMSScriptTable_GetValue;
    p->SetValue = CGXDLMSScriptTable_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSScriptTable_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSScriptTable_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSScriptTable_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSScriptTable_GetAttributeIndexToRead;

    Vector_(&p->m_Scripts, sizeof(CGXDLMSScript*), NULL, NULL); //std::vector<CGXDLMSScript*>
}
//Constructor.
void CGXDLMSScriptTable_1(CGXDLMSScriptTable* p)
{
	String t_Str;
	String_3(&t_Str, "");

	CGXDLMSScriptTable_2(p, t_Str, 0);

	String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSScriptTable_2(CGXDLMSScriptTable* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_SCRIPT_TABLE, &ln, sn);

	CGXDLMSScriptTable__(p);
}

//LN Constructor.
void CGXDLMSScriptTable_3(CGXDLMSScriptTable* p, String ln)
{
	CGXDLMSScriptTable_2(p, ln, 0);
}

//Destructor.
void CGXDLMSScriptTable_d(CGXDLMSScriptTable* p)
{
	//for (std_vector<CGXDLMSScript*>_iterator it = p->m_Scripts.begin(); it != p->m_Scripts.end(); ++it)
	for (unsigned int i = Vector_begin(&p->m_Scripts); i != Vector_end(&p->m_Scripts); ++i)
    {
        CGXDLMSScript** it = Vector_at(&(p->m_Scripts), i);

        CGXDLMSScript_d(*it);
        DLMSPort_free(*it);
    }
	Vector_clear(&p->m_Scripts);

	CGXDLMSObject_d((CGXDLMSObject*) p);
}


Vector* CGXDLMSScriptTable_GetScripts(CGXDLMSScriptTable* p) //std::vector<CGXDLMSScript*>&
{
    return &p->m_Scripts;
}

// Returns amount of attributes.
int CGXDLMSScriptTable_GetAttributeCount(CGXDLMSScriptTable* p)
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSScriptTable_GetMethodCount(CGXDLMSScriptTable* p)
{
    return 1;
}

void CGXDLMSScriptTable_GetValues(CGXDLMSScriptTable* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std_vector<CGXDLMSScript*>_iterator it = p->m_Scripts.begin(); it != p->m_Scripts.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_Scripts); i != Vector_end(&p->m_Scripts); ++i)
    {
    	CGXDLMSScript** it = Vector_at(&(p->m_Scripts), i);
        if (!empty)
        {
        	String_append_1(&sb, ", ");
        }
        empty = false;

        String_append_int(&sb, (*it)->m_ID);

        //for (std_vector<CGXDLMSScriptAction*>_iterator a = (*it)->GetActions().begin(); a != (*it)->GetActions().end(); ++a)
        for (unsigned int i_2 = Vector_begin(CGXDLMSScript_GetActions(*it));
                    i_2 != Vector_end(CGXDLMSScript_GetActions(*it)); ++i_2)
        {
        	CGXDLMSScriptAction** it_2 = Vector_at(CGXDLMSScript_GetActions(*it), i_2);

        	String_append_1(&sb, " ");

            String str = CGXDLMSScriptAction_ToString(*it_2);

            String_append_3(&sb, &str);

            String_d(&str);
        }
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);
}

void CGXDLMSScriptTable_GetAttributeIndexToRead(CGXDLMSScriptTable* p, Vector* attributes) //std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Scripts
    if (CGXDLMSScriptTable_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSScriptTable_GetDataType(CGXDLMSScriptTable* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    //Scripts
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSScriptTable_GetValue(CGXDLMSScriptTable* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_Scripts), &data);
        int ret;

        CGXDLMSVariant id, type, oType, ln, index;
        CGXDLMSVariant_1(&id);
        CGXDLMSVariant_1(&type);
        CGXDLMSVariant_1(&oType);
        CGXDLMSVariant_1(&ln);
        CGXDLMSVariant_1(&index);

        //for (std_vector<CGXDLMSScript*>_iterator it = p->m_Scripts.begin(); it != p->m_Scripts.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_Scripts); i != Vector_end(&p->m_Scripts); ++i)
        {
            CGXDLMSScript** it = Vector_at(&p->m_Scripts, i);
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            //Count
            CGXByteBuffer_SetUInt8_1(&data, 2);
            //Script_identifier:
            CGXDLMSVariant_copy_12(&id, (*it)->m_ID);
            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &id)) != 0)
            {
                CGXByteBuffer_d(&data);
                CGXDLMSVariant_d(&id);
                CGXDLMSVariant_d(&type);
                CGXDLMSVariant_d(&oType);
                CGXDLMSVariant_d(&ln);
                CGXDLMSVariant_d(&index);
                return ret;
            }
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
            //Count
            GXHelpers_SetObjectCount((unsigned long)Vector_size(CGXDLMSScript_GetActions(*it)), &data);
            //for (std_vector<CGXDLMSScriptAction*>_iterator a = (*it)->GetActions().begin(); a != (*it)->GetActions().end(); ++a)
            for (unsigned int j = Vector_begin(CGXDLMSScript_GetActions(*it)); j != Vector_end(CGXDLMSScript_GetActions(*it)); ++j)
            {
                CGXDLMSScriptAction** a = Vector_at(CGXDLMSScript_GetActions(*it), j);

                String temp = CGXDLMSScriptAction_GetLogicalName(*a);

                GXHelpers_SetLogicalName_1(String_c_str(&temp), &ln);

                String_d(&temp);

                CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
                CGXByteBuffer_SetUInt8_1(&data, 5);
                // type = (*a)->GetType();
                // oType = (*a)->GetObjectType();
                // index = (*a)->GetIndex();
                // CGXDLMSVariant param = (*a)->GetParameter();

                CGXDLMSVariant_copy_12(&type, (*a)->m_Type);
                CGXDLMSVariant_copy_12(&oType, (*a)->m_ObjectType);
                CGXDLMSVariant_copy_12(&index, (*a)->m_Index);

                CGXDLMSVariant param = CGXDLMSScriptAction_GetParameter(*a);

                if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_ENUM, &type)) != 0 || //service_id
                    (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &oType)) != 0 || //class_id
                    (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != 0 || //logical_name
                    (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_INT8, &index)) != 0 || //index
                    (ret = GXHelpers_SetData(&data, param.st.vt, &param)) != 0) //parameter
                {
                    CGXDLMSVariant_d(&param);

                    CGXByteBuffer_d(&data);
                    CGXDLMSVariant_d(&id);
                    CGXDLMSVariant_d(&type);
                    CGXDLMSVariant_d(&oType);
                    CGXDLMSVariant_d(&ln);
                    CGXDLMSVariant_d(&index);
                    return ret;
                }

                CGXDLMSVariant_d(&param);
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&id);
        CGXDLMSVariant_d(&type);
        CGXDLMSVariant_d(&oType);
        CGXDLMSVariant_d(&ln);
        CGXDLMSVariant_d(&index);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSScriptTable_SetValue(CGXDLMSScriptTable* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        //for (std_vector<CGXDLMSScript*>_iterator it = p->m_Scripts.begin(); it != p->m_Scripts.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_Scripts); i != Vector_end(&p->m_Scripts); ++i)
        {
            CGXDLMSScript** it = Vector_at(&p->m_Scripts, i);

            CGXDLMSScript_d(*it);
            DLMSPort_free(*it);
        }
        Vector_clear(&p->m_Scripts);

        //Fix Xemex bug here.
        //Xemex meters do not return array as they shoul be according standard.
        if (Vector_size(&CGXDLMSValueEventArg_GetValue(e)->Arr) != 0)
        {
            if (((CGXDLMSVariant*)Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 0))->st.vt == DLMS_DATA_TYPE_STRUCTURE)
            {
                String ln;
                String_(&ln);

                Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
                //for (std_vector<CGXDLMSVariant>_iterator item = e.GetValue().Arr.begin(); item != e.GetValue().Arr.end(); ++item)
                for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
                {
                    CGXDLMSVariant* item = Vector_at(temp, i);

                    //CGXDLMSScript* script = new CGXDLMSScript();
                    CGXDLMSScript* script = DLMSPort_malloc(sizeof(CGXDLMSScript));
                    CGXDLMSScript_(script);

                    //script->SetID((*item).Arr[0].ToInteger());
                    script->m_ID = CGXDLMSVariant_ToInteger(Vector_at(&item->Arr, 0));
                    //p->m_Scripts.push_back(script);
                    Vector_push_back(&p->m_Scripts, &script);

                    Vector *temp_child = &(((CGXDLMSVariant*)Vector_at(&item->Arr, 1))->Arr);

                    //for (std_vector<CGXDLMSVariant>_iterator arr = (*item).Arr[1].Arr.begin(); arr != (*item).Arr[1].Arr.end(); ++arr)
                    for (int j = Vector_begin(temp_child); j != Vector_end(temp_child); ++j)
                    {
                        CGXDLMSVariant* arr = Vector_at(temp_child, j);

                        CGXDLMSScriptAction* it = DLMSPort_malloc(sizeof(CGXDLMSScriptAction));
                        CGXDLMSScriptAction_(it);

                        SCRIPT_ACTION_TYPE type = (SCRIPT_ACTION_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&arr->Arr, 0));
                        it->m_Type = type;
                        DLMS_OBJECT_TYPE ot = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&arr->Arr, 1));
                        it->m_ObjectType = ot;
                        String_clear(&ln);
                        GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&arr->Arr, 2))->st.un.byteArr, &ln);
                        CGXDLMSScriptAction_SetLogicalName(it, ln);
                        it->m_Index = CGXDLMSVariant_ToInteger(Vector_at(&arr->Arr, 3));
                        CGXDLMSScriptAction_SetParameter(it, *((CGXDLMSVariant*)Vector_at(&arr->Arr, 4)));

                        Vector_push_back(CGXDLMSScript_GetActions(script), &it);
                    }
                }

                String_d(&ln);
            }
            else //Read Xemex meter here.
            {
                CGXDLMSScript* script = DLMSPort_malloc(sizeof(CGXDLMSScript));
                CGXDLMSScript_(script);

                script->m_ID = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));
                Vector_push_back(&p->m_Scripts, &script);

                CGXDLMSScriptAction *it = DLMSPort_malloc(sizeof(CGXDLMSScriptAction));
                CGXDLMSScriptAction_(it);

                SCRIPT_ACTION_TYPE type = (SCRIPT_ACTION_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->Arr, 0));
                it->m_Type = type;
                DLMS_OBJECT_TYPE ot = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->Arr, 1));
                it->m_ObjectType = ot;

                String ln;
                String_(&ln);

                GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->Arr, 2))->st.un.byteArr, &ln);
                CGXDLMSScriptAction_SetLogicalName(it, ln);
                it->m_Index = CGXDLMSVariant_ToInteger(Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->Arr, 3));
                CGXDLMSScriptAction_SetParameter(it, *((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->Arr, 4)));

                Vector_push_back(CGXDLMSScript_GetActions(script), &it);

                String_d(&ln);
            }
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
