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

#include "../include/enums.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXHelpers.h"
#include "../include/GXAPDU.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXSecure.h"
#include "../include/GXSerialNumberCounter.h"
#include "../include/GXDLMSLNParameters.h"
#include "../include/GXDLMSSNParameters.h"

#include "../include/Vector.h"
#include "../include/Pair.h"

static int CGXDLMSClient_Read(
    CGXDLMSClient *p,
    CGXDLMSVariant* name,
    DLMS_OBJECT_TYPE objectType,
    int attributeOrdinal,
    CGXByteBuffer* data,
    Vector* reply);

// CGXDLMSClient::CGXDLMSClient(bool UseLogicalNameReferencing,
//     int clientAddress,
//     int serverAddress,
//     //Authentication type.
//     DLMS_AUTHENTICATION authentication,
//     //Password if authentication is used.
//     const char* password,
//     DLMS_INTERFACE_TYPE intefaceType) : m_Settings(false)
void CGXDLMSClient_(
    CGXDLMSClient *p,
    bool UseLogicalNameReferencing,
    int clientAddress,
    int serverAddress,
    //Authentication type.
    DLMS_AUTHENTICATION authentication,
    //Password if authentication is used.
    const char* password,
    DLMS_INTERFACE_TYPE intefaceType)
{
    CGXDLMSSettings_(&p->m_Settings, false);
    p->m_IsAuthenticationRequired = false;
    // m_Settings.SetUseLogicalNameReferencing(UseLogicalNameReferencing);
    // m_Settings.SetClientAddress(clientAddress);
    // m_Settings.SetServerAddress(serverAddress);
    // m_Settings.SetInterfaceType(intefaceType);
    // m_Settings.SetAuthentication(authentication);
    // m_Settings.GetPassword().AddString(password);
    p->m_Settings.m_UseLogicalNameReferencing = UseLogicalNameReferencing;
    p->m_Settings.m_ClientAddress = clientAddress;
    p->m_Settings.m_ServerAddress = serverAddress;
    p->m_Settings.m_InterfaceType = intefaceType;
    p->m_Settings.m_Authentication = authentication;
    CGXByteBuffer_AddString_2(CGXDLMSSettings_GetPassword(&p->m_Settings), password);


    if (UseLogicalNameReferencing)
    {
        CGXDLMSClient_SetProposedConformance(p, (DLMS_CONFORMANCE)(DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_ACTION |
            DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_SET_OR_WRITE |
            DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_GET_OR_READ |
            DLMS_CONFORMANCE_SET | DLMS_CONFORMANCE_SELECTIVE_ACCESS |
            DLMS_CONFORMANCE_ACTION | DLMS_CONFORMANCE_MULTIPLE_REFERENCES |
            DLMS_CONFORMANCE_GET));
    }
    else
    {
        CGXDLMSClient_SetProposedConformance(p, (DLMS_CONFORMANCE)(DLMS_CONFORMANCE_INFORMATION_REPORT |
            DLMS_CONFORMANCE_READ | DLMS_CONFORMANCE_UN_CONFIRMED_WRITE |
            DLMS_CONFORMANCE_WRITE | DLMS_CONFORMANCE_PARAMETERIZED_ACCESS |
            DLMS_CONFORMANCE_MULTIPLE_REFERENCES));
    }
}

void CGXDLMSClient_d(CGXDLMSClient *p)
{
    CGXDLMSSettings_d(&p->m_Settings);
}

DLMS_CONFORMANCE CGXDLMSClient_GetNegotiatedConformance(CGXDLMSClient *p)
{
    return (DLMS_CONFORMANCE)p->m_Settings.m_NegotiatedConformance;
}

void CGXDLMSClient_SetNegotiatedConformance(CGXDLMSClient *p, DLMS_CONFORMANCE value)
{
    p->m_Settings.m_NegotiatedConformance = value;
}


DLMS_CONFORMANCE CGXDLMSClient_GetProposedConformance(CGXDLMSClient *p)
{
    return (DLMS_CONFORMANCE)p->m_Settings.m_ProposedConformance;
}

void CGXDLMSClient_SetProposedConformance(CGXDLMSClient *p, DLMS_CONFORMANCE value)
{
    p->m_Settings.m_ProposedConformance = value;
}

bool CGXDLMSClient_GetUseLogicalNameReferencing(CGXDLMSClient *p)
{
    return p->m_Settings.m_UseLogicalNameReferencing;
}

DLMS_INTERFACE_TYPE CGXDLMSClient_GetInterfaceType(CGXDLMSClient *p)
{
    return p->m_Settings.m_InterfaceType;
}

DLMS_PRIORITY CGXDLMSClient_GetPriority(CGXDLMSClient *p)
{
    return p->m_Settings.m_Priority;
}

void CGXDLMSClient_SetPriority(CGXDLMSClient *p, DLMS_PRIORITY value)
{
    p->m_Settings.m_Priority = value;
}

DLMS_SERVICE_CLASS CGXDLMSClient_GetServiceClass(CGXDLMSClient *p)
{
    return p->m_Settings.m_ServiceClass;
}

void CGXDLMSClient_SetServiceClass(CGXDLMSClient *p, DLMS_SERVICE_CLASS value)
{
    p->m_Settings.m_ServiceClass = value;
}

CGXDLMSLimits* CGXDLMSClient_GetLimits(CGXDLMSClient *p)
{
    return CGXDLMSSettings_GetLimits(&p->m_Settings);
}

// Collection of the objects.
CGXDLMSObjectCollection* CGXDLMSClient_GetObjects(CGXDLMSClient *p)
{
    return CGXDLMSSettings_GetObjects(&p->m_Settings);
}

//int CGXDLMSClient::SNRMRequest(std::vector<CGXByteBuffer>& packets)
int CGXDLMSClient_SNRMRequest(
    CGXDLMSClient *p,
    Vector* packets)
{
    int ret;
    p->m_Settings.m_Connected = false;
    Vector_clear(packets);
    p->m_IsAuthenticationRequired = false;
    // SNRM request is not used in network connections.
    if (p->m_Settings.m_InterfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        return 0;
    }

    CGXByteBuffer data;
    CGXByteBuffer_2(&data, 25);

    // FromatID
    CGXByteBuffer_SetUInt8_1(&data, 0x81);
    // GroupID
    CGXByteBuffer_SetUInt8_1(&data, 0x80);
    // Length is updated later.
    CGXByteBuffer_SetUInt8_1(&data, 0);
    // If custom HDLC parameters are used.
    //CGXDLMSClient_GetLimits(p);
    
    if (DEFAULT_MAX_INFO_TX != CGXDLMSClient_GetLimits(p)->m_MaxInfoTX)
    {
        CGXByteBuffer_SetUInt8_1(&data, HDLC_INFO_MAX_INFO_TX);
        CGXDLMS_AppendHdlcParameter(&data, CGXDLMSClient_GetLimits(p)->m_MaxInfoTX);
    }
    if (DEFAULT_MAX_INFO_RX != CGXDLMSClient_GetLimits(p)->m_MaxInfoRX)
    {
        CGXByteBuffer_SetUInt8_1(&data, HDLC_INFO_MAX_INFO_RX);
        CGXDLMS_AppendHdlcParameter(&data, CGXDLMSClient_GetLimits(p)->m_MaxInfoRX);
    }
    if (DEFAULT_WINDOWS_SIZE_TX != CGXDLMSClient_GetLimits(p)->m_WindowSizeRX)
    {
        CGXByteBuffer_SetUInt8_1(&data, HDLC_INFO_WINDOW_SIZE_TX);
        CGXByteBuffer_SetUInt8_1(&data, 4);
        CGXByteBuffer_SetUInt32(&data, CGXDLMSClient_GetLimits(p)->m_WindowSizeRX);
    }
    if (DEFAULT_WINDOWS_SIZE_RX != CGXDLMSClient_GetLimits(p)->m_WindowSizeTX)
    {
        CGXByteBuffer_SetUInt8_1(&data, HDLC_INFO_WINDOW_SIZE_RX);
        CGXByteBuffer_SetUInt8_1(&data, 4);
        CGXByteBuffer_SetUInt32(&data, CGXDLMSClient_GetLimits(p)->m_WindowSizeTX);
    }
    // If default HDLC parameters are not used.
    if (data.m_Size != 3)
    {
        // Length.
        CGXByteBuffer_SetUInt8_2(&data, 2, (unsigned char)(data.m_Size - 3));
    }
    else
    {
        CGXByteBuffer_Clear(&data);
    }
    CGXDLMSSettings_ResetFrameSequence(&p->m_Settings);

    CGXByteBuffer reply;
    CGXByteBuffer_1(&reply);

    ret = CGXDLMS_GetHdlcFrame(&p->m_Settings, DLMS_COMMAND_SNRM, &data, &reply);    
    Vector_push_back(packets, &reply);

    CGXByteBuffer_d(&reply);
    CGXByteBuffer_d(&data);
    return ret;
}

