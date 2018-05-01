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

#ifndef GXDLMSMBUSCLIENT_H
#define GXDLMSMBUSCLIENT_H

#include "GXDLMSObject.h"

#include "Vector.h"
#include "String.h"

typedef struct //class CGXDLMSMBusClient : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSMBusClient_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSMBusClient_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSMBusClient_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSMBusClient_SetValue
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
    d_FuncPtr d; // = CGXDLMSMBusClient_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSMBusClient_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSMBusClient_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSMBusClient_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    long m_CapturePeriod;
    int m_PrimaryAddress;
    String m_MBusPortReference;
    Vector m_CaptureDefinition; // std::vector<std::pair<std::string, std::string> >
    long m_IdentificationNumber;
    int m_ManufacturerID;
    int m_DataHeaderVersion;
    int m_DeviceType;
    int m_AccessNumber;
    int m_Status;
    int m_Alarm;

} CGXDLMSMBusClient;

#define CGXDLMSMBusClient_GetVersion(p)           CGXDLMSObject_GetVersion((CGXDLMSObject*) (p))
#define CGXDLMSMBusClient_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSMBusClient_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSMBusClient_1(CGXDLMSMBusClient* p);

//SN Constructor.
extern void CGXDLMSMBusClient_2(CGXDLMSMBusClient* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSMBusClient_3(CGXDLMSMBusClient* p, String ln);

/**
Provides reference to an "M-Bus master port setup" object, used to configure
an M-Bus port, each interface allowing to exchange data with one or more
M-Bus slave devices
*/
extern String CGXDLMSMBusClient_GetMBusPortReference(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetMBusPortReference(CGXDLMSMBusClient* p, String value);

extern Vector* CGXDLMSMBusClient_GetCaptureDefinition(CGXDLMSMBusClient* p); //std::vector<std::pair<std::string, std::string> >&

extern long CGXDLMSMBusClient_GetCapturePeriod(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetCapturePeriod(CGXDLMSMBusClient* p, long value);

extern int CGXDLMSMBusClient_GetPrimaryAddress(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetPrimaryAddress(CGXDLMSMBusClient* p, int value);

extern long CGXDLMSMBusClient_GetIdentificationNumber(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetIdentificationNumber(CGXDLMSMBusClient* p, long value);

extern int CGXDLMSMBusClient_GetManufacturerID(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetManufacturerID(CGXDLMSMBusClient* p, int value);

/*
    * Carries the Version element of the data header as specified in EN
    * 13757-3 sub-clause 5.6.
    */
extern int CGXDLMSMBusClient_GetDataHeaderVersion(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetDataHeaderVersion(CGXDLMSMBusClient* p, int value);

extern int CGXDLMSMBusClient_GetDeviceType(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetDeviceType(CGXDLMSMBusClient* p, int value);

extern int CGXDLMSMBusClient_GetAccessNumber(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetAccessNumber(CGXDLMSMBusClient* p, int value);

extern int CGXDLMSMBusClient_GetStatus(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetStatus(CGXDLMSMBusClient* p, int value);

extern int CGXDLMSMBusClient_GetAlarm(CGXDLMSMBusClient* p);
extern void CGXDLMSMBusClient_SetAlarm(CGXDLMSMBusClient* p, int value);

// Returns amount of attributes.
extern int CGXDLMSMBusClient_GetAttributeCount(CGXDLMSMBusClient* p);

// Returns amount of methods.
extern int CGXDLMSMBusClient_GetMethodCount(CGXDLMSMBusClient* p);

//Get attribute values of object.
extern void CGXDLMSMBusClient_GetValues(CGXDLMSMBusClient* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSMBusClient_GetAttributeIndexToRead(CGXDLMSMBusClient* p, Vector* attributes); //std::vector<int>&

extern int CGXDLMSMBusClient_GetDataType(CGXDLMSMBusClient* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSMBusClient_GetValue(CGXDLMSMBusClient* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSMBusClient_SetValue(CGXDLMSMBusClient* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSMBusClient_d(CGXDLMSMBusClient* p);

#endif //GXDLMSMBUSCLIENT_H
