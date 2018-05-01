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
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSServer.h"
#include "../include/Optimize.h"

static void CGXDLMSAssociationLogicalName__(CGXDLMSAssociationLogicalName* p)
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	 p->GetAttributeCount = CGXDLMSAssociationLogicalName_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSAssociationLogicalName_GetMethodCount;
	 p->GetValue = CGXDLMSAssociationLogicalName_GetValue;
	 p->SetValue = CGXDLMSAssociationLogicalName_SetValue;
	 p->Invoke = CGXDLMSAssociationLogicalName_Invoke;

    // Override CGXDLMSObject
	 p->d = CGXDLMSAssociationLogicalName_d;
	 p->SetDataType = CGXDLMSObject_SetDataType;
	 p->GetDataType = CGXDLMSAssociationLogicalName_GetDataType;
	 p->GetUIDataType = CGXDLMSObject_GetUIDataType;
	 p->GetValues = CGXDLMSAssociationLogicalName_GetValues;
	 p->GetAttributeIndexToRead = CGXDLMSAssociationLogicalName_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

     CGXDLMSObjectCollection_(&p->m_ObjectList);
     CGXApplicationContextName_(&p->m_ApplicationContextName);
     CGXDLMSContextType_(&p->m_XDLMSContextInfo);
     CGXAuthenticationMechanismName_(&p->m_AuthenticationMechanismName);
     CGXByteBuffer_1(&p->m_Secret);
     String_(&p->m_SecuritySetupReference);
     Vector_(&p->m_UserList, sizeof(Pair), Pair_v_c, Pair_v_d); // std::vector<std::pair<unsigned char, std::string>>

     unsigned char tmp1 = 0;
     String tmp2;
     String_(&tmp2);
     Pair_(&p->m_CurrentUser, sizeof(unsigned char), sizeof(String),
           NULL, NULL, String_v_c, String_v_d, &tmp1, &tmp2); // std::pair<unsigned char, std::string>
     String_d(&tmp2);
}
static void CGXDLMSAssociationLogicalName_UpdateAccessRights(
    CGXDLMSAssociationLogicalName* p,
    CGXDLMSObject* pObj,
    CGXDLMSVariant data)
{
    // std::vector<CGXDLMSVariant >
    Vector* vec = &(((CGXDLMSVariant*) Vector_at(&data.Arr, 0))->Arr);
    for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
    {
        CGXDLMSVariant* it = Vector_at(vec, i);

        // Vector_at(&it->Arr, 0)
        int id = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 0));
        DLMS_ACCESS_MODE mode = (DLMS_ACCESS_MODE) CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 1));
        CGXDLMSObject_SetAccess(pObj, id, mode);
    }

    // std::vector<CGXDLMSVariant >
    vec = &(((CGXDLMSVariant*) Vector_at(&data.Arr, 1))->Arr);
    for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
    {
        CGXDLMSVariant* it = Vector_at(vec, i);

        int id = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 0));
        DLMS_METHOD_ACCESS_MODE mode = (DLMS_METHOD_ACCESS_MODE) CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 1));
        CGXDLMSObject_SetMethodAccess(pObj, id, mode);
    }
}

static int CGXDLMSAssociationLogicalName_GetAccessRights(
    CGXDLMSAssociationLogicalName* p,
    CGXDLMSObject* pItem,
    CGXDLMSServer* server,
    CGXByteBuffer* data)
{
    int ret;
    int cnt = pItem->GetAttributeCount(pItem);

    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
    CGXByteBuffer_SetUInt8_1(data, 2);
    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    GXHelpers_SetObjectCount(cnt, data);

    CGXDLMSValueEventArg e;
    CGXDLMSValueEventArg_1(&e, server, pItem, 0);

    CGXDLMSVariant index, access, empty;
    CGXDLMSVariant_1(&index);
    CGXDLMSVariant_1(&access);
    CGXDLMSVariant_1(&empty);

    for (int pos = 0; pos != cnt; ++pos)
    {
        e.m_Index = pos + 1;
        CGXDLMSVariant_copy_12(&index, pos + 1);
        if (server != NULL)
        {
            CGXDLMSVariant_copy_12(&access, server->GetAttributeAccess(server, &e));
        }
        else
        {
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
            CGXDLMSVariant_d(&index);
            CGXDLMSVariant_d(&access);
            CGXDLMSVariant_d(&empty);
            return ret;
        }
    }
    cnt = pItem->GetMethodCount(pItem);
    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    GXHelpers_SetObjectCount(cnt, data);
    for (int pos = 0; pos != cnt; ++pos)
    {
        e.m_Index = pos + 1;
        CGXDLMSVariant_copy_12(&index, pos + 1);
        if (server != NULL)
        {
            CGXDLMSVariant_copy_12(&access, server->GetMethodAccess(server, &e));
        }
        else
        {
            CGXDLMSVariant_copy_12(&access, DLMS_METHOD_ACCESS_MODE_ACCESS);
        }
        //attribute_access_item
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(data, 2);
        GXHelpers_SetData(data, DLMS_DATA_TYPE_INT8, &index);
        GXHelpers_SetData(data, DLMS_DATA_TYPE_ENUM, &access);
    }

    CGXDLMSValueEventArg_d(&e);
    CGXDLMSVariant_d(&index);
    CGXDLMSVariant_d(&access);
    CGXDLMSVariant_d(&empty);
    return DLMS_ERROR_CODE_OK;
}


