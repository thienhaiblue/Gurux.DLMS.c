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

#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSActivityCalendar.h"
#include "../include/Optimize.h"

static void CGXDLMSActivityCalendar__(CGXDLMSActivityCalendar* p)
{
    /////////////////////////////////////////////////////////////////////////////
    p->GetAttributeCount = CGXDLMSActivityCalendar_GetAttributeCount;
    p->GetMethodCount = CGXDLMSActivityCalendar_GetMethodCount;
    p->GetValue = CGXDLMSActivityCalendar_GetValue;
    p->SetValue = CGXDLMSActivityCalendar_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSActivityCalendar_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSActivityCalendar_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSActivityCalendar_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSActivityCalendar_GetAttributeIndexToRead;
    /////////////////////////////////////////////////////////////////////////////

    String_(&p->m_CalendarNameActive);
    String_(&p->m_CalendarNamePassive);
    Vector_(&p->m_SeasonProfileActive, sizeof(CGXDLMSSeasonProfile*), NULL, NULL); // std::vector<CGXDLMSSeasonProfile*>
    Vector_(&p->m_WeekProfileTableActive, sizeof(CGXDLMSWeekProfile*), NULL, NULL); // std::vector<CGXDLMSWeekProfile*>
    Vector_(&p->m_DayProfileTableActive, sizeof(CGXDLMSDayProfile*), NULL, NULL); // std::vector<CGXDLMSDayProfile*>
    Vector_(&p->m_SeasonProfilePassive, sizeof(CGXDLMSSeasonProfile*), NULL, NULL); // std::vector<CGXDLMSSeasonProfile*>
    Vector_(&p->m_DayProfileTablePassive, sizeof(CGXDLMSDayProfile*), NULL, NULL); // std::vector<CGXDLMSDayProfile*>
    Vector_(&p->m_WeekProfileTablePassive, sizeof(CGXDLMSWeekProfile*), NULL, NULL); // std::vector<CGXDLMSWeekProfile*>
    CGXDateTime_1(&p->m_Time);
}

void CGXDLMSActivityCalendar_1(CGXDLMSActivityCalendar *p)
{
    String t_Str;
    String_3(&t_Str, "0.0.13.0.0.255");

    CGXDLMSActivityCalendar_2(p, t_Str, 0);

    String_d(&t_Str);
}

void CGXDLMSActivityCalendar_2(CGXDLMSActivityCalendar *p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR, &ln, sn);

	CGXDLMSActivityCalendar__(p);
}

void CGXDLMSActivityCalendar_3(CGXDLMSActivityCalendar *p, String ln)
{
	CGXDLMSActivityCalendar_2(p, ln, 0);
}

void CGXDLMSActivityCalendar_d(CGXDLMSActivityCalendar *p)
{

    //for (std_vector<CGXDLMSSeasonProfile*>_iterator it = p->m_SeasonProfileActive.begin(); it != p->m_SeasonProfileActive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_SeasonProfileActive);
            i != Vector_end(&p->m_SeasonProfileActive); ++i)
    {
        CGXDLMSSeasonProfile** it = Vector_at(&p->m_SeasonProfileActive, i);

        //delete *it;
        CGXDLMSSeasonProfile_d(*it);
        DLMSPort_free(*it);

    }
    Vector_clear(&p->m_SeasonProfileActive);

    //for (std_vector<CGXDLMSWeekProfile*>_iterator it = p->m_WeekProfileTableActive.begin(); it != p->m_WeekProfileTableActive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_WeekProfileTableActive);
            i != Vector_end(&p->m_WeekProfileTableActive); ++i)
    {
        CGXDLMSWeekProfile** it = Vector_at(&p->m_WeekProfileTableActive, i);

        //delete *it;
        CGXDLMSWeekProfile_d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_WeekProfileTableActive);

    //for (std_vector<CGXDLMSDayProfile*>_iterator it = p->m_DayProfileTableActive.begin(); it != p->m_DayProfileTableActive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_DayProfileTableActive);
            i != Vector_end(&p->m_DayProfileTableActive); ++i)
    {
        CGXDLMSDayProfile** it = Vector_at(&p->m_DayProfileTableActive, i);

        //delete *it;
        CGXDLMSDayProfile_d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_DayProfileTableActive);

    //for (std_vector<CGXDLMSSeasonProfile*>_iterator it = p->m_SeasonProfilePassive.begin(); it != p->m_SeasonProfilePassive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_SeasonProfilePassive);
            i != Vector_end(&p->m_SeasonProfilePassive); ++i)
    {
        CGXDLMSSeasonProfile** it = Vector_at(&p->m_SeasonProfilePassive, i);

        //delete *it;
        CGXDLMSSeasonProfile_d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_SeasonProfilePassive);

    //for (std_vector<CGXDLMSWeekProfile*>_iterator it = p->m_WeekProfileTablePassive.begin(); it != p->m_WeekProfileTablePassive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_WeekProfileTablePassive);
            i != Vector_end(&p->m_WeekProfileTablePassive); ++i)
    {
        CGXDLMSWeekProfile** it = Vector_at(&p->m_WeekProfileTablePassive, i);

        //delete *it;
        CGXDLMSWeekProfile_d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_WeekProfileTablePassive);

    //for (std_vector<CGXDLMSDayProfile*>_iterator it = p->m_DayProfileTablePassive.begin(); it != p->m_DayProfileTablePassive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_DayProfileTablePassive);
            i != Vector_end(&p->m_DayProfileTablePassive); ++i)
    {
        CGXDLMSDayProfile** it = Vector_at(&p->m_DayProfileTablePassive, i);

        //delete *it;
        CGXDLMSDayProfile_d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_DayProfileTablePassive);

    String_d(&p->m_CalendarNameActive);
    String_d(&p->m_CalendarNamePassive);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}


