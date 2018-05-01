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
#ifndef GXDLMSAUTOANSWER_H
#define GXDLMSAUTOANSWER_H

#include "GXDLMSObject.h"
#include "Vector.h"
#include "String.h"

typedef enum
{
    /*
     * No auto dialling,
     */
    AUTO_CONNECT_MODE_NO_AUTO_DIALLING = 0,
    /**
     * Auto dialling allowed anytime,
     */
    AUTO_CONNECT_MODE_AUTO_DIALLING_ALLOWED_ANYTIME = 1,
    /**
     * Auto dialling allowed within the validity time of the calling window.
     */
    AUTO_CONNECT_MODE_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 2,
    /**
     * �regular� auto dialling allowed within the validity time
     * of the calling window; �alarm� initiated auto dialling allowed anytime,
     */
    AUTO_CONNECT_MODE_REGULAR_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 3,
    /**
     * SMS sending via Public Land Mobile Network (PLMN),
     */
    AUTO_CONNECT_MODE_SMS_SENDING_PLMN = 4,
    /*
     * SMS sending via PSTN.
     */
    AUTO_CONNECT_MODE_SMS_SENDING_PSTN = 5,
    /*
     * Email sending.
     */
    AUTO_CONNECT_MODE_EMAIL_SENDING = 6
} AUTO_CONNECT_MODE;

typedef enum
{
    AUTO_ANSWER_STATUS_INACTIVE = 0,
    AUTO_ANSWER_STATUS_ACTIVE = 1,
    AUTO_ANSWER_STATUS_LOCKED = 2
} AUTO_ANSWER_STATUS;

typedef struct // class CGXDLMSAutoAnswer : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSAutoAnswer_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSAutoAnswer_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSAutoAnswer_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSAutoAnswer_SetValue
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
    d_FuncPtr d; // = CGXDLMSAutoAnswer_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSAutoAnswer_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSAutoAnswer_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSAutoAnswer_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    int m_NumberOfRingsInListeningWindow, m_NumberOfRingsOutListeningWindow;
    AUTO_CONNECT_MODE m_Mode;
    Vector m_ListeningWindow; // std::vector<std::pair< CGXDateTime, CGXDateTime> >
    AUTO_ANSWER_STATUS m_Status;
    int m_NumberOfCalls;

} CGXDLMSAutoAnswer;

#define CGXDLMSAutoAnswer_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSAutoAnswer_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSAutoAnswer_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))

//public
/**
 Constructor.
*/
extern void CGXDLMSAutoAnswer_1(CGXDLMSAutoAnswer *p);

/**
 Constructor.

 @param ln Logical Name of the object.
*/
extern void CGXDLMSAutoAnswer_2(CGXDLMSAutoAnswer *p, String ln);

/**
 Constructor.

 @param ln Logical Name of the object.
 @param sn Short Name of the object.
*/
extern void CGXDLMSAutoAnswer_3(CGXDLMSAutoAnswer *p, String ln, unsigned short sn);

extern AUTO_CONNECT_MODE CGXDLMSAutoAnswer_GetMode(CGXDLMSAutoAnswer *p);
extern void CGXDLMSAutoAnswer_SetMode(CGXDLMSAutoAnswer *p, AUTO_CONNECT_MODE value);

extern Vector* CGXDLMSAutoAnswer_GetListeningWindow(CGXDLMSAutoAnswer *p);//std::vector<std::pair< CGXDateTime, CGXDateTime> >&
extern void CGXDLMSAutoAnswer_SetListeningWindow(CGXDLMSAutoAnswer *p, Vector* value);//std::vector<std::pair< CGXDateTime, CGXDateTime> >&

extern AUTO_ANSWER_STATUS CGXDLMSAutoAnswer_GetStatus(CGXDLMSAutoAnswer *p);
extern void CGXDLMSAutoAnswer_SetStatus(CGXDLMSAutoAnswer *p, AUTO_ANSWER_STATUS value);

extern int CGXDLMSAutoAnswer_GetNumberOfCalls(CGXDLMSAutoAnswer *p);
extern void CGXDLMSAutoAnswer_SetNumberOfCalls(CGXDLMSAutoAnswer *p, int value);

// Number of rings within the window defined by ListeningWindow.
extern int CGXDLMSAutoAnswer_GetNumberOfRingsInListeningWindow(CGXDLMSAutoAnswer *p);
extern void CGXDLMSAutoAnswer_SetNumberOfRingsInListeningWindow(CGXDLMSAutoAnswer *p, int value);

//Number of rings outside the window defined by ListeningWindow.
extern int CGXDLMSAutoAnswer_GetNumberOfRingsOutListeningWindow(CGXDLMSAutoAnswer *p);
extern void CGXDLMSAutoAnswer_SetNumberOfRingsOutListeningWindow(CGXDLMSAutoAnswer *p, int value);

// Returns amount of attributes.
extern int CGXDLMSAutoAnswer_GetAttributeCount(CGXDLMSAutoAnswer *p);

// Returns amount of methods.
extern int CGXDLMSAutoAnswer_GetMethodCount(CGXDLMSAutoAnswer *p);

//Get attribute values of object.
extern void CGXDLMSAutoAnswer_GetValues(CGXDLMSAutoAnswer *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSAutoAnswer_GetAttributeIndexToRead(CGXDLMSAutoAnswer *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSAutoAnswer_GetDataType(CGXDLMSAutoAnswer *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSAutoAnswer_GetValue(CGXDLMSAutoAnswer *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

/*
 * Set value of given attribute.
 */
extern int CGXDLMSAutoAnswer_SetValue(CGXDLMSAutoAnswer *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSAutoAnswer_d(CGXDLMSAutoAnswer *p);

#endif //GXDLMSAUTOANSWER_H
