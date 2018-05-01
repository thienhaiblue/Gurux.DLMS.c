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
#include "../include/GXDLMSAssociationShortName.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSServer.h"
#include "../include/Optimize.h"

static void CGXDLMSAssociationShortName__(CGXDLMSAssociationShortName* p)
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	 p->GetAttributeCount = CGXDLMSAssociationShortName_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSAssociationShortName_GetMethodCount;
	 p->GetValue = CGXDLMSAssociationShortName_GetValue;
	 p->SetValue = CGXDLMSAssociationShortName_SetValue;
	 p->Invoke = CGXDLMSAssociationShortName_Invoke;

    // Override CGXDLMSObject
	 p->d = CGXDLMSAssociationShortName_d;
	 p->SetDataType = CGXDLMSObject_SetDataType;
	 p->GetDataType = CGXDLMSAssociationShortName_GetDataType;
	 p->GetUIDataType = CGXDLMSObject_GetUIDataType;
	 p->GetValues = CGXDLMSAssociationShortName_GetValues;
	 p->GetAttributeIndexToRead = CGXDLMSAssociationShortName_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

	 CGXDLMSObjectCollection_(&p->m_ObjectList);
	 String_(&p->m_SecuritySetupReference);
	 CGXByteBuffer_1(&p->m_Secret);

}
static int CGXDLMSAssociationShortName_GetAccessRights(CGXDLMSAssociationShortName *p, CGXDLMSObject* pObj, CGXDLMSServer* server, CGXByteBuffer* data)
{
    int ret, cnt = pObj->GetAttributeCount(pObj);

    CGXDLMSVariant ln;
    CGXDLMSVariant_20(&ln, pObj->m_SN);

    CGXDLMSValueEventArg e;
    CGXDLMSValueEventArg_1(&e, server, pObj, 0);

    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
    CGXByteBuffer_SetUInt8_1(data, 3);
    GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT16, &ln);
    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    GXHelpers_SetObjectCount(cnt, data);

    CGXDLMSVariant_d(&ln);

    CGXDLMSVariant empty, index, access;
    CGXDLMSVariant_1(&empty);
    CGXDLMSVariant_1(&index);
    CGXDLMSVariant_1(&access);

    for (int pos = 0; pos != cnt; ++pos)
    {
        e.m_Index = pos + 1;
        //index = pos + 1;
        CGXDLMSVariant_copy_12(&index, pos + 1);

        if (server != NULL)
        {
            // access = server->GetAttributeAccess(&e);
            CGXDLMSVariant_copy_12(&access, server->GetAttributeAccess(server, &e));
        }
        else
        {
            //access = DLMS_ACCESS_MODE_READ_WRITE;
            CGXDLMSVariant_copy_12(&access, DLMS_ACCESS_MODE_READ_WRITE);
        }
        //attribute_access_item
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(data, 3);
        if ((ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_INT8, &index)) != 0 ||
            (ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_ENUM, &access)) != 0 ||
            (ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_NONE, &empty)) != 0)
        {
            CGXDLMSValueEventArg_d(&e);
            CGXDLMSVariant_d(&empty);
            CGXDLMSVariant_d(&index);
            CGXDLMSVariant_d(&access);
            return ret;
        }
    }

    cnt = pObj->GetMethodCount(pObj);

    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    GXHelpers_SetObjectCount(cnt, data);
    for (int pos = 0; pos != cnt; ++pos)
    {
        e.m_Index = pos + 1;
        CGXDLMSVariant_copy_12(&index, pos + 1);
        if (server != NULL)
        {
            //access = server->GetMethodAccess(&e);
            CGXDLMSVariant_copy_12(&access, server->GetMethodAccess(server, &e));
        }
        else
        {
            //access = DLMS_METHOD_ACCESS_MODE_ACCESS;
            CGXDLMSVariant_copy_12(&access, DLMS_METHOD_ACCESS_MODE_ACCESS);
        }
        //attribute_access_item
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(data, 2);
        GXHelpers_SetData(data, DLMS_DATA_TYPE_INT8, &index);
        GXHelpers_SetData(data, DLMS_DATA_TYPE_ENUM, &access);
    }

    CGXDLMSValueEventArg_d(&e);
    CGXDLMSVariant_d(&empty);
    CGXDLMSVariant_d(&index);
    CGXDLMSVariant_d(&access);
    return DLMS_ERROR_CODE_OK;
}

