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
#ifndef GXDLMSREGISTER_H
#define GXDLMSREGISTER_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"

typedef struct //class CGXDLMSRegister : public CGXDLMSObject
{
     ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSRegister_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSRegister_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSRegister_GetValue_2
	SetValue_FuncPtr SetValue; // = CGXDLMSRegister_SetValue_2
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
    d_FuncPtr d; // = CGXDLMSRegister_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSRegister_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSRegister_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSRegister_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

//protected:
    CGXDLMSVariant m_Value;
    signed char m_Scaler;
    unsigned char m_Unit;
} CGXDLMSRegister;

#define CGXDLMSRegister_GetLogicalName_2(p, ln)     CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSRegister_CanRead(p, index)           CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSRegister_SetAccess(p, index, access) CGXDLMSObject_SetAccess((CGXDLMSObject*) (p), (index), (access))

//SN Constructor.
extern void CGXDLMSRegister_1(CGXDLMSRegister* p, DLMS_OBJECT_TYPE type, String ln, unsigned short sn);

extern bool CGXDLMSRegister_IsRead(CGXDLMSRegister* p, int index);

//public:
//Constructor.
extern void CGXDLMSRegister_2(CGXDLMSRegister* p);

//SN Constructor.
extern void CGXDLMSRegister_3(CGXDLMSRegister* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSRegister_4(CGXDLMSRegister* p, String ln);

/// <summary>
/// Get value of COSEM Data object.
/// </summary>
extern CGXDLMSVariant CGXDLMSRegister_GetValue_1(CGXDLMSRegister* p);

/// <summary>
/// Set value of COSEM Data object.
/// </summary>
extern void CGXDLMSRegister_SetValue_1(CGXDLMSRegister* p, CGXDLMSVariant* value);

// Scaler of COSEM Register object.
extern double CGXDLMSRegister_GetScaler(CGXDLMSRegister* p);

extern void CGXDLMSRegister_SetScaler(CGXDLMSRegister* p, double value);

// Unit of COSEM Register object.
extern int CGXDLMSRegister_GetUnit(CGXDLMSRegister* p);

extern void CGXDLMSRegister_SetUnit(CGXDLMSRegister* p, unsigned char value);

/*
    * Reset value.
    */
extern void CGXDLMSRegister_Reset(CGXDLMSRegister* p);

// Returns amount of attributes.
extern int CGXDLMSRegister_GetAttributeCount(CGXDLMSRegister* p);

// Returns amount of methods.
extern int CGXDLMSRegister_GetMethodCount(CGXDLMSRegister* p);

extern int CGXDLMSRegister_Invoke(CGXDLMSRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

//Get attribute values of object.
extern void CGXDLMSRegister_GetValues(CGXDLMSRegister* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSRegister_GetAttributeIndexToRead(CGXDLMSRegister* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSRegister_GetDataType(CGXDLMSRegister* p, int index, DLMS_DATA_TYPE* type);

extern int CGXDLMSRegister_GetValue_2(CGXDLMSRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern int CGXDLMSRegister_SetValue_2(CGXDLMSRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSRegister_d(CGXDLMSRegister* p);

#endif //GXDLMSREGISTER_H
