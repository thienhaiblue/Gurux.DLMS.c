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

#ifndef GXDLMSACTIVITYCALENDAR_H
#define GXDLMSACTIVITYCALENDAR_H

#include "GXDLMSObject.h"
#include "GXDLMSSeasonProfile.h"
#include "GXDLMSWeekProfile.h"
#include "GXDLMSDayProfile.h"
#include "String.h"

typedef struct //class CGXDLMSActivityCalendar : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSActivityCalendar_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSActivityCalendar_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSActivityCalendar_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSActivityCalendar_SetValue
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
    d_FuncPtr d; // = CGXDLMSActivityCalendar_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSActivityCalendar_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSActivityCalendar_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSActivityCalendar_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    String m_CalendarNameActive;
    String m_CalendarNamePassive;
    Vector m_SeasonProfileActive; // std::vector<CGXDLMSSeasonProfile*>
    Vector m_WeekProfileTableActive; // std::vector<CGXDLMSWeekProfile*>
    Vector m_DayProfileTableActive; // std::vector<CGXDLMSDayProfile*>
    Vector m_SeasonProfilePassive; // std::vector<CGXDLMSSeasonProfile*>
    Vector m_DayProfileTablePassive; // std::vector<CGXDLMSDayProfile*>
    Vector m_WeekProfileTablePassive; // std::vector<CGXDLMSWeekProfile*>
    CGXDateTime m_Time;
} CGXDLMSActivityCalendar;

#define CGXDLMSActivityCalendar_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSActivityCalendar_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

    //Constructor.
extern void CGXDLMSActivityCalendar_1(CGXDLMSActivityCalendar *p);

    //SN Constructor.
extern void CGXDLMSActivityCalendar_2(CGXDLMSActivityCalendar *p, String ln, unsigned short sn);

    //LN Constructor.
extern void CGXDLMSActivityCalendar_3(CGXDLMSActivityCalendar *p, String ln);

    //Destructor.
extern void CGXDLMSActivityCalendar_d(CGXDLMSActivityCalendar *p);

extern String CGXDLMSActivityCalendar_GetCalendarNameActive(CGXDLMSActivityCalendar *p);
extern void CGXDLMSActivityCalendar_SetCalendarNameActive(CGXDLMSActivityCalendar *p, String value);

extern Vector* CGXDLMSActivityCalendar_GetSeasonProfileActive(CGXDLMSActivityCalendar *p); // std::vector<CGXDLMSSeasonProfile*>&
extern void CGXDLMSActivityCalendar_SetSeasonProfileActive(CGXDLMSActivityCalendar *p, Vector* value); // std::vector<CGXDLMSSeasonProfile*>&

extern Vector* CGXDLMSActivityCalendar_GetWeekProfileTableActive(CGXDLMSActivityCalendar *p); // std::vector<CGXDLMSWeekProfile*>&
extern void CGXDLMSActivityCalendar_SetWeekProfileTableActive(CGXDLMSActivityCalendar *p, Vector* value); // std::vector<CGXDLMSWeekProfile*>&

extern Vector* CGXDLMSActivityCalendar_GetDayProfileTableActive(CGXDLMSActivityCalendar *p); // std::vector<CGXDLMSDayProfile*>&
extern void CGXDLMSActivityCalendar_SetDayProfileTableActive(CGXDLMSActivityCalendar *p, Vector* value); // std::vector<CGXDLMSDayProfile*>&

extern String CGXDLMSActivityCalendar_GetCalendarNamePassive(CGXDLMSActivityCalendar *p);
extern void CGXDLMSActivityCalendar_SetCalendarNamePassive(CGXDLMSActivityCalendar *p, String value);

extern Vector* CGXDLMSActivityCalendar_GetSeasonProfilePassive(CGXDLMSActivityCalendar *p); // std::vector<CGXDLMSSeasonProfile*>&
extern void CGXDLMSActivityCalendar_SetSeasonProfilePassive(CGXDLMSActivityCalendar *p, Vector* value); // std::vector<CGXDLMSSeasonProfile*>&

extern Vector* CGXDLMSActivityCalendar_GetWeekProfileTablePassive(CGXDLMSActivityCalendar *p); // std::vector<CGXDLMSWeekProfile*>&
extern void CGXDLMSActivityCalendar_SetWeekProfileTablePassive(CGXDLMSActivityCalendar *p, Vector* value); // std::vector<CGXDLMSWeekProfile*>&

extern Vector* CGXDLMSActivityCalendar_GetDayProfileTablePassive(CGXDLMSActivityCalendar *p); // std::vector<CGXDLMSDayProfile*>&
extern void CGXDLMSActivityCalendar_SetDayProfileTablePassive(CGXDLMSActivityCalendar *p, Vector* value); // std::vector<CGXDLMSDayProfile*>&

extern CGXDateTime* CGXDLMSActivityCalendar_GetTime(CGXDLMSActivityCalendar *p);
extern void CGXDLMSActivityCalendar_SetTime(CGXDLMSActivityCalendar *p, CGXDateTime* value);

    // Returns amount of attributes.
extern int CGXDLMSActivityCalendar_GetAttributeCount(CGXDLMSActivityCalendar *p);

    // Returns amount of methods.
extern int CGXDLMSActivityCalendar_GetMethodCount(CGXDLMSActivityCalendar *p);

    //Get attribute values of object.
extern void CGXDLMSActivityCalendar_GetValues(CGXDLMSActivityCalendar *p, Vector* values); // std::vector<std::string>&

extern void CGXDLMSActivityCalendar_GetAttributeIndexToRead(CGXDLMSActivityCalendar *p, Vector* attributes); // std::vector<int>&

extern int CGXDLMSActivityCalendar_GetDataType(CGXDLMSActivityCalendar *p, int index, DLMS_DATA_TYPE* type);

    // Returns value of given attribute.
extern int CGXDLMSActivityCalendar_GetValue(CGXDLMSActivityCalendar *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

    // Set value of given attribute.
extern int CGXDLMSActivityCalendar_SetValue(CGXDLMSActivityCalendar *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSACTIVITYCALENDAR_H
