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
#ifndef GXDLMSEXTENDEDREGISTER_H
#define GXDLMSEXTENDEDREGISTER_H

#include <stdbool.h>
#include <math.h>
#include "GXDLMSRegister.h"

typedef struct //class CGXDLMSExtendedRegister : public CGXDLMSRegister
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSExtendedRegister_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSExtendedRegister_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSExtendedRegister_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSExtendedRegister_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSRegister_Invoke

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
    d_FuncPtr d; // = CGXDLMSExtendedRegister_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSExtendedRegister_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSExtendedRegister_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSExtendedRegister_GetAttributeIndexToRead

    // (CGXDLMSRegister)
    CGXDLMSVariant m_Value;
    signed char m_Scaler;
    unsigned char m_Unit;
    ///////////////////////////////////////////////////////////////////////////

    CGXDateTime m_CaptureTime;
    CGXDLMSVariant m_Status;

} CGXDLMSExtendedRegister;

#define CGXDLMSExtendedRegister_CanRead(p, ln) CGXDLMSRegister_CanRead((CGXDLMSRegister*) (p), (ln))

//protected:
extern bool CGXDLMSExtendedRegister_IsRead(CGXDLMSExtendedRegister* p, int index);
//public:

//Constructor.
extern void CGXDLMSExtendedRegister_1(CGXDLMSExtendedRegister* p);

//SN Constructor.
extern void CGXDLMSExtendedRegister_2(CGXDLMSExtendedRegister* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSExtendedRegister_3(CGXDLMSExtendedRegister* p, String ln);

/**
 Status of COSEM Extended Register object.
*/
extern CGXDLMSVariant CGXDLMSExtendedRegister_GetStatus(CGXDLMSExtendedRegister* p);

extern void CGXDLMSExtendedRegister_SetStatus(CGXDLMSExtendedRegister* p, CGXDLMSVariant value);

/**
 Capture time of COSEM Extended Register object.
*/
extern CGXDateTime* CGXDLMSExtendedRegister_GetCaptureTime(CGXDLMSExtendedRegister* p);

extern void CGXDLMSExtendedRegister_SetCaptureTime(CGXDLMSExtendedRegister* p, CGXDateTime value);

// Returns amount of attributes.
extern int CGXDLMSExtendedRegister_GetAttributeCount(CGXDLMSExtendedRegister* p);

// Returns amount of methods.
extern int CGXDLMSExtendedRegister_GetMethodCount(CGXDLMSExtendedRegister* p);

//Get attribute values of object.
extern void CGXDLMSExtendedRegister_GetValues(CGXDLMSExtendedRegister* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSExtendedRegister_GetAttributeIndexToRead(CGXDLMSExtendedRegister* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSExtendedRegister_GetDataType(CGXDLMSExtendedRegister* p, int index, DLMS_DATA_TYPE* type);

extern int CGXDLMSExtendedRegister_GetValue(CGXDLMSExtendedRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern int CGXDLMSExtendedRegister_SetValue(CGXDLMSExtendedRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern int CGXDLMSExtendedRegister_GetUIDataType(CGXDLMSExtendedRegister* p, int index, DLMS_DATA_TYPE* type);

extern void CGXDLMSExtendedRegister_d(CGXDLMSExtendedRegister* p);

#endif //GXDLMSEXTENDEDREGISTER_H
