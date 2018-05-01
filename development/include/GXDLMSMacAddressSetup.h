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

#ifndef GXDLMSMACADDRESSSETUP_H
#define GXDLMSMACADDRESSSETUP_H

#include "GXDLMSObject.h"

#include "String.h"
#include "Vector.h"

typedef struct //class CGXDLMSMacAddressSetup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSMacAddressSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSMacAddressSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSMacAddressSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSMacAddressSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSMacAddressSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSMacAddressSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSMacAddressSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSMacAddressSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    String m_MacAddress;

} CGXDLMSMacAddressSetup;

#define CGXDLMSMacAddressSetup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSMacAddressSetup_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

/**
 Constructor.
*/
extern void CGXDLMSMacAddressSetup_1(CGXDLMSMacAddressSetup* p);
/**
 Constructor.

    @param ln Logical Name of the object.
*/
extern void CGXDLMSMacAddressSetup_2(CGXDLMSMacAddressSetup* p, String ln);

/**
 Constructor.

    @param ln Logical Name of the object.
    @param sn Short Name of the object.
*/
extern void CGXDLMSMacAddressSetup_3(CGXDLMSMacAddressSetup* p, String ln, unsigned short sn);

/**
 Value of COSEM Data object.
*/
extern String CGXDLMSMacAddressSetup_GetMacAddress(CGXDLMSMacAddressSetup* p);
extern void CGXDLMSMacAddressSetup_SetMacAddress(CGXDLMSMacAddressSetup* p, String value);

// Returns amount of attributes.
extern int CGXDLMSMacAddressSetup_GetAttributeCount(CGXDLMSMacAddressSetup* p);

// Returns amount of methods.
extern int CGXDLMSMacAddressSetup_GetMethodCount(CGXDLMSMacAddressSetup* p);

//Get attribute values of object.
extern void CGXDLMSMacAddressSetup_GetValues(CGXDLMSMacAddressSetup* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSMacAddressSetup_GetAttributeIndexToRead(CGXDLMSMacAddressSetup* p, Vector* attributes); //std::vector<int>&
extern int CGXDLMSMacAddressSetup_GetDataType(CGXDLMSMacAddressSetup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSMacAddressSetup_GetValue(CGXDLMSMacAddressSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSMacAddressSetup_SetValue(CGXDLMSMacAddressSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSMacAddressSetup_d(CGXDLMSMacAddressSetup* p);

#endif //GXDLMSMACADDRESSSETUP_H
