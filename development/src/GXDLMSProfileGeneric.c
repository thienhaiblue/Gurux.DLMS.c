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

#include "../include/GXDLMSProfileGeneric.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSDemandRegister.h"
#include "../include/GXDLMSServer.h"
#include "../include/Optimize.h"

static int CGXDLMSProfileGeneric_GetSelectedColumns_1(
    CGXDLMSProfileGeneric* p,
    Vector* cols, //std::vector<CGXDLMSVariant>&
    Vector* columns); //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&

static void CGXDLMSProfileGeneric__(CGXDLMSProfileGeneric* p)
{
    // Override IGXDLMSBase
    p->GetAttributeCount = CGXDLMSProfileGeneric_GetAttributeCount;
    p->GetMethodCount = CGXDLMSProfileGeneric_GetMethodCount;
	p->GetValue = CGXDLMSProfileGeneric_GetValue;
	p->SetValue = CGXDLMSProfileGeneric_SetValue;
	p->Invoke = CGXDLMSProfileGeneric_Invoke;

    // Override CGXDLMSObject
	p->d = CGXDLMSProfileGeneric_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSProfileGeneric_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSProfileGeneric_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSProfileGeneric_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

    Vector_(&p->m_DynamicColumns, sizeof(CGXDLMSObject*), NULL, NULL); //std::vector<CGXDLMSObject*>

    Vector_(&p->m_Buffer, sizeof(Vector), Vector_v_c, Vector_v_d); //std::vector< std::vector<CGXDLMSVariant> >
    Vector_(&p->m_CaptureObjects, sizeof(Pair), Pair_v_c, Pair_v_d); //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
}
void CGXDLMSProfileGeneric_d(CGXDLMSProfileGeneric* p)
{
    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    for (unsigned int i = Vector_begin(&p->m_CaptureObjects);
        i != Vector_end(&p->m_CaptureObjects); ++i)
    {
        Pair* it = Vector_at(&p->m_CaptureObjects, i);

        //delete it->second;
        CGXDLMSCaptureObject* it_second = *((CGXDLMSCaptureObject**) (it->second));

        // Do not CGXDLMSCaptureObject_d(it_second);
        DLMSPort_free(it_second);
    }

    // std::vector<CGXDLMSObject*>
    for (unsigned int i = Vector_begin(&p->m_DynamicColumns);
        i != Vector_end(&p->m_DynamicColumns); ++i)
    {
        CGXDLMSObject** it = Vector_at(&p->m_DynamicColumns, i);

        //delete *it;
        (*it)->d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_DynamicColumns);
    Vector_clear(&p->m_CaptureObjects);
    Vector_clear(&p->m_Buffer);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}