static void CGXDLMSAssociationShortName_UpdateAccessRights(CGXDLMSAssociationShortName *p, CGXDLMSVariant* buff)
{
    Vector *temp = &buff->Arr;
    //for (std_vector<CGXDLMSVariant>_iterator access = buff.Arr.begin(); access != buff.Arr.end(); ++access)
    for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
    {
        CGXDLMSVariant* access = Vector_at(temp, i);

        //int sn = access->Arr[0].ToInteger();
        int sn = CGXDLMSVariant_ToInteger(Vector_at(&access->Arr, 0));
        CGXDLMSObject* pObj = CGXDLMSObjectCollection_FindBySN(&p->m_ObjectList, sn);
        if (pObj != NULL)
        {
            Vector *temp1 = &((CGXDLMSVariant*)Vector_at(&access->Arr, 1))->Arr;
            //for (std_vector<CGXDLMSVariant>_iterator attributeAccess = access->Arr[1].Arr.begin();
                //attributeAccess != access->Arr[1].Arr.end(); ++attributeAccess)
            for (unsigned int j = Vector_begin(temp1); j != Vector_end(temp1); ++j)
            {
                CGXDLMSVariant* attributeAccess = Vector_at(temp1, j);

                //int id = attributeAccess->Arr[0].ToInteger();
                //int tmp = attributeAccess->Arr[1].ToInteger();
                int id = CGXDLMSVariant_ToInteger(Vector_at(&attributeAccess->Arr, 0));
                int tmp = CGXDLMSVariant_ToInteger(Vector_at(&attributeAccess->Arr, 1));
                CGXDLMSObject_SetAccess(pObj, id, (DLMS_ACCESS_MODE)tmp);
            }

            Vector *temp2 = &((CGXDLMSVariant*)Vector_at(&access->Arr, 2))->Arr;
            //for (std_vector<CGXDLMSVariant>_iterator methodAccess = access->Arr[2].Arr.begin();
              //  methodAccess != access->Arr[2].Arr.end(); ++methodAccess)
            for (unsigned int j = Vector_begin(temp2); j != Vector_end(temp2); ++j)
            {
                CGXDLMSVariant* methodAccess = Vector_at(temp2, j);

                //int id = methodAccess->Arr[0].ToInteger();
                //int tmp = methodAccess->Arr[1].ToInteger();
                int id = CGXDLMSVariant_ToInteger(Vector_at(&methodAccess->Arr, 0));
                int tmp = CGXDLMSVariant_ToInteger(Vector_at(&methodAccess->Arr, 1));
                CGXDLMSObject_SetMethodAccess(pObj, id, (DLMS_METHOD_ACCESS_MODE)tmp);
            }
        }
    }
}

//Constructor.
void CGXDLMSAssociationShortName_(CGXDLMSAssociationShortName *p)
{
	CGXDLMSObject_2((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME);

	CGXDLMSAssociationShortName__(p);

    GXHelpers_SetLogicalName_2("0.0.40.0.0.255", p->m_LN);
    CGXByteBuffer_AddString_2(&p->m_Secret, "Gurux");
    p->m_SN = 0xFA00;
    p->m_Version = 2;
}

CGXDLMSObjectCollection* CGXDLMSAssociationShortName_GetObjectList(CGXDLMSAssociationShortName *p)
{
    return &p->m_ObjectList;
}

CGXByteBuffer* CGXDLMSAssociationShortName_GetSecret(CGXDLMSAssociationShortName *p)
{
    return &p->m_Secret;
}
void CGXDLMSAssociationShortName_SetSecret(CGXDLMSAssociationShortName *p, CGXByteBuffer* value)
{
	CGXByteBuffer_copy(&p->m_Secret, value);
}

String* CGXDLMSAssociationShortName_GetSecuritySetupReference(CGXDLMSAssociationShortName *p)
{
    return &p->m_SecuritySetupReference;
}
void CGXDLMSAssociationShortName_SetSecuritySetupReference(CGXDLMSAssociationShortName *p, String* value)
{
	String_copy_1(&p->m_SecuritySetupReference, value);
}


void CGXDLMSAssociationShortName_GetValues(
    CGXDLMSAssociationShortName *p,
    Vector* values)//std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String ln = CGXDLMSObjectCollection_ToString(&p->m_ObjectList);

    Vector_push_back(values, &ln);

    String_d(&ln);

    Vector_push_back_Str_3(values, "");

    Vector_push_back(values, &p->m_SecuritySetupReference);
}

