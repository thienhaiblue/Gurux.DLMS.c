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
#ifndef GXDLMSASSOCIATIONLOGICALNAME_H
#define GXDLMSASSOCIATIONLOGICALNAME_H

#include "GXDLMSObject.h"
#include "GXApplicationContextName.h"
#include "GXDLMSContextType.h"
#include "GXAuthenticationMechanismName.h"
#include "String.h"
#include "Vector.h"
#include "Pair.h"

typedef struct CGXDLMSAssociationLogicalName // class CGXDLMSAssociationLogicalName : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSAssociationLogicalName_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSAssociationLogicalName_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSAssociationLogicalName_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSAssociationLogicalName_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSAssociationLogicalName_Invoke

    // (CGXDLMSObject)
    CGXAttributeCollection m_Attributes;
    CGXAttributeCollection m_MethodAttributes;
    String m_Description;
    DLMS_OBJECT_TYPE m_ObjectType;
    char m_AttributeIndex;
    unsigned short m_DataIndex;
    unsigned short m_Version;

    Map m_ReadTimes; // std::map<int, time_t> m_ReadTimes;
    unsigned short m_SN;
    unsigned char m_LN[6];

    // Override CGXDLMSObject
    d_FuncPtr d; // = CGXDLMSAssociationLogicalName_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSAssociationLogicalName_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSAssociationLogicalName_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSAssociationLogicalName_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    DLMS_DLMS_ASSOCIATION_STATUS m_AssociationStatus;
    CGXDLMSObjectCollection m_ObjectList;
    unsigned char m_ClientSAP;
    unsigned short m_ServerSAP;
    CGXApplicationContextName m_ApplicationContextName;
    CGXDLMSContextType m_XDLMSContextInfo;
    CGXAuthenticationMechanismName m_AuthenticationMechanismName;
    /**
    * Secret.
    */
    CGXByteBuffer m_Secret;

    String m_SecuritySetupReference;

    Vector m_UserList; // std::vector<std::pair<unsigned char, std::string>>

    Pair m_CurrentUser; // std::pair<unsigned char, std::string>

} CGXDLMSAssociationLogicalName;

#define CGXDLMSAssociationLogicalName_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSAssociationLogicalName_GetVersion(p)           CGXDLMSObject_GetVersion((CGXDLMSObject*) (p))
#define CGXDLMSAssociationLogicalName_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//public
/**
 Constructor.
*/
extern void CGXDLMSAssociationLogicalName_1(CGXDLMSAssociationLogicalName *p);

/**
 Constructor.
 @param ln Logical Name of the object.
*/
extern void CGXDLMSAssociationLogicalName_2(CGXDLMSAssociationLogicalName *p, String ln);

extern CGXDLMSObjectCollection* CGXDLMSAssociationLogicalName_GetObjectList(CGXDLMSAssociationLogicalName *p);


/// Contains the identifiers of the COSEM client APs within the physical devices hosting these APs,
/// which belong to the AA modelled by the �Association LN� object.
extern unsigned char CGXDLMSAssociationLogicalName_GetClientSAP(CGXDLMSAssociationLogicalName *p);
extern void CGXDLMSAssociationLogicalName_SetClientSAP(CGXDLMSAssociationLogicalName *p, unsigned char value);

/// Contains the identifiers of the COSEM server (logical device) APs within the physical
/// devices hosting these APs, which belong to the AA modelled by the �Association LN� object.
extern unsigned short CGXDLMSAssociationLogicalName_GetServerSAP(CGXDLMSAssociationLogicalName *p);
extern void CGXDLMSAssociationLogicalName_SetServerSAP(CGXDLMSAssociationLogicalName *p, unsigned short value);

extern CGXApplicationContextName* CGXDLMSAssociationLogicalName_GetApplicationContextName(CGXDLMSAssociationLogicalName *p);

