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

#include "../include/GXDLMSObject.h"
#include "../include/GXHelpers.h"
#include "../include/GXDLMSAttribute.h"

// Init function pointer
static void CGXDLMSObject__(CGXDLMSObject* p)
{
    p->GetAttributeCount = CGXDLMSObject_GetAttributeCount;
    p->GetMethodCount = CGXDLMSObject_GetMethodCount;
    p->GetValue = CGXDLMSObject_GetValue;
    p->SetValue = CGXDLMSObject_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSObject_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSObject_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSObject_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSObject_GetAttributeIndexToRead;

    CGXAttributeCollection_(&p->m_Attributes);
    CGXAttributeCollection_(&p->m_MethodAttributes);
    String_(&p->m_Description);
    // // std::map<int, time_t> m_ReadTimes;
    Map_(&p->m_ReadTimes, sizeof(int), sizeof(time_t),
         NULL, NULL, NULL, NULL);
}

//SN Constructor.
void CGXDLMSObject_3(CGXDLMSObject* p, DLMS_OBJECT_TYPE type, String* ln, unsigned short sn)
{
    CGXDLMSObject__(p);
    CGXDLMSObject_Initialize(p, sn, type, 0, NULL);
    GXHelpers_SetLogicalName_2(String_c_str(ln), p->m_LN);
}

//LN Constructor.
void CGXDLMSObject_4(CGXDLMSObject* p, DLMS_OBJECT_TYPE type, String* ln)
{
    CGXDLMSObject__(p);
    CGXDLMSObject_Initialize(p, 0, type, 0, NULL);
    GXHelpers_SetLogicalName_2(String_c_str(ln), p->m_LN);
}

void CGXDLMSObject_1(CGXDLMSObject* p)
{
    CGXDLMSObject__(p);
    CGXDLMSObject_Initialize(p, 0, DLMS_OBJECT_TYPE_NONE, 0, NULL);
}

void CGXDLMSObject_5(CGXDLMSObject* p, short sn, unsigned short class_id, unsigned char version, CGXByteBuffer* ln)
{
    CGXDLMSObject__(p);
    CGXDLMSObject_Initialize(p, sn, class_id, version, ln);
}

void CGXDLMSObject_2(CGXDLMSObject* p, DLMS_OBJECT_TYPE type)
{
    CGXDLMSObject__(p);
    CGXDLMSObject_Initialize(p, 0, type, 0, NULL);
}

