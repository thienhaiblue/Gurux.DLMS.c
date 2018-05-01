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

#ifndef GXDLMSSPECIALDAYSTABLE_H
#define GXDLMSSPECIALDAYSTABLE_H

#include "GXDLMSObject.h"
#include "GXDLMSSpecialDay.h"
#include "Vector.h"
#include "String.h"

typedef struct
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSSpecialDaysTable_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSSpecialDaysTable_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSSpecialDaysTable_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSSpecialDaysTable_SetValue
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
    d_FuncPtr d; // = CGXDLMSSpecialDaysTable_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSSpecialDaysTable_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSSpecialDaysTable_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSSpecialDaysTable_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_Entries; // std::vector<CGXDLMSSpecialDay*>

} CGXDLMSSpecialDaysTable;

#define CGXDLMSSpecialDaysTable_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSSpecialDaysTable_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p),(index))

//public
//Constructor.
extern void CGXDLMSSpecialDaysTable_1(CGXDLMSSpecialDaysTable *p);

//SN Constructor.
extern void CGXDLMSSpecialDaysTable_2(CGXDLMSSpecialDaysTable *p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSSpecialDaysTable_3(CGXDLMSSpecialDaysTable *p, String ln);

extern void CGXDLMSSpecialDaysTable_d(CGXDLMSSpecialDaysTable *p);

extern Vector* CGXDLMSSpecialDaysTable_GetEntries(CGXDLMSSpecialDaysTable *p);//std::vector<CGXDLMSSpecialDay*>&

// Returns amount of attributes.
extern int CGXDLMSSpecialDaysTable_GetAttributeCount(CGXDLMSSpecialDaysTable *p);

// Returns amount of methods.
extern int CGXDLMSSpecialDaysTable_GetMethodCount(CGXDLMSSpecialDaysTable *p);

//Get attribute values of object.
extern void CGXDLMSSpecialDaysTable_GetValues(CGXDLMSSpecialDaysTable *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSSpecialDaysTable_GetAttributeIndexToRead(CGXDLMSSpecialDaysTable *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSSpecialDaysTable_GetDataType(CGXDLMSSpecialDaysTable *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSSpecialDaysTable_GetValue(CGXDLMSSpecialDaysTable *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSSpecialDaysTable_SetValue(CGXDLMSSpecialDaysTable *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSSPECIALDAYSTABLE_H
