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
#include "../include/errorcodes.h"
#include "../include/GXHelpers.h"
#include "../include/DLMSPort.h"

void dlmsVARIANT_2(dlmsVARIANT* p, dlmsVARIANT* src)
{
    p->st = src->st;
    p->dateTime = src->dateTime;
    p->size = src->size;

    String_copy_1(&p->strVal, &src->strVal);
    Vector_copy_1(&p->Arr, &src->Arr);
}

static int CGXDLMSVariant_Convert(CGXDLMSVariant* item, DLMS_DATA_TYPE type)
{
    if (item->st.vt == type)
    {
        return DLMS_ERROR_CODE_OK;
    }
    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, item);

    if (type == DLMS_DATA_TYPE_STRING)
    {
        CGXDLMSVariant_Clear(item);
        if (tmp.st.vt == DLMS_DATA_TYPE_ARRAY || tmp.st.vt == DLMS_DATA_TYPE_STRUCTURE)
        {
            bool empty = true;
            String sb;
            String_(&sb);

            String_append_1(&sb, "{");
            for (unsigned int it = Vector_begin(&(tmp.Arr));
                 it != Vector_end(&(tmp.Arr)); ++it)
            {
                if (!empty)
                {
                    String_append_1(&sb, ", ");
                }
                else
                {
                    empty = false;
                }

                String t_Str = CGXDLMSVariant_ToString(Vector_at(&(tmp.Arr), it));

                String_append_3(&sb, &t_Str);

                String_d(&t_Str);
            }
            String_append_1(&sb, "}");
            String_copy_1(&(item->strVal), &sb);
            item->st.vt = type;
            String_d(&sb);

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_BOOLEAN)
        {

            if (tmp.st.un.boolVal == 0)
            {
                String_copy_2(&(item->strVal), "False");
            }
            else
            {
                String_copy_2(&(item->strVal), "True");
            }
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        char buff[250];
        if (tmp.st.vt == DLMS_DATA_TYPE_INT32)
        {
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%ld", tmp.st.un.lVal);
#else
            DLMSPort_sprintf(buff, "%ld", tmp.st.un.lVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_UINT32)
        {
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%lu", tmp.st.un.ulVal);
#else
            DLMSPort_sprintf(buff, "%lu", tmp.st.un.ulVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_INT8)
        {
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%d", tmp.st.un.cVal);
#else
            DLMSPort_sprintf(buff, "%d", tmp.st.un.cVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_INT16)
        {
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%d", tmp.st.un.iVal);
#else
            DLMSPort_sprintf(buff, "%d", tmp.st.un.iVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_UINT8)
        {
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%d", tmp.st.un.bVal);
#else
            DLMSPort_sprintf(buff, "%d", tmp.st.un.bVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_UINT16)
        {
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%d", tmp.st.un.uiVal);
#else
            DLMSPort_sprintf(buff, "%d", tmp.st.un.uiVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_INT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%lld", tmp.st.un.llVal);
#else
            DLMSPort_sprintf(buff, "%I64d", tmp.st.un.llVal);
#endif

#else
            DLMSPort_sprintf(buff, "%lld", tmp.st.un.llVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_UINT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%llu", tmp.st.un.ullVal);
#else
            DLMSPort_sprintf(buff, "%I64u", tmp.st.un.llVal);
#endif
#else
            DLMSPort_sprintf(buff, "%llu", tmp.st.un.ullVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_ENUM)
        {
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 250, "%d", tmp.st.un.bVal);
#else
            DLMSPort_sprintf(buff, "%d", tmp.st.un.bVal);
#endif
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_FLOAT32)
        {
            DLMSPort_snprintf(buff, 250, "%f", tmp.st.un.fltVal);
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_FLOAT64)
        {
            DLMSPort_snprintf(buff, 250, "%lf", tmp.st.un.dblVal);
            String_copy_2(&(item->strVal), buff);
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_BIT_STRING)
        {
            //TODO:
            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_DATETIME)
        {
            String t_Str = CGXDateTime_ToString(&(tmp.dateTime));

            String_copy_1(&(item->strVal), &t_Str);
            item->st.vt = type;

            String_d(&t_Str);

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            unsigned char ch;
            char buff[4];
            for (int pos = 0; pos != tmp.size; ++pos)
            {
                if (pos != 0)
                {
                    String_append_1(&(item->strVal), ".");
                }
                ch = tmp.st.un.byteArr[pos];
#if _MSC_VER > 1000
                DLMSPort_sprintf_s(buff, 4, "%d", ch);
#else
                DLMSPort_sprintf(buff, "%d", ch);
#endif
                String_append_1(&(item->strVal), buff);
            }
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
    }
    if (item->st.vt == DLMS_DATA_TYPE_STRING)
    {
        CGXDLMSVariant_Clear(item);
        if (type == DLMS_DATA_TYPE_BOOLEAN)
        {
            item->st.un.boolVal = String_compare(&(tmp.strVal), "False") == 0 ? 0 : 1;
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT32)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%ld", &item->st.un.lVal);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%ld", &item->st.un.lVal);
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
    }
        if (type == DLMS_DATA_TYPE_UINT32)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%lu", &item->st.un.ulVal);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%lu", &item->st.un.ulVal);
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT8)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%c", &item->st.un.cVal, 1);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%c", &item->st.un.cVal);
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT16)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%hd", &item->st.un.iVal);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%hd", &item->st.un.iVal);
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_UINT8)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%hhu", &item->st.un.bVal);
#else
            int value;
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%d", &value);
            item->st.un.bVal = value & 0xFF;
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_UINT16)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%hu", &item->st.un.uiVal);
#else
            int value;
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%d", &value);
            item->st.un.uiVal = value & 0xFFFF;
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%lld", &item->st.un.llVal);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%I64d", &item->st.un.llVal);
#endif
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%lld", &item->st.un.llVal);
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_UINT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%llu", &item->st.un.ullVal);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%I64u", &item->st.un.ullVal);
#endif
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%llu", &item->st.un.ullVal);
#endif

