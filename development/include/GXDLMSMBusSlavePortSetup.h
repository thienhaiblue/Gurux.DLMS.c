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

#ifndef GXDLMSMBUSSLAVEPORTSETUP_H
#define GXDLMSMBUSSLAVEPORTSETUP_H

#include "GXDLMSObject.h"

typedef struct //class CGXDLMSMBusSlavePortSetup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSMBusSlavePortSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSMBusSlavePortSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSMBusSlavePortSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSMBusSlavePortSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSMBusSlavePortSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSMBusSlavePortSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSMBusSlavePortSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSMBusSlavePortSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    DLMS_BAUD_RATE m_DefaultBaud;
    DLMS_BAUD_RATE m_AvailableBaud;
    DLMS_ADDRESS_STATE m_AddressState;
    int m_BusAddress;

} CGXDLMSMBusSlavePortSetup;

//Constructor.
extern void CGXDLMSMBusSlavePortSetup_1(CGXDLMSMBusSlavePortSetup* p);

//SN Constructor.
extern void CGXDLMSMBusSlavePortSetup_2(CGXDLMSMBusSlavePortSetup* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSMBusSlavePortSetup_3(CGXDLMSMBusSlavePortSetup* p, String ln);

/**
 Defines the baud rate for the opening sequence.
*/
extern DLMS_BAUD_RATE CGXDLMSMBusSlavePortSetup_GetDefaultBaud(CGXDLMSMBusSlavePortSetup* p);

extern void CGXDLMSMBusSlavePortSetup_SetDefaultBaud(CGXDLMSMBusSlavePortSetup* p, DLMS_BAUD_RATE value);

/**
 Defines the baud rate for the opening sequence.
*/
extern DLMS_BAUD_RATE CGXDLMSMBusSlavePortSetup_GetAvailableBaud(CGXDLMSMBusSlavePortSetup* p);

extern void CGXDLMSMBusSlavePortSetup_SetAvailableBaud(CGXDLMSMBusSlavePortSetup* p, DLMS_BAUD_RATE value);

/**
 Defines whether or not the device has been assigned an address
    * since last power up of the device.
*/
extern DLMS_ADDRESS_STATE CGXDLMSMBusSlavePortSetup_GetAddressState(CGXDLMSMBusSlavePortSetup* p);

extern void CGXDLMSMBusSlavePortSetup_SetAddressState(CGXDLMSMBusSlavePortSetup* p, DLMS_ADDRESS_STATE value);

/**
 Defines the baud rate for the opening sequence.
*/
extern int CGXDLMSMBusSlavePortSetup_GetBusAddress(CGXDLMSMBusSlavePortSetup* p);

extern void CGXDLMSMBusSlavePortSetup_SetBusAddress(CGXDLMSMBusSlavePortSetup* p, int value);

// Returns amount of attributes.
extern int CGXDLMSMBusSlavePortSetup_GetAttributeCount(CGXDLMSMBusSlavePortSetup* p);

// Returns amount of methods.
extern int CGXDLMSMBusSlavePortSetup_GetMethodCount(CGXDLMSMBusSlavePortSetup* p);

//Get attribute values of object.
extern void CGXDLMSMBusSlavePortSetup_GetValues(CGXDLMSMBusSlavePortSetup* p, Vector* values); //std::vector<std::string>& 

extern void CGXDLMSMBusSlavePortSetup_GetAttributeIndexToRead(CGXDLMSMBusSlavePortSetup* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSMBusSlavePortSetup_GetDataType(CGXDLMSMBusSlavePortSetup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSMBusSlavePortSetup_GetValue(CGXDLMSMBusSlavePortSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSMBusSlavePortSetup_SetValue(CGXDLMSMBusSlavePortSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSMBusSlavePortSetup_d(CGXDLMSMBusSlavePortSetup* p);

#endif //GXDLMSMBUSSLAVEPORTSETUP_H