// SN referencing
static int CGXDLMSClient_ParseSNObjects(CGXDLMSClient *p, CGXByteBuffer* buff, bool onlyKnownObjects)
{
    int ret;
    //Get array tag.
    unsigned char ch;
    unsigned long cnt;
    //Check that data is in the array
    // Get array tag.
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    if (ch != 1)
    {
        return DLMS_ERROR_CODE_INVALID_RESPONSE;
    }
    //get object count
    if ((ret = GXHelpers_GetObjectCount(buff, &cnt)) != 0)
    {
        return ret;
    }

    CGXDataInfo info;
    CGXDataInfo_(&info);

    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    for (unsigned long objPos = 0; objPos != cnt; ++objPos)
    {
        CGXDataInfo_Clear(&info);
        if ((ret = GXHelpers_GetData(buff, &info, &value)) != 0)
        {
            CGXDLMSVariant_d(&value);
            return ret;
        }
        if (value.st.vt != DLMS_DATA_TYPE_STRUCTURE || Vector_size(&value.Arr) != 4)
        {
            CGXDLMSVariant_d(&value);
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        if (((CGXDLMSVariant*)Vector_at(&value.Arr, 0))->st.vt != DLMS_DATA_TYPE_INT16 ||
            ((CGXDLMSVariant*)Vector_at(&value.Arr, 1))->st.vt != DLMS_DATA_TYPE_UINT16 ||
            ((CGXDLMSVariant*)Vector_at(&value.Arr, 2))->st.vt != DLMS_DATA_TYPE_UINT8 ||
            ((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->st.vt != DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXDLMSVariant_d(&value);
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        
        short sn = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&value.Arr, 0));
        unsigned short class_id = (unsigned short)CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&value.Arr, 1));
        unsigned char version = (unsigned char)CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&value.Arr, 2));

        CGXDLMSVariant ln;
        CGXDLMSVariant_2(&ln, (CGXDLMSVariant*)Vector_at(&value.Arr, 3));

        CGXDLMSObject* pObj = CGXDLMSObjectFactory_CreateObject_1((DLMS_OBJECT_TYPE)class_id);
        if (pObj != NULL)
        {
            pObj->m_SN = sn;
            pObj->m_Version = version;
            int cnt = CGXDLMSVariant_GetSize_1(&ln);
            assert(cnt == 6);
            CGXDLMSObject_SetLogicalName(pObj, &ln);
            CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &pObj);
        }

        CGXDLMSVariant_d(&ln);
    }

    CGXDLMSVariant_d(&value);
    return 0;
}

/**
* Parse LN objects.
*
* buff
*            Byte stream where objects are parsed.
* onlyKnownObjects
*            Only known objects are parsed.
* @return Collection of COSEM objects.
*/
static int CGXDLMSClient_ParseLNObjects(
    CGXDLMSClient *p,
    CGXByteBuffer* buff,
    bool onlyKnownObjects)
{
    int ret;
    unsigned long cnt;
    unsigned char ch;

    CGXDataInfo info;
    CGXDataInfo_(&info);

    // Get array tag.
    if ((ret = CGXByteBuffer_GetUInt8_1(buff, &ch)) != 0)
    {
        return ret;
    }
    // Check that data is in the array
    if (ch != 0x01)
    {
        //Invalid response.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    if ((ret = GXHelpers_GetObjectCount(buff, &cnt)) != 0)
    {
        CGXDLMSVariant_d(&value);
        return ret;
    }
    for (unsigned long pos = 0; pos != cnt; ++pos)
    {
        // Some meters give wrong item count.
        // This fix Iskraemeco (MT-880) bug.
        if (buff->m_Position == buff->m_Size)
        {
            break;
        }
        info.m_Type = DLMS_DATA_TYPE_NONE;
        info.m_Index = 0;
        info.m_Count = 0;
        if ((ret = GXHelpers_GetData(buff, &info, &value)) != 0)
        {
            CGXDLMSVariant_d(&value);
            return ret;
        }
        if (Vector_size(&value.Arr) != 4)
        {
            //Invalid structure format.
            CGXDLMSVariant_d(&value);
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        //(CGXDLMSVariant*)Vector_at(&value.Arr, 0);
        //CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&value.Arr, 0));
        int classID = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&value.Arr, 0)) & 0xFFFF;
        if (classID > 0)
        {
            CGXDLMSObject* pObj = CGXDLMSObjectFactory_CreateObject_1((DLMS_OBJECT_TYPE)classID);
            if (pObj != NULL)
            {
                if (value.st.vt != DLMS_DATA_TYPE_STRUCTURE || Vector_size(&value.Arr) != 4)
                {
                    CGXDLMSVariant_d(&value);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if (((CGXDLMSVariant*)Vector_at(&value.Arr, 0))->st.vt != DLMS_DATA_TYPE_UINT16)
                {
                    CGXDLMSVariant_d(&value);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if (((CGXDLMSVariant*)Vector_at(&value.Arr, 1))->st.vt != DLMS_DATA_TYPE_UINT8)
                {
                    CGXDLMSVariant_d(&value);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                unsigned char version = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&value.Arr, 1));
                if (((CGXDLMSVariant*)Vector_at(&value.Arr, 2))->st.vt != DLMS_DATA_TYPE_OCTET_STRING)
                {
                    CGXDLMSVariant_d(&value);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }

                CGXDLMSVariant ln;
                CGXDLMSVariant_2(&ln, (CGXDLMSVariant*)Vector_at(&value.Arr, 2));

                //Get Access rights...
                if (((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->st.vt != DLMS_DATA_TYPE_STRUCTURE || Vector_size(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr) != 2)
                {
                    CGXDLMSVariant_d(&ln);
                    CGXDLMSVariant_d(&value);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                pObj->m_Version = version;
                int cnt;
                // attribute_access_descriptor Start
                if (((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->st.vt != DLMS_DATA_TYPE_ARRAY)
                {
                    //delete pObj;
                    pObj->d(pObj);
                    DLMSPort_free(pObj);

                    CGXDLMSVariant_d(&ln);
                    CGXDLMSVariant_d(&value);
                    return DLMS_ERROR_CODE_INVALID_PARAMETER;
                }
                if (Vector_size(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr) == 2)
                {
                    for (unsigned int pos = 0; pos != Vector_size(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr); ++pos)
                    {
                        if (((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->st.vt != DLMS_DATA_TYPE_STRUCTURE ||
                            Vector_size(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->Arr) != 3)
                        {
                            //delete pObj;
                            pObj->d(pObj);
                            DLMSPort_free(pObj);

                            CGXDLMSVariant_d(&ln);
                            return DLMS_ERROR_CODE_INVALID_PARAMETER;
                        }
                        //int id = value.Arr[3].Arr[0].Arr[pos].Arr[0].ToInteger();
                        int id = CGXDLMSVariant_ToInteger(((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->Arr, 0)));
                        //Get access_mode
                        DLMS_DATA_TYPE tp = ((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->Arr, 1))->st.vt;
                        if (tp != DLMS_DATA_TYPE_ENUM)
                        {
                            //delete pObj;
                            pObj->d(pObj);
                            DLMSPort_free(pObj);

                            CGXDLMSVariant_d(&ln);
                            CGXDLMSVariant_d(&value);
                            return DLMS_ERROR_CODE_INVALID_PARAMETER;
                        }
                        CGXDLMSObject_SetAccess(pObj, id, (DLMS_ACCESS_MODE)CGXDLMSVariant_ToInteger(((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->Arr, 1))));
                        //Get access_selectors
                        if (((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->Arr, 2))->st.vt == DLMS_DATA_TYPE_ARRAY)
                        {
                            //int cnt2 = (unsigned long)value.Arr[3].Arr[0].Arr[pos].Arr[2].Arr.size();
                            int cnt2 = Vector_size(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->Arr, 2))->Arr);
                            for (int pos2 = 0; pos2 != cnt2; ++pos2)
                            {
                                //Get access_mode
                            }
                        }
                        else if (((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 0))->Arr, pos))->Arr, 2))->st.vt != DLMS_DATA_TYPE_NONE)
                        {
                            //delete pObj;
                            pObj->d(pObj);
                            DLMSPort_free(pObj);

                            CGXDLMSVariant_d(&ln);
                            CGXDLMSVariant_d(&value);
                            return DLMS_ERROR_CODE_INVALID_PARAMETER;
                        }
                    }
                    // attribute_access_descriptor End
                    // method_access_item Start
                    if (((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 1))->st.vt != DLMS_DATA_TYPE_ARRAY)
                    {
                        //delete pObj;
                        pObj->d(pObj);
                        DLMSPort_free(pObj);

                        CGXDLMSVariant_d(&ln);
                        CGXDLMSVariant_d(&value);
                        return DLMS_ERROR_CODE_INVALID_PARAMETER;
                    }
                    for (unsigned int pos = 0; pos != Vector_size(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 1))->Arr); ++pos)
                    {
                        //CGXDLMSVariant tmp = value.Arr[3].Arr[1].Arr[pos];
                        CGXDLMSVariant tmp;
                        CGXDLMSVariant_2(&tmp, (CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&((CGXDLMSVariant*)Vector_at(&value.Arr, 3))->Arr, 1))->Arr, pos));

                        if (tmp.st.vt != DLMS_DATA_TYPE_STRUCTURE ||
                            Vector_size(&tmp.Arr) != 2)
                        {
                            //delete pObj;
                            pObj->d(pObj);
                            DLMSPort_free(pObj);

                            CGXDLMSVariant_d(&tmp);
                            CGXDLMSVariant_d(&ln);
                            CGXDLMSVariant_d(&value);
                            return DLMS_ERROR_CODE_INVALID_PARAMETER;
                        }
                        //int id = tmp.Arr[0].ToInteger();
                        int id = CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&tmp.Arr, 0));
                        //Get access_mode
                        //In version 0 data type is boolean.
                        if (((CGXDLMSVariant*)Vector_at(&tmp.Arr, 1))->st.vt != DLMS_DATA_TYPE_ENUM && ((CGXDLMSVariant*)Vector_at(&tmp.Arr, 1))->st.vt != DLMS_DATA_TYPE_BOOLEAN)
                        {
                            //delete pObj;
                            pObj->d(pObj);
                            DLMSPort_free(pObj);

                            CGXDLMSVariant_d(&tmp);
                            CGXDLMSVariant_d(&ln);
                            CGXDLMSVariant_d(&value);
                            return DLMS_ERROR_CODE_INVALID_PARAMETER;
                        }
                        CGXDLMSObject_SetMethodAccess(pObj, id, (DLMS_METHOD_ACCESS_MODE)CGXDLMSVariant_ToInteger((CGXDLMSVariant*)Vector_at(&tmp.Arr, 1)));

                        CGXDLMSVariant_d(&tmp);
                    }
                }
                // method_access_item End
                cnt = CGXDLMSVariant_GetSize_1(&ln);
                assert(cnt == 6);
                if ((ret = CGXDLMSObject_SetLogicalName(pObj, &ln)) != 0)
                {
                    CGXDLMSVariant_d(&ln);
                    CGXDLMSVariant_d(&value);
                    return ret;
                }
                CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &pObj);

                CGXDLMSVariant_d(&ln);
            }
        }
    }

    CGXDLMSVariant_d(&value);
    return 0;
}