#if _MSC_VER > 1000
#else
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_ENUM)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%hhu", &item->st.un.bVal);
#else
            int value;
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%d", &value);
            item->st.un.bVal = value & 0xFF;
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_FLOAT32)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%f", &item->st.un.fltVal);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%f", &item->st.un.fltVal);
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_FLOAT64)
        {
#if _MSC_VER > 1000
            DLMSPort_sscanf_s(String_c_str(&(tmp.strVal)), "%lf", &item->st.un.dblVal);
#else
            DLMSPort_sscanf(String_c_str(&(tmp.strVal)), "%lf", &item->st.un.dblVal);
#endif
            item->st.vt = type;

            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXByteBuffer tmp2;
            CGXByteBuffer_1(&tmp2);

            GXHelpers_HexToBytes(tmp.strVal, &tmp2);
            CGXDLMSVariant_Add_1(item, tmp2.m_Data, tmp2.m_Size);
            item->st.vt = type;

            CGXByteBuffer_d(&tmp2);
            CGXDLMSVariant_d(&tmp);
            return DLMS_ERROR_CODE_OK;
        }

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
    }
    int fromSize = CGXDLMSVariant_GetSize_1(&tmp);
    int toSize = CGXDLMSVariant_GetSize_2(type);

    //If we try to change bigger valut to smaller check that value is not too big.
    //Example Int16 to Int8.
    if (fromSize > toSize)
    {
        unsigned char* pValue = &(tmp.st.un.bVal);
        for (int pos = toSize; pos != fromSize; ++pos)
        {
            if (pValue[pos] != 0)
            {
                CGXDLMSVariant_d(&tmp);
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
        }
    }
    CGXDLMSVariant_Clear(item);
    if (fromSize > toSize)
    {
        memcpy(&(item->st.un.bVal), &(tmp.st.un.bVal), toSize);
    }
    else
    {
        memset(&(item->st.un.bVal), 0, toSize);
        memcpy(&(item->st.un.bVal), &(tmp.st.un.bVal), fromSize);
    }
    item->st.vt = type;

    CGXDLMSVariant_d(&tmp);
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSVariant_Clear(CGXDLMSVariant* p)
{
    Vector_clear(&(p->Arr));
    String_clear(&(p->strVal));
    if (p->st.vt == DLMS_DATA_TYPE_OCTET_STRING && p->st.un.byteArr != NULL)
    {
        if (p->size == 0)
        {
            assert(p->size != 0);
        }
        DLMSPort_free(p->st.un.byteArr);
        p->st.un.byteArr = NULL;
        p->size = 0;
    }
    p->st.vt = DLMS_DATA_TYPE_NONE;
    p->st.un.byteArr = NULL;
    p->size = 0;
}

static void CGXDLMSVariant__(CGXDLMSVariant* p)
{
    CGXDateTime_1(&p->dateTime);
    String_(&p->strVal);
//    WString strUtfVal;
    Vector_(&p->Arr, sizeof(CGXDLMSVariant), CGXDLMSVariant_v_c, CGXDLMSVariant_v_d); // std::vector<CGXDLMSVariant>
}

void CGXDLMSVariant_1(CGXDLMSVariant* p)
{
    CGXDLMSVariant__(p);

    p->size = 0;
    p->st.un.byteArr = NULL;
    CGXDLMSVariant_Clear(p);
}

void CGXDLMSVariant_d(CGXDLMSVariant* p)
{
    CGXDLMSVariant_Clear(p);

//    WString strUtfVal;
}
void CGXDLMSVariant_17(CGXDLMSVariant* p, CGXDLMSVariant* value)
{
    CGXDLMSVariant__(p);

    p->st.un.byteArr = NULL;
    p->st.vt = value->st.vt;
    if (p->st.vt == DLMS_DATA_TYPE_NONE)
    {
        return;
    }
    else if (p->st.vt == DLMS_DATA_TYPE_STRING ||
        p->st.vt == DLMS_DATA_TYPE_BIT_STRING)
    {
        String_append_3(&(p->strVal), &(value->strVal));
    }
    else if (p->st.vt == DLMS_DATA_TYPE_DATETIME ||
            p->st.vt == DLMS_DATA_TYPE_DATE ||
        p->st.vt == DLMS_DATA_TYPE_TIME)
    {
        p->dateTime = value->dateTime;
    }
    else if (p->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        p->size = value->size;
        if (p->size != 0)
        {
            p->st.un.byteArr = (unsigned char*) DLMSPort_malloc(p->size);
            memcpy(p->st.un.byteArr, value->st.un.byteArr, p->size);
        }
    }
    else if (p->st.vt == DLMS_DATA_TYPE_ARRAY || p->st.vt == DLMS_DATA_TYPE_STRUCTURE)
    {
        for (unsigned int it = Vector_begin(&(value->Arr)); it != Vector_end(&(value->Arr)); ++it)
        {
            Vector_push_back(&(p->Arr), Vector_at(&(value->Arr), it));
        }
    }
    else
    {
        int size = CGXDLMSVariant_GetSize_1(value);
        if (size > 0)
        {
            memcpy(&(p->st.un.bVal), &(value->st.un.bVal), size);
        }
        else
        {
            assert(0);
        }
    }
}

void CGXDLMSVariant_3(CGXDLMSVariant* p, float value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_FLOAT32;
    p->st.un.fltVal = value;
}

void CGXDLMSVariant_4(CGXDLMSVariant* p, double value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_FLOAT64;
    p->st.un.dblVal = value;
}


void CGXDLMSVariant_5(CGXDLMSVariant* p, unsigned long long value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_UINT64;
    p->st.un.ullVal = value;
}

void CGXDLMSVariant_6(CGXDLMSVariant* p, long long value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_INT64;
    p->st.un.llVal = value;
}

void CGXDLMSVariant_7(CGXDLMSVariant* p, bool value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_BOOLEAN;
    p->st.un.boolVal = value;
}


void CGXDLMSVariant_8(CGXDLMSVariant* p, char value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_INT8;
    p->st.un.cVal = value;
}

void CGXDLMSVariant_9(CGXDLMSVariant* p, short value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_INT16;
    p->st.un.iVal = value;
}


void CGXDLMSVariant_10(CGXDLMSVariant* p, int value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_INT32;
    p->st.un.lVal = value;
}

void CGXDLMSVariant_11(CGXDLMSVariant* p, long value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_INT32;
    p->st.un.lVal = value;
}

void CGXDLMSVariant_12(CGXDLMSVariant* p, struct tm* value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_DATETIME;
    p->dateTime.m_Value = *value;
}

void CGXDLMSVariant_23(CGXDLMSVariant* p, CGXByteBuffer* value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    p->size = (unsigned short) value->m_Size;
    if (p->size != 0)
    {
        p->st.un.byteArr = (unsigned char*)DLMSPort_malloc(p->size);
        memcpy(p->st.un.byteArr, value->m_Data, p->size);
    }
    else
    {
        p->st.un.byteArr = NULL;
    }
}

void CGXDLMSVariant_14(CGXDLMSVariant* p, CGXDate* value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_DATE;
    p->dateTime = *((CGXDateTime*) value);
}

void CGXDLMSVariant_15(CGXDLMSVariant* p, CGXTime* value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_TIME;
    p->dateTime = *((CGXDateTime*) value);
}

void CGXDLMSVariant_16(CGXDLMSVariant* p, CGXDateTime* value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_DATETIME;
    p->dateTime = *value;
}

void CGXDLMSVariant_19(CGXDLMSVariant* p, unsigned char value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_UINT8;
    p->st.un.bVal = value;
}

void CGXDLMSVariant_20(CGXDLMSVariant* p, unsigned short value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_UINT16;
    p->st.un.uiVal = value;
}

void CGXDLMSVariant_21(CGXDLMSVariant* p, unsigned long value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_UINT32;
    p->st.un.ulVal = value;
}

void CGXDLMSVariant_22(CGXDLMSVariant* p, String value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_STRING;
    String_copy_1(&(p->strVal), &value);
}

void CGXDLMSVariant_13(CGXDLMSVariant* p, unsigned char* value, int count)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    p->size = count;
    if (p->size != 0)
    {
        p->st.un.byteArr = (unsigned char*)DLMSPort_malloc(p->size);
        memcpy(p->st.un.byteArr, value, p->size);
    }
    else
    {
        p->st.un.byteArr = NULL;
    }
}

