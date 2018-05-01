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

#ifndef GXDLMSDISCONNECTCONTROL_H
#define GXDLMSDISCONNECTCONTROL_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"

typedef struct // class CGXDLMSDisconnectControl : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSDisconnectControl_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSDisconnectControl_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSDisconnectControl_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSDisconnectControl_SetValue
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
    d_FuncPtr d; // = CGXDLMSDisconnectControl_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSDisconnectControl_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSDisconnectControl_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSDisconnectControl_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    bool m_OutputState;
    DLMS_CONTROL_STATE m_ControlState;
    DLMS_CONTROL_MODE m_ControlMode;

} CGXDLMSDisconnectControl;

#define CGXDLMSDisconnectControl_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSDisconnectControl_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSDisconnectControl_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//public
//Constructor.
extern void CGXDLMSDisconnectControl_1(CGXDLMSDisconnectControl *p);

//SN Constructor.
extern void CGXDLMSDisconnectControl_2(CGXDLMSDisconnectControl *p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSDisconnectControl_3(CGXDLMSDisconnectControl *p, String ln);

/**
 Output state of COSEM Disconnect Control object.
*/
extern bool CGXDLMSDisconnectControl_GetOutputState(CGXDLMSDisconnectControl *p);
extern void CGXDLMSDisconnectControl_SetOutputState(CGXDLMSDisconnectControl *p, bool value);

/**
 Control state of COSEM Disconnect Control object.
*/
extern DLMS_CONTROL_STATE CGXDLMSDisconnectControl_GetControlState(CGXDLMSDisconnectControl *p);
extern void CGXDLMSDisconnectControl_SetControlState(CGXDLMSDisconnectControl *p, DLMS_CONTROL_STATE value);

/**
Control mode of COSEM Disconnect Control object.
*/
extern DLMS_CONTROL_MODE CGXDLMSDisconnectControl_GetControlMode(CGXDLMSDisconnectControl *p);
extern void CGXDLMSDisconnectControl_SetControlMode(CGXDLMSDisconnectControl *p, DLMS_CONTROL_MODE value);

// Returns amount of attributes.
extern int CGXDLMSDisconnectControl_GetAttributeCount(CGXDLMSDisconnectControl *p);

// Returns amount of methods.
extern int CGXDLMSDisconnectControl_GetMethodCount(CGXDLMSDisconnectControl *p);

//Get attribute values of object.
extern void CGXDLMSDisconnectControl_GetValues(CGXDLMSDisconnectControl *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSDisconnectControl_GetAttributeIndexToRead(CGXDLMSDisconnectControl *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSDisconnectControl_GetDataType(CGXDLMSDisconnectControl *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSDisconnectControl_GetValue(CGXDLMSDisconnectControl *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSDisconnectControl_SetValue(CGXDLMSDisconnectControl *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSDisconnectControl_d(CGXDLMSDisconnectControl *p);

#endif //GXDLMSDISCONNECTCONTROL_H