int CGXDLMSClient_ParseObjects(
    CGXDLMSClient *p,
    CGXByteBuffer* data,
    bool onlyKnownObjects)
{
    int ret;
    //m_Settings.GetObjects().Free();
    CGXDLMSObjectCollection_Free(CGXDLMSSettings_GetObjects(&p->m_Settings));
    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        if ((ret = CGXDLMSClient_ParseLNObjects(p, data, onlyKnownObjects)) != 0)    
        {
            return ret;
        }
    }
    else
    {
        if ((ret = CGXDLMSClient_ParseSNObjects(p, data, onlyKnownObjects)) != 0)    
        {
            return ret;
        }
    }
    return 0;
}

int CGXDLMSClient_UpdateValue(
    CGXDLMSClient *p,
    CGXDLMSObject* target,
    int attributeIndex,
    CGXDLMSVariant* value)
{
    int ret;
    if (value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        DLMS_DATA_TYPE type;
        if ((ret = target->GetUIDataType(target, attributeIndex, &type)) != 0)
        {
            return ret;
        }
        if (type == DLMS_DATA_TYPE_DATETIME && CGXDLMSVariant_GetSize_1(value) == 5)
        {
            type = DLMS_DATA_TYPE_DATE;
            CGXDLMSObject_SetUIDataType(target, attributeIndex, type);
        }
        if (type != DLMS_DATA_TYPE_NONE)
        {
            if ((ret = CGXDLMSClient_ChangeType_2(value, type, value)) != 0)
            {
                return ret;
            }
        }
    }

    CGXDLMSValueEventArg e;
    CGXDLMSValueEventArg_1(&e, NULL, target, attributeIndex);

    CGXDLMSValueEventArg_SetValue(&e, value);

    ret = target->SetValue(target, &p->m_Settings, &e);

    CGXDLMSValueEventArg_d(&e);
    return ret;
}

int CGXDLMSClient_GetValue(
    CGXDLMSClient *p,
    CGXByteBuffer* data,
    CGXDLMSVariant* value)
{
    CGXDataInfo info;
    CGXDataInfo_(&info);

    return GXHelpers_GetData(data, &info, value);
}


int CGXDLMSClient_ChangeType_2(
    CGXDLMSVariant* value,
    DLMS_DATA_TYPE type,
    CGXDLMSVariant* newValue)
{
    if (value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        CGXByteBuffer tmp;
        CGXByteBuffer_1(&tmp);

        CGXByteBuffer_Set_1(&tmp, value->st.un.byteArr, CGXDLMSVariant_GetSize_1(value));

        int ret = CGXDLMSClient_ChangeType_1(&tmp, type, newValue);

        CGXByteBuffer_d(&tmp);
        return ret;
    }
    else
    {
        CGXDLMSVariant_copy_1(newValue, value);
    }
    return 0;
}

int CGXDLMSClient_ChangeType_1(
    CGXByteBuffer* value,
    DLMS_DATA_TYPE type,
    CGXDLMSVariant* newValue)
{
    int ret;

    CGXDataInfo info;
    CGXDataInfo_(&info);

    CGXDLMSVariant_Clear(newValue);
    if (value->m_Size == 0)
    {
        return 0;
    }
    if (type == DLMS_DATA_TYPE_NONE)
    {
        //newValue = value.ToHexString();
        String out = CGXByteBuffer_ToHexString(value);

        CGXDLMSVariant_copy_2(newValue, out);

        String_d(&out);
    }
    if (value->m_Size == 0 && (type == DLMS_DATA_TYPE_STRING || type == DLMS_DATA_TYPE_OCTET_STRING))
    {
        //newValue = "";
        CGXDLMSVariant_copy_3(newValue, "");

        return 0;
    }
    info.m_Type = type;
    if ((ret = GXHelpers_GetData(value, &info, newValue)) != 0)    
    {
        return ret;
    }
    if (!info.m_Compleate)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    if (type == DLMS_DATA_TYPE_OCTET_STRING && newValue->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        int size = newValue->size;

        String str;
        String_(&str);

        if (size == 0)
        {
            //str = "";
            String_copy_2(&str, "");
        }
        else
        {
            CGXByteBuffer bcd;
            CGXByteBuffer_2(&bcd, size * 4);

            for (int pos = 0; pos != size; ++pos)
            {
                CGXByteBuffer_AddIntAsString(&bcd, newValue->st.un.byteArr[pos]);
                CGXByteBuffer_SetUInt8_1(&bcd, '.');
            }
            //Remove last dot.
            if (bcd.m_Size != 0)
            {
                CGXByteBuffer_SetSize(&bcd, bcd.m_Size - 1);
            }
            CGXByteBuffer_ToString(&bcd, &str);
        }
        //newValue = str;
        CGXDLMSVariant_copy_2(newValue, str);

        String_d(&str);
    }
    return ret;
}

int CGXDLMSClient_ParseUAResponse(
    CGXDLMSClient *p,
    CGXByteBuffer* data)
{
    return CGXDLMS_ParseSnrmUaResponse(data, CGXDLMSSettings_GetLimits(&p->m_Settings));
}

//int CGXDLMSClient::AARQRequest(std::vector<CGXByteBuffer>& packets)
int CGXDLMSClient_AARQRequest(
    CGXDLMSClient *p,
    Vector* packets)
{
    p->m_Settings.m_BlockIndex = 1;
    p->m_Settings.m_NegotiatedConformance = (DLMS_CONFORMANCE)0;
    Vector_clear(packets);
    int ret = CGXDLMS_CheckInit(&p->m_Settings);    
    if (ret != 0)
    {
        return ret;
    }
    CGXByteBuffer_Clear(CGXDLMSSettings_GetStoCChallenge(&p->m_Settings));
    // If authentication or ciphering is used.
    if (p->m_Settings.m_Authentication > DLMS_AUTHENTICATION_LOW)
    {
        CGXByteBuffer challenge;
        CGXByteBuffer_1(&challenge);

        if ((ret = CGXSecure_GenerateChallenge(p->m_Settings.m_Authentication, &challenge)) != 0)
        {
            CGXByteBuffer_d(&challenge);
            return ret;
        }
        CGXDLMSSettings_SetCtoSChallenge(&p->m_Settings, &challenge);

        CGXByteBuffer_d(&challenge);
    }
    else
    {
        CGXByteBuffer_Clear(CGXDLMSSettings_GetCtoSChallenge(&p->m_Settings));
    }

    CGXByteBuffer buff;
    CGXByteBuffer_2(&buff, 20);

    if ((ret = CGXAPDU_GenerateAarq(&p->m_Settings, p->m_Settings.m_Cipher, NULL, &buff)) != 0)
    {
        CGXByteBuffer_d(&buff);
        return ret;
    }
    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        CGXDLMSLNParameters pa;        
        CGXDLMSLNParameters_(&pa, &p->m_Settings, 0, DLMS_COMMAND_AARQ, 0, &buff, NULL, 0xff);

        ret = CGXDLMS_GetLnMessages(&pa, packets);

        //CGXDLMSLNParameters_d(&pa);
    }
    else
    {
        CGXDLMSSNParameters pa;
        CGXDLMSSNParameters_(&pa, &p->m_Settings, DLMS_COMMAND_AARQ, 0, 0, NULL, &buff);

        ret = CGXDLMS_GetSnMessages(&pa, packets);

        //CGXDLMSSNParameters_d(&pa);
    }

    CGXByteBuffer_d(&buff);
    return ret;
}