int CGXDLMSProfileGeneric_GetSelectedColumns_2(
    CGXDLMSProfileGeneric* p,
    int selector,
    CGXDLMSVariant* parameters,
    Vector* columns) //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
{
    Vector_clear(columns);
    if (selector == 0)
    {
        // Return all rows.
        // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
        for (unsigned int i = Vector_begin(&p->m_CaptureObjects);
            i != Vector_end(&p->m_CaptureObjects); ++i)
        {
            Pair* it = Vector_at(&p->m_CaptureObjects, i);

            Vector_push_back(columns, it);
        }
        return 0;
    }
    else if (selector == 1)
    {

        return CGXDLMSProfileGeneric_GetSelectedColumns_1(p, &(((CGXDLMSVariant*) Vector_at(&parameters->Arr, 3))->Arr),
                                                          columns);
    }
    else if (selector == 2)
    {
        int colStart = 1;
        int colCount = 0;
        if (Vector_size(&parameters->Arr) > 2)
        {
            colStart = CGXDLMSVariant_ToInteger(Vector_at(&parameters->Arr, 2));
        }
        if (Vector_size(&parameters->Arr) > 3)
        {
            colCount = CGXDLMSVariant_ToInteger(Vector_at(&parameters->Arr, 3));
        }
        else if (colStart != 1)
        {
            colCount = (int)Vector_size(&p->m_CaptureObjects);
        }
        if (colStart != 1 || colCount != 0)
        {
            // Return all rows.
            // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
            for (unsigned int i = colStart - 1; i != colStart + colCount - 1; ++i)
            {
                Pair* it = Vector_at(&p->m_CaptureObjects, i);

                Vector_push_back(columns, it);
            }

//            columns.insert(columns.end(), p->m_CaptureObjects.begin() + colStart - 1,
//                p->m_CaptureObjects.begin() + colStart + colCount - 1);
        }
        else
        {
            // Return all rows.
            //columns.insert(columns.end(), p->m_CaptureObjects.begin(), p->m_CaptureObjects.end());
            // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
            for (unsigned int i = Vector_begin(&p->m_CaptureObjects);
                i != Vector_end(&p->m_CaptureObjects); ++i)
            {
                Pair* it = Vector_at(&p->m_CaptureObjects, i);

                Vector_push_back(columns, it);
            }
        }
        return 0;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}
static int CGXDLMSProfileGeneric_GetColumns(CGXDLMSProfileGeneric* p, CGXByteBuffer* data)
{
    unsigned long cnt = (unsigned long)Vector_size(&p->m_CaptureObjects);
    CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
    //Add count
    GXHelpers_SetObjectCount(cnt, data);

    //String ln;
    //String_(&ln);

    int ret;

    CGXDLMSVariant tmp, ai, di;
    CGXDLMSVariant_1(&tmp);
    CGXDLMSVariant_1(&ai);
    CGXDLMSVariant_1(&di);

    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    for (unsigned int i = Vector_begin(&p->m_CaptureObjects);
            i != Vector_end(&p->m_CaptureObjects); ++i)
    {
        Pair* it = Vector_at(&p->m_CaptureObjects, i);

        CGXDLMSObject* it_first = *((CGXDLMSObject**) (it->first));
        CGXDLMSCaptureObject* it_second = *((CGXDLMSCaptureObject**) (it->second));

        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(data, 4); //Count

        CGXDLMSVariant_copy_12(&tmp, it_first->m_ObjectType);

        if ((ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT16, &tmp)) != 0) //ClassID
        {
            CGXDLMSVariant_d(&tmp);
            CGXDLMSVariant_d(&ai);
            CGXDLMSVariant_d(&di);
            return ret;
        }
        CGXDLMSVariant_Clear(&tmp);
        if ((ret = CGXDLMSObject_GetLogicalName_1(it_first, &tmp)) != 0)
        {
            CGXDLMSVariant_d(&tmp);
            CGXDLMSVariant_d(&ai);
            CGXDLMSVariant_d(&di);
            return ret;
        }

        CGXDLMSVariant_copy_12(&ai, it_second->m_AttributeIndex);
        CGXDLMSVariant_copy_12(&di, it_second->m_DataIndex);

        if ((ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0 || //LN
            (ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_INT8, &ai)) != 0 || //Attribute Index
            (ret = GXHelpers_SetData(data, DLMS_DATA_TYPE_UINT16, &di)) != 0) //Data Index
        {
            CGXDLMSVariant_d(&tmp);
            CGXDLMSVariant_d(&ai);
            CGXDLMSVariant_d(&di);
            return ret;
        }
    }

    CGXDLMSVariant_d(&tmp);
    CGXDLMSVariant_d(&ai);
    CGXDLMSVariant_d(&di);
    return DLMS_ERROR_CODE_OK;
}

