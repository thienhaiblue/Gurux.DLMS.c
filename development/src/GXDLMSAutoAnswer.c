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
#include "../include/GXDLMSAutoAnswer.h"

#include "../include/Vector.h"
#include "../include/Pair.h"
#include "../include/Optimize.h"

static void CGXDLMSAutoAnswer__(CGXDLMSAutoAnswer* p)
{
    p->GetAttributeCount = CGXDLMSAutoAnswer_GetAttributeCount;
    p->GetMethodCount = CGXDLMSAutoAnswer_GetMethodCount;
    p->GetValue = CGXDLMSAutoAnswer_GetValue;
    p->SetValue = CGXDLMSAutoAnswer_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSAutoAnswer_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSAutoAnswer_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSAutoAnswer_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSAutoAnswer_GetAttributeIndexToRead;

    Vector_(&p->m_ListeningWindow, sizeof(Pair), Pair_v_c, Pair_v_d); // std::vector<std::pair< CGXDateTime, CGXDateTime> >
}

//CGXDLMSAutoAnswer::CGXDLMSAutoAnswer() :
  //  CGXDLMSAutoAnswer("0.0.2.2.0.255", 0)
void CGXDLMSAutoAnswer_1(CGXDLMSAutoAnswer *p)
{
    String t_Str;
    String_3(&t_Str, "0.0.2.2.0.255");

    CGXDLMSAutoAnswer_3(p, t_Str, 0);

    String_d(&t_Str);
}

//CGXDLMSAutoAnswer::CGXDLMSAutoAnswer(std::string ln) :
  //  CGXDLMSAutoAnswer(ln, 0)
void CGXDLMSAutoAnswer_2(CGXDLMSAutoAnswer *p, String ln)
{
    CGXDLMSAutoAnswer_3(p, ln, 0);
}

//CGXDLMSAutoAnswer::CGXDLMSAutoAnswer(std::string ln, unsigned short sn) :
  //  CGXDLMSObject(DLMS_OBJECT_TYPE_AUTO_ANSWER, ln, sn)
void CGXDLMSAutoAnswer_3(CGXDLMSAutoAnswer *p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_AUTO_ANSWER, &ln, sn);
    CGXDLMSAutoAnswer__(p);

    p->m_NumberOfRingsInListeningWindow = p->m_NumberOfRingsOutListeningWindow = 0;
    p->m_Mode = AUTO_CONNECT_MODE_NO_AUTO_DIALLING;
    p->m_Status = AUTO_ANSWER_STATUS_INACTIVE;
    p->m_NumberOfCalls = 0;
}

//std::vector<std::pair< CGXDateTime, CGXDateTime> >& CGXDLMSAutoAnswer::GetListeningWindow()
Vector* CGXDLMSAutoAnswer_GetListeningWindow(CGXDLMSAutoAnswer *p)
{
    return &(p->m_ListeningWindow);
}
//void CGXDLMSAutoAnswer::SetListeningWindow(std::vector<std::pair< CGXDateTime, CGXDateTime> >& value)
void CGXDLMSAutoAnswer_SetListeningWindow(CGXDLMSAutoAnswer *p, Vector* value)
{
    Vector_copy_1(&(p->m_ListeningWindow), value);
}

// Returns amount of attributes.
int CGXDLMSAutoAnswer_GetAttributeCount(CGXDLMSAutoAnswer *p)
{
    return 6;
}

// Returns amount of methods.
int CGXDLMSAutoAnswer_GetMethodCount(CGXDLMSAutoAnswer *p)
{
    return 0;
}

//void CGXDLMSAutoAnswer::GetValues(std::vector<std::string>& values)
void CGXDLMSAutoAnswer_GetValues(CGXDLMSAutoAnswer *p, Vector* values)
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_2(values, p->m_Mode);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    // std::vector<std::pair< CGXDateTime, CGXDateTime> >
    for (unsigned int it = Vector_begin(&(p->m_ListeningWindow));
         it != Vector_end(&(p->m_ListeningWindow)); ++it)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDateTime_ToString((CGXDateTime*) Pair_first((Pair*) Vector_at(&(p->m_ListeningWindow), it)));

        String_append_3(&sb, &str);
        String_append_1(&sb, " ");

        String_d(&str);

        str = CGXDateTime_ToString((CGXDateTime*) Pair_second((Pair*) Vector_at(&(p->m_ListeningWindow), it)));

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    Vector_push_back_Str_2(values, p->m_Status);

    Vector_push_back_Str_2(values, p->m_NumberOfCalls);

    String sb2;
    String_(&sb2);

    String_append_int(&sb2, p->m_NumberOfRingsInListeningWindow);

    String_append_1(&sb2, "/");

    String_append_int(&sb2, p->m_NumberOfRingsOutListeningWindow);

    Vector_push_back(values, &sb2);

    String_d(&sb2);
}

