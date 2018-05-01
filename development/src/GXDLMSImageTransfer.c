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

#include "../include/GXDLMSImageTransfer.h"
#include "../include/GXDLMSClient.h"
#include "../include/Optimize.h"

static void CGXDLMSImageTransfer__(CGXDLMSImageTransfer* p)
{
    p->GetAttributeCount = CGXDLMSImageTransfer_GetAttributeCount;
    p->GetMethodCount = CGXDLMSImageTransfer_GetMethodCount;
    p->GetValue = CGXDLMSImageTransfer_GetValue;
    p->SetValue = CGXDLMSImageTransfer_SetValue;
    p->Invoke = CGXDLMSImageTransfer_Invoke;

    p->d = CGXDLMSImageTransfer_d;
    p->SetDataType = CGXDLMSObject_SetDataType;
    p->GetDataType = CGXDLMSImageTransfer_GetDataType;
    p->GetUIDataType = CGXDLMSObject_GetUIDataType;
    p->GetValues = CGXDLMSImageTransfer_GetValues;
    p->GetAttributeIndexToRead = CGXDLMSImageTransfer_GetAttributeIndexToRead;

    String_(&p->m_ImageTransferredBlocksStatus);
    Vector_(&p->m_ImageActivateInfo, sizeof(CGXDLMSImageActivateInfo*), NULL, NULL); //std::vector<CGXDLMSImageActivateInfo*>
}
//Constructor.
//CGXDLMSImageTransfer::CGXDLMSImageTransfer() : CGXDLMSImageTransfer("0.0.44.0.0.255", 0)
void CGXDLMSImageTransfer_1(CGXDLMSImageTransfer* p)
{
    String t_Str;
    String_3(&t_Str, "0.0.44.0.0.255");

    CGXDLMSImageTransfer_2(p, t_Str, 0);
    String_d(&t_Str);
}

//SN Constructor.
//CGXDLMSImageTransfer::CGXDLMSImageTransfer(std::string ln, unsigned short sn) :
  //  CGXDLMSObject(DLMS_OBJECT_TYPE_IMAGE_TRANSFER, ln, sn)
void CGXDLMSImageTransfer_2(CGXDLMSImageTransfer* p, String ln, unsigned short sn)
{
    CGXDLMSObject_3((CGXDLMSObject*) p, DLMS_OBJECT_TYPE_IMAGE_TRANSFER, &ln, sn);

    CGXDLMSImageTransfer__(p);

    p->m_ImageBlockSize = 200;
    p->m_ImageFirstNotTransferredBlockNumber = 0;
    p->m_ImageTransferEnabled = true;
    p->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_NOT_INITIATED;
}

//LN Constructor.
//CGXDLMSImageTransfer::CGXDLMSImageTransfer(std::string ln) : CGXDLMSImageTransfer(ln, 0)
void CGXDLMSImageTransfer_3(CGXDLMSImageTransfer* p, String ln)
{
    CGXDLMSImageTransfer_2(p, ln, 0);
}

//CGXDLMSImageTransfer::~CGXDLMSImageTransfer()
void CGXDLMSImageTransfer_d(CGXDLMSImageTransfer* p)
{
    // for (std::vector<CGXDLMSImageActivateInfo*>::iterator it = m_ImageActivateInfo.begin();
    //     it != m_ImageActivateInfo.end(); ++it)
    // {
    //     delete *it;
    // }
    // m_ImageActivateInfo.clear();

    for (unsigned int i = Vector_begin(&p->m_ImageActivateInfo); i != Vector_end(&p->m_ImageActivateInfo); ++i)
    {
        CGXDLMSImageActivateInfo** pp = (CGXDLMSImageActivateInfo**) Vector_at(&p->m_ImageActivateInfo, i);

        CGXDLMSImageActivateInfo_d(*pp);
        DLMSPort_free(*pp);
    }
    Vector_clear(&p->m_ImageActivateInfo);

    String_d(&p->m_ImageTransferredBlocksStatus);

    CGXDLMSObject_d((CGXDLMSObject*) p);
}

