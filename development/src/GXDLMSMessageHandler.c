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

#include "../include/GXDLMSMessageHandler.h"
#include "../include/GXDLMSClient.h"

#include "../include/Vector.h"
#include "../include/Pair.h"
#include "../include/Optimize.h"

static void CGXDLMSMessageHandler__(CGXDLMSMessageHandler* p)
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
     p->GetAttributeCount = CGXDLMSMessageHandler_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSMessageHandler_GetMethodCount;
	 p->GetValue = CGXDLMSMessageHandler_GetValue;
	 p->SetValue = CGXDLMSMessageHandler_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
     p->d = CGXDLMSMessageHandler_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSMessageHandler_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSMessageHandler_GetValues;
     p->GetAttributeIndexToRead = CGXDLMSMessageHandler_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

     Vector_(&p->m_ListeningWindow, sizeof(Pair), Pair_v_c, Pair_v_d); //std::vector<std::pair<CGXDateTime, CGXDateTime> >
     Vector_(&p->m_AllowedSenders, sizeof(String), String_v_c, String_v_d); //std::vector<std::string>
     Vector_(&p->m_SendersAndActions, sizeof(Pair), Pair_v_c, Pair_v_d); //std::vector<std::pair<std::string, std::pair<int, CGXDLMSScriptAction> > >
}
//Constructor.
void CGXDLMSMessageHandler_1(CGXDLMSMessageHandler* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSMessageHandler_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSMessageHandler_2(CGXDLMSMessageHandler* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_MESSAGE_HANDLER, &ln, sn);

	CGXDLMSMessageHandler__(p);
}

//LN Constructor.
void CGXDLMSMessageHandler_3(CGXDLMSMessageHandler* p, String ln)
{
	CGXDLMSMessageHandler_2(p, ln, 0);
}

Vector* CGXDLMSMessageHandler_GetListeningWindow(CGXDLMSMessageHandler* p) // std::vector<std::pair<CGXDateTime, CGXDateTime> >&
{
    return &p->m_ListeningWindow;
}

Vector* CGXDLMSMessageHandler_GetAllowedSenders(CGXDLMSMessageHandler* p) // std::vector<std::string>&
{
    return &p->m_AllowedSenders;
}

Vector* CGXDLMSMessageHandler_GetSendersAndActions(CGXDLMSMessageHandler* p) //std::vector<std::pair<std::string, std::pair<int, CGXDLMSScriptAction> > >&
{
    return &p->m_SendersAndActions;
}

// Returns amount of attributes.
int CGXDLMSMessageHandler_GetAttributeCount(CGXDLMSMessageHandler* p)
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSMessageHandler_GetMethodCount(CGXDLMSMessageHandler* p)
{
    return 0;
}

void CGXDLMSMessageHandler_GetValues(CGXDLMSMessageHandler* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std::vector<std::pair<CGXDateTime, CGXDateTime> >::iterator it = p->m_ListeningWindow.begin(); it != p->m_ListeningWindow.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_ListeningWindow); i != Vector_end(&p->m_ListeningWindow); ++i)
    {
        Pair* it = Vector_at(&p->m_ListeningWindow, i);
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;
        // std::string str = it->first.ToString();
        // sb.write(str.c_str(), str.size());
        String str = CGXDateTime_ToString((CGXDateTime*)Pair_first(it));
        String_append_3(&sb, &str);

        String_append_1(&sb, " ");

        String_d(&str);

        // str = it->second.ToString();
        // sb.write(str.c_str(), str.size());
        str = CGXDateTime_ToString((CGXDateTime*)Pair_second(it));

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    String_append_1(&sb, "[");
    empty = true;
    //for (std::vector<std::string>::iterator it = p->m_AllowedSenders.begin(); it != p->m_AllowedSenders.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_AllowedSenders);
            i != Vector_end(&p->m_AllowedSenders); ++i)
    {
        String* it = Vector_at(&(p->m_AllowedSenders), i);
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

    String_append_1(&sb, "[");
    empty = true;
    //for (std::vector<std::pair<std::string, std::pair<int, CGXDLMSScriptAction> > >::iterator it = p->m_SendersAndActions.begin(); it != p->m_SendersAndActions.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_SendersAndActions); i != Vector_end(&p->m_SendersAndActions); ++i)
    {
        Pair* it = Vector_at(&p->m_SendersAndActions, i);
        
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;
        //sb.write(it->first.c_str(), it->first.size());
        String_append_3(&sb, (String*)Pair_first(it));
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);
}

void CGXDLMSMessageHandler_GetAttributeIndexToRead(CGXDLMSMessageHandler* p, Vector* attributes) //std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //ListeningWindow
    if (CGXDLMSMessageHandler_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //AllowedSenders
    if (CGXDLMSMessageHandler_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //SendersAndActions
    if (CGXDLMSMessageHandler_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSMessageHandler_GetDataType(CGXDLMSMessageHandler* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    //ListeningWindow
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    //AllowedSenders
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    //SendersAndActions
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSMessageHandler_GetValue(CGXDLMSMessageHandler* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        //TODO: e.SetValue(p->m_ListeningWindow);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        //TODO: e.SetValue(p->m_AllowedSenders);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        //TODO: e.SetValue(p->m_SendersAndActions);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSMessageHandler_SetValue(CGXDLMSMessageHandler* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        Vector_clear(&p->m_ListeningWindow);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
            //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
            {
                CGXDLMSVariant* it = Vector_at(temp, i);

                CGXDLMSVariant tmp;
                CGXDLMSVariant_1(&tmp);

                CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&(it->Arr), 0), DLMS_DATA_TYPE_DATETIME, &tmp);

                CGXDateTime start = tmp.dateTime;

                CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&(it->Arr), 1), DLMS_DATA_TYPE_DATETIME, &tmp);

                CGXDateTime end = tmp.dateTime;

                Pair pair;
                Pair_(&pair, sizeof(CGXDateTime), sizeof(CGXDateTime),
                      NULL, NULL, NULL, NULL, &start, &end);

                Vector_push_back(&p->m_ListeningWindow, &pair);

                Pair_d(&pair);
                CGXDLMSVariant_d(&tmp);
            }
        }

    }
    else if (e_index == 3)
    {
        Vector_clear(&p->m_AllowedSenders);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
            //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
            {
                CGXDLMSVariant* it = Vector_at(temp, i);

                String str;
                String_(&str);

                //str.append(reinterpret_cast<char const*>(it->byteArr), it->size);
                String_append_2(&str, (char const*)it->st.un.byteArr, it->size);
                Vector_push_back(&p->m_AllowedSenders, &str);

                String_d(&str);
            }
        }
    }
    else if (e_index == 4)
    {
        Vector_clear(&p->m_SendersAndActions);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
            //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
            {
                //std::string id = it->Arr[0].byteArr.ToString();
                //Object[] tmp2 = (Object[]) tmp[1];
                /*TODO:
                KeyValuePair<int, GXDLMSScriptAction> executed_script = new KeyValuePair<int, GXDLMSScriptAction>(Convert.ToInt32(tmp2[1], tmp2[2]));
                p->m_SendersAndActions.Add(new KeyValuePair<std::string, KeyValuePair<int, GXDLMSScriptAction>>(id, tmp[1] as GXDateTime));
                 * */
            }
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSMessageHandler_d(CGXDLMSMessageHandler* p)
{
    Vector_d(&p->m_ListeningWindow);
    Vector_d(&p->m_AllowedSenders);
    Vector_d(&p->m_SendersAndActions);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
