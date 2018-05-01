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

#ifndef GXDLMSASSOCIATIONSHORTNAME_H
#define GXDLMSASSOCIATIONSHORTNAME_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"

typedef int (*GetAttributeCount_FuncPtr)(void* p);
typedef int (*GetMethodCount_FuncPtr)(void* p);
typedef int (*GetValue_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);
typedef int (*SetValue_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);
typedef int (*Invoke_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

typedef void (*d_FuncPtr)(void* p);

typedef int (*SetDataType_FuncPtr)(void* p, int index, DLMS_DATA_TYPE type);
typedef int (*GetDataType_FuncPtr)(void* p, int index, DLMS_DATA_TYPE* type);

typedef int (*GetUIDataType_FuncPtr)(void* p, int index, DLMS_DATA_TYPE* type);

typedef void (*GetValues_FuncPtr)(void* p, Vector* values); // std::vector<std::string>&
typedef void (*GetAttributeIndexToRead_FuncPtr)(void* p, Vector* int_attributes);

typedef struct CGXDLMSAssociationShortName
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSAssociationShortName_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSAssociationShortName_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSAssociationShortName_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSAssociationShortName_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSAssociationShortName_Invoke

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
    d_FuncPtr d; // = CGXDLMSAssociationShortName_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSAssociationShortName_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSAssociationShortName_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSAssociationShortName_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    CGXDLMSObjectCollection m_ObjectList;
    String m_SecuritySetupReference;
    CGXByteBuffer m_Secret;
} CGXDLMSAssociationShortName;

#define CGXDLMSAssociationShortName_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSAssociationShortName_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//public
//Constructor.
extern void CGXDLMSAssociationShortName_(CGXDLMSAssociationShortName *p);
//destructor
extern void CGXDLMSAssociationShortName_d(CGXDLMSAssociationShortName *p);

extern CGXDLMSObjectCollection* CGXDLMSAssociationShortName_GetObjectList(CGXDLMSAssociationShortName *p);

extern CGXByteBuffer* CGXDLMSAssociationShortName_GetSecret(CGXDLMSAssociationShortName *p);

extern void CGXDLMSAssociationShortName_SetSecret(CGXDLMSAssociationShortName *p, CGXByteBuffer* value);

extern String* CGXDLMSAssociationShortName_GetSecuritySetupReference(CGXDLMSAssociationShortName *p);

extern void CGXDLMSAssociationShortName_SetSecuritySetupReference(CGXDLMSAssociationShortName *p, String* value);

//Get attribute values of object.
extern void CGXDLMSAssociationShortName_GetValues(
    CGXDLMSAssociationShortName *p,
    Vector* values);//std::vector<std::string>&

extern void CGXDLMSAssociationShortName_GetAttributeIndexToRead(
    CGXDLMSAssociationShortName *p,
    Vector* attributes);//std::vector<int>&

// Returns amount of attributes.
extern int CGXDLMSAssociationShortName_GetAttributeCount(CGXDLMSAssociationShortName *p);

// Returns amount of methods.
extern int CGXDLMSAssociationShortName_GetMethodCount(CGXDLMSAssociationShortName *p);

extern int CGXDLMSAssociationShortName_GetDataType(
    CGXDLMSAssociationShortName *p,
    int index,
    DLMS_DATA_TYPE* type);

// Returns SN Association View.
extern int CGXDLMSAssociationShortName_GetObjects(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e,
    CGXByteBuffer* data);

extern int CGXDLMSAssociationShortName_Invoke(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e);

extern int CGXDLMSAssociationShortName_GetValue(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e);

extern int CGXDLMSAssociationShortName_SetValue(
    CGXDLMSAssociationShortName *p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e);

#endif //GXDLMSASSOCIATIONSHORTNAME_H
