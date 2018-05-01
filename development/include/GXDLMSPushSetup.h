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

#ifndef GXDLMSPUSHSETUP_H
#define GXDLMSPUSHSETUP_H

#include "GXDLMSObject.h"
#include "GXDLMSPushObject.h"
#include "GXDLMSCaptureObject.h"
#include "String.h"
#include "Vector.h"

typedef struct // class CGXDLMSPushSetup : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSPushSetup_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSPushSetup_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSPushSetup_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSPushSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSPushSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSPushSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSPushSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSPushSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    DLMS_SERVICE_TYPE m_Service;
    String m_Destination;
    DLMS_MESSAGE_TYPE m_Message;
    Vector m_PushObjectList; //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> > m_PushObjectList;
    Vector m_CommunicationWindow; //std::vector<std::pair<CGXDateTime, CGXDateTime> > m_CommunicationWindow;
    int m_RandomisationStartInterval, m_NumberOfRetries, m_RepetitionDelay;

} CGXDLMSPushSetup;

#define CGXDLMSPushSetup_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSPushSetup_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

extern void CGXDLMSPushSetup_d(CGXDLMSPushSetup* p);
//Constructor.
extern void CGXDLMSPushSetup_1(CGXDLMSPushSetup* p);

//SN Constructor.
extern void CGXDLMSPushSetup_2(CGXDLMSPushSetup* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSPushSetup_3(CGXDLMSPushSetup* p, String ln);

/**
    Defines the list of attributes or objects to be pushed.
    Upon a call of the push (data) method the selected attributes are sent to the desti-nation
    defined in send_destination_and_method.
*/
//std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >& GetPushObjectList()
extern Vector* CGXDLMSPushSetup_GetPushObjectList(CGXDLMSPushSetup* p);

extern DLMS_SERVICE_TYPE CGXDLMSPushSetup_GetService(CGXDLMSPushSetup* p);
extern void CGXDLMSPushSetup_SetService(CGXDLMSPushSetup* p, DLMS_SERVICE_TYPE value);

extern String* CGXDLMSPushSetup_GetDestination(CGXDLMSPushSetup* p);
extern void CGXDLMSPushSetup_SetDestination(CGXDLMSPushSetup* p, String* value);

extern DLMS_MESSAGE_TYPE CGXDLMSPushSetup_GetMessage(CGXDLMSPushSetup* p);
extern void CGXDLMSPushSetup_SetMessage(CGXDLMSPushSetup* p, DLMS_MESSAGE_TYPE value);

/**
 Contains the start and end date/time
    stamp when the communication window(s) for the push become active
    (for the start instant), or inac-tive (for the end instant).
*/
//std::vector<std::pair<CGXDateTime, CGXDateTime> >& GetCommunicationWindow()
extern Vector* CGXDLMSPushSetup_GetCommunicationWindow(CGXDLMSPushSetup* p);

/**
 To avoid simultaneous network connections of a lot of devices at ex-actly
    the same point in time, a randomisation interval in seconds can be defined.
    This means that the push operation is not started imme-diately at the
    beginning of the first communication window but started randomly delayed.
*/
extern int CGXDLMSPushSetup_GetRandomisationStartInterval(CGXDLMSPushSetup* p);

extern void CGXDLMSPushSetup_SetRandomisationStartInterval(CGXDLMSPushSetup* p, int value);
/**
 The maximum number of retrials in case of unsuccessful push at-tempts. After a successful push no further push attempts are made until the push setup is triggered again.
    A value of 0 means no repetitions, i.e. only the initial connection at-tempt is made.
*/

extern int CGXDLMSPushSetup_GetNumberOfRetries(CGXDLMSPushSetup* p);
extern void CGXDLMSPushSetup_SetNumberOfRetries(CGXDLMSPushSetup* p, int value);

extern int CGXDLMSPushSetup_GetRepetitionDelay(CGXDLMSPushSetup* p);

extern void CGXDLMSPushSetup_SetRepetitionDelay(CGXDLMSPushSetup* p, int value);
// Returns amount of attributes.
extern int CGXDLMSPushSetup_GetAttributeCount(CGXDLMSPushSetup* p);

// Returns amount of methods.
extern int CGXDLMSPushSetup_GetMethodCount(CGXDLMSPushSetup* p);

//Get attribute values of object.
extern void CGXDLMSPushSetup_GetValues(CGXDLMSPushSetup* p, Vector* values);//std::vector<std::string>& values);

extern void CGXDLMSPushSetup_GetAttributeIndexToRead(CGXDLMSPushSetup* p, Vector* attributes);//std::vector<int>& attributes);

extern int CGXDLMSPushSetup_GetDataType(CGXDLMSPushSetup* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSPushSetup_GetValue(CGXDLMSPushSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSPushSetup_SetValue(CGXDLMSPushSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSPUSHSETUP_H
