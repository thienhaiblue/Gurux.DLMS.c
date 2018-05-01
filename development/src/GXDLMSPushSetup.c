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

#include "../include/GXDLMSPushSetup.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSObjectFactory.h"

#include "../include/Pair.h"
#include "../include/Optimize.h"

//Constructor.
//CGXDLMSPushSetup::CGXDLMSPushSetup() :
//    CGXDLMSPushSetup("0.7.25.9.0.255", 0)
static void CGXDLMSPushSetup__(CGXDLMSPushSetup* p)
{
    p->GetAttributeCount = CGXDLMSPushSetup_GetAttributeCount;
    p->GetMethodCount = CGXDLMSPushSetup_GetMethodCount;
    p->GetValue = CGXDLMSPushSetup_GetValue;
    p->SetValue = CGXDLMSPushSetup_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSPushSetup_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSPushSetup_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSPushSetup_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSPushSetup_GetAttributeIndexToRead;

    String_(&p->m_Destination);
    Vector_(&p->m_PushObjectList, sizeof(Pair), Pair_v_c, Pair_v_d); //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> > m_PushObjectList;
    Vector_(&p->m_CommunicationWindow, sizeof(Pair), Pair_v_c, Pair_v_d); //std::vector<std::pair<CGXDateTime, CGXDateTime> > m_CommunicationWindow;
}

void CGXDLMSPushSetup_1(CGXDLMSPushSetup* p)
{
    String t_Str;
    String_3(&t_Str, "0.7.25.9.0.255");

    CGXDLMSPushSetup_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
//CGXDLMSPushSetup::CGXDLMSPushSetup(std::string ln, unsigned short sn) :
//    CGXDLMSObject(DLMS_OBJECT_TYPE_PUSH_SETUP, ln, sn)
void CGXDLMSPushSetup_2(CGXDLMSPushSetup* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_PUSH_SETUP, &ln, sn);

    CGXDLMSPushSetup__(p);

    p->m_RandomisationStartInterval = p->m_NumberOfRetries = p->m_RepetitionDelay = 0;
    GXHelpers_SetLogicalName_2("0.7.25.9.0.255", p->m_LN);
    p->m_Service = DLMS_SERVICE_TYPE_TCP;
    p->m_Message = DLMS_MESSAGE_TYPE_COSEM_APDU;
}

//LN Constructor.
//CGXDLMSPushSetup::CGXDLMSPushSetup(std::string ln) :
//    CGXDLMSPushSetup(ln, 0)
void CGXDLMSPushSetup_3(CGXDLMSPushSetup* p, String ln)
{
    CGXDLMSPushSetup_2(p, ln, 0);
}

String* CGXDLMSPushSetup_GetDestination(CGXDLMSPushSetup* p)
{
    return &p->m_Destination;
}

void CGXDLMSPushSetup_SetDestination(CGXDLMSPushSetup* p, String* value)
{
    String_copy_1(&p->m_Destination, value);
}

// Returns amount of attributes.
int CGXDLMSPushSetup_GetAttributeCount(CGXDLMSPushSetup* p)
{
    return 7;
}

// Returns amount of methods.
int CGXDLMSPushSetup_GetMethodCount(CGXDLMSPushSetup* p)
{
    return 1;
}

void CGXDLMSPushSetup_GetValues(CGXDLMSPushSetup* p, Vector* values)//std::vector<std::string>& values);
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_3(&sb, "[");

    bool empty = true;

    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >
    for (unsigned int i = Vector_begin(&p->m_PushObjectList); i != Vector_end(&p->m_PushObjectList); ++i)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        Pair* it = Vector_at(&p->m_PushObjectList, i);

        String str;
        String_(&str);

        CGXDLMSObject_GetLogicalName_2(*((CGXDLMSObject**) (it->first)), &str);
        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);

    String_append_int(&sb, p->m_Service);
    String_append_1(&sb, " ");

    String_append_3(&sb, CGXDLMSPushSetup_GetDestination(p));
    String_append_1(&sb, " ");

    String_append_int(&sb, p->m_Message);

    Vector_push_back(values, &sb);

    String_d(&sb);

    String_3(&sb, "[");
    empty = true;

    // std::vector<std::pair<CGXDateTime, CGXDateTime> >
    for (unsigned int i = Vector_begin(&p->m_CommunicationWindow);
         i != Vector_end(&p->m_CommunicationWindow); ++i)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        Pair* it = Vector_at(&p->m_CommunicationWindow, i);

        String str = CGXDateTime_ToString((CGXDateTime*) it->first);

        String_append_3(&sb, &str);

        String_append_1(&sb, " ");

        String_d(&str);

        str = CGXDateTime_ToString((CGXDateTime*) it->second);

        String_append_3(&sb, &str);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);

    Vector_push_back_Str_2(values, p->m_RandomisationStartInterval);

    Vector_push_back_Str_2(values, p->m_NumberOfRetries);

    Vector_push_back_Str_2(values, p->m_RepetitionDelay);
}

