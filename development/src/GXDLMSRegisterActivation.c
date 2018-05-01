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
#include "../include/GXDLMSRegisterActivation.h"

#include "../include/Pair.h"
#include "../include/Optimize.h"

static void CGXDLMSRegisterActivation__(CGXDLMSRegisterActivation* p)
{
    p->GetAttributeCount = CGXDLMSRegisterActivation_GetAttributeCount;
    p->GetMethodCount = CGXDLMSRegisterActivation_GetMethodCount;
    p->GetValue = CGXDLMSRegisterActivation_GetValue;
    p->SetValue = CGXDLMSRegisterActivation_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSRegisterActivation_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSRegisterActivation_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSRegisterActivation_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSRegisterActivation_GetAttributeIndexToRead;

    Vector_(&p->m_RegisterAssignment, sizeof(CGXDLMSObjectDefinition),
            CGXDLMSObjectDefinition_v_c, CGXDLMSObjectDefinition_v_d); //std::vector<CGXDLMSObjectDefinition>
    Vector_(&p->m_MaskList, sizeof(Pair), Pair_v_c, Pair_v_d); //std::vector<std::pair<CGXByteBuffer, CGXByteBuffer > >
    CGXByteBuffer_1(&p->m_ActiveMask);
}
//Constructor.
void CGXDLMSRegisterActivation_1(CGXDLMSRegisterActivation *p)
{
	String t_Str;
	String_3(&t_Str, "");

	CGXDLMSRegisterActivation_2(p, t_Str, 0);

	String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSRegisterActivation_2(CGXDLMSRegisterActivation *p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_REGISTER_ACTIVATION, &ln, sn);

	CGXDLMSRegisterActivation__(p);
}

//LN Constructor.
void CGXDLMSRegisterActivation_3(CGXDLMSRegisterActivation *p, String ln)
{
	CGXDLMSRegisterActivation_2(p, ln, 0);
}

Vector* CGXDLMSRegisterActivation_GetRegisterAssignment(CGXDLMSRegisterActivation *p) //std_vector<CGXDLMSObjectDefinition>&
{
    return &(p->m_RegisterAssignment);
}

Vector* CGXDLMSRegisterActivation_GetMaskList(CGXDLMSRegisterActivation *p) //std_vector<std_pair<CGXByteBuffer, CGXByteBuffer > >&
{
    return &p->m_MaskList;
}

CGXByteBuffer* CGXDLMSRegisterActivation_GetActiveMask(CGXDLMSRegisterActivation *p)
{
    return &p->m_ActiveMask;
}

// Returns amount of attributes.
int CGXDLMSRegisterActivation_GetAttributeCount(CGXDLMSRegisterActivation *p)
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSRegisterActivation_GetMethodCount(CGXDLMSRegisterActivation *p)
{
    return 3;
}