// Updates secret.
int CGXDLMSAssociationLogicalName_UpdateSecret(
    CGXDLMSAssociationLogicalName *p,
    CGXDLMSClient* client,
    Vector* reply)//std::vector<CGXByteBuffer>&
{
    if (p->m_AuthenticationMechanismName.m_MechanismId == DLMS_AUTHENTICATION_NONE)
    {
#if defined(_WIN32) || defined(_WIN64)//Windows
        DLMSPort_printf("Invalid authentication level in MechanismId.\n");
#endif
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (p->m_AuthenticationMechanismName.m_MechanismId == DLMS_AUTHENTICATION_HIGH_GMAC)
    {
#if defined(_WIN32) || defined(_WIN64)//Windows
        DLMSPort_printf("HighGMAC secret is updated using Security setup.\n");
#endif
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (p->m_AuthenticationMechanismName.m_MechanismId == DLMS_AUTHENTICATION_LOW)
    {
        return CGXDLMSClient_Write_3(client, (CGXDLMSObject*) p, 7, reply);
    }
    //Action is used to update High authentication password.
    CGXDLMSVariant tmp;
    CGXDLMSVariant_copy_4(&tmp, &p->m_Secret);

    int ret = CGXDLMSClient_Method_1(client, (CGXDLMSObject*) p, 2, &tmp, reply);

    CGXDLMSVariant_d(&tmp);
    return ret;
}

// Add user to user list.
int CGXDLMSAssociationLogicalName_AddUser(
    CGXDLMSAssociationLogicalName *p,
    CGXDLMSClient* client,
    unsigned char id,
    String name,
    Vector* reply)//std::vector<CGXByteBuffer>&
{
    CGXByteBuffer data;
    CGXByteBuffer_1(&data);

    CGXByteBuffer_SetUInt8_1(&data, (unsigned char)DLMS_DATA_TYPE_STRUCTURE);
    //Add structure size.
    CGXByteBuffer_SetUInt8_1(&data, 2);

    CGXDLMSVariant tmp;
    CGXDLMSVariant_19(&tmp, id);

    GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &tmp);

    CGXDLMSVariant_copy_2(&tmp, name);

    GXHelpers_SetData(&data, DLMS_DATA_TYPE_STRING, &tmp);

    CGXDLMSVariant_copy_4(&tmp, &data);

    int ret = CGXDLMSClient_Method_1(client, (CGXDLMSObject*) p, 5, &tmp, reply);

    CGXDLMSVariant_d(&tmp);
    CGXByteBuffer_d(&data);
    return ret;
}

// Remove user fro user list.
int CGXDLMSAssociationLogicalName_RemoveUser(
    CGXDLMSAssociationLogicalName *p,
    CGXDLMSClient* client,
    unsigned char id,
    String name,
    Vector* reply)//std::vector<CGXByteBuffer>&
{
    CGXByteBuffer data;
    CGXByteBuffer_1(&data);

    CGXByteBuffer_SetUInt8_1(&data, (unsigned char)DLMS_DATA_TYPE_STRUCTURE);
    //Add structure size.
    CGXByteBuffer_SetUInt8_1(&data, 2);

    CGXDLMSVariant tmp;
    CGXDLMSVariant_19(&tmp, id);

    GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &tmp);

    CGXDLMSVariant_copy_2(&tmp, name);

    GXHelpers_SetData(&data, DLMS_DATA_TYPE_STRING, &tmp);

    CGXDLMSVariant_copy_4(&tmp, &data);

    int ret = CGXDLMSClient_Method_1(client, (CGXDLMSObject*) p, 6, &tmp, reply);

    CGXDLMSVariant_d(&tmp);
    CGXByteBuffer_d(&data);
    return ret;
}

