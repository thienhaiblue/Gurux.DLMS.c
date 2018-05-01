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

#include "../include/GXDLMSIp4Setup.h"
#include "../include/GXDLMSClient.h"
#include "../include/Optimize.h"

#if defined(_WIN32) || defined(_WIN64)//Windows includes
#include <Winsock.h> //Add support for sockets
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

static void CGXDLMSIp4Setup__(CGXDLMSIp4Setup* p)
{
    p->GetAttributeCount = CGXDLMSIp4Setup_GetAttributeCount;
    p->GetMethodCount = CGXDLMSIp4Setup_GetMethodCount;
    p->GetValue = CGXDLMSIp4Setup_GetValue;
    p->SetValue = CGXDLMSIp4Setup_SetValue;
    p->Invoke = CGXDLMSObject_Invoke;

    p->d = CGXDLMSIp4Setup_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSIp4Setup_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSIp4Setup_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSIp4Setup_GetAttributeIndexToRead;

    String_(&p->m_DataLinkLayerReference);
    String_(&p->m_IPAddress);
    Vector_(&p->m_MulticastIPAddress, sizeof(unsigned long), NULL, NULL); //std::vector<unsigned long>
    Vector_(&p->m_IPOptions, sizeof(CGXDLMSIp4SetupIpOption),
            CGXDLMSIp4SetupIpOption_v_c, CGXDLMSIp4SetupIpOption_v_d); // std::vector<CGXDLMSIp4SetupIpOption>
    CGXDLMSVariant_1(&p->m_Value);
}

//Constructor.
//CGXDLMSIp4Setup::CGXDLMSIp4Setup() :
  //  CGXDLMSIp4Setup("", 0)
void CGXDLMSIp4Setup_1(CGXDLMSIp4Setup* p)
{
    String t_Str;
    String_3(&t_Str, "");

    CGXDLMSIp4Setup_2(p, t_Str, 0);

    String_d(&t_Str);
}

//SN Constructor.
//CGXDLMSIp4Setup::CGXDLMSIp4Setup(std::string ln, unsigned short sn) :
  //  CGXDLMSObject(DLMS_OBJECT_TYPE_IP4_SETUP, ln, sn)
void CGXDLMSIp4Setup_2(CGXDLMSIp4Setup* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_IP4_SETUP, &ln, sn);

    CGXDLMSIp4Setup__(p);

    String_copy_2(&p->m_IPAddress, "");
    p->m_SubnetMask = 0;
    p->m_GatewayIPAddress = 0;
    p->m_UseDHCP = false;
    p->m_PrimaryDNSAddress = 0;
    p->m_SecondaryDNSAddress = 0;
}

//LN Constructor.
//CGXDLMSIp4Setup::CGXDLMSIp4Setup(std::string ln) :
  //  CGXDLMSIp4Setup(ln, 0)
void CGXDLMSIp4Setup_3(CGXDLMSIp4Setup* p, String ln)
{
    CGXDLMSIp4Setup_2(p, ln, 0);
}

String* CGXDLMSIp4Setup_GetDataLinkLayerReference(CGXDLMSIp4Setup* p)
{
    return &p->m_DataLinkLayerReference;
}
void CGXDLMSIp4Setup_SetDataLinkLayerReference(CGXDLMSIp4Setup* p, String value)
{
    String_copy_1(&p->m_DataLinkLayerReference, &value);
}

String* CGXDLMSIp4Setup_GetIPAddress(CGXDLMSIp4Setup* p)
{
    return &p->m_IPAddress;
}

void CGXDLMSIp4Setup_SetIPAddress(CGXDLMSIp4Setup* p, String* value)
{
    String_copy_1(&p->m_IPAddress, value);
}

//std::vector<unsigned long>& CGXDLMSIp4Setup::GetMulticastIPAddress()
Vector* CGXDLMSIp4Setup_GetMulticastIPAddress(CGXDLMSIp4Setup* p)
{
    return &p->m_MulticastIPAddress;
}

Vector* CGXDLMSIp4Setup_GetIPOptions(CGXDLMSIp4Setup* p)
{
    return &p->m_IPOptions;
}
void CGXDLMSIp4Setup_SetIPOptions(CGXDLMSIp4Setup* p, Vector* value)
{
    //m_IPOptions.clear();
    Vector_clear(&p->m_IPOptions);

    //for (std::vector<CGXDLMSIp4SetupIpOption>::iterator it = value.begin(); it != value.end(); ++it)
    for (unsigned int i = Vector_begin(value); i != Vector_end(value); ++i)
    {
        CGXDLMSIp4SetupIpOption* it = Vector_at(value, i);
        //m_IPOptions.push_back(*it);
        Vector_push_back(&p->m_IPOptions, it);
    }
}