void CGXDLMSVariant_2(CGXDLMSVariant* p, const CGXDLMSVariant* value)
{
	CGXDLMSVariant__(p);

    //If Octect String, copy byte buffer.
    if (value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        p->st.vt = value->st.vt;
        p->size = value->size;
        if (p->size != 0)
        {
            p->st.un.byteArr = (unsigned char*)DLMSPort_malloc(p->size);
            memcpy(p->st.un.byteArr, value->st.un.byteArr, p->size);
        }
        else
        {
            p->st.un.byteArr = NULL;
        }
    }
    else
    {
        dlmsVARIANT_2((dlmsVARIANT*) p, (dlmsVARIANT*) value);
    }
}

void CGXDLMSVariant_copy_1(CGXDLMSVariant* p, const CGXDLMSVariant* value)
{
    CGXDLMSVariant_Clear(p);
    //If Octect String, copy byte buffer.
    if (value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        p->st.vt = value->st.vt;
        p->size = value->size;
        if (p->size != 0)
        {
            p->st.un.byteArr = (unsigned char*)DLMSPort_malloc(p->size);
            memcpy(p->st.un.byteArr, value->st.un.byteArr, p->size);
        }
    }
    else
    {
        dlmsVARIANT_2((dlmsVARIANT*) p, (dlmsVARIANT*) value);
    }
}