static int CGXDLMSProfileGeneric_GetData(
    CGXDLMSProfileGeneric* p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e,
    Vector* table, //std::vector< std::vector<CGXDLMSVariant> >&
    Vector* columns, //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
    CGXByteBuffer* data)
{
    if (settings->m_Index == 0) {
        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_ARRAY);
        if (e->m_RowEndIndex != 0) {
            GXHelpers_SetObjectCount(e->m_RowEndIndex - e->m_RowBeginIndex, data);
        }
        else {
            GXHelpers_SetObjectCount((unsigned long)Vector_size(table), data);
        }
    }

    Vector types; // std::vector<DLMS_DATA_TYPE>
    Vector_(&types, sizeof(DLMS_DATA_TYPE), NULL, NULL);

    DLMS_DATA_TYPE type;
    int ret;

    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    for (unsigned int i = Vector_begin(&p->m_CaptureObjects);
        i != Vector_end(&p->m_CaptureObjects); ++i)
    {
        Pair* it = Vector_at(&p->m_CaptureObjects, i);

        CGXDLMSObject* it_first = *((CGXDLMSObject**) (it->first));
        CGXDLMSCaptureObject* it_second = *((CGXDLMSCaptureObject**) (it->second));

        if ((ret = it_first->GetDataType(it_first, it_second->m_AttributeIndex, &type)) != 0)
        {
            Vector_d(&types);
            return ret;
        }
        Vector_push_back(&types, &type);
    }

    // std::vector< std::vector<CGXDLMSVariant> >::iterator
    for (unsigned int irow = Vector_begin(table); irow != Vector_end(table); ++irow)
    {
        Vector* row = Vector_at(table, irow);

        CGXByteBuffer_SetUInt8_1(data, DLMS_DATA_TYPE_STRUCTURE);
        if (Vector_size(columns) == 0)
        {
            GXHelpers_SetObjectCount((unsigned long)Vector_size(row), data);
        }
        else
        {
            GXHelpers_SetObjectCount((unsigned long)Vector_size(columns), data);
        }
        int pos = -1;

        // std::vector<CGXDLMSVariant>
        for (unsigned int ivalue = Vector_begin(row); ivalue != Vector_end(row); ++ivalue)
        {
            CGXDLMSVariant* value = Vector_at(row, ivalue);

            // DLMS_DATA_TYPE tp = types[++pos];
            DLMS_DATA_TYPE tp = *((DLMS_DATA_TYPE*) Vector_at(&types, ++pos));
            if (tp == DLMS_DATA_TYPE_NONE)
            {
                tp = value->st.vt;

                //types[pos] = tp;
                *((DLMS_DATA_TYPE*) Vector_at(&types, pos)) = tp;
            }

//            if (Vector_size(columns) == 0 ||
//                std::find(columns.begin(), columns.end(), p->m_CaptureObjects.at(pos)) != columns.end())
//            {
//                if ((ret = GXHelpers_SetData(data, tp, value)) != 0)
//                {
//                    Vector_d(&types);
//                    return ret;
//                }
//            }
            if (Vector_size(columns) == 0)
            {
                if ((ret = GXHelpers_SetData(data, tp, value)) != 0)
                {
                    Vector_d(&types);
                    return ret;
                }
            }
            else
            {
                Pair* p_target = Vector_at(&p->m_CaptureObjects, pos);

                CGXDLMSObject* target_first = *((CGXDLMSObject**) (p_target->first));
                CGXDLMSCaptureObject* target_second = *((CGXDLMSCaptureObject**) (p_target->second));

                unsigned int j;
                //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
                for (j = Vector_begin(columns); j < Vector_end(columns); j++)
                {
                    Pair* pair = Vector_at(columns, j);

                    CGXDLMSObject* pair_first = *((CGXDLMSObject**) (pair->first));
                    CGXDLMSCaptureObject* pair_second = *((CGXDLMSCaptureObject**) (pair->second));

                    if ((pair_first == target_first) && (pair_second == target_second))
                    {
                        break;
                    }
                }

                if (j != Vector_end(columns))
                {
                    if ((ret = GXHelpers_SetData(data, tp, value)) != 0)
                    {
                        Vector_d(&types);
                        return ret;
                    }
                }
            }

        }
        settings->m_Index = settings->m_Index + 1;
    }
    if (e->m_RowEndIndex != 0)
    {
        e->m_RowBeginIndex = e->m_RowBeginIndex + (unsigned short)Vector_size(table);
    }

    Vector_d(&types);
    return DLMS_ERROR_CODE_OK;
}

/*
* Add new capture object (column) to the profile generic.
*/
static int CGXDLMSProfileGeneric_AddCaptureObject(
    CGXDLMSProfileGeneric* p,
    CGXDLMSObject* pObj,
    int attributeIndex,
    int dataIndex)
{
    if (pObj == NULL)
    {
        //Invalid Object
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (attributeIndex < 1)
    {
        //Invalid attribute index
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (dataIndex < 0)
    {
        //Invalid data index
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    // CGXDLMSCaptureObject* pCO = new CGXDLMSCaptureObject(attributeIndex, dataIndex);
    CGXDLMSCaptureObject* pCO = DLMSPort_malloc(sizeof(CGXDLMSCaptureObject));
    CGXDLMSCaptureObject_2(pCO, attributeIndex, dataIndex);

    // std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*>(pObj, pCO)
    Pair pair;
    Pair_(&pair, sizeof(CGXDLMSObject*), sizeof(CGXDLMSCaptureObject*),
          NULL, NULL, NULL, NULL, &pObj, &pCO);

    Vector_push_back(&p->m_CaptureObjects, &pair);

    Pair_d(&pair);
    return DLMS_ERROR_CODE_OK;
}

/**
 * Get selected columns.
 *
 * @param parameters
 *            Received data.
 * @param cols
 *            Selected columns.
 */
static int CGXDLMSProfileGeneric_GetSelectedColumns_1(
    CGXDLMSProfileGeneric* p,
    Vector* cols, //std::vector<CGXDLMSVariant>&
    Vector* columns) //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
{
    int dataIndex;
    unsigned char attributeIndex;

    String ln, ln2;
    String_(&ln);
    String_(&ln2);

    // std::vector<CGXDLMSVariant>
    for (unsigned int i = Vector_begin(cols); i != Vector_end(cols); ++i)
    {
        CGXDLMSVariant* it = Vector_at(cols, i);

        DLMS_OBJECT_TYPE ot = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 0));
        GXHelpers_GetLogicalName_1(((CGXDLMSVariant*)Vector_at(&it->Arr, 1))->st.un.byteArr, &ln);
        attributeIndex = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 2));
        dataIndex = CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 3));

        // Find columns and update only them.
        // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
        for (unsigned int ic = Vector_begin(&p->m_CaptureObjects);
                ic != Vector_end(&p->m_CaptureObjects); ++ic)
        {
            Pair* c = Vector_at(&p->m_CaptureObjects, ic);

            CGXDLMSObject* c_first = *((CGXDLMSObject**) (c->first));
            CGXDLMSCaptureObject* c_second = *((CGXDLMSCaptureObject**) (c->second));

            CGXDLMSObject_GetLogicalName_2(c_first, &ln2);

            if (c_first->m_ObjectType == ot
             && c_second->m_AttributeIndex == attributeIndex
             && c_second->m_DataIndex == dataIndex
             && String_compare(&ln2, String_c_str(&ln)) == 0)
            {
                Vector_push_back(columns, c);
                break;
            }
        }
    }

    String_d(&ln);
    String_d(&ln2);
    return 0;
}

