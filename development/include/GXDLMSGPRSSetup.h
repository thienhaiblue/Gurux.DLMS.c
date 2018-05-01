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

#ifndef GXDLMSGPRSSETUP_H
#define GXDLMSGPRSSETUP_H

#include "GXDLMSObject.h"
#include "GXDLMSQualityOfService.h"
#include "String.h"
#include "Vector.h"

typedef struct // class CGXDLMSGPRSSetup : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSGPRSSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSGPRSSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSGPRSSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSGPRSSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSGPRSSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSGPRSSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSGPRSSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSGPRSSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    String m_APN;
    long m_PINCode;
    CGXDLMSQualityOfService m_DefaultQualityOfService;
    CGXDLMSQualityOfService m_RequestedQualityOfService;

} CGXDLMSGPRSSetup;

#define CGXDLMSGPRSSetup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSGPRSSetup_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSGPRSSetup_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

//public
//Constructor.
extern void CGXDLMSGPRSSetup_1(CGXDLMSGPRSSetup *p);

//SN Constructor.
extern void CGXDLMSGPRSSetup_2(CGXDLMSGPRSSetup *p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSGPRSSetup_3(CGXDLMSGPRSSetup *p, String ln);

extern String CGXDLMSGPRSSetup_GetAPN(CGXDLMSGPRSSetup *p);
extern void CGXDLMSGPRSSetup_SetAPN(CGXDLMSGPRSSetup *p, String value);

extern long CGXDLMSGPRSSetup_GetPINCode(CGXDLMSGPRSSetup *p);
extern void CGXDLMSGPRSSetup_SetPINCode(CGXDLMSGPRSSetup *p, long value);

extern CGXDLMSQualityOfService* CGXDLMSGPRSSetup_GetDefaultQualityOfService(CGXDLMSGPRSSetup *p);

extern CGXDLMSQualityOfService* CGXDLMSGPRSSetup_GetRequestedQualityOfService(CGXDLMSGPRSSetup *p);

// Returns amount of attributes.
extern int CGXDLMSGPRSSetup_GetAttributeCount(CGXDLMSGPRSSetup *p);

// Returns amount of methods.
extern int CGXDLMSGPRSSetup_GetMethodCount(CGXDLMSGPRSSetup *p);

//Get attribute values of object.
extern void CGXDLMSGPRSSetup_GetValues(CGXDLMSGPRSSetup *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSGPRSSetup_GetAttributeIndexToRead(CGXDLMSGPRSSetup *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSGPRSSetup_GetDataType(CGXDLMSGPRSSetup *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSGPRSSetup_GetValue(CGXDLMSGPRSSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSGPRSSetup_SetValue(CGXDLMSGPRSSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSGPRSSetup_d(CGXDLMSGPRSSetup *p);

#endif //GXDLMSGPRSSETUP_H
