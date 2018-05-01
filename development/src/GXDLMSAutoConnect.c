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
#include "../include/GXDLMSAutoConnect.h"

#include "../include/Vector.h"
#include "../include/Pair.h"
#include "../include/Optimize.h"

static void CGXDLMSAutoConnect__(CGXDLMSAutoConnect* p)
{
	 p->GetAttributeCount = CGXDLMSAutoConnect_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSAutoConnect_GetMethodCount;
	 p->GetValue = CGXDLMSAutoConnect_GetValue;
	 p->SetValue = CGXDLMSAutoConnect_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
	 p->d = CGXDLMSAutoConnect_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSAutoConnect_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSAutoConnect_GetValues;
	 p->GetAttributeIndexToRead = CGXDLMSAutoConnect_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

	 Vector_(&p->m_CallingWindow, sizeof(Pair), Pair_v_c, Pair_v_d);//std::vector<std::pair< CGXDateTime, CGXDateTime> >
	 Vector_(&p->m_Destinations, sizeof(String), String_v_c, String_v_d);//std::vector< std::string >
}
//Constructor.
void CGXDLMSAutoConnect_1(CGXDLMSAutoConnect *p)
{
    String t_Str;
    String_3(&t_Str, "0.0.2.1.0.255");

    CGXDLMSAutoConnect_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSAutoConnect_2(CGXDLMSAutoConnect *p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_AUTO_CONNECT, &ln, sn);

	CGXDLMSAutoConnect__(p);

    p->m_Mode = AUTO_CONNECT_MODE_NO_AUTO_DIALLING;
    p->m_RepetitionDelay = p->m_Repetitions = 0;
}

//LN Constructor.
void CGXDLMSAutoConnect_3(CGXDLMSAutoConnect *p, String ln)
{
	CGXDLMSAutoConnect_2(p, ln, 0);
}

void CGXDLMSAutoConnect_d(CGXDLMSAutoConnect *p)
{
    Vector_d(&p->m_CallingWindow);
    Vector_d(&p->m_Destinations);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}

Vector* CGXDLMSAutoConnect_GetCallingWindow(CGXDLMSAutoConnect *p)//std::vector<std::pair< CGXDateTime, CGXDateTime> >&
{
    return &p->m_CallingWindow;
}
void CGXDLMSAutoConnect_SetCallingWindow(CGXDLMSAutoConnect *p, Vector value)//std::vector<std::pair< CGXDateTime, CGXDateTime> >
{
	Vector_copy_1(&p->m_CallingWindow, &value);
}

Vector* CGXDLMSAutoConnect_GetDestinations(CGXDLMSAutoConnect *p)//std::vector< std::string >&
{
    return &p->m_Destinations;
}

void CGXDLMSAutoConnect_SetDestinations(CGXDLMSAutoConnect *p, Vector* value)//std::vector< std::string >&
{
	Vector_copy_1(&p->m_Destinations, value);
}

// Returns amount of attributes.
int CGXDLMSAutoConnect_GetAttributeCount(CGXDLMSAutoConnect *p)
{
    return 6;
}

// Returns amount of methods.
int CGXDLMSAutoConnect_GetMethodCount(CGXDLMSAutoConnect *p)
{
    return 0;
}

void CGXDLMSAutoConnect_GetValues(CGXDLMSAutoConnect *p, Vector* values)//std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_2(values, p->m_Mode);

    Vector_push_back_Str_2(values, p->m_Repetitions);

    Vector_push_back_Str_2(values, p->m_RepetitionDelay);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std::vector<std::pair< CGXDateTime, CGXDateTime> >::iterator it = p->m_CallingWindow.begin(); it != p->m_CallingWindow.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_CallingWindow); i != Vector_end(&p->m_CallingWindow); ++i)
    {
        Pair* it = Vector_at(&p->m_CallingWindow, i);
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDateTime_ToString((CGXDateTime*)Pair_first(it));

        String_append_3(&sb, &str);
        
        String_d(&str);

        String_append_1(&sb, " ");

        str = CGXDateTime_ToString((CGXDateTime*)Pair_second(it));

        String_append_3(&sb, &str);

        String_d(&str);
    }

    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    //Clear str.
    String_d(&sb);

    String_append_1(&sb, "[");
    empty = true;
    //for (std::vector< std::string >::iterator it = p->m_Destinations.begin(); it != p->m_Destinations.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_Destinations);
            i != Vector_end(&p->m_Destinations); ++i)
    {
        String* it = Vector_at(&(p->m_Destinations), i);
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String_append_3(&sb, it);

    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);
}

