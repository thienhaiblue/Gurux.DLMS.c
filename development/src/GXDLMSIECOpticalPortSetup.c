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

#include "../include/GXDLMSIECOpticalPortSetup.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSConverter.h"
#include "../include/Optimize.h"

static void CGXDLMSIECOpticalPortSetup__(CGXDLMSIECOpticalPortSetup* p)
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	 p->GetAttributeCount = CGXDLMSIECOpticalPortSetup_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSIECOpticalPortSetup_GetMethodCount;
	 p->GetValue = CGXDLMSIECOpticalPortSetup_GetValue;
	 p->SetValue = CGXDLMSIECOpticalPortSetup_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
     p->d = CGXDLMSIECOpticalPortSetup_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSIECOpticalPortSetup_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSIECOpticalPortSetup_GetValues;
     p->GetAttributeIndexToRead = CGXDLMSIECOpticalPortSetup_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

     String_(&p->m_Password1);
     String_(&p->m_Password2);
     String_(&p->m_Password5);
     String_(&p->m_DeviceAddress);
}
//Constructor.
void CGXDLMSIECOpticalPortSetup_1(CGXDLMSIECOpticalPortSetup *p)
{
    String t_Str;
    String_3(&t_Str, "0.0.20.0.0.255");

    CGXDLMSIECOpticalPortSetup_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSIECOpticalPortSetup_2(CGXDLMSIECOpticalPortSetup *p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, &ln, sn);

	CGXDLMSIECOpticalPortSetup__(p);

    p->m_DefaultMode = DLMS_OPTICAL_PROTOCOL_MODE_DEFAULT;
    p->m_DefaultBaudrate = DLMS_BAUD_RATE_300;
    p->m_ProposedBaudrate = DLMS_BAUD_RATE_9600;
}

//LN Constructor.
void CGXDLMSIECOpticalPortSetup_3(CGXDLMSIECOpticalPortSetup *p, String ln)
{
	CGXDLMSIECOpticalPortSetup_2(p, ln, 0);
}

String CGXDLMSIECOpticalPortSetup_GetDeviceAddress(CGXDLMSIECOpticalPortSetup *p)
{
    String res;
    String_2(&res, &(p->m_DeviceAddress));

    return res; // = copy cons + des
}
void CGXDLMSIECOpticalPortSetup_SetDeviceAddress(CGXDLMSIECOpticalPortSetup *p, String value)
{
	String_copy_1(&(p->m_DeviceAddress), &value);
}

String CGXDLMSIECOpticalPortSetup_GetPassword1(CGXDLMSIECOpticalPortSetup *p)
{
    String res;
    String_2(&res, &(p->m_Password1));

    return res; // = copy cons + des
}
void CGXDLMSIECOpticalPortSetup_SetPassword1(CGXDLMSIECOpticalPortSetup *p, String value)
{
	String_copy_1(&(p->m_Password1), &value);
}

String CGXDLMSIECOpticalPortSetup_GetPassword2(CGXDLMSIECOpticalPortSetup *p)
{
    String res;
    String_2(&res, &(p->m_Password2));

    return res; // = copy cons + des
}
void CGXDLMSIECOpticalPortSetup_SetPassword2(CGXDLMSIECOpticalPortSetup *p, String value)
{
	String_copy_1(&(p->m_Password2), &value);
}

String CGXDLMSIECOpticalPortSetup_GetPassword5(CGXDLMSIECOpticalPortSetup *p)
{
    String res;
    String_2(&res, &(p->m_Password5));

    return res; // = copy cons + des
}
void CGXDLMSIECOpticalPortSetup_SetPassword5(CGXDLMSIECOpticalPortSetup *p, String value)
{
	String_copy_1(&(p->m_Password5), &value);
}

// Returns amount of attributes.
int CGXDLMSIECOpticalPortSetup_GetAttributeCount(CGXDLMSIECOpticalPortSetup *p)
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSIECOpticalPortSetup_GetMethodCount(CGXDLMSIECOpticalPortSetup *p)
{
    return 0;
}

