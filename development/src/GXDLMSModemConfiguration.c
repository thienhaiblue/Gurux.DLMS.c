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
#include "../include/GXDLMSModemConfiguration.h"
#include "../include/GXDLMSConverter.h"
#include "../include/Optimize.h"

static void CGXDLMSModemConfiguration__(CGXDLMSModemConfiguration* p)
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
     p->GetAttributeCount = CGXDLMSModemConfiguration_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSModemConfiguration_GetMethodCount;
	 p->GetValue = CGXDLMSModemConfiguration_GetValue;
	 p->SetValue = CGXDLMSModemConfiguration_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
     p->d = CGXDLMSModemConfiguration_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSModemConfiguration_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSModemConfiguration_GetValues;
     p->GetAttributeIndexToRead = CGXDLMSModemConfiguration_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

     Vector_(&p->m_InitialisationStrings, sizeof(CGXDLMSModemInitialisation),
             CGXDLMSModemInitialisation_v_c, CGXDLMSModemInitialisation_v_d); //std::vector<CGXDLMSModemInitialisation>
     Vector_(&p->m_ModemProfile, sizeof(String), String_v_c, String_v_d); //std::vector< std::string >

}
void CGXDLMSModemConfiguration_1(CGXDLMSModemConfiguration* p)
{
    String t_Str;
    String_3(&t_Str, "0.0.2.0.0.255");

    CGXDLMSModemConfiguration_3(p, t_Str, 0);

    String_d(&t_Str);
}

void CGXDLMSModemConfiguration_2(CGXDLMSModemConfiguration* p, String ln)
{
	CGXDLMSModemConfiguration_3(p, ln, 0);
}

void CGXDLMSModemConfiguration_3(CGXDLMSModemConfiguration* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_MODEM_CONFIGURATION, &ln, sn);

	CGXDLMSModemConfiguration__(p);

    p->m_CommunicationSpeed = DLMS_BAUD_RATE_9600;

    Vector_push_back_Str_3(&p->m_ModemProfile, "OK");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT");
    Vector_push_back_Str_3(&p->m_ModemProfile, "RING");
    Vector_push_back_Str_3(&p->m_ModemProfile, "NO CARRIER");
    Vector_push_back_Str_3(&p->m_ModemProfile, "ERROR");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 1200");
    Vector_push_back_Str_3(&p->m_ModemProfile, "NO DIAL TONE");
    Vector_push_back_Str_3(&p->m_ModemProfile, "BUSY");
    Vector_push_back_Str_3(&p->m_ModemProfile, "NO ANSWER");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 600");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 2400");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 4800");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 9600");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 14 400");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 28 800");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 33 600");
    Vector_push_back_Str_3(&p->m_ModemProfile, "CONNECT 56 000");
}

Vector* CGXDLMSModemConfiguration_GetInitialisationStrings(CGXDLMSModemConfiguration* p) //std::vector<CGXDLMSModemInitialisation>&
{
    return &p->m_InitialisationStrings;
}
void CGXDLMSModemConfiguration_SetInitialisationStrings(CGXDLMSModemConfiguration* p, Vector* value) //std::vector<CGXDLMSModemInitialisation>&
{
	Vector_copy_1(&p->m_InitialisationStrings, value);
}

Vector CGXDLMSModemConfiguration_GetModemProfile(CGXDLMSModemConfiguration* p)  //std::vector< std::string >
{
    Vector vec;
    Vector_2(&vec, &p->m_ModemProfile);

    return vec; // = copy cons + des
}

void CGXDLMSModemConfiguration_SetModemProfile(CGXDLMSModemConfiguration* p, Vector* value) //std::vector< std::string >&
{
	Vector_copy_1(&p->m_ModemProfile, value);
}

// Returns amount of attributes.
int CGXDLMSModemConfiguration_GetAttributeCount(CGXDLMSModemConfiguration* p)
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSModemConfiguration_GetMethodCount(CGXDLMSModemConfiguration* p)
{
    return 0;
}

