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

#ifndef GXDLMSMBUSMASTERPORTSETUP_H
#define GXDLMSMBUSMASTERPORTSETUP_H

#include "GXDLMSObject.h"

typedef struct//class CGXDLMSMBusMasterPortSetup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSMBusMasterPortSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSMBusMasterPortSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSMBusMasterPortSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSMBusMasterPortSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSMBusMasterPortSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSMBusMasterPortSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSMBusMasterPortSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSMBusMasterPortSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    DLMS_BAUD_RATE m_CommSpeed;

} CGXDLMSMBusMasterPortSetup;

//Constructor.
extern void CGXDLMSMBusMasterPortSetup_1(CGXDLMSMBusMasterPortSetup* p);

//SN Constructor.
extern void CGXDLMSMBusMasterPortSetup_2(CGXDLMSMBusMasterPortSetup* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSMBusMasterPortSetup_3(CGXDLMSMBusMasterPortSetup* p, String ln);

// The communication speed supported by the port.
extern DLMS_BAUD_RATE CGXDLMSMBusMasterPortSetup_GetCommSpeed(CGXDLMSMBusMasterPortSetup* p);
extern void CGXDLMSMBusMasterPortSetup_SetCommSpeed(CGXDLMSMBusMasterPortSetup* p, DLMS_BAUD_RATE value);

// Returns amount of attributes.
extern int CGXDLMSMBusMasterPortSetup_GetAttributeCount(CGXDLMSMBusMasterPortSetup* p);

// Returns amount of methods.
extern int CGXDLMSMBusMasterPortSetup_GetMethodCount(CGXDLMSMBusMasterPortSetup* p);

//Get attribute values of object.
extern void CGXDLMSMBusMasterPortSetup_GetValues(CGXDLMSMBusMasterPortSetup* p, Vector* values); //std::vector<std::string>& 

extern void CGXDLMSMBusMasterPortSetup_GetAttributeIndexToRead(CGXDLMSMBusMasterPortSetup* p, Vector* attributes);  //std::vector<int>& 

extern int CGXDLMSMBusMasterPortSetup_GetDataType(CGXDLMSMBusMasterPortSetup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSMBusMasterPortSetup_GetValue(CGXDLMSMBusMasterPortSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSMBusMasterPortSetup_SetValue(CGXDLMSMBusMasterPortSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSMBusMasterPortSetup_d(CGXDLMSMBusMasterPortSetup* p);

#endif //GXDLMSMBUSMASTERPORTSETUP_H
