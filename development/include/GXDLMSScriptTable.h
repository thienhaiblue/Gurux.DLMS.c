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

#ifndef GXDLMSSCRIPTTABLE_H
#define GXDLMSSCRIPTTABLE_H

#include "GXDLMSObject.h"
#include "GXDLMSScript.h"

#include "String.h"
#include "Vector.h"

typedef struct //class CGXDLMSScriptTable : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSScriptTable_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSScriptTable_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSScriptTable_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSScriptTable_SetValue
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
    d_FuncPtr d; // = CGXDLMSScriptTable_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSScriptTable_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSScriptTable_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSScriptTable_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_Scripts; //std::vector<CGXDLMSScript*>
} CGXDLMSScriptTable;

#define CGXDLMSScriptTable_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSScriptTable_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSScriptTable_1(CGXDLMSScriptTable* p);

//SN Constructor.
extern void CGXDLMSScriptTable_2(CGXDLMSScriptTable* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSScriptTable_3(CGXDLMSScriptTable* p, String ln);

//Destructor.
extern void CGXDLMSScriptTable_d(CGXDLMSScriptTable* p);

extern Vector* CGXDLMSScriptTable_GetScripts(CGXDLMSScriptTable* p); //std::vector<CGXDLMSScript*>& 

// Returns amount of attributes.
extern int CGXDLMSScriptTable_GetAttributeCount(CGXDLMSScriptTable* p);

// Returns amount of methods.
extern int CGXDLMSScriptTable_GetMethodCount(CGXDLMSScriptTable* p);

//Get attribute values of object.
extern void CGXDLMSScriptTable_GetValues(CGXDLMSScriptTable* p, Vector* values); //std::vector<std::string>& 

extern void CGXDLMSScriptTable_GetAttributeIndexToRead(CGXDLMSScriptTable* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSScriptTable_GetDataType(CGXDLMSScriptTable* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSScriptTable_GetValue(CGXDLMSScriptTable* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSScriptTable_SetValue(CGXDLMSScriptTable* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSSCRIPTTABLE_H
