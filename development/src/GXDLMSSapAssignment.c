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
#include "../include/GXDLMSSapAssignment.h"
#include "../include/Optimize.h"

static void CGXDLMSSapAssignment__(CGXDLMSSapAssignment* p)
{
    p->GetAttributeCount = CGXDLMSSapAssignment_GetAttributeCount;
    p->GetMethodCount = CGXDLMSSapAssignment_GetMethodCount;
    p->GetValue = CGXDLMSSapAssignment_GetValue;
    p->SetValue = CGXDLMSSapAssignment_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSSapAssignment_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSSapAssignment_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSSapAssignment_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSSapAssignment_GetAttributeIndexToRead;

    Map_(&p->m_SapAssignmentList, sizeof(int), sizeof(String),
         NULL, NULL, String_v_c, String_v_d); // std::map<int, std::string >
}

//CGXDLMSSapAssignment::CGXDLMSSapAssignment() :
//    CGXDLMSSapAssignment("0.0.41.0.0.255", 0)
void CGXDLMSSapAssignment_1(CGXDLMSSapAssignment* p)
{
    String t_Str;
    String_3(&t_Str, "0.0.41.0.0.255");

    CGXDLMSSapAssignment_3(p, t_Str, 0);

    String_d(&t_Str);
}


//CGXDLMSSapAssignment::CGXDLMSSapAssignment(std::string ln) :
//    CGXDLMSSapAssignment(ln, 0)
void CGXDLMSSapAssignment_2(CGXDLMSSapAssignment* p, String ln)
{
    CGXDLMSSapAssignment_3(p, ln, 0);
}


//CGXDLMSSapAssignment::CGXDLMSSapAssignment(std::string ln, unsigned short sn) :
//    CGXDLMSObject(DLMS_OBJECT_TYPE_SAP_ASSIGNMENT, ln, sn)
void CGXDLMSSapAssignment_3(CGXDLMSSapAssignment* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_SAP_ASSIGNMENT, &ln, sn);

    CGXDLMSSapAssignment__(p);
}

Map* CGXDLMSSapAssignment_GetSapAssignmentList(CGXDLMSSapAssignment* p) //std::map<int, std::string >&
{
    return &p->m_SapAssignmentList;
}

void CGXDLMSSapAssignment_SetSapAssignmentList(CGXDLMSSapAssignment* p, Map* value) //std::map<int, std::string >&
{
    Map_copy_1(&p->m_SapAssignmentList, value);
}

// Returns amount of attributes.
int CGXDLMSSapAssignment_GetAttributeCount(CGXDLMSSapAssignment* p)
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSSapAssignment_GetMethodCount(CGXDLMSSapAssignment* p)
{
    return 1;
}

void CGXDLMSSapAssignment_GetValues(CGXDLMSSapAssignment* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;

    // std::map<int, std::string >::iterator
    for (unsigned int it = Map_begin(&p->m_SapAssignmentList); it != Map_end(&p->m_SapAssignmentList); ++it)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        int it_first = *((int*) Map_first_at(&p->m_SapAssignmentList, it));

        String_append_var_int(&sb, it_first);

        String_append_1(&sb, ", ");

        String_append_3(&sb, Map_item_at(&p->m_SapAssignmentList, it));
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);
}

void CGXDLMSSapAssignment_GetAttributeIndexToRead(CGXDLMSSapAssignment* p, Vector* attributes) //std::vector<int>&
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //SapAssignmentList
    if (!CGXDLMSSapAssignment_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSSapAssignment_GetDataType(CGXDLMSSapAssignment* p, int index, DLMS_DATA_TYPE* type)
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
int CGXDLMSSapAssignment_GetValue(CGXDLMSSapAssignment* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        e->m_ByteArray = true;
        unsigned long cnt = (unsigned long)Map_size(&p->m_SapAssignmentList);

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount(cnt, &data);
        int ret;
        if (cnt != 0)
        {
            CGXDLMSVariant f, s;
            CGXDLMSVariant_1(&f);
            CGXDLMSVariant_1(&s);

            CGXByteBuffer bb;
            CGXByteBuffer_1(&bb);

            // std::map<int, std::string >
            for (unsigned int it = Map_begin(&p->m_SapAssignmentList);
                it != Map_end(&p->m_SapAssignmentList); ++it)
            {
                CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
                CGXByteBuffer_SetUInt8_1(&data, 2); //Count

                CGXDLMSVariant_copy_12(&f, *((int*) Map_first_at(&p->m_SapAssignmentList, it)));

                CGXByteBuffer_Clear(&bb);
                CGXByteBuffer_AddString_1(&bb, (String*) Map_second_at(&p->m_SapAssignmentList, it));

                CGXDLMSVariant_copy_4(&s, &bb);

                if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &f)) != 0 ||
                    (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &s)) != 0)
                {
                    CGXDLMSVariant_d(&f);
                    CGXDLMSVariant_d(&s);
                    CGXByteBuffer_d(&bb);

                    CGXByteBuffer_d(&data);
                    return ret;
                }
            }

            CGXDLMSVariant_d(&f);
            CGXDLMSVariant_d(&s);
            CGXByteBuffer_d(&bb);
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSSapAssignment_SetValue(CGXDLMSSapAssignment* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    if (e_index == 2)
    {
        Map_clear(&p->m_SapAssignmentList);

        // std::vector<CGXDLMSVariant>
        for (unsigned i = Vector_begin(&CGXDLMSValueEventArg_GetValue(e)->Arr);
            i != Vector_end(&CGXDLMSValueEventArg_GetValue(e)->Arr); ++i)
        {
            String str;

            CGXDLMSVariant* item = Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, i);

            if (((CGXDLMSVariant*) Vector_at(&item->Arr, 1))->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                String_(&str);

                CGXDLMSVariant tmp;
                CGXDLMSVariant_1(&tmp);

                CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&item->Arr, 1), DLMS_DATA_TYPE_STRING, &tmp);

                String_copy_1(&str, &tmp.strVal);

                CGXDLMSVariant_d(&tmp);
            }
            else
            {
                str = CGXDLMSVariant_ToString(Vector_at(&item->Arr, 1));
            }

            int key = CGXDLMSVariant_ToInteger(Vector_at(&item->Arr, 0));

            int index = Map_find(&p->m_SapAssignmentList, &key);

            if (index == Map_end(&p->m_SapAssignmentList))
            {
                Map_insert(&p->m_SapAssignmentList, &key, &str);
            }
            else
            {
                String_copy_1((String*) Map_second_at(&p->m_SapAssignmentList, index), &str);
            }

            String_d(&str);
        }
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

void CGXDLMSSapAssignment_d(CGXDLMSSapAssignment* p)
{
    Map_d(&p->m_SapAssignmentList);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