/**
 * Provides information about the transfer status of each
 * ImageBlock. Each bit in the bit-std::string provides information about
 * one individual ImageBlock.
*/
String* CGXDLMSImageTransfer_GetImageTransferredBlocksStatus(CGXDLMSImageTransfer* p)
{
    return &p->m_ImageTransferredBlocksStatus;
}
void CGXDLMSImageTransfer_SetImageTransferredBlocksStatus(CGXDLMSImageTransfer* p, String value)
{
    String_copy_1(&p->m_ImageTransferredBlocksStatus, &value);
}

Vector* CGXDLMSImageTransfer_GetImageActivateInfo(CGXDLMSImageTransfer* p)
{
    return &p->m_ImageActivateInfo;
}

// Returns amount of attributes.
int CGXDLMSImageTransfer_GetAttributeCount(CGXDLMSImageTransfer* p)
{
    return 7;
}

// Returns amount of methods.
int CGXDLMSImageTransfer_GetMethodCount(CGXDLMSImageTransfer* p)
{
    return 4;
}

void CGXDLMSImageTransfer_GetValues(CGXDLMSImageTransfer* p, Vector* values)
{
    // values.clear();
    // std::string ln;
    // GetLogicalName(ln);
    // values.push_back(ln);
    // values.push_back(CGXDLMSVariant(m_ImageBlockSize).ToString());
    // values.push_back(CGXDLMSVariant(m_ImageTransferredBlocksStatus).ToString());
    // values.push_back(CGXDLMSVariant(m_ImageFirstNotTransferredBlockNumber).ToString());
    // values.push_back(CGXDLMSVariant(m_ImageTransferEnabled).ToString());
    // values.push_back(CGXDLMSVariant(m_ImageTransferStatus).ToString());
    // std::stringstream sb;
    // sb << '[';
    // bool empty = true;
    // for (std::vector<CGXDLMSImageActivateInfo*>::iterator it = m_ImageActivateInfo.begin();
    //     it != m_ImageActivateInfo.end(); ++it)
    // {
    //     if (!empty)
    //     {
    //         sb << ", ";
    //     }
    //     empty = false;
    //     std::string str = (*it)->ToString();
    //     sb.write(str.c_str(), str.size());
    // }
    // sb << ']';
    // values.push_back(sb.str());

    Vector_clear(values);

    Vector_push_back_Str_LN(values, (CGXDLMSObject*) p);

    Vector_push_back_Str_6(values, p->m_ImageBlockSize);

    Vector_push_back_Str_8(values, &p->m_ImageTransferredBlocksStatus);

    Vector_push_back_Str_6(values, p->m_ImageFirstNotTransferredBlockNumber);

    Vector_push_back_Str_7(values, p->m_ImageTransferEnabled);

    Vector_push_back_Str_2(values, p->m_ImageTransferStatus);

    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    //for (std::vector<CGXDLMSImageActivateInfo*>::iterator it = m_ImageActivateInfo.begin();
      //  it != m_ImageActivateInfo.end(); ++it)
    for (unsigned int i = Vector_begin(&p->m_ImageActivateInfo); i != Vector_end(&p->m_ImageActivateInfo); ++i)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;
        CGXDLMSImageActivateInfo** it = Vector_at(&p->m_ImageActivateInfo, i);

        String str = CGXDLMSImageActivateInfo_ToString(*it);
        String_append_3(&sb, &str);

        String_d(&str);
    }
    String_append_1(&sb, "]");
    Vector_push_back(values, &sb);

    String_d(&sb);
}