static int CGXDLMSProfileGeneric_GetProfileGenericData(
    CGXDLMSProfileGeneric* p,
    CGXDLMSSettings* settings,
    CGXDLMSValueEventArg* e,
    CGXByteBuffer* reply)
{
    Vector columns; // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    Vector_(&columns, sizeof(Pair), Pair_v_c, Pair_v_d);

    //If all data is read.
    if (e->m_Selector == 0
     || CGXDLMSValueEventArg_GetParameters(e)->st.vt == DLMS_DATA_TYPE_NONE
     || e->m_RowEndIndex != 0)
    {
        int ret = CGXDLMSProfileGeneric_GetData(p, settings, e,
                                                CGXDLMSProfileGeneric_GetBuffer(p), &columns, reply);

        Vector_d(&columns);
        return ret;
    }

    Vector* table = CGXDLMSProfileGeneric_GetBuffer(p); // std::vector< std::vector<CGXDLMSVariant> >&

    Vector items; // std::vector< std::vector<CGXDLMSVariant> >
    Vector_(&items, sizeof(Vector), Vector_v_c, Vector_v_d);

    if (e->m_Selector == 1) //Read by range
    {
        int ret;

        CGXDLMSVariant value;
        CGXDLMSVariant_1(&value);

        if ((ret = CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 1),
                                              DLMS_DATA_TYPE_DATETIME, &value)) != 0)
        {
            CGXDLMSVariant_d(&value);
            Vector_d(&columns);
            Vector_d(&items);
            return ret;
        }

        struct tm tmp = value.dateTime.m_Value;
        time_t start = mktime(&tmp);

        CGXDLMSVariant_Clear(&value);

        if ((ret = CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 2),
                                            DLMS_DATA_TYPE_DATETIME, &value)) != 0)
        {
            CGXDLMSVariant_d(&value);
            Vector_d(&columns);
            Vector_d(&items);
            return ret;
        }
        tmp = value.dateTime.m_Value;
        time_t end = mktime(&tmp);
        CGXDLMSVariant_Clear(&value);

        if (Vector_size(&CGXDLMSValueEventArg_GetParameters(e)->Arr) > 3)
        {
            ret = CGXDLMSProfileGeneric_GetSelectedColumns_1(p, &((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 2))->Arr, &columns);
        }

        // std::vector< std::vector<CGXDLMSVariant> >
        for (unsigned int irow = Vector_begin(table); irow != Vector_end(table); ++irow)
        {
            Vector* row = Vector_at(table, irow);

            tmp = ((CGXDLMSVariant*) Vector_at(row, 0))->dateTime.m_Value;
            time_t tm = mktime(&tmp);
            if (tm >= start && tm <= end)
            {
                Vector_push_back(&items, row);
            }
        }

        CGXDLMSVariant_d(&value);
    }
    else if (e->m_Selector == 2) //Read by entry.
    {
        int start = CGXDLMSVariant_ToInteger(Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 0));
        int count = CGXDLMSVariant_ToInteger(Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 1));
        if (start == 0)
        {
            start = 1;
        }
        if (count == 0)
        {
            count = (int)Vector_size(table);
        }
        if ((unsigned long)(start + count - 1) > Vector_size(table))
        {
            count = (int)Vector_size(table);
        }

        int colStart = 1;
        int colCount = 0;
        if (Vector_size(&CGXDLMSValueEventArg_GetParameters(e)->Arr) > 2)
        {
            colStart = CGXDLMSVariant_ToInteger(Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 2));
        }
        if (Vector_size(&CGXDLMSValueEventArg_GetParameters(e)->Arr) > 3)
        {
            colCount = CGXDLMSVariant_ToInteger(Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 3));
        }
        else if (colStart != 1)
        {
            colCount = (int)Vector_size(&p->m_CaptureObjects);
        }
        if (colStart != 1 || colCount != 0)
        {
            // columns.insert(columns.end(), p->m_CaptureObjects.begin() + colStart - 1,
            //    p->m_CaptureObjects.begin() + colStart + colCount - 1);

            // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
            for (unsigned int i = colStart - 1; i != colStart + colCount - 1; ++i)
            {
                Pair* it = Vector_at(&p->m_CaptureObjects, i);

                Vector_push_back(&columns, it);
            }
        }
        //Get rows.
        // Starting index is 1.
        for (int pos = 0; pos < count; ++pos)
        {
            if ((unsigned int)(pos + start - 1) == Vector_size(table))
            {
                break;
            }
            Vector_push_back(&items, Vector_at(table, start + pos - 1));
        }
    }
    else
    {
        Vector_d(&columns);
        Vector_d(&items);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    int ret = CGXDLMSProfileGeneric_GetData(p, settings, e, &items, &columns, reply);

    Vector_d(&columns);
    Vector_d(&items);
    return ret;
}