void CGXDLMSIECOpticalPortSetup_GetValues(CGXDLMSIECOpticalPortSetup *p, Vector* values)//std::vector<std::string>&
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_2(values, p->m_DefaultMode);

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_1(p->m_DefaultBaudrate));

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_1(p->m_ProposedBaudrate));

    Vector_push_back_Str_2(values, p->m_ResponseTime);

    Vector_push_back(values, &p->m_DeviceAddress);
    Vector_push_back(values, &p->m_Password1);
    Vector_push_back(values, &p->m_Password2);
    Vector_push_back(values, &p->m_Password5);
}

void CGXDLMSIECOpticalPortSetup_GetAttributeIndexToRead(CGXDLMSIECOpticalPortSetup *p, Vector* attributes)
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //DefaultMode
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //DefaultBaudrate
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //ProposedBaudrate
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //ResponseTime
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //DeviceAddress
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //Password1
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    //Password2
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //Password5
    if (!CGXDLMSIECOpticalPortSetup_IsRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSIECOpticalPortSetup_GetDataType(CGXDLMSIECOpticalPortSetup *p, int index, DLMS_DATA_TYPE* type)
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
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 5)
    {
        *type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 6)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 7)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 8)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 9)
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
int CGXDLMSIECOpticalPortSetup_GetValue(CGXDLMSIECOpticalPortSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_DefaultMode);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_DefaultBaudrate);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_ProposedBaudrate);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_ResponseTime);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        CGXDLMSVariant_Add_2(CGXDLMSValueEventArg_GetValue(e),
                             String_c_str(&p->m_DeviceAddress),
                             (unsigned long)String_size(&p->m_DeviceAddress));
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 7)
    {
        CGXDLMSVariant_Add_2(CGXDLMSValueEventArg_GetValue(e),
                             String_c_str(&p->m_Password1),
                             (unsigned long)String_size(&p->m_Password1));
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 8)
    {
        CGXDLMSVariant_Add_2(CGXDLMSValueEventArg_GetValue(e),
                             String_c_str(&p->m_Password2),
                             (unsigned long)String_size(&p->m_Password2));
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 9)
    {
        CGXDLMSVariant_Add_2(CGXDLMSValueEventArg_GetValue(e),
                             String_c_str(&p->m_Password5),
                             (unsigned long)String_size(&p->m_Password5));
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSIECOpticalPortSetup_SetValue(CGXDLMSIECOpticalPortSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        p->m_DefaultMode = (DLMS_OPTICAL_PROTOCOL_MODE)CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 3)
    {
        p->m_DefaultBaudrate = (DLMS_BAUD_RATE)CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 4)
    {
        p->m_ProposedBaudrate = (DLMS_BAUD_RATE)CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 5)
    {
        p->m_ResponseTime = (DLMS_LOCAL_PORT_RESPONSE_TIME)CGXDLMSValueEventArg_GetValue(e)->st.un.lVal;
        return DLMS_ERROR_CODE_OK;
    }
    else if ((e_index == 6) || (e_index == 7) || (e_index == 8) || (e_index == 9))
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        CGXDLMSClient_ChangeType_2(CGXDLMSValueEventArg_GetValue(e), DLMS_DATA_TYPE_STRING, &tmp);
        if (e_index == 6)
        {
            CGXDLMSIECOpticalPortSetup_SetDeviceAddress(p, tmp.strVal);
        }
        else if (e_index == 7)
        {
            CGXDLMSIECOpticalPortSetup_SetPassword1(p, tmp.strVal);
        }
        else if (e_index == 8)
        {
            CGXDLMSIECOpticalPortSetup_SetPassword2(p, tmp.strVal);
        }
        else if (e_index == 9)
        {
            CGXDLMSIECOpticalPortSetup_SetPassword5(p, tmp.strVal);
        }

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

void CGXDLMSIECOpticalPortSetup_d(CGXDLMSIECOpticalPortSetup *p)
{
    String_d(&p->m_Password1);
    String_d(&p->m_Password2);
    String_d(&p->m_Password5);
    String_d(&p->m_DeviceAddress);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