String CGXDLMSActivityCalendar_GetCalendarNameActive(CGXDLMSActivityCalendar *p)
{
	String out;
	String_2(&out, &(p->m_CalendarNameActive));

	return out; // = copy cons + des
}

void CGXDLMSActivityCalendar_SetCalendarNameActive(CGXDLMSActivityCalendar *p, String value)
{
	String_copy_1(&(p->m_CalendarNameActive), &value);
}

Vector* CGXDLMSActivityCalendar_GetSeasonProfileActive(CGXDLMSActivityCalendar *p) // std::vector<CGXDLMSSeasonProfile*>&
{
    return &p->m_SeasonProfileActive;
}

void CGXDLMSActivityCalendar_SetSeasonProfileActive(CGXDLMSActivityCalendar *p, Vector* value) // std::vector<CGXDLMSSeasonProfile*>&
{
    Vector_copy_1(&p->m_SeasonProfileActive, value);
}

Vector* CGXDLMSActivityCalendar_GetWeekProfileTableActive(CGXDLMSActivityCalendar *p) // std::vector<CGXDLMSWeekProfile*>&
{
    return &p->m_WeekProfileTableActive;
}

void CGXDLMSActivityCalendar_SetWeekProfileTableActive(CGXDLMSActivityCalendar *p, Vector* value) // std::vector<CGXDLMSWeekProfile*>&
{
    Vector_copy_1(&p->m_WeekProfileTableActive, value);
}

Vector* CGXDLMSActivityCalendar_GetDayProfileTableActive(CGXDLMSActivityCalendar *p) // std::vector<CGXDLMSDayProfile*>&
{
    return &p->m_DayProfileTableActive;
}

void CGXDLMSActivityCalendar_SetDayProfileTableActive(CGXDLMSActivityCalendar *p, Vector* value) // std::vector<CGXDLMSDayProfile*>&
{
    Vector_copy_1(&p->m_DayProfileTableActive, value);
}

String CGXDLMSActivityCalendar_GetCalendarNamePassive(CGXDLMSActivityCalendar *p)
{
    String out;
    String_2(&out, &(p->m_CalendarNamePassive));

    return out; // = copy cons + des
}

void CGXDLMSActivityCalendar_SetCalendarNamePassive(CGXDLMSActivityCalendar *p, String value)
{
	String_copy_1(&(p->m_CalendarNamePassive), &value);
}

Vector* CGXDLMSActivityCalendar_GetSeasonProfilePassive(CGXDLMSActivityCalendar *p) // std::vector<CGXDLMSSeasonProfile*>&
{
    return &p->m_SeasonProfilePassive;
}