extern CGXDLMSContextType* CGXDLMSAssociationLogicalName_GetXDLMSContextInfo(CGXDLMSAssociationLogicalName *p);

extern CGXAuthenticationMechanismName* CGXDLMSAssociationLogicalName_GetAuthenticationMechanismName(CGXDLMSAssociationLogicalName *p);

extern CGXByteBuffer* CGXDLMSAssociationLogicalName_GetSecret(CGXDLMSAssociationLogicalName *p);

extern void CGXDLMSAssociationLogicalName_SetSecret(CGXDLMSAssociationLogicalName *p, CGXByteBuffer* value);

extern Vector* CGXDLMSAssociationLogicalName_GetUserList(CGXDLMSAssociationLogicalName *p);//std::vector<std::pair<unsigned char, std::string>>&

extern void CGXDLMSAssociationLogicalName_SetUserList(CGXDLMSAssociationLogicalName *p, Vector* value);//std::vector<std::pair<unsigned char, std::string>>&

extern Pair* CGXDLMSAssociationLogicalName_GetCurrentUser(CGXDLMSAssociationLogicalName *p);//std::pair<unsigned char, std::string>&

extern void CGXDLMSAssociationLogicalName_SetCurrentUser(CGXDLMSAssociationLogicalName *p, Pair* value);//std::pair<unsigned char, std::string>&


// Updates secret.
extern int CGXDLMSAssociationLogicalName_UpdateSecret(
    CGXDLMSAssociationLogicalName *p,
    CGXDLMSClient* client,
    Vector* reply);//std::vector<CGXByteBuffer>&

// Add user to user list.
extern int CGXDLMSAssociationLogicalName_AddUser(
    CGXDLMSAssociationLogicalName *p,
    CGXDLMSClient* client,
    unsigned char id,
    String name,
    Vector* reply);//std::vector<CGXByteBuffer>&

// Remove user fro user list.
extern int CGXDLMSAssociationLogicalName_RemoveUser(
    CGXDLMSAssociationLogicalName *p,
    CGXDLMSClient* client,
    unsigned char id,
    String name,
    Vector* reply);//std::vector<CGXByteBuffer>&


extern DLMS_DLMS_ASSOCIATION_STATUS CGXDLMSAssociationLogicalName_GetAssociationStatus(CGXDLMSAssociationLogicalName *p);

extern void CGXDLMSAssociationLogicalName_SetAssociationStatus(CGXDLMSAssociationLogicalName *p, DLMS_DLMS_ASSOCIATION_STATUS value);

extern String CGXDLMSAssociationLogicalName_GetSecuritySetupReference(CGXDLMSAssociationLogicalName *p);
extern void CGXDLMSAssociationLogicalName_SetSecuritySetupReference(CGXDLMSAssociationLogicalName *p, String value);

// Returns amount of attributes.
extern int CGXDLMSAssociationLogicalName_GetAttributeCount(CGXDLMSAssociationLogicalName *p);

// Returns amount of methods.
extern int CGXDLMSAssociationLogicalName_GetMethodCount(CGXDLMSAssociationLogicalName *p);

//Get attribute values of object.
extern void CGXDLMSAssociationLogicalName_GetValues(CGXDLMSAssociationLogicalName *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSAssociationLogicalName_GetAttributeIndexToRead(CGXDLMSAssociationLogicalName *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSAssociationLogicalName_GetDataType(CGXDLMSAssociationLogicalName *p, int index, DLMS_DATA_TYPE* type);

extern int CGXDLMSAssociationLogicalName_Invoke(CGXDLMSAssociationLogicalName *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern int CGXDLMSAssociationLogicalName_GetValue(CGXDLMSAssociationLogicalName *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);
extern int CGXDLMSAssociationLogicalName_SetValue(CGXDLMSAssociationLogicalName *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSAssociationLogicalName_d(CGXDLMSAssociationLogicalName *p);

#endif //GXDLMSASSOCIATIONLOGICALNAME_H