void CGXDLMSVariant_copy_4(CGXDLMSVariant* p, CGXByteBuffer* value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    p->size = (unsigned short) value->m_Size;
    if (p->size != 0)
    {
        p->st.un.byteArr = (unsigned char*)DLMSPort_malloc(p->size);
        memcpy(p->st.un.byteArr, value->m_Data, p->size);
    }
}

void CGXDLMSVariant_24(CGXDLMSVariant* p, const char* value)
{
    CGXDLMSVariant__(p);

    p->st.vt = DLMS_DATA_TYPE_STRING;
    String_append_1(&(p->strVal), value);
}

void CGXDLMSVariant_18(CGXDLMSVariant* p, unsigned char* pValue, int count, DLMS_DATA_TYPE type)
{
    CGXDLMSVariant__(p);

    assert(count > -1);
    p->st.un.byteArr = NULL;
    p->size = count;
    if (p->size != 0)
    {
        p->st.un.byteArr = (unsigned char*)DLMSPort_malloc(count);
        memcpy(p->st.un.byteArr, pValue, count);
    }
    p->st.vt = type;
}

void CGXDLMSVariant_copy_2(CGXDLMSVariant* p, String value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_STRING;
    String_append_3(&(p->strVal), &value);
}

void CGXDLMSVariant_copy_3(CGXDLMSVariant* p, const char* value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_STRING;
    String_append_1(&(p->strVal), value);
}

