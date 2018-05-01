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
#include "../include/GXDLMSSpecialDaysTable.h"
#include "../include/Optimize.h"

static void CGXDLMSSpecialDaysTable__(CGXDLMSSpecialDaysTable* p)
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
     p->GetAttributeCount = CGXDLMSSpecialDaysTable_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSSpecialDaysTable_GetMethodCount;
	 p->GetValue = CGXDLMSSpecialDaysTable_GetValue;
	 p->SetValue = CGXDLMSSpecialDaysTable_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
     p->d = CGXDLMSSpecialDaysTable_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSSpecialDaysTable_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSSpecialDaysTable_GetValues;
     p->GetAttributeIndexToRead = CGXDLMSSpecialDaysTable_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

     Vector_(&p->m_Entries, sizeof(CGXDLMSSpecialDay*), NULL, NULL); // std::vector<CGXDLMSSpecialDay*>
}
//Constructor.
void CGXDLMSSpecialDaysTable_1(CGXDLMSSpecialDaysTable *p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSSpecialDaysTable_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSSpecialDaysTable_2(CGXDLMSSpecialDaysTable *p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE, &ln, sn);

	CGXDLMSSpecialDaysTable__(p);
}

//LN Constructor.
void CGXDLMSSpecialDaysTable_3(CGXDLMSSpecialDaysTable *p, String ln)
{
	CGXDLMSSpecialDaysTable_2(p, ln, 0);
}

void CGXDLMSSpecialDaysTable_d(CGXDLMSSpecialDaysTable *p)
{
   // for (std::vector<CGXDLMSSpecialDay*>::iterator it = m_Entries.begin(); it != m_Entries.end(); ++it)
	for (unsigned int i = Vector_begin(&p->m_Entries);
	    		i != Vector_end(&p->m_Entries); ++i)
	{
		CGXDLMSSpecialDay** it = Vector_at(&(p->m_Entries), i);

		// Do not CGXDLMSSpecialDay_d(*it);
		DLMSPort_free(*it);
	}
	Vector_clear(&p->m_Entries);

	CGXDLMSObject_d((CGXDLMSObject*) p);
}

Vector* CGXDLMSSpecialDaysTable_GetEntries(CGXDLMSSpecialDaysTable *p)//std::vector<CGXDLMSSpecialDay*>&
{
    return &p->m_Entries;
}

// Returns amount of attributes.
int CGXDLMSSpecialDaysTable_GetAttributeCount(CGXDLMSSpecialDaysTable *p)
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSSpecialDaysTable_GetMethodCount(CGXDLMSSpecialDaysTable *p)
{
    return 2;
}

void CGXDLMSSpecialDaysTable_GetValues(CGXDLMSSpecialDaysTable *p, Vector* values)//std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std::vector<CGXDLMSSpecialDay*>::iterator it = m_Entries.begin(); it != m_Entries.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_Entries);
            i != Vector_end(&p->m_Entries); ++i)
    {
    	CGXDLMSSpecialDay** it = Vector_at(&(p->m_Entries), i);
        if (!empty)
        {
        	String_append_1(&sb, ", ");
        }
        empty = false;

        String str = CGXDLMSSpecialDay_ToString(*it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);
}

void CGXDLMSSpecialDaysTable_GetAttributeIndexToRead(CGXDLMSSpecialDaysTable *p, Vector* attributes)//std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Entries
    if (CGXDLMSSpecialDaysTable_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSSpecialDaysTable_GetDataType(CGXDLMSSpecialDaysTable *p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    //Entries
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSSpecialDaysTable_GetValue(CGXDLMSSpecialDaysTable *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_Entries), &data);

        int ret;

        CGXDLMSVariant index, date, id;
        CGXDLMSVariant_1(&index);
        CGXDLMSVariant_1(&date);
        CGXDLMSVariant_1(&id);

        //for (std::vector<CGXDLMSSpecialDay*>::iterator it = m_Entries.begin(); it != m_Entries.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_Entries); i != Vector_end(&p->m_Entries); ++i)
        {
            CGXDLMSSpecialDay** it = Vector_at(&p->m_Entries, i);

            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 3); //Count
            // index = (*it)->GetIndex();
            // date = (*it)->GetDate();
            // id = (*it)->GetDayId();
            CGXDLMSVariant_copy_12(&index, (*it)->m_Index);
            CGXDLMSVariant_copy_21(&date, &((*it)->m_Date));
            CGXDLMSVariant_copy_12(&id, (*it)->m_DayId);

            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT16, &index)) != DLMS_ERROR_CODE_OK ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &date)) != DLMS_ERROR_CODE_OK ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT8, &id)) != DLMS_ERROR_CODE_OK)
            {
                CGXByteBuffer_d(&data);
                CGXDLMSVariant_d(&index);
                CGXDLMSVariant_d(&date);
                CGXDLMSVariant_d(&id);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);

        CGXDLMSVariant_d(&index);
        CGXDLMSVariant_d(&date);
        CGXDLMSVariant_d(&id);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSSpecialDaysTable_SetValue(CGXDLMSSpecialDaysTable *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    else if (e_index == 2)
    {
        //for (std::vector<CGXDLMSSpecialDay*>::iterator it = m_Entries.begin(); it != m_Entries.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_Entries); i != Vector_end(&p->m_Entries); ++i)
        {
            CGXDLMSSpecialDay** it = Vector_at(&p->m_Entries, i);

            // Do not CGXDLMSSpecialDay_d(*it);
            DLMSPort_free(*it);
        }
        Vector_clear(&p->m_Entries);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
            //for (std::vector<CGXDLMSVariant>::iterator item = e.GetValue().Arr.begin(); item != e.GetValue().Arr.end(); ++item) 
            for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
            {
                CGXDLMSVariant* item = Vector_at(temp, i);

                CGXDLMSSpecialDay *it = DLMSPort_malloc(sizeof(CGXDLMSSpecialDay));
                CGXDLMSSpecialDay_(it);

                it->m_Index = CGXDLMSVariant_ToInteger(Vector_at(&(item->Arr), 0));
                CGXDLMSClient_ChangeType_2(Vector_at(&(item->Arr), 1), DLMS_DATA_TYPE_DATE, &tmp);
                it->m_Date = tmp.dateTime;
                it->m_DayId = CGXDLMSVariant_ToInteger(Vector_at(&(item->Arr), 2));

                Vector_push_back(&p->m_Entries, &it);
            }

            CGXDLMSVariant_d(&tmp);
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