void CGXDLMSActivityCalendar_SetSeasonProfilePassive(CGXDLMSActivityCalendar *p, Vector* value) // std::vector<CGXDLMSSeasonProfile*>&
{
    Vector_copy_1(&p->m_SeasonProfilePassive, value);
}

Vector* CGXDLMSActivityCalendar_GetWeekProfileTablePassive(CGXDLMSActivityCalendar *p) // std::vector<CGXDLMSWeekProfile*>&
{
    return &p->m_WeekProfileTablePassive;
}
void CGXDLMSActivityCalendar_SetWeekProfileTablePassive(CGXDLMSActivityCalendar *p, Vector* value)// std::vector<CGXDLMSWeekProfile*>&
{
    Vector_copy_1(&p->m_WeekProfileTablePassive, value);
}

Vector* CGXDLMSActivityCalendar_GetDayProfileTablePassive(CGXDLMSActivityCalendar *p) // std::vector<CGXDLMSDayProfile*>&
{
    return &p->m_DayProfileTablePassive;
}
void CGXDLMSActivityCalendar_SetDayProfileTablePassive(CGXDLMSActivityCalendar *p, Vector* value) // std::vector<CGXDLMSDayProfile*>&
{
    Vector_copy_1(&p->m_DayProfileTablePassive, value);
}

// Returns amount of attributes.
int CGXDLMSActivityCalendar_GetAttributeCount(CGXDLMSActivityCalendar *p)
{
    return 10;
}

// Returns amount of methods.
int CGXDLMSActivityCalendar_GetMethodCount(CGXDLMSActivityCalendar *p)
{
    return 1;
}

void CGXDLMSActivityCalendar_GetValues(CGXDLMSActivityCalendar *p, Vector* values) // std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back(values, &p->m_CalendarNameActive);

    String sb;
    String_3(&sb, "[");

    bool empty = true;
    //for (std_vector<CGXDLMSSeasonProfile*>_iterator it = p->m_SeasonProfileActive.begin(); it != p->m_SeasonProfileActive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_SeasonProfileActive);
            i != Vector_end(&p->m_SeasonProfileActive); ++i)
    {
        CGXDLMSSeasonProfile** it = Vector_at(&p->m_SeasonProfileActive, i);

        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSSeasonProfile_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    String_3(&sb, "[");

    empty = true;
    //for (std_vector<CGXDLMSWeekProfile*>_iterator it = p->m_WeekProfileTableActive.begin(); it != p->m_WeekProfileTableActive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_WeekProfileTableActive);
            i != Vector_end(&p->m_WeekProfileTableActive); ++i)
    {
        CGXDLMSWeekProfile** it = Vector_at(&p->m_WeekProfileTableActive, i);

        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSWeekProfile_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    String_3(&sb, "[");

    empty = true;
    //for (std_vector<CGXDLMSDayProfile*>_iterator it = p->m_DayProfileTableActive.begin(); it != p->m_DayProfileTableActive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_DayProfileTableActive);
            i != Vector_end(&p->m_DayProfileTableActive); ++i)
    {
        CGXDLMSDayProfile** it = Vector_at(&p->m_DayProfileTableActive, i);

        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSDayProfile_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    Vector_push_back(values, &p->m_CalendarNamePassive);

    String_3(&sb, "[");

    empty = true;
    //for (std_vector<CGXDLMSSeasonProfile*>_iterator it = p->m_SeasonProfilePassive.begin(); it != p->m_SeasonProfilePassive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_SeasonProfilePassive);
            i != Vector_end(&p->m_SeasonProfilePassive); ++i)
    {
        CGXDLMSSeasonProfile** it = Vector_at(&p->m_SeasonProfilePassive, i);

        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSSeasonProfile_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    String_3(&sb, "[");

    empty = true;
    //for (std_vector<CGXDLMSWeekProfile*>_iterator it = p->m_WeekProfileTablePassive.begin(); it != p->m_WeekProfileTablePassive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_WeekProfileTablePassive);
            i != Vector_end(&p->m_WeekProfileTablePassive); ++i)
    {
        CGXDLMSWeekProfile** it = Vector_at(&p->m_WeekProfileTablePassive, i);

        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSWeekProfile_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    String_3(&sb, "[");

    empty = true;
    //for (std_vector<CGXDLMSDayProfile*>_iterator it = p->m_DayProfileTablePassive.begin(); it != p->m_DayProfileTablePassive.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_DayProfileTablePassive);
            i != Vector_end(&p->m_DayProfileTablePassive); ++i)
    {
        CGXDLMSDayProfile** it = Vector_at(&p->m_DayProfileTablePassive, i);

        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSDayProfile_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);

    String ln = CGXDateTime_ToString(&p->m_Time);

    Vector_push_back(values, &ln);

    String_d(&ln);
}

