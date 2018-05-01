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

#include "../include/GXDLMSNotify.h"
#include "../include/Pair.h"

void CGXDLMSNotify_SetCipher(CGXDLMSNotify *p, CGXCipher* value)
{
    p->m_Settings.m_Cipher = value;
}

CGXDLMSSettings* CGXDLMSNotify_GetSettings(CGXDLMSNotify *p)
{
    return &p->m_Settings;
}

void CGXDLMSNotify_(CGXDLMSNotify *p, bool useLogicalNameReferencing,
    int clientAddress,
    int serverAddress,
    DLMS_INTERFACE_TYPE interfaceType)
{
    CGXDLMSSettings_(&p->m_Settings, true);
    p->m_Settings.m_UseLogicalNameReferencing = useLogicalNameReferencing;
    p->m_Settings.m_ClientAddress = clientAddress;
    p->m_Settings.m_ServerAddress = serverAddress;
    p->m_Settings.m_InterfaceType = interfaceType;
}

CGXDLMSObjectCollection* CGXDLMSNotify_GetObjects(CGXDLMSNotify *p)
{
    return CGXDLMSSettings_GetObjects(&p->m_Settings);
}

CGXDLMSLimits* CGXDLMSNotify_GetLimits(CGXDLMSNotify *p)
{
    return CGXDLMSSettings_GetLimits(&p->m_Settings);
}

int CGXDLMSNotify_GetMaxPduSize(CGXDLMSNotify *p)
{
    return p->m_Settings.m_MaxReceivePDUSize;
}

void CGXDLMSNotify_SetMaxReceivePDUSize(CGXDLMSNotify *p, int value)
{
    CGXDLMSSettings_SetMaxReceivePDUSize(&p->m_Settings, value);
}

bool CGXDLMSNotify_GetUseLogicalNameReferencing(CGXDLMSNotify *p)
{
    return p->m_Settings.m_UseLogicalNameReferencing;
}

void CGXDLMSNotify_SetUseLogicalNameReferencing(CGXDLMSNotify *p, bool value)
{
    p->m_Settings.m_UseLogicalNameReferencing = value;
}

DLMS_PRIORITY CGXDLMSNotify_GetPriority(CGXDLMSNotify *p)
{
    return p->m_Settings.m_Priority;
}

void CGXDLMSNotify_SetPriority(CGXDLMSNotify *p, DLMS_PRIORITY value)
{
    p->m_Settings.m_Priority = value;
}

DLMS_SERVICE_CLASS CGXDLMSNotify_GetServiceClass(CGXDLMSNotify *p)
{
    return p->m_Settings.m_ServiceClass;
}

void CGXDLMSNotify_SetServiceClass(CGXDLMSNotify *p, DLMS_SERVICE_CLASS value)
{
    p->m_Settings.m_ServiceClass = value;
}

unsigned char CGXDLMSNotify_GetInvokeID(CGXDLMSNotify *p)
{
    return p->m_Settings.m_InvokeID;
}

void CGXDLMSNotify_SetInvokeID(CGXDLMSNotify *p, unsigned char value)
{
    p->m_Settings.m_InvokeID = value;
}

int CGXDLMSNotify_GetData(CGXDLMSNotify *p, CGXByteBuffer* reply, CGXReplyData* data)
{
    return CGXDLMS_GetData(&p->m_Settings, reply, data);
}