// Returns LN Association View.
static int CGXDLMSAssociationLogicalName_GetObjects(
    CGXDLMSAssociationLogicalName* p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e,
    CGXByteBuffer* data)
{
    int ret;
    unsigned long pos = 0;
    //Add count only for first time.
    if (settings->m_Index == 0)
    {
        settings->m_Count = (unsigned short)CGXDLMSObjectCollection_size(&p->m_ObjectList);
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount((unsigned long)CGXDLMSObjectCollection_size(&p->m_ObjectList), data);
    }

    // CGXDLMSObjectCollection
    for (unsigned int i = CGXDLMSObjectCollection_begin(&p->m_ObjectList);
            i != CGXDLMSObjectCollection_end(&p->m_ObjectList); ++i)
    {
        CGXDLMSObject** it = CGXDLMSObjectCollection_at(&p->m_ObjectList, i);

        ++pos;
        if (!(pos <= settings->m_Index))
        {
            CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(data, 4);//Count

            CGXDLMSVariant type;
            CGXDLMSVariant_10(&type, (*it)->m_ObjectType);

            CGXDLMSVariant version;
            CGXDLMSVariant_20(&version, (*it)->m_Version);

            GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT16, &type);//ClassID
            GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &version);//Version

            CGXDLMSVariant ln;
            CGXDLMSVariant_18(&ln, (*it)->m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);

            GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &ln);//LN
            //Access rights.
            if ((ret = CGXDLMSAssociationLogicalName_GetAccessRights(p, *it,
                                        e->m_Server, data)) != 0)
            {
                CGXDLMSVariant_d(&type);
                CGXDLMSVariant_d(&version);
                CGXDLMSVariant_d(&ln);
                return ret;
            };
            if (settings->m_Server)
            {
                settings->m_Index = settings->m_Index + 1;
                //If PDU is full.
                if (!e->m_SkipMaxPduSize
                 && data->m_Size >= settings->m_MaxReceivePDUSize)
                {
                    CGXDLMSVariant_d(&type);
                    CGXDLMSVariant_d(&version);
                    CGXDLMSVariant_d(&ln);
                    break;
                }
            }

            CGXDLMSVariant_d(&type);
            CGXDLMSVariant_d(&version);
            CGXDLMSVariant_d(&ln);
        }
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns user list
static int CGXDLMSAssociationLogicalName_GetUsers(
    CGXDLMSAssociationLogicalName* p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e,
    CGXByteBuffer* data)
{
    unsigned long pos = 0;
    //Add count only for first time.
    if (settings->m_Index == 0)
    {
        settings->m_Count = (unsigned short)Vector_size(&p->m_UserList);
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_UserList), data);
    }

    // std::vector<std::pair<unsigned char, std::string> >
    for (unsigned int i = Vector_begin(&p->m_UserList);
            i != Vector_end(&p->m_UserList); ++i)
    {
        Pair* it = Vector_at(&p->m_UserList, i);

        ++pos;
        if (!(pos <= settings->m_Index))
        {
            CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(data, 2);//Count

            CGXDLMSVariant tmp;
            CGXDLMSVariant_19(&tmp, *((unsigned char*) it->first));

            GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);//Id

            CGXDLMSVariant_copy_2(&tmp, *((String*)it->second));

            GXHelpers_SetData(data, DLMS_DATA_TYPE_STRING, &tmp);//Name

            if (settings->m_Server)
            {
                settings->m_Index = settings->m_Index + 1;
                //If PDU is full.
                if (!e->m_SkipMaxPduSize
                 && data->m_Size >= settings->m_MaxReceivePDUSize)
                {
                	CGXDLMSVariant_d(&tmp);
                    break;
                }
            }

            CGXDLMSVariant_d(&tmp);
        }
    }
    return DLMS_ERROR_CODE_OK;
}


void CGXDLMSAssociationLogicalName_1(CGXDLMSAssociationLogicalName *p)
{
	String t_Str;
	String_3(&t_Str, "0.0.40.0.0.255");

	CGXDLMSAssociationLogicalName_2(p, t_Str);

	String_d(&t_Str);
}

/**
 Constructor.
 @param ln Logical Name of the object.
*/
void CGXDLMSAssociationLogicalName_2(CGXDLMSAssociationLogicalName *p, String ln)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, &ln, 0);

    CGXDLMSAssociationLogicalName__(p);

	String t_Str;
	String_3(&t_Str, "Gurux");

    p->m_AssociationStatus = DLMS_DLMS_ASSOCIATION_STATUS_NON_ASSOCIATED;
    CGXByteBuffer_AddString_1(&p->m_Secret, &t_Str);
    p->m_Version = 2;

    String_d(&t_Str);
}

CGXDLMSObjectCollection* CGXDLMSAssociationLogicalName_GetObjectList(CGXDLMSAssociationLogicalName *p)
{
    return &p->m_ObjectList;
}

CGXApplicationContextName* CGXDLMSAssociationLogicalName_GetApplicationContextName(CGXDLMSAssociationLogicalName *p)
{
    return &p->m_ApplicationContextName;
}

CGXDLMSContextType* CGXDLMSAssociationLogicalName_GetXDLMSContextInfo(CGXDLMSAssociationLogicalName *p)
{
    return &p->m_XDLMSContextInfo;
}

CGXAuthenticationMechanismName* CGXDLMSAssociationLogicalName_GetAuthenticationMechanismName(CGXDLMSAssociationLogicalName *p)
{
    return &p->m_AuthenticationMechanismName;
}

CGXByteBuffer* CGXDLMSAssociationLogicalName_GetSecret(CGXDLMSAssociationLogicalName *p)
{
    return &p->m_Secret;
}
void CGXDLMSAssociationLogicalName_SetSecret(CGXDLMSAssociationLogicalName *p, CGXByteBuffer* value)
{
	CGXByteBuffer_copy(&p->m_Secret, value);
}

Vector* CGXDLMSAssociationLogicalName_GetUserList(CGXDLMSAssociationLogicalName *p)//std::vector<std::pair<unsigned char, std::string>>&
{
    return &p->m_UserList;
}

void CGXDLMSAssociationLogicalName_SetUserList(CGXDLMSAssociationLogicalName *p, Vector* value)//std::vector<std::pair<unsigned char, std::string>>&
{
	Vector_copy_1(&p->m_UserList, value);
}