void CGXDLMSAssociationShortName_GetAttributeIndexToRead(
    CGXDLMSAssociationShortName *p,
    Vector* attributes)//std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //ObjectList is static and read only once.
    if (!CGXDLMSAssociationShortName_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    if (p->m_Version > 1)
    {
        //AccessRightsList is static and read only once.
        if (!CGXDLMSAssociationShortName_IsRead(p, 3))
        {
            tmp = 3;
            Vector_push_back(attributes, &tmp);
        }
        //SecuritySetupReference is static and read only once.
        if (!CGXDLMSAssociationShortName_IsRead(p, 4))
        {
            tmp = 4;
            Vector_push_back(attributes, &tmp);
        }
    }
}

// Returns amount of attributes.
int CGXDLMSAssociationShortName_GetAttributeCount(CGXDLMSAssociationShortName *p)
{
    if (p->m_Version < 2)
    {
        return 2;
    }
    return 4;
}

// Returns amount of methods.
int CGXDLMSAssociationShortName_GetMethodCount(CGXDLMSAssociationShortName *p)
{
    return 8;
}

int CGXDLMSAssociationShortName_GetDataType(
    CGXDLMSAssociationShortName *p,
    int index,
    DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns SN Association View.
int CGXDLMSAssociationShortName_GetObjects(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e,
    CGXByteBuffer* data)
{
    unsigned long pos = 0;
    int ret;
    //Add count only for first time.
    if (settings->m_Index == 0)
    {
        settings->m_Count = (unsigned short)CGXDLMSObjectCollection_size(&p->m_ObjectList);
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount((unsigned long)CGXDLMSObjectCollection_size(&p->m_ObjectList), data);
    }
    //for (CGXDLMSObjectCollection_iterator it = p->m_ObjectList.begin(); it != p->m_ObjectList.end(); ++it)
    for (unsigned int i = CGXDLMSObjectCollection_begin(&p->m_ObjectList); i != CGXDLMSObjectCollection_end(&p->m_ObjectList); ++i)
    {
        CGXDLMSObject** it = CGXDLMSObjectCollection_at(&p->m_ObjectList, i);
        ++pos;
        if (!(pos <= settings->m_Index))
        {
            CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(data, 4);//Count
            //CGXDLMSVariant type = (*it)->GetObjectType();
            //CGXDLMSVariant version = (*it)->GetVersion();
            //CGXDLMSVariant sn = (*it)->GetShortName();
            //CGXDLMSVariant ln((*it)->m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);

            CGXDLMSVariant type, version, sn, ln;
            CGXDLMSVariant_10(&type, (*it)->m_ObjectType);
            CGXDLMSVariant_20(&version, (*it)->m_Version);
            CGXDLMSVariant_20(&sn, (*it)->m_SN);
            CGXDLMSVariant_18(&ln, (*it)->m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);


            if ((ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_INT16, &sn)) != 0 || //base address.
                (ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT16, &type)) != 0 || //ClassID
                (ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &version)) != 0 || //Version
                (ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &ln)) != 0) //LN
            {
                CGXDLMSVariant_d(&type);
                CGXDLMSVariant_d(&version);
                CGXDLMSVariant_d(&sn);
                CGXDLMSVariant_d(&ln);
                return ret;
            }
            if (settings->m_Server)
            {
                settings->m_Index = settings->m_Index + 1;
                //If PDU is full.
                if (!e->m_SkipMaxPduSize && data->m_Size >= settings->m_MaxReceivePDUSize)
                {
                    CGXDLMSVariant_d(&type);
                    CGXDLMSVariant_d(&version);
                    CGXDLMSVariant_d(&sn);
                    CGXDLMSVariant_d(&ln);
                    break;
                }
            }

            CGXDLMSVariant_d(&type);
            CGXDLMSVariant_d(&version);
            CGXDLMSVariant_d(&sn);
            CGXDLMSVariant_d(&ln);
        }
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSAssociationShortName_Invoke(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e)
{
    // Check reply_to_HLS_authentication
    if (e->m_Index == 8)
    {
        int ret;
        unsigned long ic = 0;
        CGXByteBuffer* readSecret;
        if (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_GMAC)
        {
            unsigned char ch;
            readSecret = CGXDLMSSettings_GetSourceSystemTitle(settings);

            CGXByteBuffer bb;
            CGXByteBuffer_1(&bb);

            CGXByteBuffer_Set_1(&bb, CGXDLMSValueEventArg_GetParameters(e)->st.un.byteArr, CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetParameters(e)));
            if ((ret = CGXByteBuffer_GetUInt8_1(&bb, &ch)) != 0)
            {
                CGXByteBuffer_d(&bb);
                return ret;
            }
            if ((ret = CGXByteBuffer_GetUInt32_1(&bb, &ic)) != 0)
            {
                CGXByteBuffer_d(&bb);
                return ret;
            }

            CGXByteBuffer_d(&bb);
        }
        else
        {
            readSecret = &p->m_Secret;
        }

        CGXByteBuffer serverChallenge;
        CGXByteBuffer_1(&serverChallenge);

        if ((ret = CGXSecure_Secure(settings, settings->m_Cipher, ic,
                           CGXDLMSSettings_GetStoCChallenge(settings), readSecret, &serverChallenge)) != 0)
        {
            CGXByteBuffer_d(&serverChallenge);
            return ret;
        }

        if (CGXByteBuffer_Compare(&serverChallenge,
                                  CGXDLMSValueEventArg_GetParameters(e)->st.un.byteArr,
                                  CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetParameters(e))))
        {
            if (settings->m_Authentication == DLMS_AUTHENTICATION_HIGH_GMAC)
            {
                readSecret = CGXCipher_GetSystemTitle(settings->m_Cipher);
                ic = settings->m_Cipher->m_FrameCounter;
            }
            else
            {
                readSecret = &p->m_Secret;
            }
            CGXByteBuffer_Clear(&serverChallenge);
            if ((ret = CGXSecure_Secure(settings,
                settings->m_Cipher,
                ic,
                CGXDLMSSettings_GetCtoSChallenge(settings),
                readSecret,
                &serverChallenge)) != 0)
            {
                CGXByteBuffer_d(&serverChallenge);
                return ret;
            }

            CGXDLMSValueEventArg_SetValue_2(e, &serverChallenge);

            settings->m_Connected = true;
        }
        else
        {
            settings->m_Connected = false;

            CGXByteBuffer_d(&serverChallenge);
            return 0;
        }

        CGXByteBuffer_d(&serverChallenge);
    }
    else
    {
        e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    }
    return 0;
}

