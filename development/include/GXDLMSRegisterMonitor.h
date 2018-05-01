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

#ifndef GXDLMSREGISTERMONITOR_H
#define GXDLMSREGISTERMONITOR_H

#include "GXDLMSMonitoredValue.h"
#include "GXDLMSActionSet.h"

typedef struct //class CGXDLMSRegisterMonitor : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSRegisterMonitor_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSRegisterMonitor_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSRegisterMonitor_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSRegisterMonitor_SetValue
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
    d_FuncPtr d; // = CGXDLMSRegisterMonitor_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSRegisterMonitor_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSRegisterMonitor_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSRegisterMonitor_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_Actions; //std::vector<CGXDLMSActionSet*>
    CGXDLMSMonitoredValue m_MonitoredValue;
    Vector m_Thresholds; //std::vector<CGXDLMSVariant> 

} CGXDLMSRegisterMonitor;

#define CGXDLMSRegisterMonitor_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSRegisterMonitor_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

/**
 Constructor.
*/
extern void CGXDLMSRegisterMonitor_1(CGXDLMSRegisterMonitor* p);

/**
 destructor.
*/
// virtual
extern void CGXDLMSRegisterMonitor_d(CGXDLMSRegisterMonitor* p);

/**
 Constructor.

    @param ln Logical Name of the object.
*/
extern void CGXDLMSRegisterMonitor_2(CGXDLMSRegisterMonitor* p, String ln);

/**
 Constructor.

    @param ln Logical Name of the object.
    @param sn Short Name of the object.
*/
extern void CGXDLMSRegisterMonitor_3(CGXDLMSRegisterMonitor* p, String ln, unsigned short sn);

extern Vector* CGXDLMSRegisterMonitor_GetThresholds(CGXDLMSRegisterMonitor* p); //std::vector<CGXDLMSVariant>

extern void CGXDLMSRegisterMonitor_SetThresholds(CGXDLMSRegisterMonitor* p, Vector value); //std::vector<CGXDLMSVariant> 


extern CGXDLMSMonitoredValue* CGXDLMSRegisterMonitor_GetMonitoredValue(CGXDLMSRegisterMonitor* p);

extern void CGXDLMSRegisterMonitor_SetMonitoredValue(CGXDLMSRegisterMonitor* p, CGXDLMSMonitoredValue* value);

extern Vector* CGXDLMSRegisterMonitor_GetActions(CGXDLMSRegisterMonitor* p); //std::vector<CGXDLMSActionSet*>&

// Returns amount of attributes.
extern int CGXDLMSRegisterMonitor_GetAttributeCount(CGXDLMSRegisterMonitor* p);

// Returns amount of methods.
extern int CGXDLMSRegisterMonitor_GetMethodCount(CGXDLMSRegisterMonitor* p);

//Get attribute values of object.
extern void CGXDLMSRegisterMonitor_GetValues(CGXDLMSRegisterMonitor* p, Vector* values); //std::vector<std::string>& 

extern void CGXDLMSRegisterMonitor_GetAttributeIndexToRead(CGXDLMSRegisterMonitor* p, Vector* attributes); //std::vector<std::string>& 

extern int CGXDLMSRegisterMonitor_GetDataType(CGXDLMSRegisterMonitor* p, int index, DLMS_DATA_TYPE* type);

/*
    * Returns value of given attribute.
    */
extern int CGXDLMSRegisterMonitor_GetValue(CGXDLMSRegisterMonitor* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

/*
    * Set value of given attribute.
    */
extern int CGXDLMSRegisterMonitor_SetValue(CGXDLMSRegisterMonitor* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSREGISTERMONITOR_H
