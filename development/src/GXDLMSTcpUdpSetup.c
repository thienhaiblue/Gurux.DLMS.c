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
#include "../include/GXDLMSTcpUdpSetup.h"
#include "../include/Optimize.h"

static void CGXDLMSTcpUdpSetup__(CGXDLMSTcpUdpSetup* p)
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
     p->GetAttributeCount = CGXDLMSTcpUdpSetup_GetAttributeCount;
	 p->GetMethodCount = CGXDLMSTcpUdpSetup_GetMethodCount;
	 p->GetValue = CGXDLMSTcpUdpSetup_GetValue;
	 p->SetValue = CGXDLMSTcpUdpSetup_SetValue;
	 p->Invoke = CGXDLMSObject_Invoke;

     // Override CGXDLMSObject
     p->d = CGXDLMSTcpUdpSetup_d;
     p->SetDataType = CGXDLMSObject_SetDataType;
     p->GetDataType = CGXDLMSTcpUdpSetup_GetDataType;
     p->GetUIDataType = CGXDLMSObject_GetUIDataType;
     p->GetValues = CGXDLMSTcpUdpSetup_GetValues;
     p->GetAttributeIndexToRead = CGXDLMSTcpUdpSetup_GetAttributeIndexToRead;
    ///////////////////////////////////////////////////////////////////////////

     String_(&p->m_IPReference);
}
/**
 Constructor.
*/
void CGXDLMSTcpUdpSetup_1(CGXDLMSTcpUdpSetup* p)
{
    String t_Str;
    String_3(&t_Str, "0.0.25.0.0.255");

    CGXDLMSTcpUdpSetup_3(p, t_Str, 0);

    String_d(&t_Str);
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
void CGXDLMSTcpUdpSetup_2(CGXDLMSTcpUdpSetup* p, String ln)
{
	CGXDLMSTcpUdpSetup_3(p, ln, 0);
}

/**
 Constructor.

 @param ln Logical Name of the object.
 @param sn Short Name of the object.
*/
void CGXDLMSTcpUdpSetup_3(CGXDLMSTcpUdpSetup* p, String ln, short sn)
{
	CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_TCP_UDP_SETUP, &ln, sn);

	CGXDLMSTcpUdpSetup__(p);

    p->m_Port = 4059;
	String_copy_2(&p->m_IPReference, "127.0.0.1");
    p->m_MaximumSimultaneousConnections = 1;
    p->m_InactivityTimeout = 180;
    p->m_MaximumSegmentSize = 576;
}

String CGXDLMSTcpUdpSetup_GetIPReference(CGXDLMSTcpUdpSetup* p)
{
    String res;
    String_2(&res, &(p->m_IPReference));

    return res; // = copy cons + des
}
void CGXDLMSTcpUdpSetup_SetIPReference(CGXDLMSTcpUdpSetup* p, String value)
{
	String_copy_1(&(p->m_IPReference), &value);
}

// Returns amount of attributes.
int CGXDLMSTcpUdpSetup_GetAttributeCount(CGXDLMSTcpUdpSetup* p)
{
    return 6;
}

// Returns amount of methods.
int CGXDLMSTcpUdpSetup_GetMethodCount(CGXDLMSTcpUdpSetup* p)
{
    return 0;
}

void CGXDLMSTcpUdpSetup_GetValues(CGXDLMSTcpUdpSetup* p, Vector* values)  //(std::vector<std::string>& values);
{
    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_2(values, p->m_Port);

    Vector_push_back(values, &p->m_IPReference);

    Vector_push_back_Str_2(values, p->m_MaximumSegmentSize);

    Vector_push_back_Str_2(values, p->m_MaximumSimultaneousConnections);

    Vector_push_back_Str_2(values, p->m_InactivityTimeout);
}

void CGXDLMSTcpUdpSetup_GetAttributeIndexToRead(CGXDLMSTcpUdpSetup* p, Vector* attributes) //(std::vector<int>& attributes);
{
	int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //Port
    if (!CGXDLMSTcpUdpSetup_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //IPReference
    if (!CGXDLMSTcpUdpSetup_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //MaximumSegmentSize
    if (!CGXDLMSTcpUdpSetup_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //MaximumSimultaneousConnections
    if (!CGXDLMSTcpUdpSetup_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //InactivityTimeout
    if (!CGXDLMSTcpUdpSetup_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSTcpUdpSetup_GetDataType(CGXDLMSTcpUdpSetup* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 5)
    {
        *type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 6)
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
int CGXDLMSTcpUdpSetup_GetValue(CGXDLMSTcpUdpSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        // CGXDLMSVariant tmp = GetPort();
        // e.SetValue(tmp);
        CGXDLMSValueEventArg_SetValue_3(e, p->m_Port);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        GXHelpers_SetLogicalName_1(String_c_str(&p->m_IPReference), &tmp);
        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        // CGXDLMSVariant tmp = GetMaximumSegmentSize();
        // e.SetValue(tmp);
        CGXDLMSValueEventArg_SetValue_3(e, p->m_MaximumSegmentSize);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        // CGXDLMSVariant tmp = GetMaximumSimultaneousConnections();
        // e.SetValue(tmp);
        CGXDLMSValueEventArg_SetValue_3(e, p->m_MaximumSimultaneousConnections);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        // CGXDLMSVariant tmp = GetInactivityTimeout();
        // e.SetValue(tmp);
        CGXDLMSValueEventArg_SetValue_3(e, p->m_InactivityTimeout);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSTcpUdpSetup_SetValue(CGXDLMSTcpUdpSetup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        //SetPort(e.GetValue().ToInteger());
        p->m_Port = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
        return DLMS_ERROR_CODE_OK;
    }
    else if (e_index == 3)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_NONE)
        {
            String empt;
            String_3(&empt, "");

            CGXDLMSTcpUdpSetup_SetIPReference(p, empt);

            String_d(&empt);
        }
        else
        {
            if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                GXHelpers_GetLogicalName_1(CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr, &p->m_IPReference);
            }
            else
            {
                String str = CGXDLMSVariant_ToString(CGXDLMSValueEventArg_GetValue(e));

                CGXDLMSTcpUdpSetup_SetIPReference(p, str);

                String_d(&str);
            }
        }
    }
    else if (e_index == 4)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_NONE)
        {
            p->m_MaximumSegmentSize = 576;
        }
        else
        {
            p->m_MaximumSegmentSize = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
        }
    }
    else if (e_index == 5)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_NONE)
        {
            p->m_MaximumSimultaneousConnections = 1;
        }
        else
        {
            p->m_MaximumSimultaneousConnections = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
        }
    }
    else if (e_index == 6)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_NONE)
        {
            p->m_InactivityTimeout = 180;
        }
        else
        {
            p->m_InactivityTimeout = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
        }
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSTcpUdpSetup_d(CGXDLMSTcpUdpSetup* p)
{
    String_d(&p->m_IPReference);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
