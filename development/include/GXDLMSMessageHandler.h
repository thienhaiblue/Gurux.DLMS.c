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

#ifndef GXDLMSMESSAGEHANDLER_H
#define GXDLMSMESSAGEHANDLER_H

#include "GXDLMSObject.h"
#include "GXDateTime.h"
#include "GXDLMSScriptAction.h"

typedef struct //class CGXDLMSMessageHandler : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSMessageHandler_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSMessageHandler_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSMessageHandler_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSMessageHandler_SetValue
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
    d_FuncPtr d; // = CGXDLMSMessageHandler_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSMessageHandler_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSMessageHandler_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSMessageHandler_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_ListeningWindow; //std::vector<std::pair<CGXDateTime, CGXDateTime> >
    Vector m_AllowedSenders; //std::vector<std::string>
    Vector m_SendersAndActions; //std::vector<std::pair<std::string, std::pair<int, CGXDLMSScriptAction> > >
} CGXDLMSMessageHandler;

#define CGXDLMSMessageHandler_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSMessageHandler_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSMessageHandler_1(CGXDLMSMessageHandler* p);

//SN Constructor.
extern void CGXDLMSMessageHandler_2(CGXDLMSMessageHandler* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSMessageHandler_3(CGXDLMSMessageHandler* p, String ln);

/**
Listening Window.
*/
extern Vector* CGXDLMSMessageHandler_GetListeningWindow(CGXDLMSMessageHandler* p); // std::vector<std::pair<CGXDateTime, CGXDateTime> >&

/**
 List of allowed Senders.
*/
extern Vector* CGXDLMSMessageHandler_GetAllowedSenders(CGXDLMSMessageHandler* p); // std::vector<std::string>& 

/**
 Contains the logical name of a "Script table" object and the script selector of the
    script to be executed if an empty message is received from a match-ing sender.
*/
extern Vector* CGXDLMSMessageHandler_GetSendersAndActions(CGXDLMSMessageHandler* p); //std::vector<std::pair<std::string, std::pair<int, CGXDLMSScriptAction> > >&

// Returns amount of attributes.
extern int CGXDLMSMessageHandler_GetAttributeCount(CGXDLMSMessageHandler* p);

// Returns amount of methods.
extern int CGXDLMSMessageHandler_GetMethodCount(CGXDLMSMessageHandler* p);

//Get attribute values of object.
extern void CGXDLMSMessageHandler_GetValues(CGXDLMSMessageHandler* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSMessageHandler_GetAttributeIndexToRead(CGXDLMSMessageHandler* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSMessageHandler_GetDataType(CGXDLMSMessageHandler* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSMessageHandler_GetValue(CGXDLMSMessageHandler* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSMessageHandler_SetValue(CGXDLMSMessageHandler* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSMessageHandler_d(CGXDLMSMessageHandler* p);

#endif //GXDLMSMESSAGEHANDLER_H
