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

#ifndef GXDLMSREGISTERACTIVATION_H
#define GXDLMSREGISTERACTIVATION_H

#include "IGXDLMSBase.h"
#include "GXDLMSObject.h"
#include "GXHelpers.h"
#include "GXDLMSObjectDefinition.h"

typedef struct //class CGXDLMSRegisterActivation : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSRegisterActivation_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSRegisterActivation_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSRegisterActivation_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSRegisterActivation_SetValue
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
    d_FuncPtr d; // = CGXDLMSRegisterActivation_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSRegisterActivation_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSRegisterActivation_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSRegisterActivation_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_RegisterAssignment; //std::vector<CGXDLMSObjectDefinition>
    Vector m_MaskList; //std::vector<std::pair<CGXByteBuffer, CGXByteBuffer > > 
    CGXByteBuffer m_ActiveMask;

} CGXDLMSRegisterActivation;

#define CGXDLMSRegisterActivation_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSRegisterActivation_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSRegisterActivation_1(CGXDLMSRegisterActivation *p);

//SN Constructor.
extern void CGXDLMSRegisterActivation_2(CGXDLMSRegisterActivation *p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSRegisterActivation_3(CGXDLMSRegisterActivation *p, String ln);

extern Vector* CGXDLMSRegisterActivation_GetRegisterAssignment(CGXDLMSRegisterActivation *p); //std::vector<CGXDLMSObjectDefinition>& 

extern Vector* CGXDLMSRegisterActivation_GetMaskList(CGXDLMSRegisterActivation *p); //std::vector<std::pair<CGXByteBuffer, CGXByteBuffer > >&

extern CGXByteBuffer* CGXDLMSRegisterActivation_GetActiveMask(CGXDLMSRegisterActivation *p);

// Returns amount of attributes.
extern int CGXDLMSRegisterActivation_GetAttributeCount(CGXDLMSRegisterActivation *p);

// Returns amount of methods.
extern int CGXDLMSRegisterActivation_GetMethodCount(CGXDLMSRegisterActivation *p);

extern void CGXDLMSRegisterActivation_GetValues(CGXDLMSRegisterActivation *p, Vector* attributes); //std::vector<std::string>&

extern void CGXDLMSRegisterActivation_GetAttributeIndexToRead(CGXDLMSRegisterActivation *p, Vector* attributes); //std::vector<int>&

extern int CGXDLMSRegisterActivation_GetDataType(CGXDLMSRegisterActivation *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSRegisterActivation_GetValue(CGXDLMSRegisterActivation *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSRegisterActivation_SetValue(CGXDLMSRegisterActivation *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSRegisterActivation_d(CGXDLMSRegisterActivation *p);

#endif //GXDLMSREGISTERACTIVATION_H
