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

#include "../include/GXDLMSMacAddressSetup.h"
#include "../include/GXDLMSClient.h"
#include "../include/Optimize.h"

static void CGXDLMSMacAddressSetup__(CGXDLMSMacAddressSetup* p)
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
     p->GetAttributeCount = CGXDLMSMacAddressSetup_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSMacAddressSetup_GetMethodCount;
	 p->GetValue = CGXDLMSMacAddressSetup_GetValue;
	 p->SetValue = CGXDLMSMacAddressSetup_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
     p->d = CGXDLMSMacAddressSetup_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSMacAddressSetup_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSMacAddressSetup_GetValues;
     p->GetAttributeIndexToRead = CGXDLMSMacAddressSetup_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

     String_(&p->m_MacAddress);
}
void CGXDLMSMacAddressSetup_1(CGXDLMSMacAddressSetup* p)
{
    String t_Str;
    String_3(&t_Str, "0.0.25.2.0.255");

    CGXDLMSMacAddressSetup_3(p, t_Str, 0);

    String_d(&t_Str);
}

void CGXDLMSMacAddressSetup_2(CGXDLMSMacAddressSetup* p, String ln)
{
	CGXDLMSMacAddressSetup_3(p, ln, 0);
}

void CGXDLMSMacAddressSetup_3(CGXDLMSMacAddressSetup* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*)p, DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP, &ln, sn);

	CGXDLMSMacAddressSetup__(p);
}

/**
 Value of COSEM Data object.
*/
String CGXDLMSMacAddressSetup_GetMacAddress(CGXDLMSMacAddressSetup* p)
{
    String t_Str;
    String_2(&t_Str, &p->m_MacAddress);

    return t_Str; // = copy cons + des
}
void CGXDLMSMacAddressSetup_SetMacAddress(CGXDLMSMacAddressSetup* p, String value)
{
    String_copy_1(&p->m_MacAddress, &value);
}

// Returns amount of attributes.
int CGXDLMSMacAddressSetup_GetAttributeCount(CGXDLMSMacAddressSetup* p)
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSMacAddressSetup_GetMethodCount(CGXDLMSMacAddressSetup* p)
{
    return 0;
}

void CGXDLMSMacAddressSetup_GetValues(CGXDLMSMacAddressSetup* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back(values, &p->m_MacAddress);
}

void CGXDLMSMacAddressSetup_GetAttributeIndexToRead(CGXDLMSMacAddressSetup* p, Vector* attributes) //std::vector<int>&
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //MacAddress
    if (!CGXDLMSMacAddressSetup_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSMacAddressSetup_GetDataType(CGXDLMSMacAddressSetup* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}


// Returns value of given attribute.
int CGXDLMSMacAddressSetup_GetValue(CGXDLMSMacAddressSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        e->m_ByteArray = true;

        String add = CGXDLMSMacAddressSetup_GetMacAddress(p);

        String colon, dot;
        String_3(&colon, ":");
        String_3(&dot, ".");

        GXHelpers_Replace(&add, colon, dot);

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXDLMSVariant tmp;
        CGXDLMSVariant_22(&tmp, add);

        int ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &tmp);
        
        CGXDLMSVariant_d(&tmp);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXByteBuffer_d(&data);
        String_d(&colon);
        String_d(&dot);
        String_d(&add);
        return ret;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSMacAddressSetup_SetValue(CGXDLMSMacAddressSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        CGXDLMSVariant newValue;
        CGXDLMSVariant_1(&newValue);

        int ret = CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_OCTET_STRING, &newValue);
        if (ret != DLMS_ERROR_CODE_OK)
        {
            CGXDLMSVariant_d(&newValue);
            return ret;
        }

        CGXDLMSVariant_d(&newValue);

        String add = CGXDLMSVariant_ToString(CGXDLMSValueEventArg_GetValue(e));

        String colon, dot;
        String_3(&colon, ":");
        String_3(&dot, ".");

        GXHelpers_Replace(&add, dot, colon);
        CGXDLMSMacAddressSetup_SetMacAddress(p, add);
        
        String_d(&colon);
        String_d(&dot);
        String_d(&add);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

void CGXDLMSMacAddressSetup_d(CGXDLMSMacAddressSetup* p)
{
    String_d(&p->m_MacAddress);

    CGXDLMSObject_d((CGXDLMSObject*)p);
}