int CGXDLMSAssociationShortName_GetValue(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    else if (e_index == 2)
    {
        e->m_ByteArray = true;

        CGXByteBuffer buff;
        CGXByteBuffer_1(&buff);

        int ret = CGXDLMSAssociationShortName_GetObjects(p, settings, e, &buff);
        
        CGXDLMSValueEventArg_SetValue_2(e, &buff);

        CGXByteBuffer_d(&buff);
        return ret;
    }
    else if (e_index == 3)
    {
        e->m_ByteArray = true;
        int ret;
        //Add count
        unsigned long cnt = (unsigned long)CGXDLMSObjectCollection_size(&p->m_ObjectList);

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        GXHelpers_SetObjectCount(cnt, &data);

        //for (std_vector<CGXDLMSObject*>_iterator it = p->m_ObjectList.begin(); it != p->m_ObjectList.end(); ++it)
        for (unsigned int i = CGXDLMSObjectCollection_begin(&p->m_ObjectList); i != CGXDLMSObjectCollection_end(&p->m_ObjectList); ++i)
        {
            CGXDLMSObject** it = CGXDLMSObjectCollection_at(&p->m_ObjectList, i);

            if ((ret = CGXDLMSAssociationShortName_GetAccessRights(p, *it, e->m_Server, &data)) != 0)
            {
                CGXByteBuffer_d(&data);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
    }
    else if (e_index == 4)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_22(&tmp, p->m_SecuritySetupReference);

        GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &tmp);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&tmp);
        CGXByteBuffer_d(&data);        
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSAssociationShortName_SetValue(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        //p->m_ObjectList.clear();
        CGXDLMSObjectCollection_clear(&p->m_ObjectList);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);

            //for (std_vector<CGXDLMSVariant>_iterator item = e.GetValue().Arr.begin(); item != e.GetValue().Arr.end(); ++item)
            for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
            {
                CGXDLMSVariant* item = Vector_at(temp, i);

                int sn = CGXDLMSVariant_ToInteger(Vector_at(&(item->Arr), 0));

                CGXDLMSObject* pObj = CGXDLMSObjectCollection_FindBySN(CGXDLMSSettings_GetObjects(settings), sn);

                if (pObj == NULL)
                {
                    DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&(item->Arr), 1));
                    int version = CGXDLMSVariant_ToInteger(Vector_at(&(item->Arr), 2));

                    String ln;
                    String_(&ln);

                    GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&(item->Arr), 3))->st.un.byteArr, &ln);
                    pObj = CGXDLMSObjectFactory_CreateObject_2(type, ln);
                    if (pObj != NULL)
                    {
                        pObj->m_SN = sn;
                        pObj->m_Version = version;
                    }

                    String_d(&ln);
                }
                if (pObj != NULL)
                {
                    CGXDLMSObjectCollection_push_back(&p->m_ObjectList, &pObj);
                }
            }
        }
    }
    else if (e_index == 3)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_NONE)
        {
            //for (std_vector<CGXDLMSObject*>_iterator it = p->m_ObjectList.begin(); it != p->m_ObjectList.end(); ++it)
            for (unsigned int i = CGXDLMSObjectCollection_begin(&p->m_ObjectList);
                    i != CGXDLMSObjectCollection_end(&p->m_ObjectList); ++i)
            {

                CGXDLMSObject** it = CGXDLMSObjectCollection_at(&p->m_ObjectList, i);

                for (int pos = 1; pos != (*it)->GetAttributeCount(*it); ++pos)
                {
                    CGXDLMSObject_SetAccess(*it, pos, DLMS_ACCESS_MODE_NONE);
                }
            }
        }
        else
        {
            CGXDLMSAssociationShortName_UpdateAccessRights(p, CGXDLMSValueEventArg_GetValue(e));
        }
    }
    else if (e_index == 4)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_STRING)
        {
            p->m_SecuritySetupReference = CGXDLMSVariant_ToString(CGXDLMSValueEventArg_GetValue(e));
        }
        else
        {
            int ret;

            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            if ((ret = CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e),
                                                DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                return ret;
            }

            String_d(&p->m_SecuritySetupReference);
            p->m_SecuritySetupReference = CGXDLMSVariant_ToString(&tmp);

            CGXDLMSVariant_d(&tmp);
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSAssociationShortName_d(CGXDLMSAssociationShortName *p)
{
    CGXDLMSObjectCollection_d(&p->m_ObjectList);
    String_d(&p->m_SecuritySetupReference);
    CGXByteBuffer_d(&p->m_Secret);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