void CGXDLMSActivityCalendar_GetAttributeIndexToRead(CGXDLMSActivityCalendar *p, Vector* attributes) // std::vector<int>&
{
    int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //CalendarNameActive
    if (CGXDLMSActivityCalendar_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //SeasonProfileActive
    if (CGXDLMSActivityCalendar_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }

    //WeekProfileTableActive
    if (CGXDLMSActivityCalendar_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //DayProfileTableActive
    if (CGXDLMSActivityCalendar_CanRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //CalendarNamePassive
    if (CGXDLMSActivityCalendar_CanRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //SeasonProfilePassive
    if (CGXDLMSActivityCalendar_CanRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    //WeekProfileTablePassive
    if (CGXDLMSActivityCalendar_CanRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //DayProfileTablePassive
    if (CGXDLMSActivityCalendar_CanRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }
    //Time.
    if (CGXDLMSActivityCalendar_CanRead(p, 10))
    {
        tmp = 10;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSActivityCalendar_GetDataType(CGXDLMSActivityCalendar *p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;

    }
    if (index == 8)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 9)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 10)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSActivityCalendar_GetSeasonProfile(Vector* items, CGXByteBuffer* data)//std_vector<CGXDLMSSeasonProfile*>& items
{
    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    unsigned long cnt = (unsigned long)Vector_size(items);
    //Add count
    GXHelpers_SetObjectCount(cnt, data);

    CGXDLMSVariant tmp;
    CGXDLMSVariant_1(&tmp);

    // std_vector<CGXDLMSSeasonProfile*>
    for (unsigned int i = Vector_begin(items); i != Vector_end(items); ++i)
    {
        CGXDLMSSeasonProfile** it = Vector_at(items, i);

        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(data, 3);
        CGXDLMSVariant_Clear(&tmp);

        String str = CGXDLMSSeasonProfile_GetName(*it);

        CGXDLMSVariant_Add_3(&tmp, str);

        String_d(&str);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &tmp);
        CGXDLMSVariant_copy_21(&tmp, &((*it)->m_Start));
        GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &tmp);
        CGXDLMSVariant_Clear(&tmp);

        str = CGXDLMSSeasonProfile_GetWeekName(*it);

        CGXDLMSVariant_Add_3(&tmp, str);

        String_d(&str);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &tmp);
    }

    CGXDLMSVariant_d(&tmp);
    return 0;
}

int CGXDLMSActivityCalendar_GetWeekProfile(Vector* items, CGXByteBuffer* data)//std_vector<CGXDLMSWeekProfile*>& items
{
    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    unsigned long cnt = (unsigned long)Vector_size(items);
    //Add count
    GXHelpers_SetObjectCount(cnt, data);

    CGXDLMSVariant tmp;
    CGXDLMSVariant_1(&tmp);

    // std_vector<CGXDLMSWeekProfile*>
    for (unsigned int i = Vector_begin(items); i != Vector_end(items); ++i)
    {
        CGXDLMSWeekProfile** it = Vector_at(items, i);

        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(data, 8);
        CGXDLMSVariant_Clear(&tmp);

        String str = CGXDLMSWeekProfile_GetName(*it);

        CGXDLMSVariant_Add_3(&tmp, str);

        String_d(&str);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &tmp);

        CGXDLMSVariant_copy_12(&tmp, (*it)->m_Monday);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);

        CGXDLMSVariant_copy_12(&tmp, (*it)->m_Tuesday);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);

        CGXDLMSVariant_copy_12(&tmp, (*it)->m_Wednesday);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);

        CGXDLMSVariant_copy_12(&tmp, (*it)->m_Thursday);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);

        CGXDLMSVariant_copy_12(&tmp, (*it)->m_Friday);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);

        CGXDLMSVariant_copy_12(&tmp, (*it)->m_Saturday);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);

        CGXDLMSVariant_copy_12(&tmp, (*it)->m_Sunday);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp);
    }

    CGXDLMSVariant_d(&tmp);
    return 0;
}