void CGXDLMSVariant_copy_5(CGXDLMSVariant* p, float value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_FLOAT32;
    p->st.un.fltVal = value;
}

void CGXDLMSVariant_copy_6(CGXDLMSVariant* p, double value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_FLOAT64;
    p->st.un.dblVal = value;
}

void CGXDLMSVariant_copy_7(CGXDLMSVariant* p, unsigned long long value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_UINT64;
    p->st.un.ullVal = value;
}

void CGXDLMSVariant_copy_8(CGXDLMSVariant* p, long long value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_INT64;
    p->st.un.llVal = value;
}

void CGXDLMSVariant_copy_9(CGXDLMSVariant* p, const bool value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_BOOLEAN;
    p->st.un.boolVal = value;
}


void CGXDLMSVariant_copy_10(CGXDLMSVariant* p, char value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_INT8;
    p->st.un.cVal = value;
}

void CGXDLMSVariant_copy_11(CGXDLMSVariant* p, short value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_INT16;
    p->st.un.iVal = value;
}

void CGXDLMSVariant_copy_12(CGXDLMSVariant* p, int value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_INT32;
    p->st.un.lVal = value;
}

void CGXDLMSVariant_copy_13(CGXDLMSVariant* p, long value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_INT32;
    p->st.un.lVal = value;
}


void CGXDLMSVariant_copy_14(CGXDLMSVariant* p, unsigned char value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_UINT8;
    p->st.un.bVal = value;
}

void CGXDLMSVariant_copy_15(CGXDLMSVariant* p, unsigned short value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_UINT16;
    p->st.un.uiVal = value;
}

void CGXDLMSVariant_copy_17(CGXDLMSVariant* p, unsigned long value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_UINT32;
    p->st.un.ulVal = value;
}

void CGXDLMSVariant_copy_18(CGXDLMSVariant* p, struct tm value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_DATETIME;
    p->dateTime.m_Value = value;
}

void CGXDLMSVariant_copy_19(CGXDLMSVariant* p, CGXDate* value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_DATE;
    p->dateTime = *((CGXDateTime*) value);
}

void CGXDLMSVariant_copy_20(CGXDLMSVariant* p, CGXTime* value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_TIME;
    p->dateTime = *((CGXDateTime*) value);
}

void CGXDLMSVariant_copy_21(CGXDLMSVariant* p, CGXDateTime* value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_DATETIME;
    p->dateTime = *value;
}

void CGXDLMSVariant_copy_16(CGXDLMSVariant* p, unsigned int value)
{
    CGXDLMSVariant_Clear(p);
    p->st.vt = DLMS_DATA_TYPE_UINT32;
    p->st.un.ulVal = value;
}

void CGXDLMSVariant_Add_1(CGXDLMSVariant* p, const unsigned char* pValue, int count)
{
    p->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    if (count != 0)
    {
        p->st.un.byteArr = (unsigned char*) DLMSPort_realloc(p->st.un.byteArr, p->size + count);
        memcpy(p->st.un.byteArr + p->size, pValue, count);
        p->size += count;
    }
}

void CGXDLMSVariant_Add_2(CGXDLMSVariant* p, const char* pValue, int count)
{
    p->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    if (count != 0)
    {
        p->st.un.byteArr = (unsigned char*) DLMSPort_realloc(p->st.un.byteArr, p->size + count);
        memcpy(p->st.un.byteArr + p->size, pValue, count);
        p->size += count;
    }
}

void CGXDLMSVariant_Add_3(CGXDLMSVariant* p, String value)
{
    p->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    if (String_size(&value) != 0)
    {
        p->st.un.byteArr = (unsigned char*) DLMSPort_realloc(p->st.un.byteArr, p->size + String_size(&value));
        memcpy(p->st.un.byteArr + p->size, String_c_str(&value), String_size(&value));
        p->size += (unsigned short)String_size(&value);
    }
}

