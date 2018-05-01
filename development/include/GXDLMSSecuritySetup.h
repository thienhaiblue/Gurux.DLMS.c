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

#ifndef GXDLMSDLMS_SECURITYSETUP_H
#define GXDLMSDLMS_SECURITYSETUP_H

#include "GXDLMSObject.h"

typedef struct //class CGXDLMSSecuritySetup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSSecuritySetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSSecuritySetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSSecuritySetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSSecuritySetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSSecuritySetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSSecuritySetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSSecuritySetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSSecuritySetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    unsigned char m_SecurityPolicy;
    DLMS_SECURITY_SUITE m_SecuritySuite;
    CGXByteBuffer m_ServerSystemTitle;
    CGXByteBuffer m_ClientSystemTitle;

} CGXDLMSSecuritySetup;

#define CGXDLMSSecuritySetup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSSecuritySetup_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSSecuritySetup_GetVersion(p)           CGXDLMSObject_GetVersion((CGXDLMSObject*) (p))

//Constructor.
extern void CGXDLMSSecuritySetup_1(CGXDLMSSecuritySetup* p);

//SN Constructor.
extern void CGXDLMSSecuritySetup_2(CGXDLMSSecuritySetup* p, String ln, unsigned short sn);


//LN Constructor.
extern void CGXDLMSSecuritySetup_3(CGXDLMSSecuritySetup* p, String ln);

//Use DLMS_SECURITY_POLICY for version 0 and DLMS_SECURITY_POLICY1 for version 1.
extern unsigned char CGXDLMSSecuritySetup_GetSecurityPolicy(CGXDLMSSecuritySetup* p);

//Use DLMS_SECURITY_POLICY for version 0 and DLMS_SECURITY_POLICY1 for version 1.
extern void CGXDLMSSecuritySetup_SetSecurityPolicy(CGXDLMSSecuritySetup* p, unsigned char value);

extern DLMS_SECURITY_SUITE CGXDLMSSecuritySetup_GetSecuritySuite(CGXDLMSSecuritySetup* p);

extern void CGXDLMSSecuritySetup_SetSecuritySuite(CGXDLMSSecuritySetup* p, DLMS_SECURITY_SUITE value);

extern CGXByteBuffer* CGXDLMSSecuritySetup_GetClientSystemTitle(CGXDLMSSecuritySetup* p);

extern void CGXDLMSSecuritySetup_SetClientSystemTitle(CGXDLMSSecuritySetup* p, CGXByteBuffer* value);

extern CGXByteBuffer* CGXDLMSSecuritySetup_GetServerSystemTitle(CGXDLMSSecuritySetup* p);

extern void CGXDLMSSecuritySetup_SetServerSystemTitle(CGXDLMSSecuritySetup* p, CGXByteBuffer* value);

// Returns amount of attributes.
extern int CGXDLMSSecuritySetup_GetAttributeCount(CGXDLMSSecuritySetup* p);

// Returns amount of methods.
extern int CGXDLMSSecuritySetup_GetMethodCount(CGXDLMSSecuritySetup* p);

//Get attribute values of object.
extern void CGXDLMSSecuritySetup_GetValues(CGXDLMSSecuritySetup* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSSecuritySetup_GetAttributeIndexToRead(CGXDLMSSecuritySetup* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSSecuritySetup_GetDataType(CGXDLMSSecuritySetup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSSecuritySetup_GetValue(CGXDLMSSecuritySetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSSecuritySetup_SetValue(CGXDLMSSecuritySetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSSecuritySetup_d(CGXDLMSSecuritySetup* p);

#endif //GXDLMSDLMS_SECURITYSETUP_H