int CGXDLMSActivityCalendar_GetDayProfile(Vector* items, CGXByteBuffer* data)//std_vector<CGXDLMSDayProfile*>& items
{
    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    unsigned long cnt = (unsigned long)Vector_size(items);
    //Add count
    GXHelpers_SetObjectCount(cnt, data);

    //std_vector<CGXDLMSDayProfile*>
    for (unsigned int i = Vector_begin(items); i != Vector_end(items); ++i)
    {
        CGXDLMSDayProfile** it = Vector_at(items, i);

        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(data, 2);

        CGXDLMSVariant tmp2;
        CGXDLMSVariant_9(&tmp2, (*it)->m_DayId);

        GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT8, &tmp2);
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);

        //Add count
        Vector* schedules = CGXDLMSDayProfile_GetDaySchedules(*it); // std_vector<CGXDLMSDayProfileAction*>&

        GXHelpers_SetObjectCount((unsigned long)Vector_size(schedules), data);

        CGXDLMSVariant time, ln, selector;
        CGXDLMSVariant_1(&time);
        CGXDLMSVariant_1(&ln);
        CGXDLMSVariant_1(&selector);

        // std_vector<CGXDLMSDayProfileAction*>
        for (unsigned int iaction = Vector_begin(schedules);
                iaction != Vector_end(schedules); ++iaction)
        {
            CGXDLMSDayProfileAction** action = Vector_at(schedules, iaction);

            String str = CGXDLMSDayProfileAction_GetScriptLogicalName(*action);

            GXHelpers_SetLogicalName_1(String_c_str(&str), &ln);

            String_d(&str);

            CGXDLMSVariant_copy_20(&time, CGXDLMSDayProfileAction_GetStartTime(*action));

            CGXDLMSVariant_copy_12(&selector, (*action)->m_ScriptSelector);

            CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(data, 3);
            GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &time);
            GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &ln);
            GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT16, &selector);
        }

        CGXDLMSVariant_d(&tmp2);
        CGXDLMSVariant_d(&time);
        CGXDLMSVariant_d(&ln);
        CGXDLMSVariant_d(&selector);
    }
    return 0;
}

