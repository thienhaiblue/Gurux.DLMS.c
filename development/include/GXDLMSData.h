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

#ifndef GXDLMSDATA_H
#define GXDLMSDATA_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"

typedef struct CGXDLMSData // class CGXDLMSData : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSData_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSData_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSData_GetValue_2
	SetValue_FuncPtr SetValue; // = CGXDLMSData_SetValue_2
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
    d_FuncPtr d; // = CGXDLMSData_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSData_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSData_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSData_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    CGXDLMSVariant m_Value;
} CGXDLMSData;

#define CGXDLMSData_CanRead(p, index)               CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSData_GetLogicalName_1(target, value) CGXDLMSObject_GetLogicalName_1((target), (value))
#define CGXDLMSData_SetLogicalName(target, value)   CGXDLMSObject_SetLogicalName((target), (value))
#define CGXDLMSData_GetLogicalName_2(p, ln)         CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSData_GetAttributes(p)                CGXDLMSObject_GetAttributes((CGXDLMSObject*) (p))

//public
//Constructor.
extern void CGXDLMSData_1(CGXDLMSData *p);

//SN Constructor.
extern void CGXDLMSData_2(CGXDLMSData *p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSData_3(CGXDLMSData *p, String ln);

// Get value of COSEM Data object.
extern void CGXDLMSData_GetValue_1(CGXDLMSData *p, CGXDLMSVariant *out);

// Set value of COSEM Data object.
extern void CGXDLMSData_SetValue_1(CGXDLMSData *p, CGXDLMSVariant* value);

// Returns amount of attributes.
extern int CGXDLMSData_GetAttributeCount(CGXDLMSData *p);

// Returns amount of methods.
extern int CGXDLMSData_GetMethodCount(CGXDLMSData *p);

//Get attribute values of object.
extern void CGXDLMSData_GetValues(CGXDLMSData *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSData_GetAttributeIndexToRead(CGXDLMSData *p, Vector* attributes);//std::vector<int>& attributes

extern int CGXDLMSData_GetDataType(CGXDLMSData *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSData_GetValue_2(CGXDLMSData *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSData_SetValue_2(CGXDLMSData *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSData_d(CGXDLMSData *p);

#endif //GXDLMSDATA_H