int CGXDLMSClient_ParseAAREResponse(
    CGXDLMSClient *p,
    CGXByteBuffer* reply)
{
    int ret;
    DLMS_SOURCE_DIAGNOSTIC sd;
    DLMS_ASSOCIATION_RESULT result;

    if ((ret = CGXAPDU_ParsePDU(&p->m_Settings, p->m_Settings.m_Cipher,
                                reply, &result, &sd)) != 0)
    {
        return ret;
    }
    p->m_IsAuthenticationRequired = (DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED == sd);
    if (p->m_Settings.m_DlmsVersionNumber != 6)
    {
        //Invalid DLMS version number.
        return DLMS_ERROR_CODE_INVALID_VERSION_NUMBER;
    }
    p->m_Settings.m_Connected = true;
    return 0;
}

bool CGXDLMSClient_IsAuthenticationRequired(CGXDLMSClient *p)
{
    return p->m_IsAuthenticationRequired;
}

//int CGXDLMSClient::GetApplicationAssociationRequest(
  //  std::vector<CGXByteBuffer>& packets)
int CGXDLMSClient_GetApplicationAssociationRequest(
    CGXDLMSClient *p,
    Vector* packets)
{
    int ret;
    Vector_clear(packets);
    if (p->m_Settings.m_Authentication != DLMS_AUTHENTICATION_HIGH_ECDSA &&
        p->m_Settings.m_Authentication != DLMS_AUTHENTICATION_HIGH_GMAC &&
        CGXDLMSSettings_GetPassword(&p->m_Settings)->m_Size == 0)
    {
        //Password is invalid.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    p->m_Settings.m_BlockIndex = 1;;

    CGXByteBuffer pw, challenge;
    CGXByteBuffer_1(&pw);
    CGXByteBuffer_1(&challenge);

    if (p->m_Settings.m_Authentication == DLMS_AUTHENTICATION_HIGH_GMAC)
    {
        //pw = *((CGXByteBuffer*)CGXCipher_GetSystemTitle(p->m_Settings.m_Cipher));
        CGXByteBuffer_copy(&pw, (CGXByteBuffer*)CGXCipher_GetSystemTitle(p->m_Settings.m_Cipher));
    }
    else
    {
        //pw = *((CGXByteBuffer*)CGXDLMSSettings_GetPassword(&p->m_Settings));
        CGXByteBuffer_copy(&pw, (CGXByteBuffer*)CGXDLMSSettings_GetPassword(&p->m_Settings));
    }
    long ic = 0;
    if (p->m_Settings.m_Cipher != NULL)
    {
        ic = p->m_Settings.m_Cipher->m_FrameCounter;
    }
    if ((ret = CGXSecure_Secure(&p->m_Settings, p->m_Settings.m_Cipher, ic,
        CGXDLMSSettings_GetStoCChallenge(&p->m_Settings), &pw, &challenge)) != 0)
    {
        CGXByteBuffer_d(&pw);
        CGXByteBuffer_d(&challenge);
        return ret;
    }

    CGXByteBuffer_d(&pw);

    CGXDLMSVariant name, data;// = challenge;
    CGXDLMSVariant_1(&name);
    CGXDLMSVariant_23(&data, &challenge);

    CGXByteBuffer_d(&challenge);

    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        //name = "0.0.40.0.0.255";
        CGXDLMSVariant_copy_3(&name, "0.0.40.0.0.255");

        ret = CGXDLMSClient_Method_2(p, name, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME,
                                     1, &data, packets);

        CGXDLMSVariant_d(&name);
        CGXDLMSVariant_d(&data);
        return ret;
    }
    //name = 0xFA00;
    CGXDLMSVariant_copy_12(&name, 0xFA00);

    ret = CGXDLMSClient_Method_2(p, name, DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME,
                                 8, &data, packets);

    CGXDLMSVariant_d(&name);
    CGXDLMSVariant_d(&data);
    return ret;
}

int CGXDLMSClient_ParseApplicationAssociationResponse(
    CGXDLMSClient *p,
    CGXByteBuffer* reply)
{
    CGXDataInfo info;
    CGXDataInfo_(&info);

    unsigned char ch;
    bool equals = false;

    int ret;
    unsigned long ic = 0;

    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    if ((ret = GXHelpers_GetData(reply, &info, &value)) != 0)
    {
        CGXDLMSVariant_d(&value);
        return ret;
    }

    CGXByteBuffer secret;
    CGXByteBuffer_1(&secret);

    if (value.st.vt != DLMS_DATA_TYPE_NONE)
    {
        if (p->m_Settings.m_Authentication == DLMS_AUTHENTICATION_HIGH_GMAC)
        {
            //secret = *((CGXByteBuffer*)CGXDLMSSettings_GetSourceSystemTitle(&p->m_Settings));
            CGXByteBuffer_copy(&secret, CGXDLMSSettings_GetSourceSystemTitle(&p->m_Settings));

            CGXByteBuffer bb;
            CGXByteBuffer_1(&bb);

            CGXByteBuffer_Set_1(&bb, value.st.un.byteArr, CGXDLMSVariant_GetSize_1(&value));
            if ((ret = CGXByteBuffer_GetUInt8_1(&bb, &ch)) != 0)            
            {
                CGXByteBuffer_d(&bb);
                CGXByteBuffer_d(&secret);
                CGXDLMSVariant_d(&value);
                return ret;
            }
            if ((ret = CGXByteBuffer_GetUInt32_1(&bb, &ic)) != 0)
            {
                CGXByteBuffer_d(&bb);
                CGXByteBuffer_d(&secret);
                CGXDLMSVariant_d(&value);
                return ret;
            }

            CGXByteBuffer_d(&bb);
        }
        else
        {
            //secret = *((CGXByteBuffer*)CGXDLMSSettings_GetPassword(&p->m_Settings));
            CGXByteBuffer_copy(&secret, CGXDLMSSettings_GetPassword(&p->m_Settings));
        }
        
        CGXByteBuffer challenge, cToS;// = CGXDLMSSettings_GetCtoSChallenge(&p->m_Settings);
        CGXByteBuffer_3(&cToS, CGXDLMSSettings_GetCtoSChallenge(&p->m_Settings));
        CGXByteBuffer_1(&challenge);

        if ((ret = CGXSecure_Secure(
            &p->m_Settings,
            p->m_Settings.m_Cipher,
            ic,
            &cToS,
            &secret,
            &challenge)) != 0)
        {
            CGXByteBuffer_d(&cToS);
            CGXByteBuffer_d(&challenge);
            CGXByteBuffer_d(&secret);
            CGXDLMSVariant_d(&value);
            return ret;
        }
        equals = CGXByteBuffer_Compare(&challenge, value.st.un.byteArr, CGXDLMSVariant_GetSize_1(&value));

        CGXByteBuffer_d(&cToS);
        CGXByteBuffer_d(&challenge);
    }
    else
    {
        // Server did not accept CtoS.
    }

    CGXByteBuffer_d(&secret);
    CGXDLMSVariant_d(&value);

    if (!equals)
    {
        //ParseApplicationAssociationResponse failed. Server to Client do not match.
        return DLMS_ERROR_CODE_AUTHENTICATION_FAILURE;
    }
    return 0;
}

int CGXDLMSClient_ReceiverReady(
    CGXDLMSClient *p,
    DLMS_DATA_REQUEST_TYPES type,
    CGXByteBuffer* packets)
{
    return CGXDLMS_ReceiverReady(&p->m_Settings, type, NULL, packets);
}

String CGXDLMSClient_ObjectTypeToString(DLMS_OBJECT_TYPE type)
{
    return CGXDLMSObjectFactory_ObjectTypeToString(type);
}