void CGXDLMSImageTransfer_GetAttributeIndexToRead(CGXDLMSImageTransfer* p, Vector* attributes)
{
    int tmp;
    //LN is static and read only once.
    if (CGXDLMSObject_IsLogicalNameEmpty(p->m_LN))
    {
        tmp = 1;
        Vector_push_back(attributes, &tmp);
    }
    //ImageBlockSize
    if (!CGXDLMSImageTransfer_IsRead(p, 2))
    {
        tmp = 2;
        Vector_push_back(attributes, &tmp);
    }
    //ImageTransferredBlocksStatus
    if (!CGXDLMSImageTransfer_IsRead(p, 3))
    {
        tmp = 3;
        Vector_push_back(attributes, &tmp);
    }
    //ImageFirstNotTransferredBlockNumber
    if (!CGXDLMSImageTransfer_IsRead(p, 4))
    {
        tmp = 4;
        Vector_push_back(attributes, &tmp);
    }
    //ImageTransferEnabled
    if (!CGXDLMSImageTransfer_IsRead(p, 5))
    {
        tmp = 5;
        Vector_push_back(attributes, &tmp);
    }
    //ImageTransferStatus
    if (!CGXDLMSImageTransfer_IsRead(p, 6))
    {
        tmp = 6;
        Vector_push_back(attributes, &tmp);
    }
    //ImageActivateInfo
    if (!CGXDLMSImageTransfer_IsRead(p, 7))
    {
        tmp = 7;
        Vector_push_back(attributes, &tmp);
    }
}

int CGXDLMSImageTransfer_Invoke(CGXDLMSImageTransfer* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    //Image transfer initiate
    if (e_index == 1)
    {
        p->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_NOT_INITIATED;
        p->m_ImageFirstNotTransferredBlockNumber = 0;
        String_copy_2(&p->m_ImageTransferredBlocksStatus, "");

        String imageIdentifier;
        String_(&imageIdentifier);

        //imageIdentifier.append(e.GetParameters().Arr[0].byteArr, e.GetParameters().Arr[0].byteArr + e.GetParameters().Arr[0].GetSize());
        String_append_2(&imageIdentifier, ((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 0))->st.un.byteArr,
                        CGXDLMSVariant_GetSize_1((CGXDLMSVariant*) Vector_at(&CGXDLMSValueEventArg_GetParameters(e)->Arr, 0)));
        //int ImageSize = e.GetParameters().Arr[1].ToInteger();
        int ImageSize = CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1));
        p->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_INITIATED;

        CGXDLMSImageActivateInfo *item = NULL;
        //for (std::vector<CGXDLMSImageActivateInfo*>::iterator it = m_ImageActivateInfo.begin(); it != m_ImageActivateInfo.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_ImageActivateInfo); i != Vector_end(&p->m_ImageActivateInfo); ++i)
        {
            CGXDLMSImageActivateInfo** it = (CGXDLMSImageActivateInfo**) Vector_at(&p->m_ImageActivateInfo, i);
            
            // if ((*it)->GetIdentification() == imageIdentifier)
            // {
            //     item = *it;
            //     break;
            // }
            String id = CGXDLMSImageActivateInfo_GetIdentification(*it);

            if (String_compare(&id, String_c_str(&imageIdentifier)) == 0)
            {
                item = *it;

                String_d(&id);
                break;
            }

            String_d(&id);
        }
        if (item == NULL)
        {
            //item = new CGXDLMSImageActivateInfo();
            item = DLMSPort_malloc(sizeof(CGXDLMSImageActivateInfo));
            CGXDLMSImageActivateInfo_1(item);
            //m_ImageActivateInfo.push_back(item);
            Vector_push_back(&p->m_ImageActivateInfo, &item);
        }
        item->m_Size = ImageSize;
        CGXDLMSImageActivateInfo_SetIdentification(item, imageIdentifier);
        int cnt = ImageSize / p->m_ImageBlockSize;
        if (ImageSize % p->m_ImageBlockSize != 0)
        {
            ++cnt;
        }
        for (int pos = 0; pos < cnt; ++pos)
        {
            char tmp[2] = {'0', '\0'};
            String_append_1(&p->m_ImageTransferredBlocksStatus, tmp);
        }

        String_d(&imageIdentifier);
        return 0;
    }
    //Image block transfer
    else if (e_index == 2)
    {
        //int imageIndex = e.GetParameters().Arr[0].ToInteger();
        int imageIndex = CGXDLMSVariant_ToInteger((CGXDLMSVariant*) Vector_at(&(CGXDLMSValueEventArg_GetParameters(e)->Arr), 1));
        *String_at(&p->m_ImageTransferredBlocksStatus, imageIndex) = '1';
        p->m_ImageFirstNotTransferredBlockNumber = imageIndex + 1;
        p->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_INITIATED;
        return 0;
    }
    //Image verify
    else if (e_index == 3)
    {
        p->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_VERIFICATION_SUCCESSFUL;
        return 0;
    }
    //Image activate.
    else if (e_index == 4)
    {
        p->m_ImageTransferStatus = DLMS_IMAGE_TRANSFER_STATUS_ACTIVATION_SUCCESSFUL;
        return 0;
    }
    else
    {
        e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        return 0;
    }
    return 0;
}