/**
 Constructor.
*/
void CGXDLMSProfileGeneric_1(CGXDLMSProfileGeneric* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSProfileGeneric_2(p, t_Str, 0);

	String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSProfileGeneric_2(CGXDLMSProfileGeneric* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_PROFILE_GENERIC, &ln, sn);

	CGXDLMSProfileGeneric__(p);

    p->m_SortObjectAttributeIndex = 0;
    p->m_SortObjectDataIndex = 0;
    p->m_SortObject = NULL;
    p->m_CapturePeriod = 3600;
    p->m_EntriesInUse = p->m_ProfileEntries = 0;
    p->m_SortMethod = DLMS_SORT_METHOD_FIFO;
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
void CGXDLMSProfileGeneric_3(CGXDLMSProfileGeneric* p, String ln)
{
	CGXDLMSProfileGeneric_2(p, ln, 0);
}

/**
 Data of profile generic.
*/
Vector* CGXDLMSProfileGeneric_GetBuffer(CGXDLMSProfileGeneric* p)//std::vector< std::vector<CGXDLMSVariant> >&
{
    return &p->m_Buffer;
}

/**
 Captured Objects.
*/
Vector* CGXDLMSProfileGeneric_GetCaptureObjects(CGXDLMSProfileGeneric* p) //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
{
    return &p->m_CaptureObjects;
}

void CGXDLMSProfileGeneric_Reset_1(CGXDLMSProfileGeneric* p)
{
    Vector_erase(&p->m_Buffer, Vector_begin(&p->m_Buffer), Vector_end(&p->m_Buffer));
    p->m_EntriesInUse = 0;
}

/*
* Copies the values of the objects to capture into the buffer by reading
* capture objects.
*/
int CGXDLMSProfileGeneric_Capture_1(CGXDLMSProfileGeneric* p, CGXDLMSServer* server)
{
    Vector values; // std::vector<CGXDLMSVariant>
    Vector_(&values, sizeof(CGXDLMSVariant), CGXDLMSVariant_v_c, CGXDLMSVariant_v_d);

    int ret;

    //CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(server, this, 2);
    CGXDLMSValueEventArg* e = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
    CGXDLMSValueEventArg_1(e, server, (CGXDLMSObject*) p, 2);

    CGXDLMSValueEventCollection args;
    CGXDLMSValueEventCollection_(&args);

    CGXDLMSValueEventCollection_push_back(&args, &e);

    server->PreGet(server, (Vector*) &args);

    if (!e->m_Handled)
    {
        // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
        for (unsigned int i = Vector_begin(&p->m_CaptureObjects);
            i != Vector_end(&p->m_CaptureObjects); ++i)
        {
            Pair* it = Vector_at(&p->m_CaptureObjects, i);

            CGXDLMSObject* it_first = *((CGXDLMSObject**) (it->first));
            CGXDLMSCaptureObject* it_second = *((CGXDLMSCaptureObject**) (it->second));

            CGXDLMSValueEventArg tmp;
            CGXDLMSValueEventArg_1(&tmp, server, it_first, it_second->m_AttributeIndex);

            if ((ret = it_first->GetValue(it_first, CGXDLMSServer_GetSettings(server), &tmp)) != 0)
            {
                CGXDLMSValueEventArg_d(&tmp);
                CGXDLMSValueEventCollection_d(&args);
                return ret;
            }
            Vector_push_back(&values, CGXDLMSValueEventArg_GetValue(&tmp));

            CGXDLMSValueEventArg_d(&tmp);
        }
        // Remove first items if buffer is full.
        if (p->m_ProfileEntries == Vector_size(CGXDLMSProfileGeneric_GetBuffer(p)))
        {
            //p->m_Buffer.pop_back();
            Vector_erase(&p->m_Buffer, p->m_Buffer.size - 1, p->m_Buffer.size);
        }
        Vector_push_back(&p->m_Buffer, &values);
        p->m_EntriesInUse = (unsigned long)Vector_size(&p->m_Buffer);
    }
    server->PostGet(server, (Vector*) &args);

    CGXDLMSValueEventCollection_d(&args);
    return 0;
}

int CGXDLMSProfileGeneric_Reset_2(CGXDLMSProfileGeneric* p, CGXDLMSClient* client, Vector* reply) //std::vector<CGXByteBuffer>&
{
    CGXDLMSVariant value;
    CGXDLMSVariant_19(&value, (unsigned char)0);

    int ret = CGXDLMSClient_Method_1(client, (CGXDLMSObject*) p, 1, &value, reply);

    CGXDLMSVariant_d(&value);
    return ret;
}

int CGXDLMSProfileGeneric_Capture_2(CGXDLMSProfileGeneric* p, CGXDLMSClient* client, Vector* reply) //std::vector<CGXByteBuffer>&
{
    CGXDLMSVariant value;
    CGXDLMSVariant_19(&value, (unsigned char)0);

    int ret = CGXDLMSClient_Method_1(client, (CGXDLMSObject*) p, 2, &value, reply);

    CGXDLMSVariant_d(&value);
    return ret;
}

void CGXDLMSProfileGeneric_GetValues(CGXDLMSProfileGeneric* p, Vector* values) //std::vector<std::string>&)
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    String sb;
    String_(&sb);

    bool empty = true;
    // std::vector< std::vector<CGXDLMSVariant> >
    for (unsigned int irow = Vector_begin(&p->m_Buffer); irow != Vector_end(&p->m_Buffer); ++irow)
    {
        Vector* row = Vector_at(&p->m_Buffer, irow);

        // std::vector<CGXDLMSVariant>
        for (unsigned int icell = Vector_begin(row); icell != Vector_end(row); ++icell)
        {
            CGXDLMSVariant* cell = Vector_at(row, icell);

            String_append_var_str(&sb, cell);

            String_append_1(&sb, " | ");
        }
        String_append_1(&sb, "\r\n");
    }

    Vector_push_back(values, &sb);

    String_d(&sb);

    //Clear str.
    String_3(&sb, "[");
    empty = true;

    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    for (unsigned int i = Vector_begin(&p->m_CaptureObjects); i != Vector_end(&p->m_CaptureObjects); ++i)
    {
        Pair* it = Vector_at(&p->m_CaptureObjects, i);

        CGXDLMSObject* it_first = *((CGXDLMSObject**) (it->first));

        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        CGXDLMSVariant var = CGXDLMSObject_GetName(it_first);

        String_append_var_str(&sb, &var);

        CGXDLMSVariant_d(&var);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);

    Vector_push_back_Str_2(values, p->m_CapturePeriod);

    Vector_push_back_Str_2(values, p->m_SortMethod);

    if (p->m_SortObject == NULL)
    {
        Vector_push_back_Str_3(values, "");
    }
    else
    {
        CGXDLMSVariant var = CGXDLMSObject_GetName(p->m_SortObject);

        Vector_push_back_Str_1(values, &var);

        CGXDLMSVariant_d(&var);
    }

    Vector_push_back_Str_5(values, p->m_EntriesInUse);

    Vector_push_back_Str_5(values, p->m_ProfileEntries);
}