void CGXDLMSAutoConnect_GetAttributeIndexToRead(CGXDLMSAutoConnect *p, Vector* attributes)//std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Mode
    if (CGXDLMSAutoConnect_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //Repetitions
    if (CGXDLMSAutoConnect_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //RepetitionDelay
    if (CGXDLMSAutoConnect_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //CallingWindow
    if (CGXDLMSAutoConnect_CanRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //Destinations
    if (CGXDLMSAutoConnect_CanRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSAutoConnect_GetDataType(CGXDLMSAutoConnect *p, int index, DLMS_DATA_TYPE* type)
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
        *type = DLMS_DATA_TYPE_UINT8;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_UINT16;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
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
int CGXDLMSAutoConnect_GetValue(CGXDLMSAutoConnect *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        //e.SetValue((unsigned char)GetMode());
        CGXDLMSValueEventArg_SetValue_4(e, (unsigned char)(p->m_Mode));
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        //e.SetValue(GetRepetitions());
        CGXDLMSValueEventArg_SetValue_3(e, p->m_Repetitions);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        //e.SetValue(GetRepetitionDelay());
        CGXDLMSValueEventArg_SetValue_3(e, p->m_Repetitions);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        e->m_ByteArray = true;
        unsigned long cnt = (unsigned long)Vector_size(&p->m_CallingWindow);

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        int ret;
        //Add count
        GXHelpers_SetObjectCount(cnt, &data);
        if (cnt != 0)
        {
            CGXDLMSVariant s, e;
            CGXDLMSVariant_1(&s);
            CGXDLMSVariant_1(&e);

            //for (std::vector<std::pair< CGXDateTime, CGXDateTime> >::iterator it = p->m_CallingWindow.begin(); it != p->m_CallingWindow.end(); ++it)
            for (unsigned int i = Vector_begin(&p->m_CallingWindow); i != Vector_end(&p->m_CallingWindow); ++i)
            {
                Pair* it = Vector_at(&p->m_CallingWindow, i);
                CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
                CGXByteBuffer_SetUInt8_1(&data, 2); //Count
                //s = it->first;
                //e = it->second;
                CGXDLMSVariant_copy_21(&s, (CGXDateTime*) Pair_first(it));
                CGXDLMSVariant_copy_21(&e, (CGXDateTime*) Pair_second(it));
                if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &s)) != 0 || //start_time
                    (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &e)) != 0) //end_time
                {
                    CGXDLMSVariant_d(&s);
                    CGXDLMSVariant_d(&e);
                    CGXByteBuffer_d(&data);
                    return ret;
                }
            }

            CGXDLMSVariant_d(&s);
            CGXDLMSVariant_d(&e);
        }
        //e.SetValue(data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        int ret;
        unsigned long cnt = (unsigned long)Vector_size(&p->m_Destinations);
        //Add count
        GXHelpers_SetObjectCount(cnt, &data);
        //for (std::vector< std::string >::iterator it = p->m_Destinations.begin(); it != p->m_Destinations.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_Destinations); i != Vector_end(&p->m_Destinations); ++i)
        {
            String* it = Vector_at(&p->m_Destinations, i);

            CGXDLMSVariant value;
            CGXDLMSVariant_1(&value);

            //e.GetValue().Add(&(*it)[0], (int)it->size());
            CGXDLMSVariant_Add_2(CGXDLMSValueEventArg_GetValue(e), String_at(it, 0), (int)String_size(it));

            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &value)) != 0) //destination
            {
                CGXDLMSVariant_d(&value);
                CGXByteBuffer_d(&data);
                return ret;
            }

            CGXDLMSVariant_d(&value);
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
//int CGXDLMSAutoConnect::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
int CGXDLMSAutoConnect_SetValue(CGXDLMSAutoConnect *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        //SetMode((AUTO_CONNECT_MODE)e.GetValue().ToInteger());
        p->m_Mode = (AUTO_CONNECT_MODE)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 3)
    {
        //SetRepetitions(e.GetValue().lVal);
        p->m_Repetitions = CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 4)
    {
        //SetRepetitionDelay(e.GetValue().lVal);
        p->m_RepetitionDelay = CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 5)
    {
        Vector_clear(&p->m_CallingWindow);

        Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
        //for (std::vector<CGXDLMSVariant>::iterator item = e.GetValue().Arr.begin(); item != e.GetValue().Arr.end(); ++item)        
        for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
        {
            CGXDLMSVariant* item = Vector_at(temp, i);

            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            CGXDLMSClient_ChangeType_2(Vector_at(&(item->Arr), 0), DLMS_DATA_TYPE_DATETIME, &tmp);
            CGXDateTime start = tmp.dateTime;
            CGXDLMSClient_ChangeType_2(Vector_at(&(item->Arr), 1), DLMS_DATA_TYPE_DATETIME, &tmp);
            CGXDateTime end = tmp.dateTime;

            Pair pair;
            Pair_(&pair, sizeof(CGXDateTime), sizeof(CGXDateTime),
                  NULL, NULL, NULL, NULL, &start, &end);

            Vector_push_back(&p->m_CallingWindow, &pair);

            Pair_d(&pair);
            CGXDLMSVariant_d(&tmp);
        }
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 6)
    {
        Vector_clear(&p->m_Destinations);

        //std::vector< std::string > items;
        Vector items;
        Vector_(&items, sizeof(String), String_v_c, String_v_d);

        Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
        //for (std::vector<CGXDLMSVariant>::iterator item = e.GetValue().Arr.begin(); item != e.GetValue().Arr.end(); ++item)
        for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
        {
            CGXDLMSVariant* item = Vector_at(temp, i);

            CGXDLMSVariant value;
            CGXDLMSVariant_1(&value);

            CGXDLMSClient_ChangeType_2(item, DLMS_DATA_TYPE_STRING, &value);
            //items.push_back(e.GetValue().ToString());
            String str = CGXDLMSVariant_ToString(CGXDLMSValueEventArg_GetValue(e));

            Vector_push_back(&items, &str);

            String_d(&str);
            CGXDLMSVariant_d(&value);
        }
        CGXDLMSAutoConnect_SetDestinations(p, &items);

        Vector_d(&items);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}