void CGXDLMSModemConfiguration_GetValues(CGXDLMSModemConfiguration* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_1(p->m_CommunicationSpeed));

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std::vector<CGXDLMSModemInitialisation>::iterator it = p->m_InitialisationStrings.begin(); it != p->m_InitialisationStrings.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_InitialisationStrings);
            i != Vector_end(&p->m_InitialisationStrings); ++i)
    {
    	CGXDLMSModemInitialisation* it = Vector_at(&(p->m_InitialisationStrings), i);
        if (!empty)
        {
        	String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSModemInitialisation_ToString(it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    //Clear str.
    String_d(&sb);
    String_append_1(&sb, "[");
    empty = true;
    //for (std::vector< std::string >::iterator it = p->m_ModemProfile.begin(); it != p->m_ModemProfile.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_ModemProfile);
                i != Vector_end(&p->m_ModemProfile); ++i)
    {
        String* it = Vector_at(&(p->m_ModemProfile), i);
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

void CGXDLMSModemConfiguration_GetAttributeIndexToRead(CGXDLMSModemConfiguration* p, Vector* attributes) //std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //CommunicationSpeed
    if (!CGXDLMSModemConfiguration_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //InitialisationStrings
    if (!CGXDLMSModemConfiguration_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //ModemProfile
    if (!CGXDLMSModemConfiguration_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSModemConfiguration_GetDataType(CGXDLMSModemConfiguration* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSModemConfiguration_GetValue(CGXDLMSModemConfiguration* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        //e.SetValue(p->m_CommunicationSpeed);
        CGXDLMSVariant tmp;
        CGXDLMSVariant_10(&tmp, p->m_CommunicationSpeed);

        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        int ret;
        unsigned long cnt = (unsigned long)Vector_size(&p->m_InitialisationStrings);
        GXHelpers_SetObjectCount(cnt, &data);

        CGXDLMSVariant request, response, delay;
        CGXDLMSVariant_1(&request);
        CGXDLMSVariant_1(&response);
        CGXDLMSVariant_1(&delay);

        //for (std::vector<CGXDLMSModemInitialisation>::iterator it = p->m_InitialisationStrings.begin();
          //  it != p->m_InitialisationStrings.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_InitialisationStrings); i != Vector_end(&p->m_InitialisationStrings); ++i)
        {
            CGXDLMSModemInitialisation* it = Vector_at(&p->m_InitialisationStrings, i);

            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 3); //Count
            //request = it->GetRequest();
            //response = it->GetResponse();
            //delay = it->GetDelay();

            String str = CGXDLMSModemInitialisation_GetRequest(it);

            CGXDLMSVariant_copy_2(&request, str);

            String_d(&str);

            str = CGXDLMSModemInitialisation_GetResponse(it);

            CGXDLMSVariant_copy_2(&response, str);

            String_d(&str);

            CGXDLMSVariant_copy_12(&delay, it->m_Delay);

            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &request)) != 0 ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &response)) != 0 ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &delay)) != 0)
            {
                CGXByteBuffer_d(&data);
                CGXDLMSVariant_d(&request);
                CGXDLMSVariant_d(&response);
                CGXDLMSVariant_d(&delay);
                return ret;
            }
        }
        //e.SetValue(data);
        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        CGXDLMSVariant_d(&request);
        CGXDLMSVariant_d(&response);
        CGXDLMSVariant_d(&delay);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        int ret;
        unsigned long cnt = (unsigned long)Vector_size(&p->m_ModemProfile);
        GXHelpers_SetObjectCount(cnt, &data);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        //for (std::vector< std::string >::iterator it = p->m_ModemProfile.begin();
          //  it != p->m_ModemProfile.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_ModemProfile); i != Vector_end(&p->m_ModemProfile); ++i)
        {
            String* it = Vector_at(&p->m_ModemProfile, i);
            //tmp = *it;
            CGXDLMSVariant_copy_2(&tmp, *it);
            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&data);
                return ret;
            }
        }

        CGXDLMSVariant_d(&tmp);

        //e.SetValue(data);
        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSModemConfiguration_SetValue(CGXDLMSModemConfiguration* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        p->m_CommunicationSpeed = (DLMS_BAUD_RATE)CGXDLMSValueEventArg_GetValue(e)->st.un.bVal;
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 3)
    {
        Vector_clear(&p->m_InitialisationStrings);
        int ret;

        Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
        //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
        {
            CGXDLMSVariant* it = Vector_at(temp, i);

            CGXDLMSModemInitialisation item;
            CGXDLMSModemInitialisation_(&item);

            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            if ((ret = CGXDLMSClient_ChangeType_2(Vector_at(&(it->Arr), 0), DLMS_DATA_TYPE_STRING, &tmp)) != DLMS_ERROR_CODE_OK)
            {
                CGXDLMSVariant_d(&tmp);
                CGXDLMSModemInitialisation_d(&item);
                return ret;
            }

            String str = CGXDLMSVariant_ToString(&tmp);

            CGXDLMSModemInitialisation_SetRequest(&item, str);

            String_d(&str);

            if ((ret = CGXDLMSClient_ChangeType_2(Vector_at(&(it->Arr), 1), DLMS_DATA_TYPE_STRING, &tmp)) != DLMS_ERROR_CODE_OK)
            {
                CGXDLMSVariant_d(&tmp);
                CGXDLMSModemInitialisation_d(&item);
                return ret;
            }

            str = CGXDLMSVariant_ToString(&tmp);

            CGXDLMSModemInitialisation_SetResponse(&item, str);

            String_d(&str);

            if (Vector_size(&it->Arr) > 2)
            {
                item.m_Delay = ((CGXDLMSVariant*)Vector_at(&(it->Arr), 2))->st.un.uiVal;
            }
            Vector_push_back(&p->m_InitialisationStrings, &item);

            CGXDLMSVariant_d(&tmp);
            CGXDLMSModemInitialisation_d(&item);
        }
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 4)
    {
        Vector_clear(&p->m_ModemProfile);
        int ret;

        Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
        //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
        {
            CGXDLMSVariant* it = Vector_at(temp, i);

            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            if ((ret = CGXDLMSClient_ChangeType_2(it, DLMS_DATA_TYPE_STRING, &tmp)) != DLMS_ERROR_CODE_OK)
            {
                CGXDLMSVariant_d(&tmp);
                return ret;
            }
            //p->m_ModemProfile.push_back(tmp.ToString());
            Vector_push_back_Str_1(&p->m_ModemProfile, &tmp);

            CGXDLMSVariant_d(&tmp);
        }
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

void CGXDLMSModemConfiguration_d(CGXDLMSModemConfiguration* p)
{
    Vector_d(&p->m_InitialisationStrings);
    Vector_d(&p->m_ModemProfile);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