// Returns amount of attributes.
int CGXDLMSIp4Setup_GetAttributeCount(CGXDLMSIp4Setup* p)
{
    return 10;
}

// Returns amount of methods.
int CGXDLMSIp4Setup_GetMethodCount(CGXDLMSIp4Setup* p)
{
    return 3;
}

void CGXDLMSIp4Setup_GetValues(CGXDLMSIp4Setup* p, Vector* values)
{
    // values.clear();
    // std::string ln;
    // GetLogicalName(ln);
    // values.push_back(ln);
    // values.push_back(m_DataLinkLayerReference);
    // values.push_back(m_IPAddress);
    // std::stringstream sb;
    // sb << '[';
    // bool empty = true;
    // for (std::vector<unsigned long>::iterator it = m_MulticastIPAddress.begin(); it != m_MulticastIPAddress.end(); ++it)
    // {
    //     if (!empty)
    //     {
    //         sb << ", ";
    //     }
    //     empty = false;
    //     std::string str = CGXDLMSVariant(*it).ToString();
    //     sb.write(str.c_str(), str.size());
    // }
    // sb << ']';
    // values.push_back(sb.str());

    // //Clear str.
    // sb.str(std::string());
    // sb << '[';
    // empty = true;
    // for (std::vector<CGXDLMSIp4SetupIpOption>::iterator it = m_IPOptions.begin(); it != m_IPOptions.end(); ++it)
    // {
    //     if (!empty)
    //     {
    //         sb << ", ";
    //     }
    //     empty = false;
    //     std::string str = it->ToString();
    //     sb.write(str.c_str(), str.size());
    // }
    // sb << ']';
    // values.push_back(sb.str());

    // values.push_back(CGXDLMSVariant(m_SubnetMask).ToString());
    // values.push_back(CGXDLMSVariant(m_GatewayIPAddress).ToString());
    // values.push_back(CGXDLMSVariant(m_UseDHCP).ToString());
    // values.push_back(CGXDLMSVariant(m_PrimaryDNSAddress).ToString());
    // values.push_back(CGXDLMSVariant(m_SecondaryDNSAddress).ToString());

    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back(values, &p->m_DataLinkLayerReference);
    Vector_push_back(values, &p->m_IPAddress);

    String sb;
    String_3(&sb, "[");

    bool empty = true;
    for (unsigned int i = Vector_begin(&(p->m_MulticastIPAddress)); i != Vector_end(&(p->m_MulticastIPAddress)); i++)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        unsigned long* it = Vector_at(&p->m_MulticastIPAddress, i);

        String_append_var_ulong(&sb, *it);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_clear(&sb);

    String_copy_2(&sb, "[");

    empty = true;
    for (unsigned int i = Vector_begin(&(p->m_IPOptions)); i != Vector_end(&(p->m_IPOptions)); i++)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;

        CGXDLMSIp4SetupIpOption* it = Vector_at(&p->m_IPOptions, i);
        
        String str = CGXDLMSIp4SetupIpOption_ToString(it);

        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");

    Vector_push_back(values, &sb);

    String_d(&sb);

    Vector_push_back_Str_5(values, p->m_SubnetMask);

    Vector_push_back_Str_5(values, p->m_GatewayIPAddress);

    Vector_push_back_Str_7(values, p->m_UseDHCP);

    Vector_push_back_Str_5(values, p->m_PrimaryDNSAddress);

    Vector_push_back_Str_5(values, p->m_SecondaryDNSAddress);
}