//void CGXDLMSAutoAnswer::GetAttributeIndexToRead(std::vector<int>& attributes)
void CGXDLMSAutoAnswer_GetAttributeIndexToRead(CGXDLMSAutoAnswer *p, Vector* attributes)
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Mode is static and read only once.
    if (!CGXDLMSAutoAnswer_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //ListeningWindow is static and read only once.
    if (!CGXDLMSAutoAnswer_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //Status is not static.
    if (CGXDLMSAutoAnswer_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }

    //NumberOfCalls is static and read only once.
    if (!CGXDLMSAutoAnswer_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //NumberOfRingsInListeningWindow is static and read only once.
    if (!CGXDLMSAutoAnswer_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSAutoAnswer_GetDataType(CGXDLMSAutoAnswer *p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_UINT8;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSAutoAnswer_GetValue(CGXDLMSAutoAnswer *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        //e.SetValue(GetMode());
        CGXDLMSValueEventArg_SetValue_3(e, p->m_Mode);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        e->m_ByteArray = true;
        int ret;
        unsigned long cnt = (unsigned long)Vector_size(&(p->m_ListeningWindow));

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount(cnt, &data);

        CGXDLMSVariant f, s;
        CGXDLMSVariant_1(&f);
        CGXDLMSVariant_1(&s);

        // std::vector<std::pair<CGXDateTime, CGXDateTime> >
        for (unsigned int it = Vector_begin(&(p->m_ListeningWindow));
             it != Vector_end(&(p->m_ListeningWindow)); ++it)
        {
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 2); //Count

            // f = it->first;
            // s = it->second;
            CGXDLMSVariant_copy_21(&f, (CGXDateTime*) Pair_first((Pair*) Vector_at(&(p->m_ListeningWindow), it)));
            CGXDLMSVariant_copy_21(&s, (CGXDateTime*) Pair_second((Pair*) Vector_at(&(p->m_ListeningWindow), it)));


            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &f)) != 0 || //start_time
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &s)) != 0) //end_time
            {
                CGXByteBuffer_d(&data);
                CGXDLMSVariant_d(&f);
                CGXDLMSVariant_d(&s);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&f);
        CGXDLMSVariant_d(&s);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_Status);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        //e.SetValue(GetNumberOfCalls());
        CGXDLMSValueEventArg_SetValue_3(e, p->m_NumberOfCalls);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        GXHelpers_SetObjectCount(2, &data);

        CGXDLMSVariant in;
        CGXDLMSVariant_10(&in, p->m_NumberOfRingsInListeningWindow);

        CGXDLMSVariant out;
        CGXDLMSVariant_10(&out, p->m_NumberOfRingsOutListeningWindow);

        int ret;
        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &in)) != DLMS_ERROR_CODE_OK ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &out)) != DLMS_ERROR_CODE_OK)
        {
            CGXByteBuffer_d(&data);
            CGXDLMSVariant_d(&in);
            CGXDLMSVariant_d(&out);
            return ret;
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&in);
        CGXDLMSVariant_d(&out);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSAutoAnswer_SetValue(CGXDLMSAutoAnswer *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    if (e_index == 2)
    {
        //SetMode((AUTO_CONNECT_MODE)e.GetValue().lVal);
        p->m_Mode = (AUTO_CONNECT_MODE)CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        //m_ListeningWindow.clear();
        Vector_clear(&p->m_ListeningWindow);

        // std::vector<CGXDLMSVariant>
        for (unsigned int i = Vector_begin(&(CGXDLMSValueEventArg_GetValue(e)->Arr));
             i != Vector_end(&(CGXDLMSValueEventArg_GetValue(e)->Arr)); ++i)
        {
            CGXDLMSVariant start, end;
            CGXDLMSVariant_1(&start);
            CGXDLMSVariant_1(&end);

            CGXDLMSVariant* item = Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), i);

            // CGXDLMSClient::ChangeType((*item).Arr[0], DLMS_DATA_TYPE_DATETIME, start);
            // CGXDLMSClient::ChangeType((*item).Arr[1], DLMS_DATA_TYPE_DATETIME, end);
            CGXDLMSClient_ChangeType_2(Vector_at(&(item->Arr), 0), DLMS_DATA_TYPE_DATETIME, &start);
            CGXDLMSClient_ChangeType_2(Vector_at(&(item->Arr), 1), DLMS_DATA_TYPE_DATETIME, &end);

            Pair t_pair;
            Pair_(&t_pair, sizeof(CGXDateTime), sizeof(CGXDateTime),
                  NULL, NULL, NULL, NULL,
                  &(start.dateTime), &(end.dateTime));

            Vector_push_back(&(p->m_ListeningWindow), &t_pair);

            Pair_d(&t_pair);

            CGXDLMSVariant_d(&start);
            CGXDLMSVariant_d(&end);
        }
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        //SetStatus((AUTO_ANSWER_STATUS)e.GetValue().lVal);
        p->m_Status = (AUTO_ANSWER_STATUS)CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        //SetNumberOfCalls(e.GetValue().lVal);
        p->m_NumberOfCalls = CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        p->m_NumberOfRingsInListeningWindow = p->m_NumberOfRingsOutListeningWindow = 0;
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt != DLMS_DATA_TYPE_NONE)
        {
            //m_NumberOfRingsInListeningWindow = e.GetValue().Arr[0].ToInteger();
            //m_NumberOfRingsOutListeningWindow = e.GetValue().Arr[1].ToInteger();
            p->m_NumberOfRingsInListeningWindow = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));
            p->m_NumberOfRingsOutListeningWindow = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1));
        }
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

void CGXDLMSAutoAnswer_d(CGXDLMSAutoAnswer *p)
{
    Vector_d(&p->m_ListeningWindow);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