static void CGXDLMSClient_UpdateOBISCodes(CGXDLMSObjectCollection* objects)
{
    /*
    stream sb;
    sb << OBIS_CODES1;
    sb << OBIS_CODES2;
    sb << OBIS_CODES3;
    sb << OBIS_CODES4;
    sb << OBIS_CODES5;
    sb << OBIS_CODES6;
    sb << OBIS_CODES7;
    sb << OBIS_CODES8;
    sb << OBIS_CODES9;
    sb << OBIS_CODES10;
    sb << OBIS_CODES11;
    CGXStandardObisCodeCollection codes;
    std::string str = sb.str();
    std::vector< std::string > rows = GXHelpers::Split(str, "\r\n", true);
    int row = 0;
    std::string last;
    for(std::vector< std::string >::iterator it = rows.begin(); it != rows.end(); ++it)
    {
        std::vector< std::string > items = GXHelpers::Split(*it, ";\r\n", false);
        if (items.size() != 8)
        {
            items = GXHelpers::Split(*it, ";\r\n", false);
        }
        assert(items.size() == 8);
        std::vector< std::string > obis = GXHelpers::Split(items[0], ".\r\n", false);
        if (obis.size() != 6)
        {
            obis = GXHelpers::Split(items[0], ".\r\n", false);
        }
        std::string str = items[3] + "; " + items[4] + "; " + items[5] + "; " + items[6] + "; " + items[7];
        codes.push_back(CGXStandardObisCode(obis, str, items[1], items[2]));
        ++row;
        last = *it;
    }
    for(std::vector<CGXDLMSObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
    {
        std::string ln;
        (*it)->GetLogicalName(ln);
        CGXStandardObisCode code;
        if (codes.Find(ln, (*it)->GetObjectType(), code))
        {
            (*it)->SetDescription(code.GetDescription());
            //If std::string is used
            if (code.GetDataType().find("10") != std::string::npos)
            {
                code.SetDataType("10");
            }
            //If date time is used.
            else if (code.GetDataType().find("25") != std::string::npos ||
                     code.GetDataType().find("26") != std::string::npos)
            {
                code.SetDataType("25");
            }
            else if (code.GetDataType().find("9"))
            {
                //Time stamps of the billing periods objects (first scheme if there are two)
                if ((CGXStandardObisCodeCollection::EqualsMask("0.0-64.96.7.10-14.255", ln) ||
                        //Time stamps of the billing periods objects (second scheme)
                        CGXStandardObisCodeCollection::EqualsMask("0.0-64.0.1.5.0-99,255", ln) ||
                        //Time of power failure
                        CGXStandardObisCodeCollection::EqualsMask("0.0-64.0.1.2.0-99,255", ln) ||
                        //Time stamps of the billing periods objects (first scheme if there are two)
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.1.2.0-99,255", ln) ||
                        //Time stamps of the billing periods objects (second scheme)
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.1.5.0-99,255", ln) ||
                        //Time expired since last end of billing period
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.0.255", ln) ||
                        //Time of last reset
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.6.255", ln) ||
                        //Date of last reset
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.7.255", ln) ||
                        //Time expired since last end of billing period (Second billing period scheme)
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.13.255", ln) ||
                        //Time of last reset (Second billing period scheme)
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.14.255", ln) ||
                        //Date of last reset (Second billing period scheme)
                        CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.15.255", ln)))
                {
                    code.SetDataType("25");
                }
                //Local time
                else if (CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.1.255", ln))
                {
                    code.SetDataType("27");
                }
                //Local date
                else if (CGXStandardObisCodeCollection::EqualsMask("1.0-64.0.9.2.255", ln))
                {
                    code.SetDataType("26");
                }
                //Active firmware identifier
                else if (CGXStandardObisCodeCollection::EqualsMask("1.0.0.2.0.255", ln))
                {
                    code.SetDataType("10");
                }
            }
            if (code.GetDataType() != "*" &&
                    code.GetDataType() != "" &&
                    code.GetDataType().find(",") == std::string::npos)
            {
                int value;
    #if _MSC_VER > 1000
                sscanf_s(code.GetDataType().c_str(), "%d", &value);
    #else
                sscanf(code.GetDataType().c_str(), "%d", &value);
    #endif
                DLMS_DATA_TYPE type = (DLMS_DATA_TYPE) value;
                switch ((*it)->GetObjectType())
                {
                case DLMS_OBJECT_TYPE_DATA:
                case DLMS_OBJECT_TYPE_REGISTER:
                case DLMS_OBJECT_TYPE_REGISTER_ACTIVATION:
                case DLMS_OBJECT_TYPE_EXTENDED_REGISTER:
                    (*it)->SetUIDataType(2, type);
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            System.out.println("Unknown OBIS Code: " + it.getLogicalName() +
                               " Type: " + it.getObjectType());
        }
    }
    */
}

int CGXDLMSClient_ReleaseRequest(
    CGXDLMSClient *p,
    Vector* packets)
{
    int ret;

    //packets.clear();
    Vector_clear(packets);
    // If connection is not established, there is no need to send DisconnectRequest.
    if (!p->m_Settings.m_Connected)
    {
        return 0;
    }

    CGXByteBuffer buff;
    CGXByteBuffer_1(&buff);

    //Length.
    CGXByteBuffer_SetUInt8_1(&buff, 0);
    CGXByteBuffer_SetUInt8_1(&buff, 0x80);
    CGXByteBuffer_SetUInt8_1(&buff, 01);
    CGXByteBuffer_SetUInt8_1(&buff, 00);
    CGXAPDU_GenerateUserInformation(&p->m_Settings, p->m_Settings.m_Cipher, NULL, &buff);
    CGXByteBuffer_SetUInt8_2(&buff, 0, (unsigned char)(buff.m_Size - 1));
    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        CGXDLMSLNParameters pa;
        CGXDLMSLNParameters_(&pa, &p->m_Settings, 0, DLMS_COMMAND_RELEASE_REQUEST, 0, NULL, &buff, 0xff);

        ret = CGXDLMS_GetLnMessages(&pa, packets);

        //CGXDLMSLNParameters_d(&pa);
    }
    else
    {
        CGXDLMSSNParameters pa;
        CGXDLMSSNParameters_(&pa, &p->m_Settings, DLMS_COMMAND_RELEASE_REQUEST, 0xFF, 0xFF, NULL, &buff);

        ret = CGXDLMS_GetSnMessages(&pa, packets);

        //CGXDLMSSNParameters_d(&pa);
    }
    if (CGXDLMSClient_GetInterfaceType(p) == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        p->m_Settings.m_Connected = false;
    }

    CGXByteBuffer_d(&buff);
    return ret;
}

int CGXDLMSClient_DisconnectRequest(
    CGXDLMSClient *p,
    Vector* packets)
{
    int ret;

    //packets.clear();
    Vector_clear(packets);
    CGXDLMSSettings_SetMaxReceivePDUSize(&p->m_Settings, 0xFFFF);
    // If connection is not established, there is no need to send DisconnectRequest.
    if (!p->m_Settings.m_Connected)
    {
        return 0;
    }

    CGXByteBuffer reply;
    CGXByteBuffer_1(&reply);

    if (CGXDLMSClient_GetInterfaceType(p) == DLMS_INTERFACE_TYPE_HDLC)
    {
        ret = CGXDLMS_GetHdlcFrame(&p->m_Settings, DLMS_COMMAND_DISC, NULL, &reply);
        Vector_push_back(packets, &reply);

        CGXByteBuffer_d(&reply);
        return ret;
    }

    CGXByteBuffer bb;
    CGXByteBuffer_2(&bb, 2);

    CGXByteBuffer_SetUInt8_1(&bb, DLMS_COMMAND_RELEASE_REQUEST);
    CGXByteBuffer_SetUInt8_1(&bb, 0x0);
    ret = CGXDLMS_GetWrapperFrame(&p->m_Settings, &bb, &reply);
    Vector_push_back(packets, &reply);

    CGXByteBuffer_d(&bb);
    CGXByteBuffer_d(&reply);
    return ret;
}

int CGXDLMSClient_GetData(
    CGXDLMSClient *p,
    CGXByteBuffer* reply,
    CGXReplyData* data)
{
    return CGXDLMS_GetData(&p->m_Settings, reply, data);
}

int CGXDLMSClient_GetObjectsRequest(
    CGXDLMSClient *p,
    Vector* reply)
{
    CGXDLMSVariant name;
    CGXDLMSVariant_1(&name);

    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        //name = "0.0.40.0.0.255";
        CGXDLMSVariant_copy_3(&name, "0.0.40.0.0.255");
    }
    else
    {
        //name = (short)0xFA00;
        CGXDLMSVariant_copy_11(&name, (short)0xFA00);
    }

    int ret = CGXDLMSClient_Read_1(p, &name, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, 2, reply);

    CGXDLMSVariant_d(&name);
    return ret;
}

int CGXDLMSClient_Read_2(
    CGXDLMSClient *p,
    CGXDLMSObject* pObject,
    int attributeOrdinal,
    Vector* reply)
{
    CGXDLMSVariant name = CGXDLMSObject_GetName(pObject);

    int ret = CGXDLMSClient_Read(p, &name, pObject->m_ObjectType, attributeOrdinal, NULL, reply);

    CGXDLMSVariant_d(&name);
    return ret;
}

