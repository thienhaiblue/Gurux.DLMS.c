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

#ifndef GXDLMSTCPUDPSETUP_H
#define GXDLMSTCPUDPSETUP_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"
#include "Map.h"

typedef struct // CGXDLMSTcpUdpSetup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSTcpUdpSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSTcpUdpSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSTcpUdpSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSTcpUdpSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSTcpUdpSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSTcpUdpSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSTcpUdpSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSTcpUdpSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    int m_Port;
    String m_IPReference;
    int m_MaximumSimultaneousConnections;
    int m_InactivityTimeout;
    int m_MaximumSegmentSize;

} CGXDLMSTcpUdpSetup;

#define CGXDLMSTcpUdpSetup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSTcpUdpSetup_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

/**
 Constructor.
*/
extern void CGXDLMSTcpUdpSetup_1(CGXDLMSTcpUdpSetup* p);

/**
 Constructor.

    @param ln Logical Name of the object.
*/
extern void CGXDLMSTcpUdpSetup_2(CGXDLMSTcpUdpSetup* p, String ln);


/**
 Constructor.

    @param ln Logical Name of the object.
    @param sn Short Name of the object.
*/
extern void CGXDLMSTcpUdpSetup_3(CGXDLMSTcpUdpSetup* p, String ln, short sn);

extern int CGXDLMSTcpUdpSetup_GetPort(CGXDLMSTcpUdpSetup* p);

extern void CGXDLMSTcpUdpSetup_SetPort(CGXDLMSTcpUdpSetup* p, int value);

extern String CGXDLMSTcpUdpSetup_GetIPReference(CGXDLMSTcpUdpSetup* p);

extern void CGXDLMSTcpUdpSetup_SetIPReference(CGXDLMSTcpUdpSetup* p, String value);

extern int CGXDLMSTcpUdpSetup_GetMaximumSegmentSize(CGXDLMSTcpUdpSetup* p);

extern void CGXDLMSTcpUdpSetup_SetMaximumSegmentSize(CGXDLMSTcpUdpSetup* p, int value);

extern int CGXDLMSTcpUdpSetup_GetMaximumSimultaneousConnections(CGXDLMSTcpUdpSetup* p);

extern void CGXDLMSTcpUdpSetup_SetMaximumSimultaneousConnections(CGXDLMSTcpUdpSetup* p, int value);

extern int CGXDLMSTcpUdpSetup_GetInactivityTimeout(CGXDLMSTcpUdpSetup* p);

extern void CGXDLMSTcpUdpSetup_SetInactivityTimeout(CGXDLMSTcpUdpSetup* p, int value);

// Returns amount of attributes.
extern int CGXDLMSTcpUdpSetup_GetAttributeCount(CGXDLMSTcpUdpSetup* p);

// Returns amount of methods.
extern int CGXDLMSTcpUdpSetup_GetMethodCount(CGXDLMSTcpUdpSetup* p);

//Get attribute values of object.
extern void CGXDLMSTcpUdpSetup_GetValues(CGXDLMSTcpUdpSetup* p, Vector* values);  //(std::vector<std::string>& values);

extern void CGXDLMSTcpUdpSetup_GetAttributeIndexToRead(CGXDLMSTcpUdpSetup* p, Vector* attributes); //(std::vector<int>& attributes);

extern int CGXDLMSTcpUdpSetup_GetDataType(CGXDLMSTcpUdpSetup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSTcpUdpSetup_GetValue(CGXDLMSTcpUdpSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSTcpUdpSetup_SetValue(CGXDLMSTcpUdpSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSTcpUdpSetup_d(CGXDLMSTcpUdpSetup* p);

#endif //GXDLMSTCPUDPSETUP_H