// Returns value of given attribute.
int CGXDLMSActivityCalendar_GetValue(CGXDLMSActivityCalendar *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        CGXDLMSVariant_Add_2(&tmp, String_c_str(&p->m_CalendarNameActive),
                             (int) String_size(&p->m_CalendarNameActive));

        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_OK;
    }

    CGXByteBuffer data;
    CGXByteBuffer_1(&data);

    if (e_index == 3)
    {
        e->m_ByteArray = true;
        CGXDLMSActivityCalendar_GetSeasonProfile(&p->m_SeasonProfileActive, &data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        e->m_ByteArray = true;
        CGXDLMSActivityCalendar_GetWeekProfile(&p->m_WeekProfileTableActive, &data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        e->m_ByteArray = true;
        CGXDLMSActivityCalendar_GetDayProfile(&p->m_DayProfileTableActive, &data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        CGXDLMSVariant_Add_3(CGXDLMSValueEventArg_GetValue(e), p->m_CalendarNamePassive);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 7)
    {
        e->m_ByteArray = true;
        CGXDLMSActivityCalendar_GetSeasonProfile(&p->m_SeasonProfilePassive, &data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 8)
    {
        e->m_ByteArray = true;
        CGXDLMSActivityCalendar_GetWeekProfile(&p->m_WeekProfileTablePassive, &data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 9)
    {
        e->m_ByteArray = true;
        CGXDLMSActivityCalendar_GetDayProfile(&p->m_DayProfileTablePassive, &data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 10)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_16(&tmp, &p->m_Time);

        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }

    CGXByteBuffer_d(&data);
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

void CGXDLMSActivityCalendar_AddSeasonProfile(Vector* items, Vector* list)//std_vector<CGXDLMSSeasonProfile*>& items, std_vector<CGXDLMSVariant>& list
{
    // std_vector<CGXDLMSSeasonProfile*>
    for (unsigned int iitem = Vector_begin(items); iitem != Vector_end(items); ++iitem)
    {
        CGXDLMSSeasonProfile** item = Vector_at(items, iitem);

        //delete *item;
        CGXDLMSSeasonProfile_d(*item);
        DLMSPort_free(*item);
    }
    Vector_clear(items);

    String name;
    String_(&name);

    CGXDLMSVariant tmp;
    CGXDLMSVariant_1(&tmp);

    // std_vector<CGXDLMSVariant>
    for (unsigned int iitem = Vector_begin(list); iitem != Vector_end(list); ++iitem)
    {
        CGXDLMSVariant* item = Vector_at(list, iitem);

        //CGXDLMSSeasonProfile *it = new CGXDLMSSeasonProfile();
        CGXDLMSSeasonProfile* it = DLMSPort_malloc(sizeof(CGXDLMSSeasonProfile));
        CGXDLMSSeasonProfile_1(it);

        String_clear(&name);

        String_append_2(&name, ((CGXDLMSVariant*) Vector_at(&(item->Arr), 0))->st.un.byteArr,
                                CGXDLMSVariant_GetSize_1(Vector_at(&(item->Arr), 0)));

        CGXDLMSSeasonProfile_SetName(it, name);

        CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&(item->Arr), 1),
                                    DLMS_DATA_TYPE_DATETIME, &tmp);

        it->m_Start = tmp.dateTime;

        String_clear(&name);

        String_append_2(&name, ((CGXDLMSVariant*) Vector_at(&(item->Arr), 2))->st.un.byteArr,
                                CGXDLMSVariant_GetSize_1(Vector_at(&(item->Arr), 2)));

        CGXDLMSSeasonProfile_SetWeekName(it, name);

        Vector_push_back(items, &it);
    }

    String_d(&name);
    CGXDLMSVariant_d(&tmp);
}

void CGXDLMSActivityCalendar_AddWeekProfileTable(Vector* items, Vector* list)//std_vector<CGXDLMSWeekProfile*>& items, std_vector<CGXDLMSVariant>& list
{
    // std_vector<CGXDLMSWeekProfile*>
    for (unsigned int iitem = Vector_begin(items); iitem != Vector_end(items); ++iitem)
    {
        CGXDLMSWeekProfile** item = Vector_at(items, iitem);

        //delete *item;
        CGXDLMSWeekProfile_d(*item);
        DLMSPort_free(*item);
    }
    Vector_clear(items);

    String name;
    String_(&name);

    // std_vector<CGXDLMSVariant>
    for (unsigned int iitem = Vector_begin(list); iitem != Vector_end(list); ++iitem)
    {
        CGXDLMSVariant* item = Vector_at(list, iitem);

        //CGXDLMSWeekProfile *it = new CGXDLMSWeekProfile();
        CGXDLMSWeekProfile* it = DLMSPort_malloc(sizeof(CGXDLMSWeekProfile));
        CGXDLMSWeekProfile_1(it);

        String_clear(&name);

        String_append_2(&name, ((CGXDLMSVariant*) Vector_at(&(item->Arr), 0))->st.un.byteArr,
                CGXDLMSVariant_GetSize_1(Vector_at(&(item->Arr), 0)));

        CGXDLMSWeekProfile_SetName(it, name);
        it->m_Monday = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 1))->st.un.lVal;
        it->m_Tuesday = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 2))->st.un.lVal;
        it->m_Wednesday = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 3))->st.un.lVal;
        it->m_Thursday = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 4))->st.un.lVal;
        it->m_Friday = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 5))->st.un.lVal;
        it->m_Saturday = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 6))->st.un.lVal;
        it->m_Sunday = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 7))->st.un.lVal;

        Vector_push_back(items, &it);
    }

    String_d(&name);
}

