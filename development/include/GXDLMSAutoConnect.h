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

#ifndef GXDLMSAUTOCONNECT_H
#define GXDLMSAUTOCONNECT_H

#include "GXDLMSObject.h"
#include "GXDLMSAutoAnswer.h"

typedef struct
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSAutoConnect_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSAutoConnect_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSAutoConnect_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSAutoConnect_SetValue
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
    d_FuncPtr d; // = CGXDLMSAutoConnect_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSAutoConnect_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSAutoConnect_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSAutoConnect_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    AUTO_CONNECT_MODE m_Mode;
    Vector m_CallingWindow;//std::vector<std::pair< CGXDateTime, CGXDateTime> >
    Vector m_Destinations;//std::vector< std::string >
    int m_RepetitionDelay;
    int m_Repetitions;

} CGXDLMSAutoConnect;

#define CGXDLMSAutoConnect_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSAutoConnect_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSAutoConnect_1(CGXDLMSAutoConnect *p);

//SN Constructor.
extern void CGXDLMSAutoConnect_2(CGXDLMSAutoConnect *p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSAutoConnect_3(CGXDLMSAutoConnect *p, String ln);

//destructor
extern void CGXDLMSAutoConnect_d(CGXDLMSAutoConnect *p);

extern AUTO_CONNECT_MODE CGXDLMSAutoConnect_GetMode(CGXDLMSAutoConnect *p);
extern void CGXDLMSAutoConnect_SetMode(CGXDLMSAutoConnect *p, AUTO_CONNECT_MODE value);

extern int CGXDLMSAutoConnect_GetRepetitions(CGXDLMSAutoConnect *p);

extern void CGXDLMSAutoConnect_SetRepetitions(CGXDLMSAutoConnect *p, int value);

extern int CGXDLMSAutoConnect_GetRepetitionDelay(CGXDLMSAutoConnect *p);
extern void CGXDLMSAutoConnect_SetRepetitionDelay(CGXDLMSAutoConnect *p, int value);

extern Vector* CGXDLMSAutoConnect_GetCallingWindow(CGXDLMSAutoConnect *p);//std::vector<std::pair< CGXDateTime, CGXDateTime> >&
extern void CGXDLMSAutoConnect_SetCallingWindow(CGXDLMSAutoConnect *p, Vector value);//std::vector<std::pair< CGXDateTime, CGXDateTime> >

extern Vector* CGXDLMSAutoConnect_GetDestinations(CGXDLMSAutoConnect *p);//std::vector< std::string >&

extern void CGXDLMSAutoConnect_SetDestinations(CGXDLMSAutoConnect *p, Vector* value);//std::vector< std::string >&

// Returns amount of attributes.
extern int CGXDLMSAutoConnect_GetAttributeCount(CGXDLMSAutoConnect *p);

// Returns amount of methods.
extern int CGXDLMSAutoConnect_GetMethodCount(CGXDLMSAutoConnect *p);

//Get attribute values of object.
extern void CGXDLMSAutoConnect_GetValues(CGXDLMSAutoConnect *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSAutoConnect_GetAttributeIndexToRead(CGXDLMSAutoConnect *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSAutoConnect_GetDataType(CGXDLMSAutoConnect *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSAutoConnect_GetValue(CGXDLMSAutoConnect *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSAutoConnect_SetValue(CGXDLMSAutoConnect *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSAUTOCONNECT_H
