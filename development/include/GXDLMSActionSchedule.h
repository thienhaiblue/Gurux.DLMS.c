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

#ifndef GXDLMSACTIONSCHEDULE_H
#define GXDLMSACTIONSCHEDULE_H

#include "GXDLMSObject.h"
#include "String.h"

typedef struct // class CGXDLMSActionSchedule : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSActionSchedule_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSActionSchedule_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSActionSchedule_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSActionSchedule_SetValue
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
    d_FuncPtr d; // = CGXDLMSActionSchedule_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSActionSchedule_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSActionSchedule_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSActionSchedule_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    String m_ExecutedScriptLogicalName;
    int m_ExecutedScriptSelector;
    DLMS_SINGLE_ACTION_SCHEDULE_TYPE m_Type;
    Vector m_ExecutionTime; // std::vector<CGXDateTime> m_ExecutionTime;
} CGXDLMSActionSchedule;

#define CGXDLMSActionSchedule_IsRead(p, index)                CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSActionSchedule_GetLogicalName_2(p, ln)         CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSActionSchedule_GetLogicalName_1(target, value) CGXDLMSObject_GetLogicalName_1((target), (value))
#define CGXDLMSActionSchedule_SetLogicalName(target, value)   CGXDLMSObject_SetLogicalName((target), (value))

    /**
     Constructor.
    */
extern void CGXDLMSActionSchedule_1(CGXDLMSActionSchedule* p);

    /**
     Constructor.

     @param ln Logical Name of the object.
    */
extern void CGXDLMSActionSchedule_2(CGXDLMSActionSchedule* p, String ln);

    /**
     Constructor.

     @param ln Logical Name of the object.
     @param sn Short Name of the object.
    */
extern void CGXDLMSActionSchedule_3(CGXDLMSActionSchedule* p, String ln, unsigned short sn);

extern String CGXDLMSActionSchedule_GetExecutedScriptLogicalName(CGXDLMSActionSchedule* p);
extern void CGXDLMSActionSchedule_SetExecutedScriptLogicalName(CGXDLMSActionSchedule* p, String value);

extern int CGXDLMSActionSchedule_GetExecutedScriptSelector(CGXDLMSActionSchedule* p);
extern void CGXDLMSActionSchedule_SetExecutedScriptSelector(CGXDLMSActionSchedule* p, int value);

extern DLMS_SINGLE_ACTION_SCHEDULE_TYPE CGXDLMSActionSchedule_GetType(CGXDLMSActionSchedule* p);
extern void CGXDLMSActionSchedule_SetType(CGXDLMSActionSchedule* p, DLMS_SINGLE_ACTION_SCHEDULE_TYPE value);

extern Vector* CGXDLMSActionSchedule_GetExecutionTime(CGXDLMSActionSchedule* p); //std::vector<CGXDateTime> GetExecutionTime();
extern void CGXDLMSActionSchedule_SetExecutionTime(CGXDLMSActionSchedule* p, Vector value); // std::vector<CGXDateTime>

    // Returns amount of attributes.
extern int CGXDLMSActionSchedule_GetAttributeCount(CGXDLMSActionSchedule* p);

    // Returns amount of methods.
extern int CGXDLMSActionSchedule_GetMethodCount(CGXDLMSActionSchedule* p);

    //Get attribute values of object.
extern void CGXDLMSActionSchedule_GetValues(CGXDLMSActionSchedule* p, Vector* values); // std::vector<std::string>&

extern void CGXDLMSActionSchedule_GetAttributeIndexToRead(CGXDLMSActionSchedule* p, Vector* attributes); // std::vector<int>&

extern int CGXDLMSActionSchedule_GetDataType(CGXDLMSActionSchedule* p, int index, DLMS_DATA_TYPE* type);

    // Returns value of given attribute.
extern int CGXDLMSActionSchedule_GetValue(CGXDLMSActionSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

    // Set value of given attribute.
extern int CGXDLMSActionSchedule_SetValue(CGXDLMSActionSchedule* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSActionSchedule_d(CGXDLMSActionSchedule* p);

#endif //GXDLMSACTIONSCHEDULE_H
