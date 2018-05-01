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

#ifndef GXDLMSIP4SETUP_H
#define GXDLMSIP4SETUP_H

#include "GXDLMSObject.h"
#include "GXDLMSIp4SetupIpOption.h"

#include "Vector.h"
#include "String.h"

typedef struct //class CGXDLMSIp4Setup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSIp4Setup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSIp4Setup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSIp4Setup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSIp4Setup_SetValue
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
    d_FuncPtr d; // = CGXDLMSIp4Setup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSIp4Setup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSIp4Setup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSIp4Setup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    String m_DataLinkLayerReference;
    String m_IPAddress;
    Vector m_MulticastIPAddress; //std::vector<unsigned long>
    Vector m_IPOptions; // std::vector<CGXDLMSIp4SetupIpOption>
    unsigned long m_SubnetMask;
    unsigned long m_GatewayIPAddress;
    bool m_UseDHCP;
    unsigned long m_PrimaryDNSAddress;
    unsigned long m_SecondaryDNSAddress;

    CGXDLMSVariant m_Value;
} CGXDLMSIp4Setup;

#define CGXDLMSIp4Setup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSIp4Setup_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSIp4Setup_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSIp4Setup_1(CGXDLMSIp4Setup* p);

//SN Constructor.
extern void CGXDLMSIp4Setup_2(CGXDLMSIp4Setup* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSIp4Setup_3(CGXDLMSIp4Setup* p, String ln);

extern String* CGXDLMSIp4Setup_GetDataLinkLayerReference(CGXDLMSIp4Setup* p);
extern void CGXDLMSIp4Setup_SetDataLinkLayerReference(CGXDLMSIp4Setup* p, String value);

extern String* CGXDLMSIp4Setup_GetIPAddress(CGXDLMSIp4Setup* p);
extern void CGXDLMSIp4Setup_SetIPAddress(CGXDLMSIp4Setup* p, String* value);

extern Vector* CGXDLMSIp4Setup_GetMulticastIPAddress(CGXDLMSIp4Setup* p); //std::vector<unsigned long>& 

extern Vector* CGXDLMSIp4Setup_GetIPOptions(CGXDLMSIp4Setup* p); //std::vector<CGXDLMSIp4SetupIpOption>&

extern void CGXDLMSIp4Setup_SetIPOptions(CGXDLMSIp4Setup* p, Vector* value); //std::vector<CGXDLMSIp4SetupIpOption>&

extern unsigned long CGXDLMSIp4Setup_GetSubnetMask(CGXDLMSIp4Setup* p);
extern void CGXDLMSIp4Setup_SetSubnetMask(CGXDLMSIp4Setup* p, unsigned long value);

extern unsigned long CGXDLMSIp4Setup_GetGatewayIPAddress(CGXDLMSIp4Setup* p);
extern void CGXDLMSIp4Setup_SetGatewayIPAddress(CGXDLMSIp4Setup* p, unsigned long value);

extern bool CGXDLMSIp4Setup_GetUseDHCP(CGXDLMSIp4Setup* p);
extern void CGXDLMSIp4Setup_SetUseDHCP(CGXDLMSIp4Setup* p, bool value);

extern unsigned long CGXDLMSIp4Setup_GetPrimaryDNSAddress(CGXDLMSIp4Setup* p);
extern void CGXDLMSIp4Setup_SetPrimaryDNSAddress(CGXDLMSIp4Setup* p, unsigned long value);

extern unsigned long CGXDLMSIp4Setup_GetSecondaryDNSAddress(CGXDLMSIp4Setup* p);
extern void CGXDLMSIp4Setup_SetSecondaryDNSAddress(CGXDLMSIp4Setup* p, unsigned long value);

// Returns amount of attributes.
extern int CGXDLMSIp4Setup_GetAttributeCount(CGXDLMSIp4Setup* p);

// Returns amount of methods.
extern int CGXDLMSIp4Setup_GetMethodCount(CGXDLMSIp4Setup* p);

//Get attribute values of object.
extern void CGXDLMSIp4Setup_GetValues(CGXDLMSIp4Setup* p, Vector* values); //std::vector<std::string>& 

extern void CGXDLMSIp4Setup_GetAttributeIndexToRead(CGXDLMSIp4Setup* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSIp4Setup_GetDataType(CGXDLMSIp4Setup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSIp4Setup_GetValue(CGXDLMSIp4Setup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSIp4Setup_SetValue(CGXDLMSIp4Setup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSIp4Setup_d(CGXDLMSIp4Setup* p);

#endif //GXDLMSIP4SETUP_H