int CGXDLMSClient_Read_1(
    CGXDLMSClient *p,
    CGXDLMSVariant* name,
    DLMS_OBJECT_TYPE objectType,
    int attributeOrdinal,
    Vector* reply)
{
    return CGXDLMSClient_Read(p, name, objectType, attributeOrdinal, NULL, reply);
}

/**
* Generates a read message.
*
* name : Short or Logical Name.
* objectType : COSEM object type.
* attributeOrdinal : Attribute index of the object.
* data : Read data parameter.
* reply : Generated read message(s).
* Returns error status.
*/
static int CGXDLMSClient_Read(
    CGXDLMSClient *p,
    CGXDLMSVariant* name,
    DLMS_OBJECT_TYPE objectType,
    int attributeOrdinal,
    CGXByteBuffer* data,
    Vector* reply)
{
    int ret;
    if ((attributeOrdinal < 1))
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    p->m_Settings.m_BlockIndex = 1;;

    CGXByteBuffer attributeDescriptor;
    CGXByteBuffer_1(&attributeDescriptor);

    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        // CI
        CGXByteBuffer_SetUInt16(&attributeDescriptor, objectType);
        // Add LN
        unsigned char ln[6];
        GXHelpers_SetLogicalName_2(String_c_str(&name->strVal), ln);
        CGXByteBuffer_Set_1(&attributeDescriptor, ln, 6);
        // Attribute ID.
        CGXByteBuffer_SetUInt8_1(&attributeDescriptor, attributeOrdinal);
        if (data == NULL || data->m_Size == 0)
        {
            // Access selection is not used.
            CGXByteBuffer_SetUInt8_1(&attributeDescriptor, 0);
        }
        else
        {
            // Access selection is used.
            CGXByteBuffer_SetUInt8_1(&attributeDescriptor, 1);
            // Add data.
            CGXByteBuffer_Set_2(&attributeDescriptor, data, 0, data->m_Size);
        }
        CGXDLMSLNParameters pa;
        CGXDLMSLNParameters_(&pa, &p->m_Settings, 0,
            DLMS_COMMAND_GET_REQUEST, DLMS_GET_COMMAND_TYPE_NORMAL,
            &attributeDescriptor, data, 0xFF);

        ret = CGXDLMS_GetLnMessages(&pa, reply);

        //CGXDLMSLNParameters_d(&pa);
    }
    else
    {
        DLMS_VARIABLE_ACCESS_SPECIFICATION requestType;

        int sn = CGXDLMSVariant_ToInteger(name);

        sn += (attributeOrdinal - 1) * 8;
        CGXByteBuffer_SetUInt16(&attributeDescriptor, sn);
        // Add Selector.
        if (data != NULL && data->m_Size != 0)
        {
            requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_PARAMETERISED_ACCESS;
        }
        else
        {
            requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME;
        }

        CGXDLMSSNParameters pa;
        CGXDLMSSNParameters_(&pa, &p->m_Settings, DLMS_COMMAND_READ_REQUEST, 1,        
            requestType, &attributeDescriptor, data);

        ret = CGXDLMS_GetSnMessages(&pa, reply);

        //CGXDLMSSNParameters_d(&pa);
    }

    CGXByteBuffer_d(&attributeDescriptor);
    return ret;
}

/**
* Read list of COSEM objects.
*
* @param list
*            DLMS objects to read.
* @return Read request as byte array.
*/
// int CGXDLMSClient::ReadList(
//     std::vector<std::pair<CGXDLMSObject*, unsigned char> >& list,
//     std::vector<CGXByteBuffer>& reply)
int CGXDLMSClient_ReadList(
    CGXDLMSClient *p,
    Vector* list,
    Vector* reply)
{
    if (Vector_size(list) == 0)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret;
    p->m_Settings.m_BlockIndex = 1;;

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        CGXDLMSLNParameters pa;
        CGXDLMSLNParameters_(&pa, &p->m_Settings, 0,
            DLMS_COMMAND_GET_REQUEST, DLMS_GET_COMMAND_TYPE_WITH_LIST,
            &bb, NULL, 0xff);

        //Request service primitive shall always fit in a single APDU.
        unsigned short pos = 0, count = (p->m_Settings.m_MaxReceivePDUSize - 12) / 10;
        if (Vector_size(list) < count)
        {
            count = (unsigned short)Vector_size(list);
        }
        //All meters can handle 10 items.
        if (count > 10)
        {
            count = 10;
        }
        // Add length.
        GXHelpers_SetObjectCount(count, &bb);
        //for (std::vector<std::pair<CGXDLMSObject*, unsigned char> >::iterator it = list.begin(); it != list.end(); ++it)
        for (unsigned int i = Vector_begin(list); i != Vector_end(list); ++i)
        {
            Pair* it = Vector_at(list, i);
            // CI.
            CGXByteBuffer_SetUInt16(&bb, (*((CGXDLMSObject**)Pair_first(it)))->m_ObjectType);
            CGXByteBuffer_Set_1(&bb, (**((CGXDLMSObject**)Pair_first(it))).m_LN, 6);
            // Attribute ID.
            CGXByteBuffer_SetUInt8_1(&bb, *((unsigned char*)Pair_second(it)));
            // Attribute selector is not used.
            CGXByteBuffer_SetUInt8_1(&bb, 0);
            ++pos;
            if (pos % count == 0 && Vector_size(list) != pos)
            {
                if ((ret = CGXDLMS_GetLnMessages(&pa, reply)) != 0)
                {
                    //CGXDLMSLNParameters_d(&pa);
                    CGXByteBuffer_d(&bb);
                    return ret;
                }
                CGXByteBuffer_Clear(&bb);
                if (Vector_size(list) - pos < count)
                {
                    GXHelpers_SetObjectCount((unsigned long)(Vector_size(list) - pos), &bb);
                }
                else
                {
                    GXHelpers_SetObjectCount(count, &bb);
                }
            }
        }
        if ((ret = CGXDLMS_GetLnMessages(&pa, reply)) != 0)
        {
            //CGXDLMSLNParameters_d(&pa);
            CGXByteBuffer_d(&bb);
            return ret;
        }

        //CGXDLMSLNParameters_d(&pa);
    }
    else
    {
        int sn;
        //for (std::vector<std::pair<CGXDLMSObject*, unsigned char> >::iterator it = list.begin(); it != list.end(); ++it)
        for (unsigned int i = Vector_begin(list); i != Vector_end(list); ++i)
        {
            // Add variable type.
            CGXByteBuffer_SetUInt8_1(&bb, DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME);
            Pair* it = Vector_at(list, i);
            sn = (*((CGXDLMSObject**)Pair_first(it)))->m_SN;
            sn += (*((unsigned char*)Pair_second(it)) - 1) * 8;
            //sn = it->first->GetShortName();
            //sn += (it->second - 1) * 8;
            CGXByteBuffer_SetUInt16(&bb, sn);
        }

        CGXDLMSSNParameters pa;
        CGXDLMSSNParameters_(&pa, &p->m_Settings, DLMS_COMMAND_READ_REQUEST,
            (unsigned long)Vector_size(list), 0xFF, &bb, NULL);

        ret = CGXDLMS_GetSnMessages(&pa, reply);

        //CGXDLMSSNParameters_d(&pa);
    }

    CGXByteBuffer_d(&bb);
    return ret;
}

/**
     * Update list of values.
     *
     * @param list
     *            read objects.
     * @param values
     *            Received values.
     */
// int CGXDLMSClient::UpdateValues(
//     std::vector<std::pair<CGXDLMSObject*, unsigned char> >& list,
//     std::vector<CGXDLMSVariant>& values)
int CGXDLMSClient_UpdateValues(
    CGXDLMSClient *p,
    Vector* list,
    Vector* values)
{
    int ret, pos = 0;
    //for (std::vector<std::pair<CGXDLMSObject*, unsigned char> >::iterator it = list.begin(); it != list.end(); ++it)
    for (unsigned int i = Vector_begin(list); i != Vector_end(list); ++i)
    {
        Pair* it = Vector_at(list, i);

        CGXDLMSObject* obj = *((CGXDLMSObject**)Pair_first(it));

        CGXDLMSValueEventArg e;
        CGXDLMSValueEventArg_1(&e, NULL, obj, *((unsigned char*)Pair_second(it)));

        CGXDLMSValueEventArg_SetValue(&e, ((CGXDLMSVariant*)Vector_at(values, pos)));
        if ((ret = obj->SetValue(obj, &p->m_Settings, &e)) != 0)
        {
            CGXDLMSValueEventArg_d(&e);
            return ret;
        }
        ++pos;

        CGXDLMSValueEventArg_d(&e);
    }
    return 0;
}

