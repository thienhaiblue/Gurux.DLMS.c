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

#ifndef GXDLMSIECHDLCSETUP_H
#define GXDLMSIECHDLCSETUP_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"

typedef struct //class CGXDLMSIecHdlcSetup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSIecHdlcSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSIecHdlcSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSIecHdlcSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSIecHdlcSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSIecHdlcSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSIecHdlcSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSIecHdlcSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSIecHdlcSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    int m_InactivityTimeout;
    int m_DeviceAddress;
    int m_MaximumInfoLengthTransmit;
    DLMS_BAUD_RATE m_CommunicationSpeed;
    int m_WindowSizeTransmit;
    int m_WindowSizeReceive;
    int m_InterCharachterTimeout;
    int m_MaximumInfoLengthReceive;

} CGXDLMSIecHdlcSetup;

#define CGXDLMSIecHdlcSetup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSIecHdlcSetup_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSIecHdlcSetup_1(CGXDLMSIecHdlcSetup* p);

//SN Constructor.
extern void CGXDLMSIecHdlcSetup_2(CGXDLMSIecHdlcSetup* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSIecHdlcSetup_3(CGXDLMSIecHdlcSetup* p, String ln);

extern DLMS_BAUD_RATE CGXDLMSIecHdlcSetup_GetCommunicationSpeed(CGXDLMSIecHdlcSetup* p);

extern void CGXDLMSIecHdlcSetup_SetCommunicationSpeed(CGXDLMSIecHdlcSetup* p, DLMS_BAUD_RATE value);

extern int CGXDLMSIecHdlcSetup_GetWindowSizeTransmit(CGXDLMSIecHdlcSetup* p);
extern void CGXDLMSIecHdlcSetup_SetWindowSizeTransmit(CGXDLMSIecHdlcSetup* p, int value);

extern int CGXDLMSIecHdlcSetup_GetWindowSizeReceive(CGXDLMSIecHdlcSetup* p);
extern void CGXDLMSIecHdlcSetup_SetWindowSizeReceive(CGXDLMSIecHdlcSetup* p, int value);
extern int CGXDLMSIecHdlcSetup_GetMaximumInfoLengthTransmit(CGXDLMSIecHdlcSetup* p);
extern void CGXDLMSIecHdlcSetup_SetMaximumInfoLengthTransmit(CGXDLMSIecHdlcSetup* p, int value);
extern int CGXDLMSIecHdlcSetup_GetMaximumInfoLengthReceive(CGXDLMSIecHdlcSetup* p);
extern void CGXDLMSIecHdlcSetup_SetMaximumInfoLengthReceive(CGXDLMSIecHdlcSetup* p, int value);

extern int CGXDLMSIecHdlcSetup_GetInterCharachterTimeout(CGXDLMSIecHdlcSetup* p);
extern void CGXDLMSIecHdlcSetup_SetInterCharachterTimeout(CGXDLMSIecHdlcSetup* p, int value);


extern int CGXDLMSIecHdlcSetup_GetInactivityTimeout(CGXDLMSIecHdlcSetup* p);
extern void CGXDLMSIecHdlcSetup_SetInactivityTimeout(CGXDLMSIecHdlcSetup* p, int value);

extern int CGXDLMSIecHdlcSetup_GetDeviceAddress(CGXDLMSIecHdlcSetup* p);
extern void CGXDLMSIecHdlcSetup_SetDeviceAddress(CGXDLMSIecHdlcSetup* p, int value);

// Returns amount of attributes.
extern int CGXDLMSIecHdlcSetup_GetAttributeCount(CGXDLMSIecHdlcSetup* p);
// Returns amount of methods.
extern int CGXDLMSIecHdlcSetup_GetMethodCount(CGXDLMSIecHdlcSetup* p);

//Get attribute values of object.
extern void CGXDLMSIecHdlcSetup_GetValues(CGXDLMSIecHdlcSetup* p, Vector* values);//std::vector<std::string>& values);

extern void CGXDLMSIecHdlcSetup_GetAttributeIndexToRead(CGXDLMSIecHdlcSetup* p, Vector* attributes);//std::vector<int>& attributes);

extern int CGXDLMSIecHdlcSetup_GetDataType(CGXDLMSIecHdlcSetup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSIecHdlcSetup_GetValue(CGXDLMSIecHdlcSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSIecHdlcSetup_SetValue(CGXDLMSIecHdlcSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSIecHdlcSetup_d(CGXDLMSIecHdlcSetup* p);

#endif //GXDLMSIECHDLCSETUP_H
