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

#ifndef GXDLMSCLOCK_H
#define GXDLMSCLOCK_H

#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"

typedef struct // class CGXDLMSClock : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSClock_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSClock_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSClock_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSClock_SetValue
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
    d_FuncPtr d; // = CGXDLMSClock_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSClock_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSClock_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSClock_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSClock_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    DLMS_CLOCK_BASE m_ClockBase;
    char m_Deviation;
    bool m_Enabled;
    CGXDateTime m_End;
    DLMS_CLOCK_STATUS m_Status;
    CGXDateTime m_Begin;
    short m_TimeZone;
    CGXDateTime m_Time;

} CGXDLMSClock;

#define CGXDLMSClock_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSClock_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSClock_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//public
/**
 Constructor.
*/
extern void CGXDLMSClock_1(CGXDLMSClock *p);

/**
 Constructor.
 @param ln Logical Name of the object.
*/
extern void CGXDLMSClock_2(CGXDLMSClock *p, String ln);

/**
 Constructor.
 @param ln Logical Name of the object.
 @param sn Short Name of the object.
*/
extern void CGXDLMSClock_3(CGXDLMSClock *p, String ln, unsigned short sn);

//destructor
extern void CGXDLMSClock_d(CGXDLMSClock *p);
/**
 Time of COSEM Clock object.
*/
extern CGXDateTime* CGXDLMSClock_GetTime(CGXDLMSClock *p);

extern void CGXDLMSClock_SetTime(CGXDLMSClock *p, CGXDateTime* value);

/**
 TimeZone of COSEM Clock object.
*/
extern short CGXDLMSClock_GetTimeZone(CGXDLMSClock *p);
extern void CGXDLMSClock_SetTimeZone(CGXDLMSClock *p, short value);

/**
 Status of COSEM Clock object.
*/
extern DLMS_CLOCK_STATUS CGXDLMSClock_GetStatus(CGXDLMSClock *p);
extern void CGXDLMSClock_SetStatus(CGXDLMSClock *p, DLMS_CLOCK_STATUS value);

extern CGXDateTime* CGXDLMSClock_GetBegin(CGXDLMSClock *p);
extern void CGXDLMSClock_SetBegin(CGXDLMSClock *p, CGXDateTime* value);

extern CGXDateTime* CGXDLMSClock_GetEnd(CGXDLMSClock *p);
extern void CGXDLMSClock_SetEnd(CGXDLMSClock *p, CGXDateTime* value);

extern char CGXDLMSClock_GetDeviation(CGXDLMSClock *p);
extern void CGXDLMSClock_SetDeviation(CGXDLMSClock *p, char value);

extern bool CGXDLMSClock_GetEnabled(CGXDLMSClock *p);
extern void CGXDLMSClock_SetEnabled(CGXDLMSClock *p, bool value);

/**
 Clock base of COSEM Clock object.
*/
extern DLMS_CLOCK_BASE CGXDLMSClock_GetClockBase(CGXDLMSClock *p);
extern void CGXDLMSClock_SetClockBase(CGXDLMSClock *p, DLMS_CLOCK_BASE value);

// Returns amount of attributes.
extern int CGXDLMSClock_GetAttributeCount(CGXDLMSClock *p);

// Returns amount of methods.
extern int CGXDLMSClock_GetMethodCount(CGXDLMSClock *p);

//Get attribute values of object.
extern void CGXDLMSClock_GetValues(CGXDLMSClock *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSClock_GetAttributeIndexToRead(CGXDLMSClock *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSClock_GetUIDataType(CGXDLMSClock *p, int index, DLMS_DATA_TYPE* type);
extern int CGXDLMSClock_GetDataType(CGXDLMSClock *p, int index, DLMS_DATA_TYPE* type);

/*
 * Returns value of given attribute.
 */
extern int CGXDLMSClock_GetValue(CGXDLMSClock *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

/*
 * Set value of given attribute.
 */
extern int CGXDLMSClock_SetValue(CGXDLMSClock *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSCLOCK_H
