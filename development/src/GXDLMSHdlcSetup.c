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

#include "../include/GXDLMSHdlcSetup.h"
#include "../include/GXDLMSConverter.h"
#include "../include/Optimize.h"

static void CGXDLMSIecHdlcSetup__(CGXDLMSIecHdlcSetup* p)
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
     p->GetAttributeCount = CGXDLMSIecHdlcSetup_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSIecHdlcSetup_GetMethodCount;
	 p->GetValue = CGXDLMSIecHdlcSetup_GetValue;
	 p->SetValue = CGXDLMSIecHdlcSetup_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

    // Override CGXDLMSObject
     p->d = CGXDLMSIecHdlcSetup_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSIecHdlcSetup_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSIecHdlcSetup_GetValues;
     p->GetAttributeIndexToRead = CGXDLMSIecHdlcSetup_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

}
//Constructor.
void CGXDLMSIecHdlcSetup_1(CGXDLMSIecHdlcSetup* p)
{
    String t_Str;
    String_3(&t_Str, "0.0.22.0.0.255");

    CGXDLMSIecHdlcSetup_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
void CGXDLMSIecHdlcSetup_2(CGXDLMSIecHdlcSetup* p, String ln, unsigned short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_IEC_HDLC_SETUP, &ln, sn);

	CGXDLMSIecHdlcSetup__(p);

    p->m_CommunicationSpeed = DLMS_BAUD_RATE_9600;
    p->m_WindowSizeTransmit = p->m_WindowSizeReceive = 1;
    p->m_MaximumInfoLengthTransmit = p->m_MaximumInfoLengthReceive = 128;
    p->m_InactivityTimeout = 120;
    p->m_DeviceAddress = 0;
    p->m_InterCharachterTimeout = 30;
}

//LN Constructor.
void CGXDLMSIecHdlcSetup_3(CGXDLMSIecHdlcSetup* p, String ln)
{
	CGXDLMSIecHdlcSetup_2(p, ln, 0);
}

// Returns amount of attributes.
int CGXDLMSIecHdlcSetup_GetAttributeCount(CGXDLMSIecHdlcSetup* p)
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSIecHdlcSetup_GetMethodCount(CGXDLMSIecHdlcSetup* p)
{
    return 0;
}

void CGXDLMSIecHdlcSetup_GetValues(CGXDLMSIecHdlcSetup* p, Vector* values)//std::vector<std::string>& values);
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_3(values, CGXDLMSConverter_ToString_1(p->m_CommunicationSpeed));

    Vector_push_back_Str_2(values, p->m_WindowSizeTransmit);

    Vector_push_back_Str_2(values, p->m_WindowSizeReceive);

    Vector_push_back_Str_2(values, p->m_MaximumInfoLengthTransmit);

    Vector_push_back_Str_2(values, p->m_MaximumInfoLengthReceive);

    Vector_push_back_Str_2(values, p->m_InterCharachterTimeout);

    Vector_push_back_Str_2(values, p->m_InactivityTimeout);

    Vector_push_back_Str_2(values, p->m_DeviceAddress);
}

void CGXDLMSIecHdlcSetup_GetAttributeIndexToRead(CGXDLMSIecHdlcSetup* p, Vector* attributes)//std::vector<int>& attributes);
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //CommunicationSpeed
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //WindowSizeTransmit
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //WindowSizeReceive
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //MaximumInfoLengthTransmit
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //MaximumInfoLengthReceive
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //InterCharachterTimeout
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    //InactivityTimeout
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //DeviceAddress
    if (!CGXDLMSIecHdlcSetup_IsRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSIecHdlcSetup_GetDataType(CGXDLMSIecHdlcSetup* p, int index, DLMS_DATA_TYPE* type)
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
        *type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 5)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 6)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 7)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 8)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 9)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSIecHdlcSetup_GetValue(CGXDLMSIecHdlcSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    else if (e_index == 2)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_CommunicationSpeed);
    }
    else if (e_index == 3)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_WindowSizeTransmit);
    }
    else if (e_index == 4)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_WindowSizeReceive);
    }
    else if (e_index == 5)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_MaximumInfoLengthTransmit);
    }
    else if (e_index == 6)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_MaximumInfoLengthReceive);
    }
    else if (e_index == 7)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_InterCharachterTimeout);
    }
    else if (e_index == 8)
    {
    }
    else if (e_index == 9)
    {
        CGXDLMSValueEventArg_SetValue_3(e, p->m_DeviceAddress);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSIecHdlcSetup_SetValue(CGXDLMSIecHdlcSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        p->m_CommunicationSpeed = (DLMS_BAUD_RATE)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 3)
    {
        p->m_WindowSizeTransmit = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 4)
    {
        p->m_WindowSizeReceive = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 5)
    {
        p->m_MaximumInfoLengthTransmit = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 6)
    {
        p->m_MaximumInfoLengthReceive = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 7)
    {
        p->m_InterCharachterTimeout = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 8)
    {
        p->m_InactivityTimeout = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 9)
    {
        p->m_DeviceAddress = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSIecHdlcSetup_d(CGXDLMSIecHdlcSetup* p)
{
    CGXDLMSObject_d((CGXDLMSObject*) p);
}
