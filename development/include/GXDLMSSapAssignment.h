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

#ifndef GXDLMSSAPASSIGNMENT_H
#define GXDLMSSAPASSIGNMENT_H

#include "GXDLMSObject.h"

#include "Map.h"
#include "Vector.h"
#include "String.h"

typedef struct //class CGXDLMSSapAssignment : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSSapAssignment_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSSapAssignment_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSSapAssignment_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSSapAssignment_SetValue
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
    d_FuncPtr d; // = CGXDLMSSapAssignment_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSSapAssignment_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSSapAssignment_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSSapAssignment_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Map m_SapAssignmentList; // std::map<int, std::string >

} CGXDLMSSapAssignment;

#define CGXDLMSSapAssignment_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSSapAssignment_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

/**
 Constructor.
*/
extern void CGXDLMSSapAssignment_1(CGXDLMSSapAssignment* p);

/**
 Constructor.

    @param ln Logical Name of the object.
*/
extern void CGXDLMSSapAssignment_2(CGXDLMSSapAssignment* p, String ln);

/**
 Constructor.
    @param sn Short Name of the object.
*/
extern void CGXDLMSSapAssignment_3(CGXDLMSSapAssignment* p, String ln, unsigned short sn);

extern Map* CGXDLMSSapAssignment_GetSapAssignmentList(CGXDLMSSapAssignment* p); //std::map<int, std::string >& 

extern void CGXDLMSSapAssignment_SetSapAssignmentList(CGXDLMSSapAssignment* p, Map* value); //std::map<int, std::string >&

// Returns amount of attributes.
extern int CGXDLMSSapAssignment_GetAttributeCount(CGXDLMSSapAssignment* p);

// Returns amount of methods.
extern int CGXDLMSSapAssignment_GetMethodCount(CGXDLMSSapAssignment* p);

//Get attribute values of object.
extern void CGXDLMSSapAssignment_GetValues(CGXDLMSSapAssignment* p, Vector* values); //std::vector<std::string>& 

extern void CGXDLMSSapAssignment_GetAttributeIndexToRead(CGXDLMSSapAssignment* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSSapAssignment_GetDataType(CGXDLMSSapAssignment* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSSapAssignment_GetValue(CGXDLMSSapAssignment* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

/*
    * Set value of given attribute.
    */
extern int CGXDLMSSapAssignment_SetValue(CGXDLMSSapAssignment* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSSapAssignment_d(CGXDLMSSapAssignment* p);

#endif //GXDLMSSAPASSIGNMENT_H