int CGXDLMSClient_Write_3(
    CGXDLMSClient *p,
    CGXDLMSObject* pObject,
    int index,
    Vector* reply)
{
    if (index < 1)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    CGXDLMSValueEventArg e;
    CGXDLMSValueEventArg_3(&e, pObject, index);

    int ret = pObject->GetValue(pObject, &p->m_Settings, &e);
    if (ret == 0)
    {
        CGXDLMSVariant name = CGXDLMSObject_GetName(pObject);

        CGXDLMSVariant value;
        CGXDLMSVariant_2(&value, CGXDLMSValueEventArg_GetValue(&e));

        int ret;
        p->m_Settings.m_BlockIndex = 1;;

        CGXByteBuffer data;
        CGXByteBuffer_1(&data);

        if (e.m_ByteArray)
        {
            CGXByteBuffer_Set_1(&data, value.st.un.byteArr, CGXDLMSVariant_GetSize_1(&value));
        }
        else
        {
            DLMS_DATA_TYPE type = DLMS_DATA_TYPE_NONE;
            if ((ret = pObject->GetDataType(pObject, index, &type)) != 0)
            {
                CGXDLMSVariant_d(&name);
                CGXDLMSVariant_d(&value);
                CGXByteBuffer_d(&data);
                return ret;
            }
            /*
            if (value.vt != DLMS_DATA_TYPE_NONE)
            {
                if ((ret = pObject->GetDataType(index, type)) != 0)            
                {
                    return ret;
                }
                if (value.vt != type)
                {
                    if ((ret = value.ChangeType(type)) != 0)
                    {
                        return ret;
                    }
                }
            }*/
            if ((ret = GXHelpers_SetData(&data, type, &value)) != 0)
            {
                CGXDLMSVariant_d(&name);
                CGXDLMSVariant_d(&value);
                CGXByteBuffer_d(&data);
                return ret;
            }
        }

        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
        {
            // Add CI.
            CGXByteBuffer_SetUInt16(&bb, pObject->m_ObjectType);
            // Add LN.
            unsigned char ln[6];
            GXHelpers_SetLogicalName_2(String_c_str(&name.strVal), ln);
            CGXByteBuffer_Set_1(&bb, ln, 6);
            // Attribute ID.
            CGXByteBuffer_SetUInt8_1(&bb, index);
            // Access selection is not used.
            CGXByteBuffer_SetUInt8_1(&bb, 0);

            CGXDLMSLNParameters pa;
            CGXDLMSLNParameters_(&pa, &p->m_Settings, 0,
                DLMS_COMMAND_SET_REQUEST, DLMS_SET_COMMAND_TYPE_NORMAL,
                &bb, &data, 0xff);

            ret = CGXDLMS_GetLnMessages(&pa, reply);

            //CGXDLMSLNParameters_d(&pa);
        }
        else
        {
            // Add name.
            int sn = CGXDLMSVariant_ToInteger(&name);
            sn += (index - 1) * 8;
            CGXByteBuffer_SetUInt16(&bb, sn);
            // Add data count.
            CGXByteBuffer_SetUInt8_1(&bb, 1);

            CGXDLMSSNParameters pa;
            CGXDLMSSNParameters_(&pa, &p->m_Settings,
                DLMS_COMMAND_WRITE_REQUEST, 1,
                DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME,
                &bb, &data);

            ret = CGXDLMS_GetSnMessages(&pa, reply);

            //CGXDLMSSNParameters_d(&pa);
        }

        CGXByteBuffer_d(&bb);
        CGXDLMSVariant_d(&name);
        CGXDLMSVariant_d(&value);
        CGXByteBuffer_d(&data);
        return ret;
    }
    return ret;
}


int CGXDLMSClient_Write_2(
    CGXDLMSClient *p,
    CGXDLMSObject* pObject,
    int index,
    CGXDLMSVariant* data,
    Vector* reply)
{
    CGXDLMSVariant name = CGXDLMSObject_GetName(pObject);

    int ret = CGXDLMSClient_Write_1(p, &name, pObject->m_ObjectType, index, data, reply);

    CGXDLMSVariant_d(&name);
    return ret;
}

int CGXDLMSClient_Write_1(
    CGXDLMSClient *p,
    CGXDLMSVariant* name,
    DLMS_OBJECT_TYPE objectType,
    int index,
    CGXDLMSVariant* value,
    Vector* reply)
{
    if (index < 1)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int ret;
    p->m_Settings.m_BlockIndex = 1;;

    CGXByteBuffer bb, data;
    CGXByteBuffer_1(&bb);
    CGXByteBuffer_1(&data);

    if ((ret = GXHelpers_SetData(&data, value->st.vt, value)) != 0)
    {
        CGXByteBuffer_d(&bb);
        CGXByteBuffer_d(&data);
        return ret;
    }

    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        // Add CI.
        CGXByteBuffer_SetUInt16(&bb, objectType);
        // Add LN.
        unsigned char ln[6];
        GXHelpers_SetLogicalName_2(String_c_str(&name->strVal), ln);
        CGXByteBuffer_Set_1(&bb, ln, 6);
        // Attribute ID.
        CGXByteBuffer_SetUInt8_1(&bb, index);
        // Access selection is not used.
        CGXByteBuffer_SetUInt8_1(&bb, 0);

        CGXDLMSLNParameters pa;
        CGXDLMSLNParameters_(&pa, &p->m_Settings, 0,
            DLMS_COMMAND_SET_REQUEST, DLMS_SET_COMMAND_TYPE_NORMAL,
            &bb, &data, 0xff);

        ret = CGXDLMS_GetLnMessages(&pa, reply);

        //CGXDLMSLNParameters_d(&pa);
    }
    else
    {
        // Add name.
        int sn = CGXDLMSVariant_ToInteger(name);
        sn += (index - 1) * 8;
        CGXByteBuffer_SetUInt16(&bb, sn);
        // Add data count.
        CGXByteBuffer_SetUInt8_1(&bb, 1);

        CGXDLMSSNParameters pa;
        CGXDLMSSNParameters_(&pa, &p->m_Settings,
            DLMS_COMMAND_WRITE_REQUEST, 1,
            DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME,
            &bb, &data);

        ret = CGXDLMS_GetSnMessages(&pa, reply);

        //CGXDLMSSNParameters_d(&pa);
    }

    CGXByteBuffer_d(&bb);
    CGXByteBuffer_d(&data);
    return ret;
}

/**
    * Generate Method (Action) request.
    *
    * @param item
    *            Method object short name or Logical Name.
    * @param index
    *            Method index.
    * @param data
    *            Method data.
    * @param type
    *            Data type.
    * @return DLMS action message.
    */
int CGXDLMSClient_Method_1(
    CGXDLMSClient *p,
    CGXDLMSObject* item,
    int index,
    CGXDLMSVariant* data,
    Vector* reply)
{
    CGXDLMSVariant name = CGXDLMSObject_GetName(item);

    int ret = CGXDLMSClient_Method_2(p, name, item->m_ObjectType, index, data, reply);

    CGXDLMSVariant_d(&name);
    return ret;
}

/**
    * Generate Method (Action) request..
    *
    * @param name
    *            Method object short name or Logical Name.
    * @param objectType
    *            Object type.
    * @param index
    *            Method index.
    * @param value
    *            Method data.
    * @param dataType
    *            Data type.
    * @return DLMS action message.
    */
int CGXDLMSClient_Method_2(
    CGXDLMSClient *p,
    CGXDLMSVariant name,
    DLMS_OBJECT_TYPE objectType,
    int index,
    CGXDLMSVariant* value,
    Vector* reply)
{
    int ret;
    if (index < 1)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    CGXByteBuffer bb, data;
    CGXByteBuffer_1(&bb);
    CGXByteBuffer_1(&data);

    p->m_Settings.m_BlockIndex = 1;;
    if ((ret = GXHelpers_SetData(&data, value->st.vt, value)) != 0)
    {
        CGXByteBuffer_d(&bb);
        CGXByteBuffer_d(&data);
        return ret;
    }
    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        // CI
        CGXByteBuffer_SetUInt16(&bb, objectType);
        // Add LN.
        unsigned char ln[6];
        GXHelpers_SetLogicalName_2(String_c_str(&name.strVal), ln);
        CGXByteBuffer_Set_1(&bb, ln, 6);
        // Attribute ID.
        CGXByteBuffer_SetUInt8_1(&bb, index);
        // Method Invocation Parameters is not used.
        if (value->st.vt == DLMS_DATA_TYPE_NONE)
        {
            CGXByteBuffer_SetUInt8_1(&bb, 0);
        }
        else
        {
            CGXByteBuffer_SetUInt8_1(&bb, 1);
        }
        CGXDLMSLNParameters pa;
        CGXDLMSLNParameters_(&pa, &p->m_Settings, 0,
            DLMS_COMMAND_METHOD_REQUEST, DLMS_ACTION_COMMAND_TYPE_NORMAL,
            &bb, &data, 0xff);

        ret = CGXDLMS_GetLnMessages(&pa, reply);

        //CGXDLMSLNParameters_d(&pa);
    }
    else
    {
        int requestType;
        if (value->st.vt == DLMS_DATA_TYPE_NONE)
        {
            requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME;
        }
        else
        {
            requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_PARAMETERISED_ACCESS;
        }
        unsigned char ind, count;
        if ((ret = CGXDLMS_GetActionInfo(objectType, &ind, &count)) != 0)
        {
            CGXByteBuffer_d(&bb);
            CGXByteBuffer_d(&data);
            return ret;
        }

        if (index > count)
        {
            CGXByteBuffer_d(&bb);
            CGXByteBuffer_d(&data);
            //Invalid parameter
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        int sn = CGXDLMSVariant_ToInteger(&name);
        index = (ind + (index - 1) * 0x8);
        sn += index;
        // Add SN count.
        CGXByteBuffer_SetUInt8_1(&bb, 1);
        // Add name length.
        CGXByteBuffer_SetUInt8_1(&bb, 4);
        // Add name.
        CGXByteBuffer_SetUInt16(&bb, sn);
        // Method Invocation Parameters is not used.
        if (value->st.vt == DLMS_DATA_TYPE_NONE)
        {
            CGXByteBuffer_SetUInt8_1(&bb, 0);
        }
        else
        {
            CGXByteBuffer_SetUInt8_1(&bb, 1);
        }

        CGXDLMSSNParameters pa;
        CGXDLMSSNParameters_(&pa, &p->m_Settings, DLMS_COMMAND_READ_REQUEST, 1,
            requestType, &bb, &data);

        ret = CGXDLMS_GetSnMessages(&pa, reply);

        //CGXDLMSSNParameters_d(&pa);
    }

    CGXByteBuffer_d(&bb);
    CGXByteBuffer_d(&data);
    return ret;
}

