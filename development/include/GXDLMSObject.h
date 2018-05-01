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

#ifndef GXDLMSOBJECT_H
#define GXDLMSOBJECT_H

#include "GXAttributeCollection.h"
#include "GXDLMSVariant.h"
#include "IGXDLMSBase.h"
//#include "GXHelpers.h"
#include "GXDateTime.h"
//#include "GXDLMSObjectCollection.h"
#include "String.h"
#include "Map.h"

#include <stdbool.h>

#include "GXDLMSValueEventArg.h"

//typedef struct CGXDLMSValueEventArg CGXDLMSValueEventArg;
//typedef struct CGXDLMSSettings CGXDLMSSettings;

//typedef int (*GetAttributeCount_FuncPtr)(void* p);
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

typedef struct CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSObject_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSObject_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSObject_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSObject_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSObject_Invoke
	///////////////////////////////////////////////////////////////////////////

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

    // virtual in CGXDLMSObject
    d_FuncPtr d; // = CGXDLMSObject_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSObject_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSObject_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSObject_GetAttributeIndexToRead
} CGXDLMSObject;

extern void CGXDLMSObject_Initialize(CGXDLMSObject* p, short sn, unsigned short class_id, unsigned char version, CGXByteBuffer* pLogicalName);

    /*
     * Is attribute read. This can be used with static attributes to make
     * meter reading faster.
     */
extern bool CGXDLMSObject_IsRead(CGXDLMSObject* p, int index);
extern bool CGXDLMSObject_CanRead(CGXDLMSObject* p, int index);
extern int CGXDLMSObject_GetLogicalName_1(CGXDLMSObject * target, CGXDLMSVariant* value);
extern int CGXDLMSObject_SetLogicalName(CGXDLMSObject * target, CGXDLMSVariant* value);

extern bool CGXDLMSObject_IsLogicalNameEmpty(unsigned char* pLN);

extern void CGXDLMSObject_1(CGXDLMSObject* p);
extern void CGXDLMSObject_2(CGXDLMSObject* p, DLMS_OBJECT_TYPE type);

    //SN Constructor.
extern void CGXDLMSObject_3(CGXDLMSObject* p, DLMS_OBJECT_TYPE type, String* ln, unsigned short sn);

    //LN Constructor.
extern void CGXDLMSObject_4(CGXDLMSObject* p, DLMS_OBJECT_TYPE type, String* ln);
extern void CGXDLMSObject_5(CGXDLMSObject* p, short sn, unsigned short class_id, unsigned char version, CGXByteBuffer* ln);

extern void CGXDLMSObject_d(CGXDLMSObject* p);

    //Get Object's Logical or Short Name as a std::string.
extern CGXDLMSVariant CGXDLMSObject_GetName(CGXDLMSObject* p);

extern int CGXDLMSObject_SetName(CGXDLMSObject* p, CGXDLMSVariant* value);

    //Get Object's Interface class type.
extern DLMS_OBJECT_TYPE CGXDLMSObject_GetObjectType(CGXDLMSObject* p);

    //Get Object's Short Name.
extern unsigned short CGXDLMSObject_GetShortName(CGXDLMSObject* p);

    //Set Object's Short Name.
extern void CGXDLMSObject_SetShortName(CGXDLMSObject* p, unsigned short value);

    //Get Object's Logical Name.
extern void CGXDLMSObject_GetLogicalName_2(CGXDLMSObject* p, String* ln);

//extern void CGXDLMSObject_SetVersion(CGXDLMSObject* p, unsigned short value);

//extern unsigned short CGXDLMSObject_GetVersion(CGXDLMSObject* p);

extern CGXAttributeCollection* CGXDLMSObject_GetAttributes(CGXDLMSObject* p);
extern CGXAttributeCollection* CGXDLMSObject_GetMethodAttributes(CGXDLMSObject* p);

extern int CGXDLMSObject_SetDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE type);
extern int CGXDLMSObject_GetDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE* type);

extern int CGXDLMSObject_GetUIDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE* type);

extern void CGXDLMSObject_SetUIDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE type);

extern DLMS_ACCESS_MODE CGXDLMSObject_GetAccess(CGXDLMSObject* p, int index);
extern void CGXDLMSObject_SetAccess(CGXDLMSObject* p, int index, DLMS_ACCESS_MODE access);
extern DLMS_METHOD_ACCESS_MODE CGXDLMSObject_GetMethodAccess(CGXDLMSObject* p, int index);
extern void CGXDLMSObject_SetMethodAccess(CGXDLMSObject* p, int index, DLMS_METHOD_ACCESS_MODE access);


    //Get description of the object.
extern void CGXDLMSObject_GetDescription(CGXDLMSObject* p, String* out);

    //Set description of the object.
extern void CGXDLMSObject_SetDescription(CGXDLMSObject* p, String value);

//Get values as std::string.
extern void CGXDLMSObject_GetValues(CGXDLMSObject* p, Vector* values); // std::vector<std::string>&

extern void CGXDLMSObject_GetAttributeIndexToRead(CGXDLMSObject* p, Vector* attributes); // std::vector<int>& attributes

    // Returns amount of attributes.
extern int CGXDLMSObject_GetAttributeCount(CGXDLMSObject* p);

    // Returns amount of methods.
extern int CGXDLMSObject_GetMethodCount(CGXDLMSObject* p);

    // Returns value of given attribute.
extern int CGXDLMSObject_GetValue(CGXDLMSObject* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

    // Set value of given attribute.
extern int CGXDLMSObject_SetValue(CGXDLMSObject* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

    // Set value of given attribute.
extern int CGXDLMSObject_Invoke(CGXDLMSObject* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

typedef struct
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSObject_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSObject_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSObject_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSObject_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSObject_Invoke

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
    d_FuncPtr d; // = CGXDLMSCustomObject_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSObject_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSObject_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSObject_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////
} CGXDLMSCustomObject;

extern void CGXDLMSCustomObject_(CGXDLMSCustomObject* p, DLMS_OBJECT_TYPE type);

extern void CGXDLMSCustomObject_d(CGXDLMSCustomObject* p);

#endif //GXDLMSOBJECT_H
