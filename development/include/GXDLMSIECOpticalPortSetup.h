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

#ifndef GXDLMSIECOPTICALPORTSETUP_H
#define GXDLMSIECOPTICALPORTSETUP_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"

typedef struct // class CGXDLMSIECOpticalPortSetup : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSIECOpticalPortSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSIECOpticalPortSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSIECOpticalPortSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSIECOpticalPortSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSIECOpticalPortSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSIECOpticalPortSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSIECOpticalPortSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSIECOpticalPortSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    String m_Password1;
    String m_Password2;
    String m_Password5;
    DLMS_OPTICAL_PROTOCOL_MODE m_DefaultMode;
    DLMS_BAUD_RATE m_DefaultBaudrate;
    DLMS_BAUD_RATE m_ProposedBaudrate;
    DLMS_LOCAL_PORT_RESPONSE_TIME m_ResponseTime;
    String m_DeviceAddress;

} CGXDLMSIECOpticalPortSetup;

#define CGXDLMSIECOpticalPortSetup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSIECOpticalPortSetup_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//private
//static void CGXDLMSIECOpticalPortSetup_Init(CGXDLMSIECOpticalPortSetup *p);

//public
//Constructor.
extern void CGXDLMSIECOpticalPortSetup_1(CGXDLMSIECOpticalPortSetup *p);
//SN Constructor.
extern void CGXDLMSIECOpticalPortSetup_2(CGXDLMSIECOpticalPortSetup *p, String ln, unsigned short sn);
//LN Constructor.
extern void CGXDLMSIECOpticalPortSetup_3(CGXDLMSIECOpticalPortSetup *p, String ln);

extern DLMS_OPTICAL_PROTOCOL_MODE CGXDLMSIECOpticalPortSetup_GetDefaultMode(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetDefaultMode(CGXDLMSIECOpticalPortSetup *p, DLMS_OPTICAL_PROTOCOL_MODE value);

extern DLMS_BAUD_RATE CGXDLMSIECOpticalPortSetup_GetDefaultBaudrate(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetDefaultBaudrate(CGXDLMSIECOpticalPortSetup *p, DLMS_BAUD_RATE value);

extern DLMS_BAUD_RATE CGXDLMSIECOpticalPortSetup_GetProposedBaudrate(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetProposedBaudrate(CGXDLMSIECOpticalPortSetup *p, DLMS_BAUD_RATE value);

extern DLMS_LOCAL_PORT_RESPONSE_TIME CGXDLMSIECOpticalPortSetup_GetResponseTime(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetResponseTime(CGXDLMSIECOpticalPortSetup *p, DLMS_LOCAL_PORT_RESPONSE_TIME value);

extern String CGXDLMSIECOpticalPortSetup_GetDeviceAddress(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetDeviceAddress(CGXDLMSIECOpticalPortSetup *p, String value);

extern String CGXDLMSIECOpticalPortSetup_GetPassword1(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetPassword1(CGXDLMSIECOpticalPortSetup *p, String value);

extern String CGXDLMSIECOpticalPortSetup_GetPassword2(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetPassword2(CGXDLMSIECOpticalPortSetup *p, String value);

extern String CGXDLMSIECOpticalPortSetup_GetPassword5(CGXDLMSIECOpticalPortSetup *p);
extern void CGXDLMSIECOpticalPortSetup_SetPassword5(CGXDLMSIECOpticalPortSetup *p, String value);

// Returns amount of attributes.
extern int CGXDLMSIECOpticalPortSetup_GetAttributeCount(CGXDLMSIECOpticalPortSetup *p);

// Returns amount of methods.
extern int CGXDLMSIECOpticalPortSetup_GetMethodCount(CGXDLMSIECOpticalPortSetup *p);

//Get attribute values of object.
extern void CGXDLMSIECOpticalPortSetup_GetValues(CGXDLMSIECOpticalPortSetup *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSIECOpticalPortSetup_GetAttributeIndexToRead(CGXDLMSIECOpticalPortSetup *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSIECOpticalPortSetup_GetDataType(CGXDLMSIECOpticalPortSetup *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSIECOpticalPortSetup_GetValue(CGXDLMSIECOpticalPortSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSIECOpticalPortSetup_SetValue(CGXDLMSIECOpticalPortSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSIECOpticalPortSetup_d(CGXDLMSIECOpticalPortSetup *p);

#endif //GXDLMSIECOPTICALPORTSETUP_H