int CGXDLMSImageTransfer_GetDataType(CGXDLMSImageTransfer* p, int index, DLMS_DATA_TYPE* type)
{
    if (index == 1)
    {
        *type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        *type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        *type = DLMS_DATA_TYPE_BIT_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        *type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        *type = DLMS_DATA_TYPE_BOOLEAN;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        *type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        *type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSImageTransfer_GetValue(CGXDLMSImageTransfer* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    //CGXDLMSVariant tmp;

    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_GetValue_1((CGXDLMSObject*) p, e);
    }
    if (e_index == 2)
    {
        //e.SetValue(GetImageBlockSize());
        CGXDLMSValueEventArg_SetValue_6(e, p->m_ImageBlockSize);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 3)
    {
        //e.SetValue(m_ImageTransferredBlocksStatus);
        CGXDLMSValueEventArg_SetValue_8(e, &p->m_ImageTransferredBlocksStatus);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 4)
    {
        //e.SetValue(m_ImageFirstNotTransferredBlockNumber);
        CGXDLMSValueEventArg_SetValue_6(e, p->m_ImageFirstNotTransferredBlockNumber);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 5)
    {
        //e.SetValue(m_ImageTransferEnabled);
        CGXDLMSValueEventArg_SetValue_7(e, p->m_ImageTransferEnabled);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 6)
    {
        //e.SetValue(m_ImageTransferStatus);
        CGXDLMSValueEventArg_SetValue_3(e, p->m_ImageTransferStatus);
        return DLMS_ERROR_CODE_OK;
    }
    if (e_index == 7)
    {
        e->m_ByteArray = true;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_ARRAY);
        GXHelpers_SetObjectCount((unsigned long)Vector_size(&p->m_ImageActivateInfo), &data); //Count
        int ret;

        CGXDLMSVariant size;
        CGXDLMSVariant_1(&size);

        //for (std::vector<CGXDLMSImageActivateInfo*>::iterator it = m_ImageActivateInfo.begin(); it != m_ImageActivateInfo.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_ImageActivateInfo); i != Vector_end(&p->m_ImageActivateInfo); ++i)
        {
            CGXDLMSImageActivateInfo** it = (CGXDLMSImageActivateInfo**) Vector_at(&p->m_ImageActivateInfo, i);

            CGXByteBuffer_SetUInt8_1(&data, DLMS_DATA_TYPE_STRUCTURE);
            CGXByteBuffer_SetUInt8_1(&data, 3);//Item count.
            //size = (*it)->GetSize();
            CGXDLMSVariant_copy_13(&size, (*it)->m_Size);

            CGXDLMSVariant id, signature;
            
            //CGXDLMSVariant id((unsigned char*)(*it)->GetIdentification().c_str(), (int)(*it)->GetIdentification().size(), DLMS_DATA_TYPE_OCTET_STRING);
            //CGXDLMSVariant signature((unsigned char*)(*it)->GetSignature().c_str(), (int)(*it)->GetSignature().size(), DLMS_DATA_TYPE_OCTET_STRING);
            
            String str_id = CGXDLMSImageActivateInfo_GetIdentification(*it);
            String str_signature = CGXDLMSImageActivateInfo_GetSignature(*it);
            CGXDLMSVariant_18(&id, (unsigned char*)String_c_str(&str_id), (int)String_size(&str_id), DLMS_DATA_TYPE_OCTET_STRING);
            CGXDLMSVariant_18(&signature, (unsigned char*)String_c_str(&str_signature), (int)String_size(&str_signature), DLMS_DATA_TYPE_OCTET_STRING);

            String_d(&str_id);
            String_d(&str_signature);

            if ((ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_UINT32, &size)) != 0 ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &id)) != 0 ||
                (ret = GXHelpers_SetData(&data, DLMS_DATA_TYPE_OCTET_STRING, &signature)) != 0)
            {
                CGXDLMSVariant_d(&id);
                CGXDLMSVariant_d(&signature);
                CGXDLMSVariant_d(&size);
                CGXByteBuffer_d(&data);
                return ret;
            }

            CGXDLMSVariant_d(&id);
            CGXDLMSVariant_d(&signature);
        }
        //e.SetValue(data);

        CGXDLMSValueEventArg_SetValue_2(e, &data);

        CGXDLMSVariant_d(&size);
        CGXByteBuffer_d(&data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSImageTransfer_SetValue(CGXDLMSImageTransfer* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e)
{
    int e_index = e->m_Index;

    if (e_index == 1)
    {
        return CGXDLMSObject_SetLogicalName((CGXDLMSObject*) p, CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 2)
    {
        p->m_ImageBlockSize = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 3)
    {
        String_d(&p->m_ImageTransferredBlocksStatus);
        p->m_ImageTransferredBlocksStatus = CGXDLMSVariant_ToString(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 4)
    {
        p->m_ImageFirstNotTransferredBlockNumber = CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 5)
    {
        p->m_ImageTransferEnabled = CGXDLMSValueEventArg_GetValue(e)->st.un.boolVal;
    }
    else if (e_index == 6)
    {
        p->m_ImageTransferStatus = (DLMS_IMAGE_TRANSFER_STATUS)CGXDLMSVariant_ToInteger(CGXDLMSValueEventArg_GetValue(e));
    }
    else if (e_index == 7)
    {
        //for (std::vector<CGXDLMSImageActivateInfo*>::iterator it = m_ImageActivateInfo.begin();
          //  it != m_ImageActivateInfo.end(); ++it)
        for (unsigned int i = Vector_begin(&p->m_ImageActivateInfo); i != Vector_end(&p->m_ImageActivateInfo); ++i)
        {
            //delete *it;
            CGXDLMSImageActivateInfo** pp = (CGXDLMSImageActivateInfo**) Vector_at(&p->m_ImageActivateInfo, i);
            DLMSPort_free(*pp);
        }
        Vector_clear(&p->m_ImageActivateInfo);
        if (CGXDLMSValueEventArg_GetValue(e)->st.vt == DLMS_DATA_TYPE_ARRAY)
        {
            CGXDLMSVariant tmp;
            CGXDLMSVariant_1(&tmp);

            //for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            Vector* temp = &(((CGXDLMSVariant*)CGXDLMSValueEventArg_GetValue(e))->Arr);
            for (unsigned int i = Vector_begin(temp); i != Vector_end(temp); ++i)
            {
                Vector it = ((CGXDLMSVariant*)Vector_at(temp, i))->Arr;
                // CGXDLMSImageActivateInfo* item = new CGXDLMSImageActivateInfo();
                // item->SetSize((*it).Arr[0].ToInteger());
                // CGXDLMSClient::ChangeType((*it).Arr[1], DLMS_DATA_TYPE_STRING, tmp);
                // item->SetIdentification(tmp.ToString());
                // CGXDLMSClient::ChangeType((*it).Arr[2], DLMS_DATA_TYPE_STRING, tmp);
                // item->SetSignature(tmp.ToString());
                // m_ImageActivateInfo.push_back(item);
                CGXDLMSImageActivateInfo* item = DLMSPort_malloc(sizeof(CGXDLMSImageActivateInfo));
                CGXDLMSImageActivateInfo_1(item);

                item->m_Size = CGXDLMSVariant_ToInteger(Vector_at(&it, 0));
                CGXDLMSClient_ChangeType_2(Vector_at(&it, 1), DLMS_DATA_TYPE_STRING, &tmp);
                CGXDLMSImageActivateInfo_SetIdentification(item, CGXDLMSVariant_ToString(&tmp));
                CGXDLMSClient_ChangeType_2(Vector_at(&it, 2), DLMS_DATA_TYPE_STRING, &tmp);
                CGXDLMSImageActivateInfo_SetSignature(item, CGXDLMSVariant_ToString(&tmp));
                Vector_push_back(&p->m_ImageActivateInfo, &item);
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