void CGXDLMSActivityCalendar_AddDayProfileTable(Vector* items, Vector* list)//std_vector<CGXDLMSDayProfile*>& items, std_vector<CGXDLMSVariant>& list
{
    // std_vector<CGXDLMSDayProfile*>
    for (unsigned int iitem = Vector_begin(items); iitem != Vector_end(items); ++iitem)
    {
        CGXDLMSDayProfile** item = Vector_at(items, iitem);

        //delete *item;
        CGXDLMSDayProfile_d(*item);
        DLMSPort_free(*item);
    }
    Vector_clear(items);

    // std_vector<CGXDLMSVariant>
    for (unsigned int iitem = Vector_begin(list); iitem != Vector_end(list); ++iitem)
    {
        CGXDLMSVariant* item = Vector_at(list, iitem);

        //CGXDLMSDayProfile* it = new CGXDLMSDayProfile();
        CGXDLMSDayProfile* it = DLMSPort_malloc(sizeof(CGXDLMSDayProfile));
        CGXDLMSDayProfile_1(it);

        it->m_DayId = ((CGXDLMSVariant*) Vector_at(&(item->Arr), 0))->st.un.iVal;

        String ln;
        String_(&ln);

        // std_vector<CGXDLMSVariant>
        Vector* vec = &(((CGXDLMSVariant*) Vector_at(&(item->Arr), 1))->Arr);
        for (unsigned int iit2 = Vector_begin(vec); iit2 != Vector_end(vec); ++iit2)
        {
            CGXDLMSVariant* it2 = Vector_at(vec, iit2);

            //CGXDLMSDayProfileAction * ac = new CGXDLMSDayProfileAction();
            CGXDLMSDayProfileAction* ac = DLMSPort_malloc(sizeof(CGXDLMSDayProfileAction));
            CGXDLMSDayProfileAction_1(ac);

            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&it2->Arr, 0),
                                        DLMS_DATA_TYPE_TIME, &tmp);

            CGXDLMSDayProfileAction_SetStartTime(ac, (CGXTime*) &(tmp.dateTime));

            GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&it2->Arr, 1))->st.un.byteArr, &ln);

            CGXDLMSDayProfileAction_SetScriptLogicalName(ac, ln);

            ac->m_ScriptSelector = ((CGXDLMSVariant*) Vector_at(&it2->Arr, 2))->st.un.lVal;

            Vector_push_back(CGXDLMSDayProfile_GetDaySchedules(it), &ac);

            CGXDLMSVariant_d(&tmp);
        }

        Vector_push_back(items, &it);

        String_d(&ln);
    }
}

// Set value of given attribute.
int CGXDLMSActivityCalendar_SetValue(CGXDLMSActivityCalendar *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        String name;
        String_(&name);

        String_append_2(&name, CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                               CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetValue(e)));
        CGXDLMSActivityCalendar_SetCalendarNameActive(p, name);

        String_d(&name);
    }
    else if (e_index == 3)
    {
        CGXDLMSActivityCalendar_AddSeasonProfile(&p->m_SeasonProfileActive,
                                                 &(CGXDLMSValueEventArg_GetValue(e)->Arr));
    }
    else if (e_index == 4)
    {
        CGXDLMSActivityCalendar_AddWeekProfileTable(&p->m_WeekProfileTableActive,
                                                    &(CGXDLMSValueEventArg_GetValue(e)->Arr));
    }
    else if (e_index == 5)
    {
        CGXDLMSActivityCalendar_AddDayProfileTable(&p->m_DayProfileTableActive,
                                                   &(CGXDLMSValueEventArg_GetValue(e)->Arr));
    }
    else if (e_index == 6)
    {
        String name;
        String_(&name);

        String_append_2(&name, CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                               CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetValue(e)));

        CGXDLMSActivityCalendar_SetCalendarNamePassive(p, name);

        String_d(&name);
    }
    else if (e_index == 7)
    {
        CGXDLMSActivityCalendar_AddSeasonProfile(&p->m_SeasonProfilePassive,
                                                 &(CGXDLMSValueEventArg_GetValue(e)->Arr));
    }
    else if (e_index == 8)
    {
        CGXDLMSActivityCalendar_AddWeekProfileTable(&p->m_WeekProfileTablePassive,
                                                    &(CGXDLMSValueEventArg_GetValue(e)->Arr));
    }
    else if (e_index == 9)
    {
        CGXDLMSActivityCalendar_AddDayProfileTable(&p->m_DayProfileTablePassive,
                                                   &(CGXDLMSValueEventArg_GetValue(e)->Arr));
    }
    else if (e_index == 10)
    {
        int ret;

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        if ((ret = CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e),
                                              DLMS_DATA_TYPE_DATETIME, &tmp)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            return ret;
        }
        p->m_Time = tmp.dateTime;

        CGXDLMSVariant_d(&tmp);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