void CGXDLMSProfileGeneric_GetAttributeIndexToRead(CGXDLMSProfileGeneric* p, Vector* attributes) //std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Buffer
    if (!CGXDLMSProfileGeneric_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //CaptureObjects
    if (!CGXDLMSProfileGeneric_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //CapturePeriod
    if (!CGXDLMSProfileGeneric_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //SortMethod
    if (!CGXDLMSProfileGeneric_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //SortObject
    if (!CGXDLMSProfileGeneric_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //EntriesInUse
    if (!CGXDLMSProfileGeneric_IsRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    //ProfileEntries
    if (!CGXDLMSProfileGeneric_IsRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
}

//Returns amount of attributes.
int CGXDLMSProfileGeneric_GetAttributeCount(CGXDLMSProfileGeneric* p)
{
    return 8;
}

//Returns amount of methods.
int CGXDLMSProfileGeneric_GetMethodCount(CGXDLMSProfileGeneric* p)
{
    return 2;
}

int CGXDLMSProfileGeneric_GetDataType(CGXDLMSProfileGeneric* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        *type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        *type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}


int CGXDLMSProfileGeneric_Invoke(CGXDLMSProfileGeneric* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1) {
        // Reset.
    	CGXDLMSProfileGeneric_Reset_1(p);
    }
    else if (e_index == 2) {
        // Capture.
    	CGXDLMSProfileGeneric_Capture_1(p, e->m_Server);
    }
    else
    {
        e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    }
    return 0;
}

/*
* Returns value of given attribute.
*/
int CGXDLMSProfileGeneric_GetValue(CGXDLMSProfileGeneric* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    else if (e_index == 2)
    {
        CGXByteBuffer tmp;
        CGXByteBuffer_1(&tmp);

        int ret = CGXDLMSProfileGeneric_GetProfileGenericData(p, settings, e, &tmp);
        e->m_ByteArray = true;

        CGXDLMSValueEventArg_SetValue_2(e, &tmp);

        CGXByteBuffer_d(&tmp);
        return ret;
    }
    else if (e_index == 3)
    {
        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        int ret = CGXDLMSProfileGeneric_GetColumns(p, &data);
        e->m_ByteArray = true;

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        return ret;
    }
    else if (e_index == 4)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_CapturePeriod);
    }
    else if (e_index == 5)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_SortMethod);
    }
    else if (e_index == 6)
    {
        e->m_ByteArray = true;
        static char empty[6] = { 0 };

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
        CGXByteBuffer_SetUInt8_1(&data, 4);
        if (p->m_SortObject == NULL)
        {
            //ClassID
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_UINT16);
            CGXByteBuffer_SetUInt16(&data, 0);
            //LN
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_OCTET_STRING);
            CGXByteBuffer_SetUInt8_1(&data, 6);
            CGXByteBuffer_Set_1(&data, empty, 6);
            //Selected Attribute Index
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_INT8);
            CGXByteBuffer_SetUInt8_1(&data, 0);
            //Selected Data Index
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_UINT16);
            CGXByteBuffer_SetUInt16(&data, 0);
        }
        else
        {
            int ret;

            CGXDLMSVariant ln;
            CGXDLMSVariant_1(&ln);

            //ClassID
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_UINT16);
            CGXByteBuffer_SetUInt16(&data, p->m_SortObject->m_ObjectType);
            //LN
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_OCTET_STRING);
            CGXByteBuffer_SetUInt8_1(&data, 6);
            if ((ret = CGXDLMSObject_GetLogicalName_1(p->m_SortObject, &ln)) != 0)
            {
                CGXDLMSVariant_d(&ln);
                CGXByteBuffer_d(&data);
                return ret;
            }
            CGXByteBuffer_Set_1(&data, ln.st.un.byteArr, 6);
            //Selected Attribute Index
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_INT8);
            CGXByteBuffer_SetUInt8_1(&data, p->m_SortObjectAttributeIndex);
            //Selected Data Index
            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_UINT16);
            CGXByteBuffer_SetUInt16(&data, p->m_SortObjectDataIndex);

            CGXDLMSVariant_d(&ln);
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
    }
    else if (e_index == 7)
    {
        CGXDLMSValueEventArg_SetValue_5(e, p->m_EntriesInUse);
    }
    else if (e_index == 8)
    {
        CGXDLMSValueEventArg_SetValue_5(e, p->m_ProfileEntries);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSProfileGeneric_SetValue(CGXDLMSProfileGeneric* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    int ret;
    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        if (Vector_size(&p->m_CaptureObjects) == 0)
        {
            //Read capture objects first.
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt != DLMS_DATA_TYPE_NONE)
        {
            Vector types; // std::vector<DLMS_DATA_TYPE>
            Vector_(&types, sizeof(DLMS_DATA_TYPE), NULL, NULL);

            DLMS_DATA_TYPE type;

            // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
            for (unsigned int i = Vector_begin(&p->m_CaptureObjects);
                    i != Vector_end(&p->m_CaptureObjects); ++i)
            {
                Pair* it = Vector_at(&p->m_CaptureObjects, i);

                CGXDLMSObject* it_first = *((CGXDLMSObject**) (it->first));
                CGXDLMSCaptureObject* it_second = *((CGXDLMSCaptureObject**) (it->second));

                if ((ret = it_first->GetUIDataType(it_first, it_second->m_AttributeIndex, &type)) != 0)
                {
                    Vector_d(&types);
                    return ret;
                }
                Vector_push_back(&types, &type);
            }

            // std::vector<CGXDLMSVariant >
            Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
            for (unsigned int irow = Vector_begin(vec); irow != Vector_end(vec); ++irow)
            {
                CGXDLMSVariant* row = Vector_at(vec, irow);

                if (Vector_size(&row->Arr) != Vector_size(&p->m_CaptureObjects))
                {
                    Vector_d(&types);
                    //Number of columns do not match.
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }

                CGXDLMSVariant data;
                CGXDLMSVariant_1(&data);

                for (unsigned int pos = 0; pos < Vector_size(&row->Arr); ++pos)
                {
                    DLMS_DATA_TYPE type = *((DLMS_DATA_TYPE*) Vector_at(&types, pos));

                    if (type != DLMS_DATA_TYPE_NONE
                     && ((CGXDLMSVariant*) Vector_at(&row->Arr, pos))->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
                    {
                        if ((ret = CGXDLMSClient_ChangeType_2((CGXDLMSVariant*) Vector_at(&row->Arr, pos), type, &data)) != 0)
                        {
                            CGXDLMSVariant_d(&data);
                            Vector_d(&types);
                            return ret;
                        }
                        CGXDLMSVariant_copy_1(Vector_at(&row->Arr, pos), &data);
                    }

                    //std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> item = p->m_CaptureObjects[pos];
                    Pair* p_item = Vector_at(&p->m_CaptureObjects, pos);

                    CGXDLMSObject* item_first = *((CGXDLMSObject**) (p_item->first));
                    CGXDLMSCaptureObject* item_second = *((CGXDLMSCaptureObject**) (p_item->second));

                    if (item_first->m_ObjectType == DLMS_OBJECT_TYPE_REGISTER
                     && item_second->m_AttributeIndex == 2)
                    {
                        double scaler = CGXDLMSRegister_GetScaler((CGXDLMSRegister*)item_first);
                        if (scaler != 1)
                        {
                            CGXDLMSVariant_copy_6(Vector_at(&row->Arr, pos),
                                                  CGXDLMSVariant_ToDouble(Vector_at(&row->Arr, pos)) * scaler);
                        }
                    }
                    else if (item_first->m_ObjectType == DLMS_OBJECT_TYPE_DEMAND_REGISTER
                         && (item_second->m_AttributeIndex == 2
                          || item_second->m_AttributeIndex == 3))
                    {
                        double scaler = CGXDLMSDemandRegister_GetScaler((CGXDLMSDemandRegister*)item_first);
                        if (scaler != 1)
                        {
                            CGXDLMSVariant_copy_6(Vector_at(&row->Arr, pos),
                                                  CGXDLMSVariant_ToDouble(Vector_at(&row->Arr, pos)) * scaler);
                        }
                    }
                }
                Vector_push_back(&p->m_Buffer, &row->Arr);

                CGXDLMSVariant_d(&data);
            }

            Vector_d(&types);
        }
        p->m_EntriesInUse = (unsigned long)Vector_size(&p->m_Buffer);
    }
    else if (e_index == 3)
    {
        Vector_clear(&p->m_CaptureObjects);
        Vector_clear(&p->m_Buffer);
        p->m_EntriesInUse = 0;
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            // std::vector<CGXDLMSVariant >
            Vector* vec = &(CGXDLMSValueEventArg_GetValue(e)->Arr);
            for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
            {
                CGXDLMSVariant* it = Vector_at(vec, i);

                if (Vector_size(&it->Arr) != 4)
                {
                    //Invalid structure format.
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 0));

                String ln;
                String_(&ln);

                GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&it->Arr, 1))->st.un.byteArr, &ln);

                CGXDLMSObject* pObj = CGXDLMSObjectCollection_FindByLN_1(CGXDLMSSettings_GetObjects(settings),
                                                                         type, &ln);

                if (pObj == NULL)
                {
                    pObj = CGXDLMSObjectFactory_CreateObject_2(type, ln);
                    Vector_push_back(&p->m_DynamicColumns, &pObj);
                }
                CGXDLMSProfileGeneric_AddCaptureObject(p, pObj,
                                                       CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 2)),
                                                       CGXDLMSVariant_ToInteger(Vector_at(&it->Arr, 3)));

                String_d(&ln);
            }
        }
    }
    else if (e_index == 4)
    {
        p->m_CapturePeriod = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 5)
    {
        p->m_SortMethod = (GX_SORT_METHOD)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 6)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_NONE)
        {
            p->m_SortObject = NULL;
        }
        else
        {
            if (Vector_size(&(CGXDLMSValueEventArg_GetValue(e)->Arr)) != 4)
            {
                //Invalid structure format.
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
            DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 0));

            String ln;
            String_(&ln);

            GXHelpers_GetLogicalName_1(((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 1))->st.un.byteArr, &ln);
            p->m_SortObjectAttributeIndex = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 2));
            p->m_SortObjectDataIndex = CGXDLMSVariant_ToInteger(Vector_at(&(CGXDLMSValueEventArg_GetValue(e)->Arr), 3));
            p->m_SortObject = CGXDLMSObjectCollection_FindByLN_1(CGXDLMSSettings_GetObjects(settings),
                                                                 type, &ln);
            if (p->m_SortObject == NULL)
            {
                p->m_SortObject = CGXDLMSObjectFactory_CreateObject_2(type, ln);
            }

            String_d(&ln);
        }
    }
    else if (e_index == 7)
    {
        p->m_EntriesInUse = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 8)
    {
        p->m_ProfileEntries = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