Pair* CGXDLMSAssociationLogicalName_GetCurrentUser(CGXDLMSAssociationLogicalName *p)//std::pair<unsigned char, std::string>&
{
    return &p->m_CurrentUser;
}

void CGXDLMSAssociationLogicalName_SetCurrentUser(CGXDLMSAssociationLogicalName *p, Pair* value)//std::pair<unsigned char, std::string>&
{
	Pair_copy(&p->m_CurrentUser, value);
}

String CGXDLMSAssociationLogicalName_GetSecuritySetupReference(CGXDLMSAssociationLogicalName *p)
{
    return p->m_SecuritySetupReference;
}
void CGXDLMSAssociationLogicalName_SetSecuritySetupReference(CGXDLMSAssociationLogicalName *p, String value)
{
	String_copy_1(&p->m_SecuritySetupReference, &value);
}

// Returns amount of attributes.
int CGXDLMSAssociationLogicalName_GetAttributeCount(CGXDLMSAssociationLogicalName *p)
{
    if (p->m_Version > 1)
        return 11;
    //Security Setup Reference is from version 1.
    if (p->m_Version > 0)
        return 9;
    return 8;
}

// Returns amount of methods.
int CGXDLMSAssociationLogicalName_GetMethodCount(CGXDLMSAssociationLogicalName *p)
{
    if (p->m_Version > 1)
    {
        return 6;
    }
    return 4;
}

void CGXDLMSAssociationLogicalName_GetValues(CGXDLMSAssociationLogicalName *p, Vector* values)//std::vector<std::string>&
{
	Vector_clear(values);

	Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

	String ln = CGXDLMSObjectCollection_ToString(&p->m_ObjectList);

	Vector_push_back(values, &ln);

	String_d(&ln);

	CGXDLMSVariant var;
	CGXDLMSVariant_19(&var, p->m_ClientSAP);

	String str = CGXDLMSVariant_ToString(&var);

	CGXDLMSVariant_d(&var);

	String_append_1(&str,"/");

	CGXDLMSVariant_19(&var, p->m_ServerSAP);

	String_append_var_str(&str, &var);

	CGXDLMSVariant_d(&var);

	Vector_push_back(values, &str);

	String_d(&str);

    str = CGXApplicationContextName_ToString(&p->m_ApplicationContextName);

	Vector_push_back(values, &str);

	String_d(&str);

	ln = CGXDLMSContextType_ToString(&p->m_XDLMSContextInfo);

	Vector_push_back(values, &ln);

	String_d(&ln);

	ln = CGXAuthenticationMechanismName_ToString(&p->m_AuthenticationMechanismName);

	Vector_push_back(values, &ln);

	String_d(&ln);

	ln = CGXByteBuffer_ToHexString(&p->m_Secret);

	Vector_push_back(values, &ln);

	String_d(&ln);

	Vector_push_back_Str_2(values, p->m_AssociationStatus);

    //Security Setup Reference is from version 1.
    if (p->m_Version > 0)
    {
    	Vector_push_back(values, &p->m_SecuritySetupReference);
    }
}