int CGXDLMSObject_GetLogicalName_1(CGXDLMSObject * target, CGXDLMSVariant* value)
{
    CGXDLMSVariant_Add_1(value, target->m_LN, 6);
    value->st.vt = DLMS_DATA_TYPE_OCTET_STRING;
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSObject_SetLogicalName(CGXDLMSObject * target, CGXDLMSVariant* value)
{
    if (value->st.vt != DLMS_DATA_TYPE_OCTET_STRING || CGXDLMSVariant_GetSize_1(value) != 6)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    memcpy(target->m_LN, value->st.un.byteArr, 6);
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSObject_Initialize(CGXDLMSObject* p, short sn, unsigned short class_id, unsigned char version, CGXByteBuffer* ln)
{
    p->m_AttributeIndex = 0;
    p->m_DataIndex = 0;
    p->m_SN = sn;
    p->m_ObjectType = (DLMS_OBJECT_TYPE)class_id;
    p->m_Version = version;
    if (ln == NULL)
    {
        memset(p->m_LN, 0, 6);
    }
    else
    {
        int cnt = ln->m_Size;
        if (cnt == 6)
        {
        	CGXByteBuffer_Get(ln, p->m_LN, 6);
        }
        else
        {
            assert(false);
        }
    }
    //Attribute 1 is always Logical name.
    CGXDLMSAttribute t_attribute;
    CGXDLMSAttribute_(&t_attribute, 1, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_OCTET_STRING, DLMS_ACCESS_MODE_READ, 1);

    CGXAttributeCollection_push_back(&(p->m_Attributes), &t_attribute);
}

void CGXDLMSObject_d(CGXDLMSObject* p)
{
    CGXAttributeCollection_clear(&(p->m_Attributes));
    CGXAttributeCollection_clear(&(p->m_MethodAttributes));
    String_d(&p->m_Description);
    Map_d(&p->m_ReadTimes);
}

//CGXDLMSVariant CGXDLMSObject_GetName(CGXDLMSObject* p)
//{
//    if (p->m_SN != 0)
//    {
//        return CGXDLMSVariant(m_SN);
//    }
//    CGXDLMSVariant ln;
//    GXHelpers_GetLogicalName_1(p->m_LN, ln.strVal);
//    ln.vt = DLMS_DATA_TYPE_STRING;
//    return ln;
//}

CGXDLMSVariant CGXDLMSObject_GetName(CGXDLMSObject* p)
{
    CGXDLMSVariant out;

    if (p->m_SN != 0)
    {
        CGXDLMSVariant t_Variant;
        CGXDLMSVariant_20(&t_Variant, p->m_SN);

        CGXDLMSVariant_2(&out, &t_Variant);

        CGXDLMSVariant_d(&t_Variant);
        return out; // = copy cons + des
    }
    CGXDLMSVariant ln;
    CGXDLMSVariant_1(&ln);

    GXHelpers_GetLogicalName_1(p->m_LN, &(ln.strVal));
    ln.st.vt = DLMS_DATA_TYPE_STRING;

    CGXDLMSVariant_2(&out, &ln);

    CGXDLMSVariant_d(&ln);
    return out; // = copy cons + des
}

int CGXDLMSObject_SetName(CGXDLMSObject* p, CGXDLMSVariant* value)
{
    if (value->st.vt == DLMS_DATA_TYPE_UINT16)
    {
        p->m_SN = value->st.un.uiVal;
        return DLMS_ERROR_CODE_OK;
    }
    if (value->st.vt == DLMS_DATA_TYPE_STRING)
    {
        GXHelpers_SetLogicalName_2(String_c_str(&(value->strVal)), p->m_LN);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSObject_GetDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE* type)
{
    if (index < 1)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
        if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
            *type = ((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Type;
            return DLMS_ERROR_CODE_OK;
        }
    }
    *type = DLMS_DATA_TYPE_NONE;
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSObject_SetDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE type)
{
    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
    	if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
            ((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Type = type;
            return DLMS_ERROR_CODE_OK;
        }
    }

    CGXDLMSAttribute att;
    CGXDLMSAttribute_(&att, index, DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_NONE, DLMS_ACCESS_MODE_READ, 1);

    att.m_Type = type;
    CGXAttributeCollection_push_back(&(p->m_Attributes), &att);

    return DLMS_ERROR_CODE_OK;
}

DLMS_ACCESS_MODE CGXDLMSObject_GetAccess(CGXDLMSObject* p, int index)
{
    //LN is read only.
    if (index == 1)
    {
        return DLMS_ACCESS_MODE_READ;
    }
    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
    	if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
    		return ((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Access;
        }
    }
    return DLMS_ACCESS_MODE_READ_WRITE;
}

// Set attribute access.
void CGXDLMSObject_SetAccess(CGXDLMSObject* p, int index, DLMS_ACCESS_MODE access)
{
    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
    	if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
    		((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Access = access;
    		return;
        }
    }
    CGXDLMSAttribute att;
    CGXDLMSAttribute_(&att, index, DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_NONE, DLMS_ACCESS_MODE_READ, 1);

    att.m_Access = access;
    CGXAttributeCollection_push_back(&(p->m_Attributes), &att);
}

DLMS_METHOD_ACCESS_MODE CGXDLMSObject_GetMethodAccess(CGXDLMSObject* p, int index)
{
    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
    	if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
    		return ((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_MethodAccess;
        }
    }
    return DLMS_METHOD_ACCESS_MODE_ACCESS;
}

void CGXDLMSObject_SetMethodAccess(CGXDLMSObject* p, int index, DLMS_METHOD_ACCESS_MODE access)
{
    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
    	if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
    		((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_MethodAccess = access;
    		return;
        }
    }
    CGXDLMSAttribute att;
    CGXDLMSAttribute_(&att, index, DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_NONE, DLMS_ACCESS_MODE_READ, 1);

    att.m_MethodAccess = access;
    CGXAttributeCollection_push_back(&(p->m_Attributes), &att);
}

int CGXDLMSObject_GetUIDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE* type)
{
    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
    	if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
    		*type = ((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_UIType;
    		return DLMS_ERROR_CODE_OK;
        }
    }
    *type = DLMS_DATA_TYPE_NONE;
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSObject_SetUIDataType(CGXDLMSObject* p, int index, DLMS_DATA_TYPE type)
{
    for (unsigned int it = CGXAttributeCollection_begin(&(p->m_Attributes));
    	 it != CGXAttributeCollection_end(&(p->m_Attributes)); it++)
    {
    	if (((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_Index == index)
        {
    	    ((CGXDLMSAttribute*)CGXAttributeCollection_at(&(p->m_Attributes), it))->m_UIType = type;
    		return;
        }
    }
    CGXDLMSAttribute att;
    CGXDLMSAttribute_(&att, index, DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_NONE, DLMS_ACCESS_MODE_READ, 1);

    att.m_UIType = type;
    CGXAttributeCollection_push_back(&(p->m_Attributes), &att);
}

void CGXDLMSObject_GetLogicalName_2(CGXDLMSObject* p, String* ln)
{
    GXHelpers_GetLogicalName_1(p->m_LN, ln);
}

CGXAttributeCollection* CGXDLMSObject_GetAttributes(CGXDLMSObject* p)
{
    return &(p->m_Attributes);
}

CGXAttributeCollection* CGXDLMSObject_GetMethodAttributes(CGXDLMSObject* p)
{
    return &(p->m_MethodAttributes);
}
/*TODO:
//Get Object's attribute index.
char CGXDLMSObject::GetAttributeIndex()
{
    return m_AttributeIndex;
}

//Set Object's attribute index.
void CGXDLMSObject::SetAttributeIndex(char value)
{
    m_AttributeIndex = value;
}

//Get Object's data index.
unsigned short CGXDLMSObject::GetDataIndex()
{
    return m_DataIndex;
}

//Set Object's data index.
void CGXDLMSObject::SetDataIndex(unsigned short value)
{
    m_DataIndex = value;
}
*/

void CGXDLMSObject_GetDescription(CGXDLMSObject* p, String* out)
{
    String_clear(out);
    String_2(out, &(p->m_Description));
}

void CGXDLMSObject_SetDescription(CGXDLMSObject* p, String value)
{
    String_copy_1(&(p->m_Description), &value);
}

bool CGXDLMSObject_IsRead(CGXDLMSObject* p, int index)
{
    if (!CGXDLMSObject_CanRead(p, index))
    {
        return true;
    }
    return Map_find(&(p->m_ReadTimes), &index) != Map_end(&(p->m_ReadTimes));
}

bool CGXDLMSObject_CanRead(CGXDLMSObject* p, int index)
{
    return CGXDLMSObject_GetAccess(p, index) != DLMS_ACCESS_MODE_NONE;
}

bool CGXDLMSObject_IsLogicalNameEmpty(unsigned char* pLN)
{
    const unsigned char EmptyLN[] = { 0, 0, 0, 0, 0, 0 };
    return memcmp(pLN, EmptyLN, 6) == 0;
}

void CGXDLMSObject_GetValues(CGXDLMSObject* p, Vector* values) // std::vector<std::string>&
{
    assert(0);
}

void CGXDLMSObject_GetAttributeIndexToRead(CGXDLMSObject* p, Vector* attributes) // std::vector<int>& attributes
{
    assert(0);
}

int CGXDLMSObject_GetAttributeCount(CGXDLMSObject* p)
{
    assert(0);
    return 1;
}

// Returns amount of methods.
int CGXDLMSObject_GetMethodCount(CGXDLMSObject* p)
{
    assert(0);
    return 0;
}

// Returns value of given attribute.
int CGXDLMSObject_GetValue(CGXDLMSObject* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSObject_SetValue(CGXDLMSObject* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSObject_Invoke(CGXDLMSObject* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSCustomObject_(CGXDLMSCustomObject* p, DLMS_OBJECT_TYPE type)
{
    CGXDLMSObject_2((CGXDLMSObject*) p, type);
}

void CGXDLMSCustomObject_d(CGXDLMSCustomObject* p)
{
    CGXDLMSObject_d((CGXDLMSObject*) p);
}