bool CGXDLMSVariant_Equals(CGXDLMSVariant* p, CGXDLMSVariant* item)
{
    if (p->st.vt != item->st.vt)
    {
        return false;
    }
    int size = CGXDLMSVariant_GetSize_1(p);
    if (size == -1 || size != CGXDLMSVariant_GetSize_1(item))
    {
        return false;
    }
    if (size != 0)
    {
        return memcmp(&(p->st.un.bVal), &(item->st.un.bVal), size) == 0;
    }
    return true;
}

int CGXDLMSVariant_ChangeType(CGXDLMSVariant* p, DLMS_DATA_TYPE newType)
{
    if (newType == p->st.vt)
    {
        return DLMS_ERROR_CODE_OK;
    }

    if (newType == DLMS_DATA_TYPE_NONE)
    {
        CGXDLMSVariant_Clear(p);
        return DLMS_ERROR_CODE_OK;
    }
    if (p->st.vt == DLMS_DATA_TYPE_ARRAY && newType == DLMS_DATA_TYPE_OCTET_STRING)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (p->st.vt == DLMS_DATA_TYPE_STRING)
    {
        return CGXDLMSVariant_Convert(p, newType);
    }
    switch (newType)
    {
    case DLMS_DATA_TYPE_STRING:
    case DLMS_DATA_TYPE_BOOLEAN:
    case DLMS_DATA_TYPE_INT32:
    case DLMS_DATA_TYPE_UINT32:
    case DLMS_DATA_TYPE_INT8:
    case DLMS_DATA_TYPE_INT16:
    case DLMS_DATA_TYPE_UINT8:
    case DLMS_DATA_TYPE_UINT16:
    case DLMS_DATA_TYPE_INT64:
    case DLMS_DATA_TYPE_UINT64:
    case DLMS_DATA_TYPE_ENUM:
    case DLMS_DATA_TYPE_FLOAT32:
    case DLMS_DATA_TYPE_FLOAT64:
        return CGXDLMSVariant_Convert(p, newType);
        break;
    default:
        //Handled later.
        break;
    }
//    CGXDLMSVariant tmp;
//    CGXDLMSVariant_2(&tmp, p);

    switch (p->st.vt)
    {
    case DLMS_DATA_TYPE_BOOLEAN:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    case DLMS_DATA_TYPE_BIT_STRING:
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    case DLMS_DATA_TYPE_INT32:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT32:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_OCTET_STRING:
        switch (newType)
        {
        case DLMS_DATA_TYPE_DATETIME:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        case DLMS_DATA_TYPE_DATE:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        case DLMS_DATA_TYPE_TIME:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
        switch (newType)
        {
        case DLMS_DATA_TYPE_INT32:
            break;
        case DLMS_DATA_TYPE_UINT32:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_INT8:
            break;
        case DLMS_DATA_TYPE_INT16:
            break;
        case DLMS_DATA_TYPE_UINT8:
            break;
        case DLMS_DATA_TYPE_UINT16:
            break;
        case DLMS_DATA_TYPE_INT64:
            break;
        case DLMS_DATA_TYPE_UINT64:
            break;
        case DLMS_DATA_TYPE_ENUM:
            break;
        case DLMS_DATA_TYPE_FLOAT32:
            break;
        case DLMS_DATA_TYPE_FLOAT64:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_INT8:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_INT16:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT8:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT16:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_INT64:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT64:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_ENUM:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_FLOAT32:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_FLOAT64:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_DATETIME:
        switch (newType)
        {
        case DLMS_DATA_TYPE_OCTET_STRING:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_DATE:
            break;
        case DLMS_DATA_TYPE_TIME:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_DATE:
        switch (newType)
        {
        case DLMS_DATA_TYPE_OCTET_STRING:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_DATETIME:
            break;
        case DLMS_DATA_TYPE_DATE:
            break;
        case DLMS_DATA_TYPE_TIME:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_TIME:
        switch (newType)
        {
        case DLMS_DATA_TYPE_OCTET_STRING:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_DATETIME:
            break;
        case DLMS_DATA_TYPE_DATE:
            break;
        case DLMS_DATA_TYPE_TIME:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_ARRAY:
    case DLMS_DATA_TYPE_STRUCTURE:
    case DLMS_DATA_TYPE_COMPACT_ARRAY:
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

//Get size in bytes.
int CGXDLMSVariant_GetSize_1(CGXDLMSVariant* p)
{
    if (p->st.vt == DLMS_DATA_TYPE_STRING ||
        p->st.vt == DLMS_DATA_TYPE_BIT_STRING)
    {
        return (int)String_size(&(p->strVal));
    }
    if (p->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        return p->size;
    }
    return CGXDLMSVariant_GetSize_2(p->st.vt);
}

//Get size in bytes.
int CGXDLMSVariant_GetSize_2(DLMS_DATA_TYPE vt)
{
    int nSize = -1;
    switch (vt)
    {
    case DLMS_DATA_TYPE_NONE:
        nSize = 0;
        break;
    case DLMS_DATA_TYPE_BOOLEAN:
    case DLMS_DATA_TYPE_INT8:
    case DLMS_DATA_TYPE_UINT8:
    case DLMS_DATA_TYPE_ENUM:
        nSize = 1;
        break;
    case DLMS_DATA_TYPE_INT16:
    case DLMS_DATA_TYPE_UINT16:
        nSize = 2;
        break;
    case DLMS_DATA_TYPE_INT32:
    case DLMS_DATA_TYPE_UINT32:
    case DLMS_DATA_TYPE_FLOAT32:
        nSize = 4;
        break;
    case DLMS_DATA_TYPE_INT64:
    case DLMS_DATA_TYPE_UINT64:
    case DLMS_DATA_TYPE_FLOAT64:
        nSize = 8;
        break;
    case DLMS_DATA_TYPE_BIT_STRING:
        break;
    case DLMS_DATA_TYPE_OCTET_STRING:
        break;
    case DLMS_DATA_TYPE_STRING:
    case DLMS_DATA_TYPE_STRING_UTF8:
        nSize = -1;
        break;
    case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
        break;
    case DLMS_DATA_TYPE_DATETIME:
        nSize = 12;
        break;
    case DLMS_DATA_TYPE_DATE:
        break;
    case DLMS_DATA_TYPE_TIME:
        break;
    case DLMS_DATA_TYPE_ARRAY:
        break;
    case DLMS_DATA_TYPE_STRUCTURE:
        break;
    case DLMS_DATA_TYPE_COMPACT_ARRAY:
        break;
    }
    return nSize;
}

String CGXDLMSVariant_ToString(CGXDLMSVariant* p)
{
    String sb;
    String_(&sb);

    CGXDLMSVariant tmp;
    CGXDLMSVariant_2(&tmp, p);

    CGXDLMSVariant_ChangeType(&tmp, DLMS_DATA_TYPE_STRING);
    if (String_length(&(tmp.strVal)) == 0)
    {
        String_3(&sb, "");
        CGXDLMSVariant_d(&tmp);
        return sb; // = copy cons + des
    }

    String_2(&sb, &(tmp.strVal));

    CGXDLMSVariant_d(&tmp);
    return sb; // = copy cons + des
}

int CGXDLMSVariant_ToInteger(CGXDLMSVariant* p)
{
    if (p->st.vt == DLMS_DATA_TYPE_NONE)
    {
        return 0;
    }

    if (p->st.vt == DLMS_DATA_TYPE_BOOLEAN)
    {
        return p->st.un.boolVal ? 1 : 0;
    }
    if (p->st.vt == DLMS_DATA_TYPE_INT32)
    {
        return p->st.un.lVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT32)
    {
        return p->st.un.ulVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_BINARY_CODED_DESIMAL)
    {
        assert(0);
    }
    if (p->st.vt == DLMS_DATA_TYPE_STRING_UTF8)
    {
        //TODO:
        assert(0);
    }
    if (p->st.vt == DLMS_DATA_TYPE_INT8)
    {
        return p->st.un.cVal;
    }

    if (p->st.vt == DLMS_DATA_TYPE_INT16)
    {
        return p->st.un.iVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT8)
    {
        return p->st.un.bVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT16)
    {
        return p->st.un.uiVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_INT64)
    {
        //TODO:
        assert(0);
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT64)
    {
        //TODO:
        assert(0);
    }
    if (p->st.vt == DLMS_DATA_TYPE_ENUM)
    {
        return p->st.un.bVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_FLOAT32)
    {
        return (int)(p->st.un.fltVal);
    }
    if (p->st.vt == DLMS_DATA_TYPE_FLOAT64)
    {
        return (int)(p->st.un.dblVal);
    }
    if (p->st.vt == DLMS_DATA_TYPE_STRING)
    {
        int val = 0;
#if _MSC_VER > 1000
        if (DLMSPort_sscanf_s(String_c_str(&(p->strVal)), "%d", &val) == -1)
#else
        if (DLMSPort_sscanf(String_c_str(&(p->strVal)), "%d", &val) == -1)
#endif
        {
            assert(0);
        }
        return val;
    }
    assert(0);
    return 0;
}

double CGXDLMSVariant_ToDouble(CGXDLMSVariant* p)
{
    if (p->st.vt == DLMS_DATA_TYPE_NONE)
    {
        return 0;
    }

    if (p->st.vt == DLMS_DATA_TYPE_BOOLEAN)
    {
        return p->st.un.boolVal ? 1 : 0;
    }
    if (p->st.vt == DLMS_DATA_TYPE_INT32)
    {
        return p->st.un.lVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT32)
    {
        return p->st.un.ulVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_BINARY_CODED_DESIMAL)
    {
        assert(0);
    }
    if (p->st.vt == DLMS_DATA_TYPE_STRING_UTF8)
    {
        assert(0);
    }
    if (p->st.vt == DLMS_DATA_TYPE_INT8)
    {
        return p->st.un.cVal;
    }

    if (p->st.vt == DLMS_DATA_TYPE_INT16)
    {
        return p->st.un.iVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT8)
    {
        return p->st.un.bVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT16)
    {
        return p->st.un.uiVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_INT64)
    {
        return (double)(p->st.un.llVal);
    }
    if (p->st.vt == DLMS_DATA_TYPE_UINT64)
    {
        return (double)(p->st.un.ullVal);
    }
    if (p->st.vt == DLMS_DATA_TYPE_ENUM)
    {
        return p->st.un.bVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_FLOAT32)
    {
        return p->st.un.fltVal;
    }
    if (p->st.vt == DLMS_DATA_TYPE_FLOAT64)
    {
        return p->st.un.dblVal;
    }
    assert(0);
    return 0;
}

/**
* Add new object to the byte buffer.
*
* @param value
*            Value to add.
*/
int CGXDLMSVariant_GetBytes(CGXDLMSVariant* p, CGXByteBuffer* value)
{
    if (p->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        CGXByteBuffer_Set_1(value, p->st.un.byteArr, p->size);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_UINT8)
    {
        CGXByteBuffer_SetUInt8_1(value, p->st.un.cVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_UINT16)
    {
        CGXByteBuffer_SetUInt16(value, p->st.un.uiVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_UINT32)
    {
        CGXByteBuffer_SetUInt32(value, p->st.un.ulVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_UINT64)
    {
        CGXByteBuffer_SetUInt64(value, p->st.un.ullVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_INT8)
    {
        CGXByteBuffer_SetInt8(value, p->st.un.bVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_INT16)
    {
        CGXByteBuffer_SetInt16(value, p->st.un.iVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_INT32)
    {
        CGXByteBuffer_SetInt32(value, p->st.un.lVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_INT64)
    {
        CGXByteBuffer_SetInt64(value, p->st.un.llVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_STRING)
    {
        CGXByteBuffer_AddString_2(value, String_c_str(&(p->strVal)));
    }
    else if (p->st.vt == DLMS_DATA_TYPE_FLOAT32)
    {
        CGXByteBuffer_SetFloat(value, p->st.un.fltVal);
    }
    else if (p->st.vt == DLMS_DATA_TYPE_FLOAT64)
    {
        CGXByteBuffer_SetDouble(value, p->st.un.dblVal);
    }
    else
    {
        //Invalid object type.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}

void CGXDLMSVariant_v_c(void* p1, const void* p2)
{
    CGXDLMSVariant_2((CGXDLMSVariant*) p1, (CGXDLMSVariant*) p2);
}

void CGXDLMSVariant_v_d(void* p)
{
    CGXDLMSVariant_d((CGXDLMSVariant*) p);
}