void CGXDLMSAssociationLogicalName_GetAttributeIndexToRead(CGXDLMSAssociationLogicalName *p, Vector* attributes)//std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //ObjectList is static and read only once.
    if (!CGXDLMSAssociationLogicalName_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //associated_partners_id is static and read only once.
    if (!CGXDLMSAssociationLogicalName_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //Application Context Name is static and read only once.
    if (!CGXDLMSAssociationLogicalName_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //xDLMS Context Info
    if (!CGXDLMSAssociationLogicalName_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    // Authentication Mechanism Name
    if (!CGXDLMSAssociationLogicalName_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    // Secret
    if (!CGXDLMSAssociationLogicalName_IsRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    // Association Status
    if (!CGXDLMSAssociationLogicalName_IsRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //Security Setup Reference is from version 1.
    if (p->m_Version > 0 && !CGXDLMSAssociationLogicalName_IsRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }
    //User list and current user are in version 2.
    if (p->m_Version > 1)
    {
        if (!CGXDLMSAssociationLogicalName_IsRead(p, 10))
        {
            tmp = 10;
            Vector_push_back(attributes, &tmp);
        }
        if (!CGXDLMSAssociationLogicalName_IsRead(p, 11))
        {
            tmp = 11;
            Vector_push_back(attributes, &tmp);
        }
    }
}

int CGXDLMSAssociationLogicalName_GetDataType(CGXDLMSAssociationLogicalName *p, int index, DLMS_DATA_TYPE* type)
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
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        *type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        *type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (p->m_Version > 0 && index == 9)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (p->m_Version > 1)
    {
        if (index == 10)
        {
            return DLMS_DATA_TYPE_ARRAY;
        }
        if (index == 11)
        {
            return DLMS_DATA_TYPE_STRUCTURE;
        }
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSAssociationLogicalName_Invoke(CGXDLMSAssociationLogicalName *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    // Check reply_to_HLS_authentication
    if (e_index == 1)
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

            CGXByteBuffer_Set_1(&bb, CGXDLMSValueEventArg_GetParameters(e)->st.un.byteArr,
                                CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetParameters(e)));
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
                                    CGXDLMSSettings_GetStoCChallenge(settings),
                                    readSecret, &serverChallenge)) != 0)
        {
            CGXByteBuffer_d(&serverChallenge);
            return ret;
        }
        if (CGXByteBuffer_Compare(&serverChallenge, CGXDLMSValueEventArg_GetParameters(e)->st.un.byteArr,
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
            if ((ret = CGXSecure_Secure(settings, settings->m_Cipher, ic,
                                        CGXDLMSSettings_GetCtoSChallenge(settings),
                                        readSecret, &serverChallenge)) != 0)
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
        }

        CGXByteBuffer_d(&serverChallenge);
    }
    else if (e_index == 2)
    {
        if (CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetParameters(e)) == 0)
        {
            e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        }
        else
        {
            CGXByteBuffer_Clear(&p->m_Secret);
            CGXByteBuffer_Set_1(&p->m_Secret,
                              CGXDLMSValueEventArg_GetParameters(e)->st.un.byteArr,
                              CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetParameters(e)));
        }
    }
    else if (e_index == 5)
    {
        if (Vector_size(&CGXDLMSValueEventArg_GetParameters(e)->Arr) != 2)
        {
            e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        }
        else
        {
            unsigned char tmp1 = ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 0))->st.un.bVal;

            String* ptmp2 = &(((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1))->strVal);

            Pair pair;
            Pair_(&pair, sizeof(unsigned char), sizeof(String),
                  NULL, NULL, String_v_c, String_v_d, &tmp1, ptmp2);

            Vector_push_back(&p->m_UserList, &pair);

            Pair_d(&pair);
        }
    }
    else if (e_index == 6)
    {
        if (Vector_size(&CGXDLMSValueEventArg_GetParameters(e)->Arr) != 2)
        {
            e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        }
        else
        {
            // std::vector<std::pair<unsigned char, std::string> >
            for (unsigned int i = Vector_begin(&p->m_UserList);
                    i != Vector_end(&p->m_UserList); ++i)
            {
                Pair* it = Vector_at(&p->m_UserList, i);

                if (*((unsigned char*) (it->first))
                        == ((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 0))->st.un.bVal)
                {
                    Vector_erase(&p->m_UserList, i, i + 1);
                    break;
                }
            }
        }
    }
    else
    {
        e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    }
    return 0;
}