int CGXDLMSClient_ReadRowsByEntry_1(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    int index,
    int count,
    Vector* reply)
{
    //std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> > cols;
    Vector cols;
    Vector_(&cols, sizeof(Pair), Pair_v_c, Pair_v_d);

    int ret = CGXDLMSClient_ReadRowsByEntry_2(p, pg, index, count, &cols, reply);

    Vector_d(&cols);
    return ret;
}

int CGXDLMSClient_ReadRowsByEntry_2(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    int index,
    int count,
    Vector* columns,//std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
    Vector* reply)
{
    if (pg == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    CGXByteBuffer buff;
    CGXByteBuffer_2(&buff, 19);

    CGXDLMSProfileGeneric_Reset_1(pg);
    // Add AccessSelector value
    CGXByteBuffer_SetUInt8_1(&buff, 0x02);
    // Add enum tag.
    CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
    // Add item count
    CGXByteBuffer_SetUInt8_1(&buff, 0x04);
    // Add start index

    CGXDLMSVariant tmp;
    CGXDLMSVariant_10(&tmp, index);

    GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT32, &tmp);
    
    // Add Count
    //tmp = count;
    CGXDLMSVariant_copy_12(&tmp, count);
    GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT32, &tmp);
    // Read all columns.
    if (CGXDLMSClient_GetUseLogicalNameReferencing(p))
    {
        //tmp = 1;
        CGXDLMSVariant_copy_12(&tmp, 1);
        GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT16, &tmp);
    }
    else
    {
        //tmp = 0;
        CGXDLMSVariant_copy_12(&tmp, 0);
        GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT16, &tmp);
    }
    //tmp = 0;
    CGXDLMSVariant_copy_12(&tmp, 0);
    GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT16, &tmp);

    CGXDLMSVariant name = CGXDLMSProfileGeneric_GetName(pg);

    int ret = CGXDLMSClient_Read(p, &name, DLMS_OBJECT_TYPE_PROFILE_GENERIC, 2, &buff, reply);

    CGXDLMSVariant_d(&name);
    CGXDLMSVariant_d(&tmp);
    CGXByteBuffer_d(&buff);
    return ret;
}

int CGXDLMSClient_ReadRowsByRange_1(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    CGXDateTime* start,
    CGXDateTime* end,
    Vector* reply)
{
    int ret;
    unsigned char LN[] = { 0, 0, 1, 0, 0, 255 };

    CGXByteBuffer buff;//(51);
    CGXByteBuffer_2(&buff, 51);

    CGXDLMSVariant name = CGXDLMSProfileGeneric_GetName(pg);

    if (pg == NULL)
    {
        CGXByteBuffer_d(&buff);
        CGXDLMSVariant_d(&name);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    CGXDLMSProfileGeneric_Reset_1(pg);
    p->m_Settings.m_BlockIndex = 1;;
    // Add AccessSelector value.
    CGXByteBuffer_SetUInt8_1(&buff, 0x01);
    // Add enum tag.
    CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
    // Add item count
    CGXByteBuffer_SetUInt8_1(&buff, 0x04);
    // Add enum tag.
    CGXByteBuffer_SetUInt8_1(&buff, 0x02);
    // Add item count
    CGXByteBuffer_SetUInt8_1(&buff, 0x04);
    // CI

    CGXDLMSVariant tmp;
    CGXDLMSVariant_10(&tmp, DLMS_OBJECT_TYPE_CLOCK);

    GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT16, &tmp);
    // LN

    CGXDLMSVariant ln;
    CGXDLMSVariant_18(&ln, LN, 6, DLMS_DATA_TYPE_OCTET_STRING);

    GXHelpers_SetData(&buff, DLMS_DATA_TYPE_OCTET_STRING, &ln);
    // Add attribute index.
    //tmp = 2;
    CGXDLMSVariant_copy_12(&tmp, 2);
    GXHelpers_SetData(&buff, DLMS_DATA_TYPE_INT8, &tmp);
    // Add version
    //tmp = 0;
    CGXDLMSVariant_copy_12(&tmp, 0);
    if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_UINT16, &tmp)) != 0)
    {
        CGXByteBuffer_d(&buff);
        CGXDLMSVariant_d(&name);
        CGXDLMSVariant_d(&tmp);
        CGXDLMSVariant_d(&ln);
        return ret;
    }
    // Add start time
    //tmp = start;
    CGXDLMSVariant_copy_21(&tmp, start);
    if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
    {
        CGXByteBuffer_d(&buff);
        CGXDLMSVariant_d(&name);
        CGXDLMSVariant_d(&tmp);
        CGXDLMSVariant_d(&ln);
        return ret;
    }
    // Add end time
    //tmp = end;
    CGXDLMSVariant_copy_21(&tmp, end);
    if ((ret = GXHelpers_SetData(&buff, DLMS_DATA_TYPE_OCTET_STRING, &tmp)) != 0)
    {
        CGXByteBuffer_d(&buff);
        CGXDLMSVariant_d(&name);
        CGXDLMSVariant_d(&tmp);
        CGXDLMSVariant_d(&ln);
        return ret;
    }
    // Add array of read columns. Read All...
    CGXByteBuffer_SetUInt8_1(&buff, 0x01);
    // Add item count
    CGXByteBuffer_SetUInt8_1(&buff, 0x00);

    ret = CGXDLMSClient_Read(p, &name, DLMS_OBJECT_TYPE_PROFILE_GENERIC, 2, &buff, reply);

    CGXByteBuffer_d(&buff);
    CGXDLMSVariant_d(&name);
    CGXDLMSVariant_d(&tmp);
    CGXDLMSVariant_d(&ln);
    return ret;
}


int CGXDLMSClient_ReadRowsByRange_2(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    struct tm* start,
    struct tm* end,
    Vector* reply)
{
    if (pg == NULL || start == NULL || end == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    CGXDateTime s, e;
    CGXDateTime_2(&s, start);
    CGXDateTime_2(&e, end);

    s.m_Skip = DATETIME_SKIPS_MS;
    e.m_Skip = DATETIME_SKIPS_MS;
    return CGXDLMSClient_ReadRowsByRange_1(p, pg, &s, &e, reply);
}

int CGXDLMSClient_ReadRowsByRange_3(
    CGXDLMSClient *p,
    CGXDLMSProfileGeneric* pg,
    struct tm* start,
    struct tm* end,
    Vector* columns,//std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >&
    Vector* reply)
{
    return CGXDLMSClient_ReadRowsByRange_2(p, pg, start, end, reply);
}

int CGXDLMSClient_GetServerAddress_1(
    unsigned long serialNumber,
    const char* formula)
{
    // If formula is not given use default formula.
    // This formula is defined in DLMS specification.
    if (formula == NULL || strlen(formula) == 0)
    {
        return 0x4000 | CGXSerialNumberCounter_Count(serialNumber, "SN % 10000 + 1000");
    }
    return 0x4000 | CGXSerialNumberCounter_Count(serialNumber, formula);
}

int CGXDLMSClient_GetServerAddress_2(unsigned long logicalAddress,
    unsigned long physicalAddress,
    unsigned char addressSize)
{
    if (addressSize < 4 && physicalAddress < 0x80
        && logicalAddress < 0x80)
    {
        return logicalAddress << 7 | physicalAddress;
    }
    if (physicalAddress < 0x4000 && logicalAddress < 0x4000)
    {
        return logicalAddress << 14 | physicalAddress;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}