int CGXDLMSNotify_AddData(CGXDLMSNotify *p,
    CGXDLMSObject* obj,
    unsigned char index,
    CGXByteBuffer* buff)
{
    int ret;
    DLMS_DATA_TYPE dt;

    CGXDLMSValueEventArg e;
    CGXDLMSValueEventArg_1(&e, NULL, obj, index);

    if ((ret = obj->GetValue(obj, &p->m_Settings, &e)) != 0)
    {
        CGXDLMSValueEventArg_d(&e);
        return ret;
    }
    if ((ret = obj->GetDataType(obj, index, &dt)) != 0)
    {
        CGXDLMSValueEventArg_d(&e);
        return ret;
    }
    if (dt == DLMS_DATA_TYPE_ARRAY)
    {
        CGXByteBuffer_Set_1(buff, CGXDLMSValueEventArg_GetValue(&e)->st.un.byteArr,
                            CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetValue(&e)));

        CGXDLMSValueEventArg_d(&e);
        return 0;
    }
    if (dt == DLMS_DATA_TYPE_NONE)
    {
        dt = CGXDLMSValueEventArg_GetValue(&e)->st.vt;
    }

    ret = GXHelpers_SetData(buff, CGXDLMSValueEventArg_GetValue(&e)->st.vt,
                            CGXDLMSValueEventArg_GetValue(&e));

    CGXDLMSValueEventArg_d(&e);
    return ret;
}

int CGXDLMSNotify_GenerateDataNotificationMessages_1(CGXDLMSNotify *p,
    struct tm* time,
    CGXByteBuffer* data,
    Vector* reply)
{
    int ret;
    if (CGXDLMSNotify_GetUseLogicalNameReferencing(p))
    {
        CGXDLMSLNParameters para;
        CGXDLMSLNParameters_(&para, &p->m_Settings, 0, DLMS_COMMAND_DATA_NOTIFICATION,
                             0, NULL, data, 0xff);

        para.m_Time = time;

        ret = CGXDLMS_GetLnMessages(&para, reply);

        //CGXDLMSLNParameters_d(&para);
    }
    else
    {
        CGXDLMSSNParameters para;
        CGXDLMSSNParameters_(&para, &p->m_Settings, DLMS_COMMAND_DATA_NOTIFICATION,
                             1, 0, data, NULL);

        ret = CGXDLMS_GetSnMessages(&para, reply);

        //CGXDLMSSNParameters_d(&para);
    }
    return ret;
}

int CGXDLMSNotify_GenerateDataNotificationMessages_2(
     CGXDLMSNotify *p,
     struct tm* date,
     Vector* objects, // std::vector<std::pair<CGXDLMSObject*, unsigned char> >& objects
     Vector* reply)  // std::vector<CGXByteBuffer>& reply
{
    CGXByteBuffer buff;
    CGXByteBuffer_1(&buff);

    CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
    GXHelpers_SetObjectCount((unsigned long) Vector_size(objects), &buff);

    // std_vector<std_pair<CGXDLMSObject*, unsigned char> >
    for (unsigned int i = Vector_begin(objects); i != Vector_end(objects); ++i)
    {
        Pair* it = Vector_at(objects, i);

        CGXDLMSObject* it_first = *((CGXDLMSObject**) it->first);
        unsigned char it_second = *((unsigned char*) it->second);

        CGXDLMSNotify_AddData(p, it_first, it_second, &buff);
    }

    int ret = CGXDLMSNotify_GenerateDataNotificationMessages_1(p, date, &buff, reply);

    CGXByteBuffer_d(&buff);
    return ret;
}