void CGXDLMSPushSetup_GetAttributeIndexToRead(CGXDLMSPushSetup* p, Vector* attributes)//std::vector<int>& attributes);
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //PushObjectList
    if (CGXDLMSPushSetup_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }

    //SendDestinationAndMethod
    if (CGXDLMSPushSetup_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //CommunicationWindow
    if (CGXDLMSPushSetup_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //RandomisationStartInterval
    if (CGXDLMSPushSetup_CanRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //NumberOfRetries
    if (CGXDLMSPushSetup_CanRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //RepetitionDelay
    if (CGXDLMSPushSetup_CanRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSPushSetup_GetDataType(CGXDLMSPushSetup* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 5)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 6)
    {
        *type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 7)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSPushSetup_GetValue(CGXDLMSPushSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int ret;

    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }

    CGXDLMSVariant tmp;
    CGXDLMSVariant_1(&tmp);

    CGXByteBuffer buff;
    CGXByteBuffer_1(&buff);

    if (e_index == 2)
    {
        e->m_ByteArray = true;
        CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_ARRAY);
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_PushObjectList), &buff);

        // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >
        for (unsigned int i = Vector_begin(&p->m_PushObjectList); i != Vector_end(&p->m_PushObjectList); ++i)
        {
            CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&buff, 4);

            Pair* it = Vector_at(&p->m_PushObjectList, i);
            CGXDLMSVariant_copy_12(&tmp, (*((CGXDLMSObject**) (it->first)))->m_ObjectType);
            if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT16, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&buff);
                return ret;
            }
            CGXDLMSVariant_Clear(&tmp);
            if ((ret = CGXDLMSObject_GetLogicalName_1(*((CGXDLMSObject**) (it->first)), &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&buff);
                return ret;
            }
            if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&buff);
                return ret;
            }
            CGXDLMSVariant_copy_12(&tmp, ((CGXDLMSCaptureObject*) (it->second))->m_AttributeIndex);
            if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_INT8, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&buff);
                return ret;
            }
            CGXDLMSVariant_copy_12(&tmp, ((CGXDLMSCaptureObject*) (it->second))->m_DataIndex);
            if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT16, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&buff);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &buff);

        CGXDLMSVariant_d(&tmp);
        CGXByteBuffer_d(&buff);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        e->m_ByteArray = true;

        CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&buff, 3);

        CGXDLMSVariant_copy_12(&tmp, p->m_Service);
        if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_ENUM, &tmp)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            CGXByteBuffer_d(&buff);
            return ret;
        }

        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_AddString_2(&bb, String_c_str(CGXDLMSPushSetup_GetDestination(p)));
        CGXDLMSVariant_copy_4(&tmp, &bb);

        CGXByteBuffer_d(&bb);

        if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            CGXByteBuffer_d(&buff);
            return ret;
        }

        CGXDLMSVariant_copy_12(&tmp, p->m_Message);
        if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_ENUM, &tmp)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            CGXByteBuffer_d(&buff);
            return ret;
        }

        CGXDLMSValueEventArg_SetValue_2(e, &buff);

        CGXDLMSVariant_d(&tmp);
        CGXByteBuffer_d(&buff);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        e->m_ByteArray = true;
        CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_ARRAY);
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_CommunicationWindow), &buff);

        // std::vector<std::pair< CGXDateTime, CGXDateTime> >
        for (unsigned int i = Vector_begin(&p->m_CommunicationWindow);
             i != Vector_end(&p->m_CommunicationWindow); ++i)
        {
            CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&buff, 2);

            Pair* it = Vector_at(&p->m_PushObjectList, i);
            CGXDLMSVariant_copy_21(&tmp, (CGXDateTime*) (it->first));
            if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&buff);
                return ret;
            }

            CGXDLMSVariant_copy_21(&tmp, (CGXDateTime*) (it->second));
            if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&buff);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &buff);

        CGXDLMSVariant_d(&tmp);
        CGXByteBuffer_d(&buff);
        return DLMS_ERROR_CODE_OK;
    }

    CGXDLMSVariant_d(&tmp);
    CGXByteBuffer_d(&buff);

    if (e_index == 5)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_RandomisationStartInterval);

        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_NumberOfRetries);

        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 7)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_RepetitionDelay);

        return DLMS_ERROR_CODE_OK;
    }

    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSPushSetup_SetValue(CGXDLMSPushSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        String ln;
        String_(&ln);

        Vector_clear(&p->m_PushObjectList);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            // std::vector<CGXDLMSVariant>
            Vector* temp = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
            for (unsigned int i = Vector_begin(temp); i != Vector_end(temp); ++i)
            {
                CGXDLMSVariant* it = Vector_at(temp, i);

                DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&it->Arr, 0));
                GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&it->Arr, 1))->st.un.byteArr, &ln);

                CGXDLMSObject* obj = CGXDLMSObjectCollection_FindByLN_1(CGXDLMSSettings_GetObjects(settings), type, &ln);

                if (obj == NULL)
                {
                    obj = CGXDLMSObjectFactory_CreateObject_1(type);
                    CGXDLMSObject_SetLogicalName(obj, (CGXDLMSVariant*) Vector_at(&it->Arr, 1));
                }
                CGXDLMSCaptureObject co;
                CGXDLMSCaptureObject_2(&co, CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&it->Arr, 2))
                                          , CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&it->Arr, 3)));

                Pair tmp; // std::pair<CGXDLMSObject*, CGXDLMSCaptureObject>
                Pair_(&tmp, sizeof(CGXDLMSObject*), sizeof(CGXDLMSCaptureObject),
                      NULL, NULL, NULL, NULL, &obj, &co);

                Vector_push_back(&p->m_PushObjectList, &tmp);

                Pair_d(&tmp);
                //CGXDLMSCaptureObject_d(&co) don't
            }
        }

        String_d(&ln);
    }
    else if (e_index == 3)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_STRUCTURE)
        {
            p->m_Service = (DLMS_SERVICE_TYPE)CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 0));

            String str;
            String_(&str);

            String_append_2(&str, ((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 1))->st.un.byteArr,
                                  ((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 1))->size);

            CGXDLMSPushSetup_SetDestination(p, &str);
            p->m_Message = (DLMS_MESSAGE_TYPE)CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetValue(e)->Arr, 2));

            String_d(&str);
        }
    }
    else if (e_index == 4)
    {
        Vector_clear(&p->m_CommunicationWindow);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            int ret;

            // std::vector<CGXDLMSVariant>
            Vector* temp = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
            for (unsigned int i = Vector_begin(temp); i != Vector_end(temp); ++i)
            {
                CGXDLMSVariant* it = Vector_at(temp, i);

                CGXDLMSVariant tmp;
                CGXDLMSVariant_1(&tmp);

                if ((ret = CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&it->Arr, 0), DLMS_DATA_TYPE_DATETIME, &tmp)) != 0)
                {
                    CGXDLMSVariant_d(&tmp);
                    return ret;
                }
                CGXDateTime start = tmp.dateTime;
                if ((ret = CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&it->Arr, 1), DLMS_DATA_TYPE_DATETIME, &tmp)) != 0)
                {
                    CGXDLMSVariant_d(&tmp);
                    return ret;
                }
                CGXDateTime end = tmp.dateTime;

                Pair t_p;
                Pair_(&t_p, sizeof(CGXDateTime), sizeof(CGXDateTime),
                      NULL, NULL, NULL, NULL, &start, &end);

                Vector_push_back(&p->m_CommunicationWindow, &t_p);

                Pair_d(&t_p);
                CGXDLMSVariant_d(&tmp);
            }
        }
    }
    else if (e_index == 5)
    {
        p->m_RandomisationStartInterval = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 6)
    {
        p->m_NumberOfRetries = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 7)
    {
        p->m_RepetitionDelay = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

Vector* CGXDLMSPushSetup_GetPushObjectList(CGXDLMSPushSetup* p)
{
    return &(p->m_PushObjectList);
}

Vector* CGXDLMSPushSetup_GetCommunicationWindow(CGXDLMSPushSetup* p)
{
    return &(p->m_CommunicationWindow);
}

/**
 To avoid simultaneous network connections of a lot of devices at ex-actly
    the same point in time, a randomisation interval in seconds can be defined.
    This means that the push operation is not started imme-diately at the
    beginning of the first communication window but started randomly delayed.
*/
int CGXDLMSPushSetup_GetRandomisationStartInterval(CGXDLMSPushSetup* p)
{
    return p->m_RandomisationStartInterval;
}
void CGXDLMSPushSetup_SetRandomisationStartInterval(CGXDLMSPushSetup* p, int value)
{
    p->m_RandomisationStartInterval = value;
}
/**
 The maximum number of retrials in case of unsuccessful push at-tempts. After a successful push no further push attempts are made until the push setup is triggered again.
    A value of 0 means no repetitions, i.e. only the initial connection at-tempt is made.
*/

int CGXDLMSPushSetup_GetNumberOfRetries(CGXDLMSPushSetup* p)
{
    return p->m_NumberOfRetries;
}
void CGXDLMSPushSetup_SetNumberOfRetries(CGXDLMSPushSetup* p, int value)
{
    p->m_NumberOfRetries = value;
}

int CGXDLMSPushSetup_GetRepetitionDelay(CGXDLMSPushSetup* p)
{
    return p->m_RepetitionDelay;
}

void CGXDLMSPushSetup_SetRepetitionDelay(CGXDLMSPushSetup* p, int value)
{
    p->m_RepetitionDelay = value;
}

void CGXDLMSPushSetup_d(CGXDLMSPushSetup* p)
{
    String_d(&p->m_Destination);
    Vector_d(&p->m_PushObjectList);
    Vector_d(&p->m_CommunicationWindow);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