void CGXDLMSRegisterActivation_GetValues(CGXDLMSRegisterActivation *p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std_vector<CGXDLMSObjectDefinition>_iterator it = p->m_RegisterAssignment.begin(); it != p->m_RegisterAssignment.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_RegisterAssignment);
         i != Vector_end(&p->m_RegisterAssignment); ++i)
    {
    	CGXDLMSObjectDefinition* it = Vector_at(&(p->m_RegisterAssignment), i);
        if (!empty)
        {
        	String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSObjectDefinition_ToString(it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);

    Vector_push_back_Str_3(values, "");

    /*TODO: Add MaskList.
    sb << '[';
    empty = true;
    for(std_vector<std_pair<CGXByteBuffer, CGXByteBuffer > >_iterator it = p->m_MaskList.begin(); it != p->m_MaskList.end(); ++it)
    {
        if (!empty)
        {
            sb << ", ";
        }
        empty = false;
        sb << it->ToString();
    }
    sb << ']';
    Vector_push_back(values, sb.str());
    */
    if (p->m_ActiveMask.m_Size != 0)
    {
        Vector_push_back_Str_4(values, &(p->m_ActiveMask));
    }
    else
    {
        Vector_push_back_Str_3(values, "");
    }
}

void CGXDLMSRegisterActivation_GetAttributeIndexToRead(CGXDLMSRegisterActivation *p, Vector* attributes) //std::vector<int>&
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //RegisterAssignment
    if (!CGXDLMSRegisterActivation_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //MaskList
    if (!CGXDLMSRegisterActivation_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //ActiveMask
    if (!CGXDLMSRegisterActivation_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSRegisterActivation_GetDataType(CGXDLMSRegisterActivation *p, int index, DLMS_DATA_TYPE* type)
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
        return CGXDLMSObject_GetDataType((CGXDLMSObject*) p, index, type);
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSRegisterActivation_GetValue(CGXDLMSRegisterActivation *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
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
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_RegisterAssignment), &data);

        CGXDLMSVariant id, ln;
        CGXDLMSVariant_1(&id);
        CGXDLMSVariant_1(&ln);

        //for (std_vector<CGXDLMSObjectDefinition>_iterator it = p->m_RegisterAssignment.begin(); it != p->m_RegisterAssignment.end(); ++it)
        for (unsigned int i = Vector_begin(&(p->m_RegisterAssignment));
             i != Vector_end(&(p->m_RegisterAssignment)); ++i)
        {
            CGXDLMSObjectDefinition* it = Vector_at(&(p->m_RegisterAssignment), i);

            String tmp = CGXDLMSObjectDefinition_GetLogicalName(it);

            GXHelpers_SetLogicalName_1(String_c_str(&tmp), &ln);

            String_d(&tmp);

            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 2);
            CGXDLMSVariant_copy_12(&id, it->m_ClassId);
            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &id)) != 0 ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != 0)
            {
                CGXDLMSVariant_d(&id);
                CGXDLMSVariant_d(&ln);
                CGXByteBuffer_d(&data);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&id);
        CGXDLMSVariant_d(&ln);
        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        int ret;
        e->m_ByteArray = true;
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_MaskList), &data);
        //for (std_vector<std_pair<CGXByteBuffer, CGXByteBuffer > >_iterator it = p->m_MaskList.begin(); it != p->m_MaskList.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_MaskList);
             i != Vector_end(&p->m_MaskList); ++i)
        {
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 2);

            Pair* it = Vector_at(&p->m_MaskList, i);

            CGXDLMSVariant_copy_4(&tmp, it->first);
            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&data);
                return ret;
            }
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
            GXHelpers_SetObjectCount((unsigned long)((CGXByteBuffer*)(it->second))->m_Size, &data);
            for (int pos = 0; pos != (int)((CGXByteBuffer*)(it->second))->m_Size; ++pos)
            {
                CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_UINT8);
                CGXByteBuffer_SetUInt8_1(&data, ((CGXByteBuffer*)(it->second))->m_Data[pos]);
            }
        }

        CGXDLMSVariant_d(&tmp);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        CGXDLMSVariant_Add_1(CGXDLMSValueEventArg_GetValue(e),
                             p->m_ActiveMask.m_Data,
                             p->m_ActiveMask.m_Size);
        CGXDLMSValueEventArg_GetValue(e)->st.vt = DLMS_DATA_TYPE_OCTET_STRING;

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }

    CGXByteBuffer_d(&data);
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSRegisterActivation_SetValue(CGXDLMSRegisterActivation *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        Vector_clear(&p->m_RegisterAssignment);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            // std_vector<CGXDLMSVariant>
            Vector* temp = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
            for (unsigned int i = Vector_begin(temp); i != Vector_end(temp); ++i)
            {
                CGXDLMSObjectDefinition item;
                CGXDLMSObjectDefinition_1(&item);

                CGXDLMSVariant* it = Vector_at(temp, i);
                //Vector_at(&it->Arr, 0)
                item.m_ClassId = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 0));

                String ln;
                String_(&ln);

                GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&it->Arr, 1))->st.un.byteArr, &ln);
                CGXDLMSObjectDefinition_SetLogicalName(&item, ln);
                Vector_push_back(&p->m_RegisterAssignment, &item);

                String_d(&ln);
                CGXDLMSObjectDefinition_d(&item);
            }
        }
    }
    else if (e_index == 3)
    {
        Vector_clear(&p->m_MaskList);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            // std_vector<CGXDLMSVariant>
            for (unsigned int i = Vector_begin(&CGXDLMSValueEventArg_GetValue(e)->Arr);
                 i != Vector_end(&CGXDLMSValueEventArg_GetValue(e)->Arr); ++i)
            {
                CGXByteBuffer key, arr;
                CGXByteBuffer_1(&key);
                CGXByteBuffer_1(&arr);

                CGXDLMSVariant* it = Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, i);

                CGXByteBuffer_Set_1(&key, ((CGXDLMSVariant*)Vector_at(&it->Arr, 0))->st.un.byteArr,
                                    ((CGXDLMSVariant*)Vector_at(&it->Arr, 0))->size);

                // std_vector<CGXDLMSVariant>
                Vector* temp = &(((CGXDLMSVariant*)Vector_at(&it->Arr, 1))->Arr);
                for (unsigned int vv = Vector_begin(temp); vv != Vector_end(temp); ++vv)
                {
                    CGXDLMSVariant* v = Vector_at(temp, vv);

                    CGXByteBuffer_SetUInt8_1(&arr, CGXDLMSVariant_ToInteger(v));
                }

                Pair t_p; // std::vector<std::pair<CGXByteBuffer, CGXByteBuffer > >
                Pair_(&t_p, sizeof(CGXByteBuffer), sizeof(CGXByteBuffer),
                      CGXByteBuffer_v_c, CGXByteBuffer_v_d, CGXByteBuffer_v_c, CGXByteBuffer_v_d,
                      &key, &arr);

                Vector_push_back(&p->m_MaskList, &t_p);

                Pair_d(&t_p);

                CGXByteBuffer_d(&key);
                CGXByteBuffer_d(&arr);
            }
        }
    }
    else if (e_index == 4)
    {
        CGXByteBuffer_Set_1(&p->m_ActiveMask, CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr, CGXDLMSValueEventArg_GetValue(e)->size);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSRegisterActivation_d(CGXDLMSRegisterActivation *p)
{
    Vector_d(&p->m_RegisterAssignment);
    Vector_d(&p->m_MaskList);
    CGXByteBuffer_d(&p->m_ActiveMask);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