int CGXDLMSNotify_GeneratePushSetupMessages(
     CGXDLMSNotify *p,
     struct tm* date,
     CGXDLMSPushSetup* push,
     Vector* reply) // std::vector<CGXByteBuffer>&
{
    if (push == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    CGXByteBuffer buff;
    CGXByteBuffer_1(&buff);

    CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
    GXHelpers_SetObjectCount((unsigned long) Vector_size(CGXDLMSPushSetup_GetPushObjectList(push)),
                             &buff);

    // std_vector<std_pair<CGXDLMSObject*, CGXDLMSCaptureObject> >
    for (unsigned int i = Vector_begin(CGXDLMSPushSetup_GetPushObjectList(push));
            i != Vector_end(CGXDLMSPushSetup_GetPushObjectList(push)); ++i)
    {
        Pair* it = Vector_at(CGXDLMSPushSetup_GetPushObjectList(push), i);

        CGXDLMSObject* it_first = *((CGXDLMSObject**) it->first);
        CGXDLMSCaptureObject* it_second = it->second;

        CGXDLMSNotify_AddData(p, it_first,
                              it_second->m_AttributeIndex, &buff);
    }

    int ret = CGXDLMSNotify_GenerateDataNotificationMessages_1(p, date, &buff, reply);

    CGXByteBuffer_d(&buff);
    return ret;
}

int CGXDLMSNotify_ParsePush(
     CGXDLMSNotify *p,
     Vector* data,   // std::vector<CGXDLMSVariant>& data
     Vector* items) // std::vector<std::pair<CGXDLMSObject*, unsigned char> >& items
{
    CGXDLMSObject *obj;

    int index, pos, ret;
    DLMS_DATA_TYPE dt;

    CGXDLMSVariant ln;
    CGXDLMSVariant_1(&ln);

    // std_vector<CGXDLMSVariant>
    Vector* vec = &(((CGXDLMSVariant*) Vector_at(data, 0))->Arr);
    for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
    {
        CGXDLMSVariant* it = Vector_at(vec, i);

        int classID = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 0)) & 0xFFFF;
        if (classID > 0)
        {
            CGXDLMSVariant_Clear(&ln);
            if ((ret = CGXDLMSClient_ChangeType_2(Vector_at(&it->Arr, 1),
                                       DLMS_DATA_TYPE_OCTET_STRING, &ln)) != 0)
            {
                CGXDLMSVariant_d(&ln);
                return ret;
            }
            obj = CGXDLMSObjectCollection_FindByLN_1(CGXDLMSNotify_GetObjects(p),
                                                    (DLMS_OBJECT_TYPE)classID, &(ln.strVal));
            if (obj == NULL)
            {
                obj = CGXDLMSObjectFactory_CreateObject_2((DLMS_OBJECT_TYPE)classID, ln.strVal);
                CGXDLMSObjectCollection_push_back(CGXDLMSNotify_GetObjects(p), &obj);
            }

            unsigned char t_tmp = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 2));

            Pair pair;
            Pair_(&pair, sizeof(CGXDLMSObject*), sizeof(unsigned char),
                  NULL, NULL, NULL, NULL, &obj, &t_tmp);

            Vector_push_back(items, &pair);

            Pair_d(&pair);
        }
    }

    CGXDLMSVariant_d(&ln);

    CGXDLMSVariant tmp, value;
    CGXDLMSVariant_1(&tmp);
    CGXDLMSVariant_1(&value);

    pos = 0;
    // std_vector<std_pair<CGXDLMSObject*, unsigned char> >
    for (unsigned int i = Vector_begin(items); i != Vector_end(items); ++i)
    {
        Pair* it = Vector_at(items, i);

        obj = *((CGXDLMSObject**) it->first);

        CGXDLMSVariant_copy_1(&value, Vector_at(data, pos));

        ++pos;
        index = *((unsigned char*) it->second);
        if (value.st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            ret = obj->GetUIDataType(obj, index, &dt);
            if (dt != DLMS_DATA_TYPE_NONE)
            {
                CGXDLMSVariant_copy_1(&tmp, &value);
                if ((ret = CGXDLMSClient_ChangeType_2(&tmp, dt, &value)) != 0)
                {
                    CGXDLMSVariant_d(&tmp);
                    CGXDLMSVariant_d(&value);
                    return ret;
                }
            }
        }

        CGXDLMSValueEventArg e;
        CGXDLMSValueEventArg_1(&e, NULL, obj, index);

        CGXDLMSValueEventArg_SetValue(&e, &value);
        obj->SetValue(obj, &p->m_Settings, &e);

        CGXDLMSValueEventArg_d(&e);
    }

    CGXDLMSVariant_d(&tmp);
    CGXDLMSVariant_d(&value);

    return 0;
}

void CGXDLMSNotify_d(CGXDLMSNotify *p)
{
    CGXDLMSSettings_d(&p->m_Settings);
}