void CGXDLMSIp4Setup_GetAttributeIndexToRead(CGXDLMSIp4Setup* p, Vector* attributes)
{
    int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //DataLinkLayerReference
    if (!CGXDLMSIp4Setup_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //IPAddress
    if (CGXDLMSIp4Setup_CanRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //MulticastIPAddress
    if (CGXDLMSIp4Setup_CanRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //IPOptions
    if (CGXDLMSIp4Setup_CanRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //SubnetMask
    if (CGXDLMSIp4Setup_CanRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //GatewayIPAddress
    if (CGXDLMSIp4Setup_CanRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
    //UseDHCP
    if (!CGXDLMSIp4Setup_IsRead(p, 8))
    {
        tmp = 8;
        Vector_push_back(attributes, &tmp);
    }
    //PrimaryDNSAddress
    if (CGXDLMSIp4Setup_CanRead(p, 9))
    {
        tmp = 9;
        Vector_push_back(attributes, &tmp);
    }
    //SecondaryDNSAddress
    if (CGXDLMSIp4Setup_CanRead(p, 10))
    {
        tmp = 10;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSIp4Setup_GetDataType(CGXDLMSIp4Setup* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 3)
    {
        *type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 4)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 5)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 6)
    {
        *type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 7)
    {
        *type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 8)
    {
        *type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 9)
    {
        *type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 10)
    {
        *type = DLMS_DATA_TYPE_UINT32;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSIp4Setup_GetValue(CGXDLMSIp4Setup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    else if (e_index == 2)
    {
        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        GXHelpers_SetLogicalName_1(String_c_str(&p->m_DataLinkLayerReference), &tmp);
        
        CGXDLMSValueEventArg_SetValue(e, &tmp);

        CGXDLMSVariant_d(&tmp);
    }
    else if (e_index == 3)
    {
        if (String_size(&p->m_IPAddress) == 0)
        {
            return 0;
        }
        struct sockaddr_in add;
        add.sin_addr.s_addr = inet_addr(String_c_str(&p->m_IPAddress));
        //If address is give as name
        if (add.sin_addr.s_addr == INADDR_NONE)
        {
            struct hostent *Hostent = gethostbyname(String_c_str(&p->m_IPAddress));
            if (Hostent == NULL)
            {
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            };
            add.sin_addr = *(struct in_addr*)(void*)Hostent->h_addr_list[0];
        };
        //e.SetValue((unsigned long)add.sin_addr.s_addr);
        CGXDLMSValueEventArg_SetValue_5(e, (unsigned long)add.sin_addr.s_addr);
    }
    else if (e_index == 4)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_MulticastIPAddress), &data);
        int ret;

        CGXDLMSVariant tmp;
        CGXDLMSVariant_1(&tmp);

        //for (std::vector<unsigned long>::iterator it = m_MulticastIPAddress.begin(); it != m_MulticastIPAddress.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_MulticastIPAddress); i != Vector_end(&p->m_MulticastIPAddress); ++i)
        {
            unsigned long* it = Vector_at(&p->m_MulticastIPAddress, i);
            //tmp = *it;
            CGXDLMSVariant_copy_17(&tmp, *it);
            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT32, &tmp)) != 0)
            {
                CGXDLMSVariant_d(&tmp);
                CGXByteBuffer_d(&data);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&tmp);
        CGXByteBuffer_d(&data);
    }
    else if (e_index == 5)
    {
        e->m_ByteArray = true;

        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_SetUInt8_1(&bb, DLMS_DATA_TYPE_ARRAY);
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_IPOptions), &bb);
        int ret;

        CGXDLMSVariant type, len, data;
        CGXDLMSVariant_1(&type);
        CGXDLMSVariant_1(&len);
        CGXDLMSVariant_1(&data);

        //for (std::vector<CGXDLMSIp4SetupIpOption>::iterator it = m_IPOptions.begin(); it != m_IPOptions.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_IPOptions); i != Vector_end(&p->m_IPOptions); ++i)
        {
            CGXDLMSIp4SetupIpOption* it = Vector_at(&p->m_IPOptions, i);
            CGXByteBuffer_SetUInt8_1(&bb, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&bb, 3);
            //type = it->GetType();
            //len = it->GetLength();
            //data = it->GetData();
            CGXDLMSVariant_copy_12(&type, it->m_Type);
            CGXDLMSVariant_copy_11(&len, it->m_Length);
            CGXDLMSVariant_copy_4(&data, CGXDLMSIp4SetupIpOption_GetData(it));

            if ((ret = GXHelpers_SetData(&bb, DLMS_DATA_TYPE_UINT8, &type)) != 0 ||
                (ret = GXHelpers_SetData(&bb, DLMS_DATA_TYPE_UINT8, &len)) != 0 ||
                (ret = GXHelpers_SetData(&bb, DLMS_DATA_TYPE_OCTET_STRING, &data)) != 0)
            {
                CGXDLMSVariant_d(&type);
                CGXDLMSVariant_d(&len);
                CGXDLMSVariant_d(&data);

                CGXByteBuffer_d(&bb);
                return ret;
            }
        }

        CGXDLMSValueEventArg_SetValue_2(e, &bb);

        CGXDLMSVariant_d(&type);
        CGXDLMSVariant_d(&len);
        CGXDLMSVariant_d(&data);

        CGXByteBuffer_d(&bb);
    }
    else if (e_index == 6)
    {
        //e.SetValue(m_SubnetMask);
        CGXDLMSValueEventArg_SetValue_5(e, p->m_SubnetMask);
    }
    else if (e_index == 7)
    {
        //e.SetValue(m_GatewayIPAddress);
        CGXDLMSValueEventArg_SetValue_5(e, p->m_GatewayIPAddress);
    }
    else if (e_index == 8)
    {
        //e.SetValue(m_UseDHCP);
        CGXDLMSValueEventArg_SetValue_7(e, p->m_UseDHCP);
    }
    else if (e_index == 9)
    {
        //e.SetValue(m_PrimaryDNSAddress);
        CGXDLMSValueEventArg_SetValue_5(e, p->m_PrimaryDNSAddress);
    }
    else if (e_index == 10)
    {
        //e.SetValue(m_SecondaryDNSAddress);
        CGXDLMSValueEventArg_SetValue_5(e, p->m_SecondaryDNSAddress);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSIp4Setup_SetValue(CGXDLMSIp4Setup* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_STRING)
        {
            //m_DataLinkLayerReference = e.GetValue().ToString();
            String_d(&p->m_DataLinkLayerReference);
            p->m_DataLinkLayerReference = CGXDLMSVariant_ToString(CGXDLMSValueEventArg_GetValue(e));
        }
        else
        {
            //m_DataLinkLayerReference.clear();
            String_clear(&p->m_DataLinkLayerReference);
            GXHelpers_GetLogicalName_1(CGXDLMSValueEventArg_GetValue(e)->st.un.byteArr, &p->m_DataLinkLayerReference);
        }
    }
    else if (e_index == 3)
    {
        long tmp = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));

        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_AddIntAsString(&bb, tmp & 0xFF);
        CGXByteBuffer_SetInt8(&bb, '.');
        CGXByteBuffer_AddIntAsString(&bb, (tmp >> 8) & 0xFF);
        CGXByteBuffer_SetInt8(&bb, '.');
        CGXByteBuffer_AddIntAsString(&bb, (tmp >> 16) & 0xFF);
        CGXByteBuffer_SetInt8(&bb, '.');
        CGXByteBuffer_AddIntAsString(&bb, (tmp >> 24) & 0xFF);

        String out;
        String_(&out);

        CGXByteBuffer_ToString(&bb, &out);

        String_copy_1(&p->m_IPAddress, &out);

        String_d(&out);
        CGXByteBuffer_d(&bb);
    }
    else if (e_index == 4)
    {
        Vector_clear(&p->m_MulticastIPAddress);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
            //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
            {
                CGXDLMSVariant* it = Vector_at(temp, i);
                //m_MulticastIPAddress.push_back((*it).ToInteger());
                unsigned long tmp = CGXDLMSVariant_ToInteger(it);
                Vector_push_back(&p->m_MulticastIPAddress, &tmp);
            }
        }
    }
    else if (e_index == 5)
    {
        Vector_clear(&p->m_IPOptions);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            Vector *temp = &(((CGXDLMSVariant*) CGXDLMSValueEventArg_GetValue(e))->Arr);
            //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            for (int i = Vector_begin(temp); i != Vector_end(temp); i++)
            {
                CGXDLMSVariant* it = Vector_at(temp, i);

                CGXDLMSIp4SetupIpOption item;
                CGXDLMSIp4SetupIpOption_(&item);

                item.m_Type = (IP_OPTION_TYPE)CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&it->Arr, 0));
                item.m_Length = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&it->Arr, 1));

                CGXByteBuffer tmp;
                CGXByteBuffer_1(&tmp);

                CGXByteBuffer_Set_1(&tmp, ((CGXDLMSVariant*)Vector_at(&it->Arr, 2))->st.un.byteArr, ((CGXDLMSVariant*)Vector_at(&it->Arr, 2))->size);
                CGXDLMSIp4SetupIpOption_SetData(&item, &tmp);

                Vector_push_back(&p->m_IPOptions, &item);

                CGXByteBuffer_d(&tmp);
                CGXDLMSIp4SetupIpOption_d(&item);
            }
        }
    }
    else if (e_index == 6)
    {
        p->m_SubnetMask = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 7)
    {
        p->m_GatewayIPAddress = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 8)
    {
        p->m_UseDHCP = CGXDLMSValueEventArg_GetValue(e)->st.un.boolVal;
    }
    else if (e_index == 9)
    {
        p->m_PrimaryDNSAddress = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 10)
    {
        p->m_SecondaryDNSAddress = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSIp4Setup_d(CGXDLMSIp4Setup* p)
{
    String_d(&p->m_DataLinkLayerReference);
    String_d(&p->m_IPAddress);
    Vector_d(&p->m_MulticastIPAddress);
    Vector_d(&p->m_IPOptions);
    CGXDLMSVariant_d(&p->m_Value);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}
