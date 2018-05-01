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
#include "../include/GXDLMSSecuritySetup.h"
#include "../include/GXDLMSConverter.h"
#include "../include/Optimize.h"

static void CGXDLMSSecuritySetup__(CGXDLMSSecuritySetup* p)
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    p->GetAttributeCount = CGXDLMSSecuritySetup_GetAttributeCount;
	p->GetMethodCount = CGXDLMSSecuritySetup_GetMethodCount;
	p->GetValue = CGXDLMSSecuritySetup_GetValue;
	p->SetValue = CGXDLMSSecuritySetup_SetValue;
	p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
    p->d = CGXDLMSSecuritySetup_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSSecuritySetup_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSSecuritySetup_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSSecuritySetup_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

    CGXByteBuffer_1(&p->m_ServerSystemTitle);
    CGXByteBuffer_1(&p->m_ClientSystemTitle);
}
//Constructor.
void CGXDLMSSecuritySetup_1(CGXDLMSSecuritySetup* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSSecuritySetup_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSSecuritySetup_2(CGXDLMSSecuritySetup* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_DLMS_SECURITY_SETUP, &ln, sn);

	CGXDLMSSecuritySetup__(p);
}

//LN Constructor.
void CGXDLMSSecuritySetup_3(CGXDLMSSecuritySetup* p, String ln)
{
	CGXDLMSSecuritySetup_2(p, ln, 0);
}

CGXByteBuffer* CGXDLMSSecuritySetup_GetClientSystemTitle(CGXDLMSSecuritySetup* p)
{
    return &p->m_ClientSystemTitle;
}

void CGXDLMSSecuritySetup_SetClientSystemTitle(CGXDLMSSecuritySetup* p, CGXByteBuffer* value)
{
    CGXByteBuffer_copy(&p->m_ClientSystemTitle, value);
}

CGXByteBuffer* CGXDLMSSecuritySetup_GetServerSystemTitle(CGXDLMSSecuritySetup* p)
{
    return &p->m_ServerSystemTitle;
}

void CGXDLMSSecuritySetup_SetServerSystemTitle(CGXDLMSSecuritySetup* p, CGXByteBuffer* value)
{
    CGXByteBuffer_copy(&p->m_ServerSystemTitle, value);
}

// Returns amount of attributes.
int CGXDLMSSecuritySetup_GetAttributeCount(CGXDLMSSecuritySetup* p)
{
    return 5;
}

// Returns amount of methods.
int CGXDLMSSecuritySetup_GetMethodCount(CGXDLMSSecuritySetup* p)
{
    return 2;
}

void CGXDLMSSecuritySetup_GetValues(CGXDLMSSecuritySetup* p, Vector* values) //std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_7((DLMS_SECURITY_POLICY)p->m_SecurityPolicy));

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_8(p->m_SecuritySuite));

    Vector_push_back_Str_4(values, &p->m_ClientSystemTitle);

    Vector_push_back_Str_4(values, &p->m_ServerSystemTitle);
}

void CGXDLMSSecuritySetup_GetAttributeIndexToRead(CGXDLMSSecuritySetup* p, Vector* attributes) //std::vector<int>&
{
	int tmp;

    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //SecurityPolicy
    if (CGXDLMSSecuritySetup_CanRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //SecuritySuite
    if (CGXDLMSSecuritySetup_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    if (p->m_Version > 0)
    {
        //ClientSystemTitle
        if (CGXDLMSSecuritySetup_CanRead(p, 4))
        {
            tmp = 4;
            Vector_push_back(attributes, &tmp);
        }
        //ServerSystemTitle
        if (CGXDLMSSecuritySetup_CanRead(p, 5))
        {
            tmp = 5;
            Vector_push_back(attributes, &tmp);
        }
        //Certificates
        if (CGXDLMSSecuritySetup_CanRead(p, 6))
        {
            tmp = 6;
            Vector_push_back(attributes, &tmp);
        }
    }
}

int CGXDLMSSecuritySetup_GetDataType(CGXDLMSSecuritySetup* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 5)
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
int CGXDLMSSecuritySetup_GetValue(CGXDLMSSecuritySetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    else if (e_index == 2)
    {
        // CGXDLMSVariant tmp = p->m_SecurityPolicy;
        // e.SetValue(tmp);
        CGXDLMSValueEventArg_SetValue_4(e, p->m_SecurityPolicy);
    }
    else if (e_index == 3)
    {
        // CGXDLMSVariant tmp = p->m_SecuritySuite;
        // e.SetValue(tmp);
        CGXDLMSValueEventArg_SetValue_3(e, p->m_SecuritySuite);
    }
    else if (e_index == 4)
    {
        // e.GetValue().Add(p->m_ClientSystemTitle.GetData(), p->m_ClientSystemTitle.GetSize());
        CGXDLMSVariant_Add_1(CGXDLMSValueEventArg_GetValue(e),
                             p->m_ClientSystemTitle.m_Data,
                             p->m_ClientSystemTitle.m_Size);
    }
    else if (e_index == 5)
    {
        // e.GetValue().Add(p->m_ServerSystemTitle.GetData(), p->m_ServerSystemTitle.GetSize());
        CGXDLMSVariant_Add_1(CGXDLMSValueEventArg_GetValue(e),
                             p->m_ServerSystemTitle.m_Data,
                             p->m_ServerSystemTitle.m_Size);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSSecuritySetup_SetValue(CGXDLMSSecuritySetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        p->m_SecurityPolicy = (DLMS_SECURITY_POLICY)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 3)
    {
        p->m_SecuritySuite = (DLMS_SECURITY_SUITE)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 4)
    {
        //p->m_ClientSystemTitle.Set(e.GetValue().byteArr, e.GetValue().size);
        CGXByteBuffer_Set_1(&p->m_ClientSystemTitle,
                            CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                            CGXDLMSValueEventArg_GetValue(e)->size);
    }
    else if (e_index == 5)
    {
        //p->m_ServerSystemTitle.Set(e.GetValue().byteArr, e.GetValue().size);
        CGXByteBuffer_Set_1(&p->m_ServerSystemTitle,
                            CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr,
                            CGXDLMSValueEventArg_GetValue(e)->size);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSSecuritySetup_d(CGXDLMSSecuritySetup* p)
{
    CGXByteBuffer_d(&p->m_ServerSystemTitle);
    CGXByteBuffer_d(&p->m_ClientSystemTitle);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
