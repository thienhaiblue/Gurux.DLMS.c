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

#ifndef GXDLMSSCHEDULE_H
#define GXDLMSSCHEDULE_H

#include "GXDLMSObject.h"
#include "GXDLMSScheduleEntry.h"

typedef struct//class CGXDLMSSchedule : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSSchedule_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSSchedule_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSSchedule_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSSchedule_SetValue
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
    d_FuncPtr d; // = CGXDLMSSchedule_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSSchedule_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSSchedule_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSSchedule_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_Entries; //std::vector<CGXDLMSScheduleEntry>

} CGXDLMSSchedule;

#define CGXDLMSSchedule_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSSchedule_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

extern void CGXDLMSSchedule_d(CGXDLMSSchedule* p);

//Constructor.
extern void CGXDLMSSchedule_1(CGXDLMSSchedule* p);

//SN Constructor.
extern void CGXDLMSSchedule_2(CGXDLMSSchedule* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSSchedule_3(CGXDLMSSchedule* p, String ln);

// Get value of COSEM Data object.
extern Vector* CGXDLMSSchedule_GetEntries(CGXDLMSSchedule* p); //std::vector<CGXDLMSScheduleEntry>&

// Set value of COSEM Data object.
extern void CGXDLMSSchedule_SetEntries(CGXDLMSSchedule* p, Vector* value); //std::vector<CGXDLMSScheduleEntry>&

// Returns amount of attributes.
extern int CGXDLMSSchedule_GetAttributeCount(CGXDLMSSchedule* p);

// Returns amount of methods.
extern int CGXDLMSSchedule_GetMethodCount(CGXDLMSSchedule* p);

//Get attribute values of object.
extern void CGXDLMSSchedule_GetValues(CGXDLMSSchedule* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSSchedule_GetAttributeIndexToRead(CGXDLMSSchedule* p, Vector* attributes); //std::vector<int>&

extern int CGXDLMSSchedule_GetDataType(CGXDLMSSchedule* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSSchedule_GetValue(CGXDLMSSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSSchedule_SetValue(CGXDLMSSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSSCHEDULE_H
