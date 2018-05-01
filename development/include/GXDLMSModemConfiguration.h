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

#ifndef GXDLMSMODEMCONFIGURATION_H
#define GXDLMSMODEMCONFIGURATION_H

#include "GXDLMSObject.h"
#include "GXDLMSModemInitialisation.h"

typedef struct // class CGXDLMSModemConfiguration : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSModemConfiguration_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSModemConfiguration_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSModemConfiguration_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSModemConfiguration_SetValue
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
    d_FuncPtr d; // = CGXDLMSModemConfiguration_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSModemConfiguration_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSModemConfiguration_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSModemConfiguration_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_InitialisationStrings; //std::vector<CGXDLMSModemInitialisation>
    Vector m_ModemProfile; //std::vector< std::string >
    DLMS_BAUD_RATE m_CommunicationSpeed;

} CGXDLMSModemConfiguration;

#define CGXDLMSModemConfiguration_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSModemConfiguration_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

/**
 Constructor.
*/
extern void CGXDLMSModemConfiguration_1(CGXDLMSModemConfiguration* p);
/**
 Constructor.
    @param ln Logical Name of the object.
*/
extern void CGXDLMSModemConfiguration_2(CGXDLMSModemConfiguration* p, String ln);

/**
 Constructor.
    @param ln Logical Name of the object.
    @param sn Short Name of the object.
*/
extern void CGXDLMSModemConfiguration_3(CGXDLMSModemConfiguration* p, String ln, unsigned short sn);

extern DLMS_BAUD_RATE CGXDLMSModemConfiguration_GetCommunicationSpeed(CGXDLMSModemConfiguration* p);

extern void CGXDLMSModemConfiguration_SetCommunicationSpeed(CGXDLMSModemConfiguration* p, DLMS_BAUD_RATE value);

extern Vector* CGXDLMSModemConfiguration_GetInitialisationStrings(CGXDLMSModemConfiguration* p); //std::vector<CGXDLMSModemInitialisation>& 
extern void CGXDLMSModemConfiguration_SetInitialisationStrings(CGXDLMSModemConfiguration* p, Vector* value); //std::vector<CGXDLMSModemInitialisation>&

extern Vector CGXDLMSModemConfiguration_GetModemProfile(CGXDLMSModemConfiguration* p);  //std::vector< std::string >
extern void CGXDLMSModemConfiguration_SetModemProfile(CGXDLMSModemConfiguration* p, Vector* value); //std::vector< std::string >&

// Returns amount of attributes.
extern int CGXDLMSModemConfiguration_GetAttributeCount(CGXDLMSModemConfiguration* p);

// Returns amount of methods.
extern int CGXDLMSModemConfiguration_GetMethodCount(CGXDLMSModemConfiguration* p);

//Get attribute values of object.
extern void CGXDLMSModemConfiguration_GetValues(CGXDLMSModemConfiguration* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSModemConfiguration_GetAttributeIndexToRead(CGXDLMSModemConfiguration* p, Vector* attributes); //std::vector<int>&

extern int CGXDLMSModemConfiguration_GetDataType(CGXDLMSModemConfiguration* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSModemConfiguration_GetValue(CGXDLMSModemConfiguration* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSModemConfiguration_SetValue(CGXDLMSModemConfiguration* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSModemConfiguration_d(CGXDLMSModemConfiguration* p);

#endif //GXDLMSMODEMCONFIGURATION_H