int CGXDLMSAssociationLogicalName_GetValue(CGXDLMSAssociationLogicalName *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int ret;

    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        e->m_ByteArray = true;

        CGXByteBuffer buff;
        CGXByteBuffer_1(&buff);

        ret = CGXDLMSAssociationLogicalName_GetObjects(p, settings, e, &buff);

        CGXDLMSValueEventArg_SetValue_2(e, &buff);

        CGXByteBuffer_d(&buff);
        return ret;
    }
    if (e_index == 3)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        //Add count
        CGXByteBuffer_SetUInt8_1(&data, 2);
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_UINT8);
        CGXByteBuffer_SetUInt8_1(&data, p->m_ClientSAP);
        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_UINT16);
        CGXByteBuffer_SetUInt16(&data, p->m_ServerSAP);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        //Add count
        CGXByteBuffer_SetUInt8_1(&data, 0x7);

        CGXDLMSVariant ctt, country, name, organization, ua, context, id;
        CGXDLMSVariant_19(&ctt, p->m_ApplicationContextName.m_JointIsoCtt);
        CGXDLMSVariant_19(&country, p->m_ApplicationContextName.m_Country);
        CGXDLMSVariant_20(&name, p->m_ApplicationContextName.m_CountryName);
        CGXDLMSVariant_19(&organization, p->m_ApplicationContextName.m_IdentifiedOrganization);
        CGXDLMSVariant_19(&ua, p->m_ApplicationContextName.m_DlmsUA);
        CGXDLMSVariant_19(&context, p->m_ApplicationContextName.m_ApplicationContext);
        CGXDLMSVariant_19(&id, p->m_ApplicationContextName.m_ContextId);

        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &ctt)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &country)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &name)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &organization)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &ua)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &context)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &id)) != 0)
        {
        }
        else
        {
            CGXDLMSValueEventArg_SetValue_2(e, &data);

            ret = DLMS_ERROR_CODE_OK;
        }

    	CGXDLMSVariant_d(&ctt);
    	CGXDLMSVariant_d(&country);
    	CGXDLMSVariant_d(&name);
    	CGXDLMSVariant_d(&organization);
    	CGXDLMSVariant_d(&ua);
    	CGXDLMSVariant_d(&context);
    	CGXDLMSVariant_d(&id);
    	CGXByteBuffer_d(&data);
        return ret;
    }
    if (e_index == 5)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 6);

        CGXByteBuffer bb, bb2;
        CGXByteBuffer_1(&bb);
        CGXByteBuffer_1(&bb2);

        CGXByteBuffer_SetUInt32(&bb, p->m_XDLMSContextInfo.m_Conformance);
        CGXByteBuffer_SubArray(&bb, 1, 3, &bb2);

        CGXDLMSVariant conformance, rx, tx, version, quality, info;
        CGXDLMSVariant_23(&conformance, &bb2);
        CGXDLMSVariant_10(&rx, p->m_XDLMSContextInfo.m_MaxReceivePduSize);
        CGXDLMSVariant_10(&tx, p->m_XDLMSContextInfo.m_MaxSendPpuSize);
        CGXDLMSVariant_10(&version, p->m_XDLMSContextInfo.m_DlmsVersionNumber);
        CGXDLMSVariant_10(&quality, p->m_XDLMSContextInfo.m_QualityOfService);
        CGXDLMSVariant_23(&info, &(p->m_XDLMSContextInfo.m_CypheringInfo));

        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_BIT_STRING, &conformance)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &rx)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &tx)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &version)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_INT8, &quality)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &info)) != 0)
        {
        }
        else
        {
            CGXDLMSValueEventArg_SetValue_2(e, &data);

            ret = DLMS_ERROR_CODE_OK;
        }

        CGXDLMSVariant_d(&conformance);
        CGXDLMSVariant_d(&rx);
        CGXDLMSVariant_d(&tx);
        CGXDLMSVariant_d(&version);
        CGXDLMSVariant_d(&quality);
        CGXDLMSVariant_d(&info);
        CGXByteBuffer_d(&data);
        CGXByteBuffer_d(&bb2);
        CGXByteBuffer_d(&bb);
        return ret;
    }
    if (e_index == 6)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        //Add count
        CGXByteBuffer_SetUInt8_1(&data, 0x7);

        CGXDLMSVariant ctt, country, name, organization, ua, context, id;
        CGXDLMSVariant_10(&ctt, p->m_AuthenticationMechanismName.m_JointIsoCtt);
        CGXDLMSVariant_10(&country, p->m_AuthenticationMechanismName.m_Country);
        CGXDLMSVariant_10(&name, p->m_AuthenticationMechanismName.m_CountryName);
        CGXDLMSVariant_10(&organization, p->m_AuthenticationMechanismName.m_IdentifiedOrganization);
        CGXDLMSVariant_10(&ua, p->m_AuthenticationMechanismName.m_DlmsUA);
        CGXDLMSVariant_10(&context, p->m_AuthenticationMechanismName.m_AuthenticationMechanismName);
        CGXDLMSVariant_10(&id, p->m_AuthenticationMechanismName.m_MechanismId);

        if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &ctt)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &country)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &name)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &organization)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &ua)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &context)) != 0 ||
            (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &id)) != 0)
        {
        }
        else
        {
            CGXDLMSValueEventArg_SetValue_2(e, &data);

            ret = DLMS_ERROR_CODE_OK;
        }

    	CGXDLMSVariant_d(&ctt);
    	CGXDLMSVariant_d(&country);
    	CGXDLMSVariant_d(&name);
    	CGXDLMSVariant_d(&organization);
    	CGXDLMSVariant_d(&ua);
    	CGXDLMSVariant_d(&context);
    	CGXDLMSVariant_d(&id);
    	CGXByteBuffer_d(&data);
        return ret;
    }
    if (e_index == 7)
    {
        CGXDLMSValueEventArg_SetValue_2(e, &p->m_Secret);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 8)
    {
        CGXDLMSValueEventArg_SetValue_4(e, (unsigned char)p->m_AssociationStatus);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 9)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        GXHelpers_SetLogicalName_1(String_c_str(&p->m_SecuritySetupReference), &tmp);
        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 10)
    {
        e->m_ByteArray = true;

        CGXByteBuffer buff;
        CGXByteBuffer_1(&buff);

        ret = CGXDLMSAssociationLogicalName_GetUsers(p, settings, e, &buff);

        CGXDLMSValueEventArg_SetValue_2(e, &buff);

        CGXByteBuffer_d(&buff);
        return ret;
    }
    if (e_index == 11)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, (unsigned char)DLMS_DATA_TYPE_STRUCTURE);
        //Add structure size.
        CGXByteBuffer_SetUInt8_1(&data, 2);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_19(&tmp, *((unsigned char*) (p->m_CurrentUser.first)));

        GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &tmp);

        CGXDLMSVariant_copy_2(&tmp, *((String*) (p->m_CurrentUser.second)));

        GXHelpers_SetData(&data, DLMS_DATA_TYPE_STRING, &tmp);

        CGXDLMSVariant_d(&tmp);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSAssociationLogicalName_SetValue(CGXDLMSAssociationLogicalName *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        CGXDLMSObjectCollection_clear(&p->m_ObjectList);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt != DLMS_DATA_TYPE_NONE)
        {
            // std::vector<CGXDLMSVariant >::
            Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
            for (unsigned i = Vector_begin(vec); i != Vector_end(vec); ++i)
            {
                CGXDLMSVariant* it = Vector_at(vec, i);

                //((CGXDLMSVariant*) Vector_at(&(it->Arr), 2))
                DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&(it->Arr), 0));
                int version = CGXDLMSVariant_ToInteger(Vector_at(&(it->Arr), 1));

                String ln;
                String_(&ln);

                GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&(it->Arr), 2))->st.un.byteArr, &ln);
                CGXDLMSObject* pObj = CGXDLMSObjectCollection_FindByLN_1(CGXDLMSSettings_GetObjects(settings),
                                                                         type, &ln);
                if (pObj == NULL)
                {
                    pObj = CGXDLMSObjectFactory_CreateObject_2(type, ln);
                    if (pObj != NULL)
                    {
                        pObj->m_Version = version;
                    }
                }
                if (pObj != NULL)
                {
                    CGXDLMSAssociationLogicalName_UpdateAccessRights(p, pObj,
                                                    *((CGXDLMSVariant*) Vector_at(&(it->Arr), 3)));
                    CGXDLMSObjectCollection_push_back(&p->m_ObjectList, &pObj);
                }

                String_d(&ln);
            }
        }
    }
    else if (e_index == 3)
    {
        if (Vector_size(&(CGXDLMSValueEventArg_GetValue(e)->Arr)) == 2)
        {
            p->m_ClientSAP = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));
            p->m_ServerSAP = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1));
        }
        else
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    else if (e_index == 4)
    {
        //Value of the object identifier encoded in BER
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXByteBuffer tmp;
            CGXByteBuffer_1(&tmp);

            CGXByteBuffer_Set_1(&tmp, CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                                CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetValue(e)));
            int ret;
            unsigned char val;
            if ((ret = CGXByteBuffer_GetUInt8_2(&tmp, 0, &val)) != 0)
            {
                CGXByteBuffer_d(&tmp);
                return ret;
            }
            if (val == 0x60)
            {
                p->m_ApplicationContextName.m_JointIsoCtt = 0;
                p->m_ApplicationContextName.m_Country = 0;
                p->m_ApplicationContextName.m_CountryName = 0;
                CGXByteBuffer_SetPosition(&tmp, 3);
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_IdentifiedOrganization = val;
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_DlmsUA = val;
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_ApplicationContext = val;
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_ContextId = val;
            }
            else
            {
                //Get Tag and Len.
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 2)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 7)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                //Get tag
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 0x11)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_JointIsoCtt = val;
                //Get tag
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 0x11)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_Country = val;
                //Get tag
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 0x12)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_CountryName = val;
                //Get tag
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 0x11)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_IdentifiedOrganization = val;
                //Get tag
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 0x11)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_DlmsUA = val;
                //Get tag
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 0x11)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_ApplicationContext = val;
                //Get tag
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val != 0x11)
                {
                    CGXByteBuffer_d(&tmp);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                p->m_ApplicationContextName.m_ContextId = val;
            }

            CGXByteBuffer_d(&tmp);
        }
        else
        {
            Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);

            p->m_ApplicationContextName.m_JointIsoCtt = CGXDLMSVariant_ToInteger(Vector_at(vec, 0));

            p->m_ApplicationContextName.m_Country = CGXDLMSVariant_ToInteger(Vector_at(vec, 1));

            p->m_ApplicationContextName.m_CountryName = CGXDLMSVariant_ToInteger(Vector_at(vec, 2));

            p->m_ApplicationContextName.m_IdentifiedOrganization = CGXDLMSVariant_ToInteger(Vector_at(vec, 3));

            p->m_ApplicationContextName.m_DlmsUA = CGXDLMSVariant_ToInteger(Vector_at(vec, 4));

            p->m_ApplicationContextName.m_ApplicationContext = CGXDLMSVariant_ToInteger(Vector_at(vec, 5));

            p->m_ApplicationContextName.m_ContextId = CGXDLMSVariant_ToInteger(Vector_at(vec, 6));
        }
    }
    else if (e_index == 5)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_STRUCTURE)
        {
            Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);

            p->m_XDLMSContextInfo.m_Conformance =
                    (DLMS_CONFORMANCE) CGXDLMSVariant_ToInteger(Vector_at(vec, 0));

            p->m_XDLMSContextInfo.m_MaxReceivePduSize =
                    CGXDLMSVariant_ToInteger(Vector_at(vec, 1));

            p->m_XDLMSContextInfo.m_MaxSendPpuSize =
                    CGXDLMSVariant_ToInteger(Vector_at(vec, 2));

            p->m_XDLMSContextInfo.m_DlmsVersionNumber =
                    CGXDLMSVariant_ToInteger(Vector_at(vec, 3));

            p->m_XDLMSContextInfo.m_QualityOfService =
                    CGXDLMSVariant_ToInteger(Vector_at(vec, 4));


            CGXByteBuffer tmp;
            CGXByteBuffer_1(&tmp);

            CGXByteBuffer_Set_1(&tmp,
                    ((CGXDLMSVariant*) Vector_at(vec, 5))->st.un.byteArr,
                    CGXDLMSVariant_GetSize_1(Vector_at(vec, 5)));
            CGXDLMSContextType_SetCypheringInfo(&p->m_XDLMSContextInfo, &tmp);

            CGXByteBuffer_d(&tmp);
        }
    }
    else if (e_index == 6)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt != DLMS_DATA_TYPE_NONE)
        {
            unsigned char val;
            int ret;
            //Value of the object identifier encoded in BER
            if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                CGXByteBuffer tmp;
                CGXByteBuffer_1(&tmp);

                CGXByteBuffer_Set_1(&tmp, CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                                    CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetValue(e)));
                if ((ret = CGXByteBuffer_GetUInt8_2(&tmp, 0, &val)) != 0)
                {
                    CGXByteBuffer_d(&tmp);
                    return ret;
                }
                if (val == 0x60)
                {
                    p->m_AuthenticationMechanismName.m_JointIsoCtt = 0;
                    p->m_AuthenticationMechanismName.m_Country = 0;
                    p->m_AuthenticationMechanismName.m_CountryName = 0;
                    CGXByteBuffer_SetPosition(&tmp, 3);
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_IdentifiedOrganization = val;
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_DlmsUA = val;
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_AuthenticationMechanismName = val;
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_MechanismId = (DLMS_AUTHENTICATION)val;
                }
                else
                {
                    //Get Tag and Len.
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 2)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 7)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    //Get tag
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 0x11)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_JointIsoCtt = val;
                    //Get tag
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 0x11)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_Country = val;
                    //Get tag
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 0x12)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    unsigned short tmp2;
                    if ((ret = CGXByteBuffer_GetUInt16_1(&tmp, &tmp2)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_CountryName = tmp2;
                    //Get tag
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 0x11)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_IdentifiedOrganization = val;
                    //Get tag
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 0x11)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_DlmsUA = val;
                    //Get tag
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 0x11)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_AuthenticationMechanismName = val;
                    //Get tag
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    if (val != 0x11)
                    {
                        CGXByteBuffer_d(&tmp);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    if ((ret = CGXByteBuffer_GetUInt8_1(&tmp, &val)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        return ret;
                    }
                    p->m_AuthenticationMechanismName.m_MechanismId = (DLMS_AUTHENTICATION)val;
                }

                CGXByteBuffer_d(&tmp);
            }
            else
            {
                Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);

                p->m_AuthenticationMechanismName.m_JointIsoCtt = CGXDLMSVariant_ToInteger(Vector_at(vec, 0));

                p->m_AuthenticationMechanismName.m_Country = CGXDLMSVariant_ToInteger(Vector_at(vec, 1));

                p->m_AuthenticationMechanismName.m_CountryName = CGXDLMSVariant_ToInteger(Vector_at(vec, 2));

                p->m_AuthenticationMechanismName.m_IdentifiedOrganization = CGXDLMSVariant_ToInteger(Vector_at(vec, 3));

                p->m_AuthenticationMechanismName.m_DlmsUA = CGXDLMSVariant_ToInteger(Vector_at(vec, 4));

                p->m_AuthenticationMechanismName.m_AuthenticationMechanismName = CGXDLMSVariant_ToInteger(Vector_at(vec, 5));

                p->m_AuthenticationMechanismName.m_MechanismId = (DLMS_AUTHENTICATION)CGXDLMSVariant_ToInteger(Vector_at(vec, 6));
            }
        }
    }
    else if (e_index == 7)
    {
        CGXByteBuffer_Clear(&p->m_Secret);
        CGXByteBuffer_Set_1(&p->m_Secret,
                            CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                            CGXDLMSValueEventArg_GetValue(e)->size);
    }
    else if (e_index == 8)
    {
        p->m_AssociationStatus = (DLMS_DLMS_ASSOCIATION_STATUS)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 9)
    {
        GXHelpers_GetLogicalName_1(CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                                   &p->m_SecuritySetupReference);
    }
    else if (e_index == 10)
    {
        Vector_clear(&p->m_UserList);

        // std::vector<CGXDLMSVariant >
        Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
        for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
        {
            CGXDLMSVariant* it = Vector_at(vec, i);

            unsigned char* ptmp1 = &(((CGXDLMSVariant*) Vector_at(&it->Arr, 0))->st.un.bVal);
            String* ptmp2 = &(((CGXDLMSVariant*) Vector_at(&it->Arr, 1))->strVal);

            Pair pair; // std::pair<unsigned char, std::string>
            Pair_(&pair, sizeof(unsigned char), sizeof(String),
                  NULL, NULL, String_v_c, String_v_d, ptmp1, ptmp2);

            Vector_push_back(&p->m_UserList, &pair);

            Pair_d(&pair);
        }
    }
    else if (e_index == 11)
    {
        if (Vector_size(&(CGXDLMSValueEventArg_GetValue(e)->Arr)) == 2)
        {
            unsigned char* ptmp1 = &(((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0))->st.un.bVal);
            String* ptmp2 = &(((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->strVal);

            Pair pair; // std::pair<unsigned char, std::string>
            Pair_(&pair, sizeof(unsigned char), sizeof(String),
                  NULL, NULL, String_v_c, String_v_d, ptmp1, ptmp2);

            Pair_copy(&p->m_CurrentUser, &pair);

            Pair_d(&pair);
        }
        else
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSAssociationLogicalName_d(CGXDLMSAssociationLogicalName *p)
{
    CGXDLMSObjectCollection_d(&p->m_ObjectList);
    CGXApplicationContextName_d(&p->m_ApplicationContextName);
    CGXDLMSContextType_d(&p->m_XDLMSContextInfo);

    CGXByteBuffer_d(&p->m_Secret);
    String_d(&p->m_SecuritySetupReference);
    Vector_d(&p->m_UserList);
    Pair_d(&p->m_CurrentUser);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
