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

#include "../include/GXDLMSServer.h"
#include "../include/GXDLMS.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSProfileGeneric.h"
#include "../include/GXDLMSAssociationShortName.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXAPDU.h"
#include "../include/GXSecure.h"
#include "../include/GXDLMSValueEventCollection.h"

//CGXDLMSServer::CGXDLMSServer(bool logicalNameReferencing,
//    DLMS_INTERFACE_TYPE type) : m_Transaction(NULL), m_Settings(true)
void CGXDLMSServer_1(CGXDLMSServer* p, bool logicalNameReferencing,
                     DLMS_INTERFACE_TYPE type)
{
    CGXReplyData_2(&p->m_Info);
    CGXByteBuffer_1(&p->m_ReceivedData);
    CGXByteBuffer_1(&p->m_ReplyData);

    p->m_Transaction = NULL;
    CGXDLMSSettings_(&p->m_Settings, true);

    p->m_Hdlc = NULL;
    p->m_Wrapper = NULL;
    p->m_DataReceived = 0;
    p->m_Settings.m_UseLogicalNameReferencing = logicalNameReferencing;
    p->m_Settings.m_InterfaceType = type;
    if (CGXDLMSServer_GetUseLogicalNameReferencing(p))
    {
        CGXDLMSServer_SetConformance(p, (DLMS_CONFORMANCE)(DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_ACTION |
                                                           DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_SET_OR_WRITE |
                                                           DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_GET_OR_READ |
                                                           DLMS_CONFORMANCE_SET | DLMS_CONFORMANCE_SELECTIVE_ACCESS |
                                                           DLMS_CONFORMANCE_ACTION | DLMS_CONFORMANCE_MULTIPLE_REFERENCES |
                                                           DLMS_CONFORMANCE_GET | DLMS_CONFORMANCE_GENERAL_PROTECTION));
    }
    else
    {
        CGXDLMSServer_SetConformance(p, (DLMS_CONFORMANCE)(DLMS_CONFORMANCE_INFORMATION_REPORT |
                                                           DLMS_CONFORMANCE_READ | DLMS_CONFORMANCE_UN_CONFIRMED_WRITE |
                                                           DLMS_CONFORMANCE_WRITE | DLMS_CONFORMANCE_PARAMETERIZED_ACCESS |
                                                           DLMS_CONFORMANCE_MULTIPLE_REFERENCES |
                                                           DLMS_CONFORMANCE_GENERAL_PROTECTION));
    }
    CGXDLMSServer_Reset_2(p);
}

//CGXDLMSServer::CGXDLMSServer(
//    CGXDLMSAssociationLogicalName* ln,
//    CGXDLMSIecHdlcSetup* hdlc) :
//    CGXDLMSServer(true, DLMS_INTERFACE_TYPE_HDLC)
void CGXDLMSServer_2(CGXDLMSServer* p,
                     CGXDLMSAssociationLogicalName* ln,
                     CGXDLMSIecHdlcSetup* hdlc)
{
    CGXDLMSServer_1(p, true, DLMS_INTERFACE_TYPE_HDLC);

    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &ln);
    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &hdlc);
    p->m_Hdlc = hdlc;
}

//CGXDLMSServer::CGXDLMSServer(
//    CGXDLMSAssociationLogicalName* ln,
//    CGXDLMSTcpUdpSetup* wrapper) :
//    CGXDLMSServer(true, DLMS_INTERFACE_TYPE_WRAPPER)
void CGXDLMSServer_3(CGXDLMSServer* p,
                     CGXDLMSAssociationLogicalName* ln,
                     CGXDLMSTcpUdpSetup* wrapper)
{
    CGXDLMSServer_1(p, true, DLMS_INTERFACE_TYPE_WRAPPER);

    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &ln);
    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &wrapper);

    p->m_Wrapper = wrapper;
}

//CGXDLMSServer::CGXDLMSServer(
//    CGXDLMSAssociationShortName* sn,
//    CGXDLMSIecHdlcSetup* hdlc) :
//    CGXDLMSServer(false, DLMS_INTERFACE_TYPE_HDLC)
void CGXDLMSServer_4(CGXDLMSServer* p,
                     CGXDLMSAssociationShortName* sn,
                     CGXDLMSIecHdlcSetup* hdlc)
{
    CGXDLMSServer_1(p, false, DLMS_INTERFACE_TYPE_HDLC);

    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &sn);
    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &hdlc);
    p->m_Hdlc = hdlc;
}

//CGXDLMSServer::CGXDLMSServer(
//    CGXDLMSAssociationShortName* sn,
//    CGXDLMSTcpUdpSetup* wrapper) :
//    CGXDLMSServer(false, DLMS_INTERFACE_TYPE_WRAPPER)
void CGXDLMSServer_5(CGXDLMSServer* p,
                     CGXDLMSAssociationShortName* sn,
                     CGXDLMSTcpUdpSetup* wrapper)
{
    CGXDLMSServer_1(p, false, DLMS_INTERFACE_TYPE_WRAPPER);

    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &sn);
    CGXDLMSObjectCollection_push_back(CGXDLMSSettings_GetObjects(&p->m_Settings), &wrapper);
    p->m_Wrapper = wrapper;
}

void CGXDLMSServer_d(CGXDLMSServer* p)
{
    CGXReplyData_d(&p->m_Info);
    CGXByteBuffer_d(&p->m_ReceivedData);
    CGXByteBuffer_d(&p->m_ReplyData);
    CGXDLMSSettings_d(&p->m_Settings);
}

/**
* @return HDLC settings.
*/
CGXDLMSIecHdlcSetup* CGXDLMSServer_GetHdlc(CGXDLMSServer* p)
{
    return p->m_Hdlc;
}

/**
* @param value
*            HDLC settings.
*/
void CGXDLMSServer_SetHdlc(CGXDLMSServer* p, CGXDLMSIecHdlcSetup* value)
{
    p->m_Hdlc = value;
}

/**
* @return Wrapper settings.
*/
CGXDLMSTcpUdpSetup* CGXDLMSServer_GetWrapper(CGXDLMSServer* p)
{
    return p->m_Wrapper;
}

/**
* @param value
*            Wrapper settings.
*/
void CGXDLMSServer_SetWrapper(CGXDLMSServer* p, CGXDLMSTcpUdpSetup* value)
{
    p->m_Wrapper = value;
}

CGXDLMSObjectCollection* CGXDLMSServer_GetItems(CGXDLMSServer* p)
{
    return CGXDLMSSettings_GetObjects(&p->m_Settings);
}

void CGXDLMSServer_SetCipher(CGXDLMSServer* p, CGXCipher* value)
{
    p->m_Settings.m_Cipher = value;
}

// CGXDLMSSettings& CGXDLMSServer::GetSettings()
CGXDLMSSettings* CGXDLMSServer_GetSettings(CGXDLMSServer* p)
{
    return &(p->m_Settings);
}

// CGXByteBuffer& CGXDLMSServer::GetCtoSChallenge()
CGXByteBuffer* CGXDLMSServer_GetCtoSChallenge(CGXDLMSServer* p)
{
    return CGXDLMSSettings_GetCtoSChallenge(&(p->m_Settings));
}

// CGXByteBuffer& CGXDLMSServer::GetStoCChallenge()
CGXByteBuffer* CGXDLMSServer_GetStoCChallenge(CGXDLMSServer* p)
{
    return CGXDLMSSettings_GetStoCChallenge(&(p->m_Settings));
}

DLMS_INTERFACE_TYPE CGXDLMSServer_GetInterfaceType(CGXDLMSServer* p)
{
    return p->m_Settings.m_InterfaceType;
}

void CGXDLMSServer_SetStoCChallenge(CGXDLMSServer* p, CGXByteBuffer* value)
{
    p->m_Settings.m_CustomChallenges = (value->m_Size != 0);
    CGXDLMSSettings_SetStoCChallenge(&(p->m_Settings), value);
}

void CGXDLMSServer_SetStartingPacketIndex(CGXDLMSServer* p, int value)
{
    p->m_Settings.m_BlockIndex = value;
}

int CGXDLMSServer_GetInvokeID(CGXDLMSServer* p)
{
    return p->m_Settings.m_InvokeID;
}

CGXDLMSLimits CGXDLMSServer_GetLimits(CGXDLMSServer* p)
{
    return *CGXDLMSSettings_GetLimits(&(p->m_Settings));
}

unsigned short CGXDLMSServer_GetMaxReceivePDUSize(CGXDLMSServer* p)
{
    return p->m_Settings.m_MaxServerPDUSize;
}

void CGXDLMSServer_SetMaxReceivePDUSize(CGXDLMSServer* p, unsigned short value)
{
    CGXDLMSSettings_SetMaxServerPDUSize(&(p->m_Settings), value);
}

bool CGXDLMSServer_GetUseLogicalNameReferencing(CGXDLMSServer* p)
{
    return p->m_Settings.m_UseLogicalNameReferencing;
}

/**
 * @param value
 *            Is Logical Name referencing used.
 */
void CGXDLMSServer_SetUseLogicalNameReferencing(CGXDLMSServer* p, bool value)
{
    p->m_Settings.m_UseLogicalNameReferencing = value;
}

int CGXDLMSServer_Initialize(CGXDLMSServer* p)
{
    CGXDLMSObject* associationObject = NULL;
    p->m_Initialized = true;

    String ln;
    String_(&ln);

    // CGXDLMSObjectCollection::iterator
    for (unsigned int i = CGXDLMSObjectCollection_begin(CGXDLMSSettings_GetObjects(&(p->m_Settings)));
         i != CGXDLMSObjectCollection_end(CGXDLMSSettings_GetObjects(&(p->m_Settings))); ++i)
    {
        CGXDLMSObject** it = CGXDLMSObjectCollection_at(CGXDLMSSettings_GetObjects(&(p->m_Settings)), i);
        CGXDLMSObject_GetLogicalName_2(*it, &ln);
        if (String_size(&ln) == 0)
        {
            String_d(&ln);
            //Invalid Logical Name.
            return DLMS_ERROR_CODE_INVALID_LOGICAL_NAME;
        }
        if ((*it)->m_ObjectType == DLMS_OBJECT_TYPE_PROFILE_GENERIC)
        {
            CGXDLMSProfileGeneric* pg = (CGXDLMSProfileGeneric*)(*it);

            if (pg->m_ProfileEntries < 1)
            {
                String_d(&ln);
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
            if (pg->m_CapturePeriod > 0)
            {
                //TODO: Start thread. new GXProfileGenericUpdater(this, pg).start();
            }
        }
        else if ((*it)->m_ObjectType == DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME
            && !p->m_Settings.m_UseLogicalNameReferencing)
        {
            CGXDLMSObjectCollection* list = CGXDLMSAssociationShortName_GetObjectList((CGXDLMSAssociationShortName*)*it);

            if (CGXDLMSObjectCollection_size(list) == 0)
            {
                for (unsigned int i2 = CGXDLMSObjectCollection_begin(CGXDLMSServer_GetItems(p));
                     i2 != CGXDLMSObjectCollection_end(CGXDLMSServer_GetItems(p)); i2++)
                {
                    CGXDLMSObjectCollection_push_back(list, CGXDLMSObjectCollection_at(CGXDLMSServer_GetItems(p), i2));
                }
                //list.CGXDLMSObjectCollection_insert(list.CGXDLMSObjectCollection_end(), GetItems().begin(), GetItems().end());
            }
            associationObject = *it;
        }
        else if ((*it)->m_ObjectType == DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME
            && p->m_Settings.m_UseLogicalNameReferencing)
        {
            CGXDLMSObjectCollection* list = CGXDLMSAssociationLogicalName_GetObjectList((CGXDLMSAssociationLogicalName*)*it);

            if (CGXDLMSObjectCollection_size(list) == 0)
            {
                for (unsigned int i2 = CGXDLMSObjectCollection_begin(CGXDLMSServer_GetItems(p));
                     i2 != CGXDLMSObjectCollection_end(CGXDLMSServer_GetItems(p)); i2++)
                {
                    CGXDLMSObjectCollection_push_back(list, CGXDLMSObjectCollection_at(CGXDLMSServer_GetItems(p), i2));
                }
                //list.CGXDLMSObjectCollection_insert(list.CGXDLMSObjectCollection_end(), GetItems().begin(), GetItems().end());
            }
            associationObject = *it;
        }
    }

    String_d(&ln);

    if (associationObject == NULL)
    {
        if (CGXDLMSServer_GetUseLogicalNameReferencing(p))
        {
            CGXDLMSAssociationLogicalName* it2 = (CGXDLMSAssociationLogicalName*)CGXDLMSObjectFactory_CreateObject_1(DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME);

            CGXDLMSObjectCollection* list = CGXDLMSAssociationLogicalName_GetObjectList(it2);

            CGXDLMSObjectCollection_push_back(CGXDLMSServer_GetItems(p), &it2);

            for (unsigned int i2 = CGXDLMSObjectCollection_begin(CGXDLMSServer_GetItems(p));
                 i2 != CGXDLMSObjectCollection_end(CGXDLMSServer_GetItems(p)); i2++)
            {
                CGXDLMSObjectCollection_push_back(list, CGXDLMSObjectCollection_at(CGXDLMSServer_GetItems(p), i2));
            }
            //list.insert(list.end(), GetItems().begin(), GetItems().end());
        }
        else
        {
            CGXDLMSAssociationShortName* it2 = (CGXDLMSAssociationShortName*)CGXDLMSObjectFactory_CreateObject_1(DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME);

            CGXDLMSObjectCollection* list = CGXDLMSAssociationShortName_GetObjectList(it2);

            CGXDLMSObjectCollection_push_back(CGXDLMSServer_GetItems(p), &it2);

            for (unsigned int i2 = CGXDLMSObjectCollection_begin(CGXDLMSServer_GetItems(p));
                 i2 != CGXDLMSObjectCollection_end(CGXDLMSServer_GetItems(p)); i2++)
            {
                CGXDLMSObjectCollection_push_back(list, CGXDLMSObjectCollection_at(CGXDLMSServer_GetItems(p), i2));
            }
            // list.insert(list.end(), GetItems().begin(), GetItems().end());
        }
    }
    // Arrange items by Short Name.

    if (!p->m_Settings.m_UseLogicalNameReferencing)
    {
        CGXDLMSServer_UpdateShortNames_1(p, false);
    }
    return 0;
}


int CGXDLMSServer_UpdateShortNames_2(CGXDLMSServer* p)
{
    return CGXDLMSServer_UpdateShortNames_1(p, true);
}

int CGXDLMSServer_UpdateShortNames_1(CGXDLMSServer* p, bool force)
{
    int ret;
    short sn = 0xA0;
    unsigned char offset, count;

    // CGXDLMSObjectCollection::iterator
    for (unsigned int i = CGXDLMSObjectCollection_begin(CGXDLMSSettings_GetObjects(&(p->m_Settings)));
        i != CGXDLMSObjectCollection_end(CGXDLMSSettings_GetObjects(&(p->m_Settings))); ++i)
    {
        CGXDLMSObject** it = CGXDLMSObjectCollection_at(CGXDLMSSettings_GetObjects(&(p->m_Settings)), i);

        if ((*it)->m_ObjectType == DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME ||
            (*it)->m_ObjectType == DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME)
        {
            continue;
        }
        // Generate Short Name if not given.
        if (force || (*it)->m_SN == 0)
        {
            (*it)->m_SN = sn;
            // Add method index addresses.
            if ((ret = CGXDLMS_GetActionInfo((*it)->m_ObjectType, &offset, &count)) != 0)
            {
                return ret;
            }
            if (count != 0)
            {
                sn += offset + (8 * count);
            }
            else
            {
                // If there are no methods.
                // Add attribute index addresses.
                sn += 8 * (*it)->GetAttributeCount(*it);
            }
        }
        else
        {
            sn = (*it)->m_SN;
        }
    }
    return 0;
}

void CGXDLMSServer_Reset_1(CGXDLMSServer* p, bool connected)
{
    if (p->m_Transaction != NULL)
    {
        // delete m_Transaction;
        CGXDLMSLongTransaction_d(p->m_Transaction);
        DLMSPort_free(p->m_Transaction);

        p->m_Transaction = NULL;
    }
    p->m_Settings.m_Count = 0;
    p->m_Settings.m_Index = 0;
    p->m_Settings.m_Connected = false;
    CGXByteBuffer_Clear(&(p->m_ReceivedData));
    CGXByteBuffer_Clear(&(p->m_ReplyData));
    if (!connected)
    {
        CGXReplyData_Clear(&(p->m_Info));
        p->m_Settings.m_ServerAddress = 0;
        p->m_Settings.m_ClientAddress = 0;
    }

    p->m_Settings.m_Authentication = DLMS_AUTHENTICATION_NONE;
    if (p->m_Settings.m_Cipher != NULL)
    {
        if (!connected)
        {
            //CGXCipher_Reset_2(p->m_Settings.m_Cipher);
        }
        else
        {
            p->m_Settings.m_Cipher->m_Security = DLMS_SECURITY_NONE;
        }
    }
}

void CGXDLMSServer_Reset_2(CGXDLMSServer* p)
{
    CGXDLMSServer_Reset_1(p, false);
}

/**
    * Parse AARQ request that client send and returns AARE request.
    *
    * @return Reply to the client.
    */
int CGXDLMSServer_HandleAarqRequest(CGXDLMSServer* p,
                                    CGXByteBuffer* data,
                                    CGXDLMSConnectionEventArgs* connectionInfo)
{
    int ret;

    CGXByteBuffer error;
    CGXByteBuffer_1(&error);

    DLMS_ASSOCIATION_RESULT result;
    DLMS_SOURCE_DIAGNOSTIC diagnostic;

    CGXByteBuffer_Clear(CGXDLMSSettings_GetCtoSChallenge(&(p->m_Settings)));
    CGXByteBuffer_Clear(CGXDLMSSettings_GetStoCChallenge(&(p->m_Settings)));
    if (p->m_Settings.m_InterfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        CGXDLMSServer_Reset_1(p, true);
    }
    ret = CGXAPDU_ParsePDU(&p->m_Settings, p->m_Settings.m_Cipher, data, &result, &diagnostic);
    if (ret != 0)
    {
        CGXByteBuffer_d(&error);
        return ret;
    }
    if (result == DLMS_ASSOCIATION_RESULT_ACCEPTED)
    {
        if (p->m_Settings.m_DlmsVersionNumber != 6)
        {
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
            diagnostic = DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN;
            CGXByteBuffer_SetUInt8_1(&error, 0xE);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_SERVICE_ERROR_INITIATE);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_INITIATE_DLMS_VERSION_TOO_LOW);
            p->m_Settings.m_DlmsVersionNumber = 6;
        }
        else if (p->m_Settings.m_MaxReceivePDUSize < 64)
        {
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
            diagnostic = DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN;
            CGXByteBuffer_SetUInt8_1(&error, 0xE);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_SERVICE_ERROR_INITIATE);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_INITIATE_PDU_SIZE_TOOSHORT);
            CGXDLMSSettings_SetMaxReceivePDUSize(&(p->m_Settings), 64);
        }
        else if (p->m_Settings.m_NegotiatedConformance == 0)
        {
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
            diagnostic = DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN;
            CGXByteBuffer_SetUInt8_1(&error, 0xE);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_SERVICE_ERROR_INITIATE);
            CGXByteBuffer_SetUInt8_1(&error, DLMS_INITIATE_INCOMPATIBLE_CONFORMANCE);
        }
        else if (diagnostic != DLMS_SOURCE_DIAGNOSTIC_NONE)
        {
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
            diagnostic = DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
            p->InvalidConnection(p, connectionInfo);
        }
        else
        {
            diagnostic = p->ValidateAuthentication(p, p->m_Settings.m_Authentication,
                                                   CGXDLMSSettings_GetPassword(&(p->m_Settings)));
            if (diagnostic != DLMS_SOURCE_DIAGNOSTIC_NONE)
            {
                result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                p->InvalidConnection(p, connectionInfo);
            }
            else if (p->m_Settings.m_Authentication > DLMS_AUTHENTICATION_LOW)
            {
                // If High authentication is used.
                result = DLMS_ASSOCIATION_RESULT_ACCEPTED;
                diagnostic = DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED;
            }
            else
            {
                p->Connected(p, connectionInfo);
                p->m_Settings.m_Connected = true;
            }
        }
    }
    if (p->m_Settings.m_Authentication > DLMS_AUTHENTICATION_LOW)
    {
        // If High authentication is used.
        CGXByteBuffer challenge;
        CGXByteBuffer_1(&challenge);

        if ((ret = CGXSecure_GenerateChallenge(p->m_Settings.m_Authentication, &challenge)) != 0)
        {
            CGXByteBuffer_d(&challenge);
            CGXByteBuffer_d(&error);
            return ret;
        }
        CGXDLMSSettings_SetStoCChallenge(&(p->m_Settings), &challenge);

        CGXByteBuffer_d(&challenge);
    }
    if (p->m_Settings.m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
    {
        CGXByteBuffer_Set_1(&(p->m_ReplyData), LLC_REPLY_BYTES, 3);
    }
    // Generate AARE packet.
    CGXDLMSSettings_ResetFrameSequence(&(p->m_Settings));

    ret = CGXAPDU_GenerateAARE(&p->m_Settings, &p->m_ReplyData, result, diagnostic,
                               p->m_Settings.m_Cipher, &error, NULL);

    CGXByteBuffer_d(&error);
    return ret;
}

/**
 * Parse SNRM Request. If server do not accept client empty byte array is
 * returned.
 *
 * @return Returns returned UA packet.
 */
int CGXDLMSServer_HandleSnrmRequest(CGXDLMSServer* p,
                                    CGXDLMSSettings* settings,
                                    CGXByteBuffer* data,
                                    CGXByteBuffer* reply)
{
    int ret;

    CGXDLMSServer_Reset_1(p, true);

    if ((ret = CGXDLMS_ParseSnrmUaResponse(data, CGXDLMSSettings_GetLimits(&(p->m_Settings)))) != 0)
    {
        return ret;
    }
    CGXByteBuffer_SetUInt8_1(reply, 0x81); // FromatID
    CGXByteBuffer_SetUInt8_1(reply, 0x80); // GroupID
    CGXByteBuffer_SetUInt8_1(reply, 0); // Length

    if (p->m_Hdlc != NULL)
    {
        //If client wants send larger HDLC frames what meter accepts.
        if (CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_MaxInfoTX
                > p->m_Hdlc->m_MaximumInfoLengthReceive)
        {
            CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_MaxInfoTX =
                                       p->m_Hdlc->m_MaximumInfoLengthReceive;
        }
        //If client wants receive larger HDLC frames what meter accepts.
        if (CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_MaxInfoRX
                > p->m_Hdlc->m_MaximumInfoLengthTransmit)
        {
            CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_MaxInfoRX =
                                       p->m_Hdlc->m_MaximumInfoLengthTransmit;
        }
        //If client asks higher window size what meter accepts.
        if (CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_WindowSizeRX
                > p->m_Hdlc->m_WindowSizeReceive)
        {
            CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_WindowSizeRX =
                                          p->m_Hdlc->m_WindowSizeReceive;
        }
        //If client asks higher window size what meter accepts.
        if (CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_WindowSizeTX
                > p->m_Hdlc->m_WindowSizeTransmit)
        {
            CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_WindowSizeTX =
                                          p->m_Hdlc->m_WindowSizeTransmit;
        }
    }

    CGXDLMSLimits tmp = CGXDLMSServer_GetLimits(p); // No cons

    CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_MAX_INFO_TX);
    CGXDLMS_AppendHdlcParameter(reply, tmp.m_MaxInfoTX);

    CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_MAX_INFO_RX);
    CGXDLMS_AppendHdlcParameter(reply, tmp.m_MaxInfoRX);

    CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_WINDOW_SIZE_TX);
    CGXByteBuffer_SetUInt8_1(reply, 4);
    CGXByteBuffer_SetUInt32(reply, CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_WindowSizeRX);

    CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_WINDOW_SIZE_RX);
    CGXByteBuffer_SetUInt8_1(reply, 4);
    CGXByteBuffer_SetUInt32(reply, CGXDLMSSettings_GetLimits(&(p->m_Settings))->m_WindowSizeTX);
    int len = reply->m_Size - 3;
    CGXByteBuffer_SetUInt8_2(reply, 2, len); // Length
    return ret;
}

/**
 * Generates disconnect request.
 *
 * @return Disconnect request.
 */
int CGXDLMSServer_GenerateDisconnectRequest(CGXDLMSSettings* settings, CGXByteBuffer* reply)
{
    if (settings->m_InterfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        CGXByteBuffer_SetUInt8_1(reply, 0x63);
        CGXByteBuffer_SetUInt8_1(reply, 0x0);
    }
    else
    {
        CGXByteBuffer_SetUInt8_1(reply, 0x81); // FromatID
        CGXByteBuffer_SetUInt8_1(reply, 0x80); // GroupID
        CGXByteBuffer_SetUInt8_1(reply, 0); // Length

        CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_MAX_INFO_TX);
        CGXDLMS_AppendHdlcParameter(reply, CGXDLMSSettings_GetLimits(settings)->m_MaxInfoTX);

        CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_MAX_INFO_RX);
        CGXDLMS_AppendHdlcParameter(reply, CGXDLMSSettings_GetLimits(settings)->m_MaxInfoRX);

        CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_WINDOW_SIZE_TX);
        CGXByteBuffer_SetUInt8_1(reply, 4);
        CGXByteBuffer_SetUInt32(reply, CGXDLMSSettings_GetLimits(settings)->m_WindowSizeRX);

        CGXByteBuffer_SetUInt8_1(reply, HDLC_INFO_WINDOW_SIZE_RX);
        CGXByteBuffer_SetUInt8_1(reply, 4);
        CGXByteBuffer_SetUInt32(reply, CGXDLMSSettings_GetLimits(settings)->m_WindowSizeTX);
        int len = reply->m_Size - 3;
        CGXByteBuffer_SetUInt8_2(reply, 2, len); // Length.
    }
    return 0;
}

int CGXDLMSServer_ReportError(CGXDLMSSettings* settings,
                              DLMS_COMMAND command,
                              DLMS_ERROR_CODE error,
                              CGXByteBuffer* reply)
{
    int ret;
    DLMS_COMMAND cmd;

    CGXByteBuffer data;
    CGXByteBuffer_1(&data);

    switch (command)
    {
    case DLMS_COMMAND_READ_REQUEST:
        cmd = DLMS_COMMAND_READ_RESPONSE;
        break;
    case DLMS_COMMAND_WRITE_REQUEST:
        cmd = DLMS_COMMAND_WRITE_RESPONSE;
        break;
    case DLMS_COMMAND_GET_REQUEST:
        cmd = DLMS_COMMAND_GET_RESPONSE;
        break;
    case DLMS_COMMAND_SET_REQUEST:
        cmd = DLMS_COMMAND_SET_RESPONSE;
        break;
    case DLMS_COMMAND_METHOD_REQUEST:
        cmd = DLMS_COMMAND_METHOD_RESPONSE;
        break;
    default:
        // Return HW error and close connection.
        cmd = DLMS_COMMAND_NONE;
        break;
    }

    if (settings->m_UseLogicalNameReferencing)
    {
        CGXDLMSLNParameters p;
        CGXDLMSLNParameters_(&p, settings, 0, cmd, 1, NULL, NULL, error);
        ret = CGXDLMS_GetLNPdu(&p, &data);
    }
    else
    {
        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_SetUInt8_1(&bb, error);

        CGXDLMSSNParameters p;
        CGXDLMSSNParameters_(&p, settings, cmd, 1, 1, NULL, &bb);

        ret = CGXDLMS_GetSNPdu(&p, &data);

        //CGXDLMSSNParameters_d(&p);
        CGXByteBuffer_d(&bb);
    }
    if (ret == 0)
    {
        if (settings->m_InterfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
        {
            ret = CGXDLMS_GetWrapperFrame(settings, &data, reply);
        }
        else
        {
            ret = CGXDLMS_GetHdlcFrame(settings, 0, &data, reply);
        }
    }

    CGXByteBuffer_d(&data);
    return ret;
}

int CGXDLMSServer_HandleSetRequest_1(CGXDLMSServer* ptr,
                                     CGXByteBuffer* data,
                                     short type,
                                     CGXDLMSLNParameters* p)
{
    CGXDataInfo i;
    CGXDataInfo_(&i);

    int ret;
    unsigned char index, ch;
    unsigned short tmp;
    if ((ret = CGXByteBuffer_GetUInt16_1(data, &tmp)) != 0)
    {
        return ret;
    }
    DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)tmp;
    unsigned char * ln;
    ln = data->m_Data + data->m_Position;
    CGXByteBuffer_SetPosition(data, data->m_Position + 6);
    // Attribute index.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &index)) != 0)
    {
        return ret;
    }
    // Get Access Selection.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    if (type == 2)
    {
        unsigned long size, blockNumber;
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            return ret;
        }
        p->m_MultipleBlocks = ch == 0;
        ret = CGXByteBuffer_GetUInt32_1(data, &blockNumber);
        if (ret != 0)
        {
            return ret;
        }
        if (blockNumber != ptr->m_Settings.m_BlockIndex)
        {
            p->m_Status = DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID;
            return 0;
        }
        ptr->m_Settings.m_BlockIndex += 1;
        ret = GXHelpers_GetObjectCount(data, &size);
        if (ret != 0)
        {
            return ret;
        }
        unsigned long realSize = data->m_Size - data->m_Position;
        if (size != realSize)
        {
            p->m_Status = DLMS_ERROR_CODE_BLOCK_UNAVAILABLE;
            return 0;
        }
    }

    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    if (!p->m_MultipleBlocks)
    {
        ptr->m_Settings.m_BlockIndex = 1;
        ret = GXHelpers_GetData(data, &i, &value);
        if (ret != 0)
        {
            CGXDLMSVariant_d(&value);
            return ret;
        }
    }

    CGXDLMSObject* obj = CGXDLMSObjectCollection_FindByLN_2(CGXDLMSSettings_GetObjects(&(ptr->m_Settings)),
                                                            ci, ln);

    if (obj == NULL)
    {
        String name;
        String_(&name);

        GXHelpers_GetLogicalName_1(ln, &name);
        obj = ptr->FindObject(ptr, ci, 0, &name);

        String_d(&name);
    }
    // If target is unknown.
    if (obj == NULL)
    {
        // Device reports a undefined object.
        p->m_Status = DLMS_ERROR_CODE_UNAVAILABLE_OBJECT;
    }
    else
    {
        // CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, obj, index);

        CGXDLMSValueEventArg* e = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
        CGXDLMSValueEventArg_1(e, ptr, obj, index);

        CGXDLMSValueEventArg_SetValue(e, &value);

        CGXDLMSValueEventCollection list;
        CGXDLMSValueEventCollection_(&list);

        CGXDLMSValueEventCollection_push_back(&list, &e);
        DLMS_ACCESS_MODE am = ptr->GetAttributeAccess(ptr, e);
        // If write is denied.
        if (am != DLMS_ACCESS_MODE_WRITE && am != DLMS_ACCESS_MODE_READ_WRITE)
        {
            //Read Write denied.
            p->m_Status = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        }
        else
        {
            if (value.st.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                DLMS_DATA_TYPE dt;
                ret = obj->GetDataType(obj, index, &dt);
                if (ret != 0)
                {
                    CGXDLMSValueEventCollection_d(&list);
                    CGXDLMSVariant_d(&value);
                    return ret;
                }
                if (dt != DLMS_DATA_TYPE_NONE && dt != DLMS_DATA_TYPE_OCTET_STRING)
                {
                    CGXByteBuffer tmp;
                    CGXByteBuffer_1(&tmp);

                    CGXByteBuffer_Set_1(&tmp, value.st.un.byteArr, CGXDLMSVariant_GetSize_1(&value));
                    CGXDLMSVariant_Clear(&value);
                    if ((ret = CGXDLMSClient_ChangeType_1(&tmp, dt, &value)) != 0)
                    {
                        CGXByteBuffer_d(&tmp);
                        CGXDLMSValueEventCollection_d(&list);
                        CGXDLMSVariant_d(&value);
                        return ret;
                    }

                    CGXByteBuffer_d(&tmp);
                }
            }
            if (p->m_MultipleBlocks)
            {
                // m_Transaction = new CGXDLMSLongTransaction(list, DLMS_COMMAND_GET_REQUEST, data);

                ptr->m_Transaction = DLMSPort_malloc(sizeof(CGXDLMSLongTransaction));
                CGXDLMSLongTransaction_(ptr->m_Transaction, &list, DLMS_COMMAND_GET_REQUEST, data);
            }
            ptr->PreWrite(ptr, (Vector*) &list);
            if (e->m_Error != 0)
            {
                p->m_Status = e->m_Error;
            }
            else if (!e->m_Handled && !p->m_MultipleBlocks)
            {
                obj->SetValue(obj, &ptr->m_Settings, e);
                ptr->PreWrite(ptr, (Vector*) &list);
            }
        }

        CGXDLMSValueEventCollection_d(&list);
    }

    CGXDLMSVariant_d(&value);
    return ret;
}

int CGXDLMSServer_HanleSetRequestWithDataBlock(CGXDLMSServer* ptr,
                                               CGXByteBuffer* data,
                                               CGXDLMSLNParameters* p)
{
    CGXDataInfo reply;
    CGXDataInfo_(&reply);

    int ret;
    unsigned long blockNumber, size;
    unsigned char ch;
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    p->m_MultipleBlocks = ch == 0;
    if ((ret = CGXByteBuffer_GetUInt32_1(data, &blockNumber)) != 0)
    {
        return ret;
    }
    if (blockNumber != ptr->m_Settings.m_BlockIndex)
    {
        p->m_Status = DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID;
    }
    else
    {
        ptr->m_Settings.m_BlockIndex += 1;
        if ((ret = GXHelpers_GetObjectCount(data, &size)) != 0)
        {
            return ret;
        }
        unsigned long realSize = data->m_Size - data->m_Position;
        if (size != realSize)
        {
            p->m_Status = DLMS_ERROR_CODE_BLOCK_UNAVAILABLE;
        }
        // m_Transaction->GetData().Set(&data, data.GetPosition());
        CGXByteBuffer_Set_2(CGXDLMSLongTransaction_GetData(ptr->m_Transaction),
                            data, data->m_Position, -1);
        // If all data is received.
        if (!p->m_MultipleBlocks)
        {
            CGXDLMSVariant value;
            CGXDLMSVariant_1(&value);

            if ((ret != GXHelpers_GetData(CGXDLMSLongTransaction_GetData(ptr->m_Transaction),
                                          &reply, &value)) != 0)
            {
                CGXDLMSVariant_d(&value);
                return ret;
            }

            CGXDLMSValueEventArg * target = *((CGXDLMSValueEventArg**)Vector_at(CGXDLMSLongTransaction_GetTargets(ptr->m_Transaction), 0));

            if (value.st.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                DLMS_DATA_TYPE dt;
                ret = target->m_Target->GetDataType(target->m_Target,
                                                                          target->m_Index, &dt);
                if (dt != DLMS_DATA_TYPE_NONE && dt != DLMS_DATA_TYPE_OCTET_STRING)
                {
                    CGXByteBuffer bb;
                    CGXByteBuffer_1(&bb);

                    CGXByteBuffer_Set_1(&bb, value.st.un.byteArr, CGXDLMSVariant_GetSize_1(&value));
                    CGXDLMSVariant_Clear(&value);
                    if ((ret = CGXDLMSClient_ChangeType_1(&bb, dt, &value)) != 0)
                    {
                        CGXDLMSVariant_d(&value);
                        return ret;
                    }
                }
            }
            CGXDLMSValueEventArg_SetValue(target, &value);
            ptr->PreWrite(ptr, CGXDLMSLongTransaction_GetTargets(ptr->m_Transaction));
            if (!target->m_Handled && !p->m_MultipleBlocks)
            {
                target->m_Target->SetValue(target->m_Target,
                                                                 &ptr->m_Settings, target);
                ptr->PostWrite(ptr, CGXDLMSLongTransaction_GetTargets(ptr->m_Transaction));
            }
            if (ptr->m_Transaction != NULL)
            {
                // delete m_Transaction;
                CGXDLMSLongTransaction_d(ptr->m_Transaction);
                DLMSPort_free(ptr->m_Transaction);

                ptr->m_Transaction = NULL;
            }
            ptr->m_Settings.m_BlockIndex = 1;

            CGXDLMSVariant_d(&value);
        }
    }
    p->m_MultipleBlocks = true;
    return 0;
}

/**
    * Generate confirmed service error.
    *
    * @param service
    *            Confirmed service error.
    * @param type
    *            Service error.
    * @param code
    *            code
    * @return
    */
void CGXDLMSServer_GenerateConfirmedServiceError(
    DLMS_CONFIRMED_SERVICE_ERROR service,
    DLMS_SERVICE_ERROR type,
    unsigned char code, CGXByteBuffer* data)
{
    CGXByteBuffer_SetUInt8_1(data, DLMS_COMMAND_CONFIRMED_SERVICE_ERROR);
    CGXByteBuffer_SetUInt8_1(data, service);
    CGXByteBuffer_SetUInt8_1(data, type);
    CGXByteBuffer_SetUInt8_1(data, code);
}

int CGXDLMSServer_HandleSetRequest_2(CGXDLMSServer* ptr, CGXByteBuffer* data)
{
    unsigned char type, invoke;
    int ret;

    // Return error if connection is not established.
    if (!(ptr->m_Settings.m_Connected))
    {
        CGXDLMSServer_GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
                                                    DLMS_SERVICE_ERROR_SERVICE, DLMS_SERVICE_UNSUPPORTED,
                                                    &ptr->m_ReplyData);
        return 0;
    }
    // Get type.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &type)) != 0)
    {
        return ret;
    }
    // Get invoke ID and priority.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &invoke)) != 0)
    {
        return ret;
    }

    // CGXDLMSLNParameters p(&m_Settings, invoke, DLMS_COMMAND_SET_RESPONSE, type, NULL, NULL, 0);
    CGXDLMSLNParameters p;
    CGXDLMSLNParameters_(&p, &ptr->m_Settings, invoke, DLMS_COMMAND_SET_RESPONSE, type, NULL, NULL, 0);

    if (type == DLMS_SET_COMMAND_TYPE_NORMAL || type == DLMS_SET_COMMAND_TYPE_FIRST_DATABLOCK)
    {
        ret = CGXDLMSServer_HandleSetRequest_1(ptr, data, type, &p);
    }
    else if (type == DLMS_SET_COMMAND_TYPE_WITH_DATABLOCK)
    {
        // Set Request With Data Block
        ret = CGXDLMSServer_HanleSetRequestWithDataBlock(ptr, data, &p);
    }
    else
    {
        ptr->m_Settings.m_BlockIndex = 1;
        p.m_Status = DLMS_ERROR_CODE_HARDWARE_FAULT;
    }
    return CGXDLMS_GetLNPdu(&p, &(ptr->m_ReplyData));
}

unsigned short CGXDLMSServer_GetRowsToPdu(CGXDLMSServer* p, CGXDLMSProfileGeneric* pg)
{
    DLMS_DATA_TYPE dt;
    int rowsize = 0;
    // Count how many rows we can fit to one PDU.

    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    Vector *temp = CGXDLMSProfileGeneric_GetCaptureObjects(pg);
    for (unsigned int i = Vector_begin(temp); i != Vector_end(temp); ++i)
    {
        Pair* it = Vector_at(temp, i);

        CGXDLMSObject* it_first = *((CGXDLMSObject**)(it->first));
        CGXDLMSCaptureObject* it_second = *((CGXDLMSCaptureObject**)(it->second));

        it_first->GetDataType(it_first, it_second->m_AttributeIndex, &dt);
        if (dt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            it_first->GetUIDataType(it_first, it_second->m_AttributeIndex, &dt);
            if (dt == DLMS_DATA_TYPE_DATETIME)
            {
                rowsize += GXHelpers_GetDataTypeSize(DLMS_DATA_TYPE_DATETIME);
            }
            else if (dt == DLMS_DATA_TYPE_DATE)
            {
                rowsize += GXHelpers_GetDataTypeSize(DLMS_DATA_TYPE_DATE);
            }
            else if (dt == DLMS_DATA_TYPE_TIME)
            {
                rowsize += GXHelpers_GetDataTypeSize(DLMS_DATA_TYPE_TIME);
            }
        }
        else if (dt == DLMS_DATA_TYPE_NONE)
        {
            rowsize += 2;
        }
        else
        {
            rowsize += GXHelpers_GetDataTypeSize(dt);
        }
    }
    if (rowsize != 0)
    {
        return p->m_Settings.m_MaxReceivePDUSize / rowsize;
    }
    return 0;
}

int CGXDLMSServer_GetRequestNormal(CGXDLMSServer* p, CGXByteBuffer* data, unsigned char invokeID)
{
    DLMS_ERROR_CODE status = DLMS_ERROR_CODE_OK;

    p->m_Settings.m_Count = 0;
    p->m_Settings.m_Index = 0;
    p->m_Settings.m_BlockIndex = 1;

    unsigned char attributeIndex;
    int ret;
    unsigned char *ln;
    // CI
    unsigned short tmp;
    if ((ret = CGXByteBuffer_GetUInt16_1(data, &tmp)) != 0)
    {
        return ret;
    }
    DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)tmp;
    ln = data->m_Data + data->m_Position;
    CGXByteBuffer_SetPosition(data, data->m_Position + 6);
    // Attribute Id
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &attributeIndex)) != 0)
    {
        return ret;
    }

    CGXDLMSObject* obj = CGXDLMSObjectCollection_FindByLN_2(CGXDLMSSettings_GetObjects(&(p->m_Settings)),
                                                            ci, ln);
    if (obj == NULL)
    {
        String name;
        String_(&name);

        GXHelpers_GetLogicalName_1(ln, &name);
        obj = p->FindObject(p, ci, 0, &name);

        String_d(&name);
    }
    // Access selection
    unsigned char selection, selector = 0;
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &selection)) != 0)
    {
        return ret;
    }

    CGXDLMSVariant parameters;
    CGXDLMSVariant_1(&parameters);

    if (selection != 0)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &selector)) != 0)
        {
            CGXDLMSVariant_d(&parameters);
            return ret;
        }

        CGXDataInfo i;
        CGXDataInfo_(&i);

        if ((ret = GXHelpers_GetData(data, &i, &parameters)) != 0)
        {
            CGXDLMSVariant_d(&parameters);
            return ret;
        }
    }

    //CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, obj, attributeIndex, selector, parameters);
    CGXDLMSValueEventArg* e = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
    CGXDLMSValueEventArg_2(e, p, obj, attributeIndex, selector, &parameters);

    CGXDLMSVariant_d(&parameters);

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    CGXDLMSValueEventCollection arr;
    CGXDLMSValueEventCollection_(&arr);

    e->m_InvokeId = invokeID;
    CGXDLMSValueEventCollection_push_back(&arr, &e);

    if (obj == NULL)
    {
        // "Access Error : Device reports a undefined object."
        status = DLMS_ERROR_CODE_UNDEFINED_OBJECT;
    }
    else
    {
        if (p->GetAttributeAccess(p, e) == DLMS_ACCESS_MODE_NONE)
        {
            // Read Write denied.
            status = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        }
        else
        {
            if (obj->m_ObjectType == DLMS_OBJECT_TYPE_PROFILE_GENERIC && attributeIndex == 2)
            {
                e->m_RowToPdu = CGXDLMSServer_GetRowsToPdu(p, (CGXDLMSProfileGeneric*)obj);
            }
            p->PreRead(p, (Vector*) &arr);
            if (!e->m_Handled)
            {
                p->m_Settings.m_Count = e->m_RowEndIndex - e->m_RowBeginIndex;
                if ((ret = obj->GetValue(obj, &p->m_Settings, e)) != 0)
                {
                    status = DLMS_ERROR_CODE_HARDWARE_FAULT;
                }
                p->PostRead(p, (Vector*) &arr);
            }
            if (status == 0)
            {
                status = e->m_Error;
            }

            CGXDLMSVariant* value = CGXDLMSValueEventArg_GetValue(e);

            if (e->m_ByteArray && value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                // If byte array is added do not add type.
                CGXByteBuffer_Set_1(&bb, value->st.un.byteArr, CGXDLMSVariant_GetSize_1(value));
            }
            else if ((ret = CGXDLMS_AppendData(obj, attributeIndex, &bb, value)) != 0)
            {
                status = DLMS_ERROR_CODE_HARDWARE_FAULT;
            }
        }
    }

    // CGXDLMSLNParameters p(&m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 1, NULL, &bb, status);
    CGXDLMSLNParameters para;
    CGXDLMSLNParameters_(&para, &p->m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 1, NULL, &bb, status);

    ret = CGXDLMS_GetLNPdu(&para, &p->m_ReplyData);

    //CGXDLMSLNParameters_d(&para);

    if (p->m_Settings.m_Count != p->m_Settings.m_Index
        || bb.m_Size != bb.m_Position)
    {
        if (p->m_Transaction != NULL)
        {
            //delete m_Transaction;
            CGXDLMSLongTransaction_d(p->m_Transaction);
            DLMSPort_free(p->m_Transaction);

            p->m_Transaction = NULL;
        }
        // m_Transaction = new CGXDLMSLongTransaction(arr, DLMS_COMMAND_GET_REQUEST, bb);
        p->m_Transaction = DLMSPort_malloc(sizeof(CGXDLMSLongTransaction));
        CGXDLMSLongTransaction_(p->m_Transaction, &arr, DLMS_COMMAND_GET_REQUEST, &bb);
    }

    CGXByteBuffer_d(&bb);
    CGXDLMSValueEventCollection_d(&arr);
    return ret;
}

int CGXDLMSServer_GetRequestNextDataBlock(CGXDLMSServer* p, CGXByteBuffer* data, unsigned char invokeID)
{
    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    int ret;
    unsigned long index;
    // Get block index.
    if ((ret = CGXByteBuffer_GetUInt32_1(data, &index)) != 0)
    {
        CGXByteBuffer_d(&bb);
        return ret;
    }
    if (index != p->m_Settings.m_BlockIndex)
    {
//        CGXDLMSLNParameters p(&m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 2,
//            NULL, &bb,
//            DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);

        CGXDLMSLNParameters para;
        CGXDLMSLNParameters_(&para, &p->m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 2,
                             NULL, &bb, DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);

        ret = CGXDLMS_GetLNPdu(&para, &p->m_ReplyData);

        //CGXDLMSLNParameters_d(&para);
        CGXByteBuffer_d(&bb);
        return ret;
    }
    else
    {
        p->m_Settings.m_BlockIndex += 1;

        // CGXDLMSLNParameters p(&m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 2, NULL, &bb, DLMS_ERROR_CODE_OK);
        CGXDLMSLNParameters para;
        CGXDLMSLNParameters_(&para, &p->m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 2,
                             NULL, &bb, DLMS_ERROR_CODE_OK);

        // If m_Transaction is not in progress.
        if (p->m_Transaction == NULL)
        {
            para.m_Status = DLMS_ERROR_CODE_NO_LONG_GET_OR_READ_IN_PROGRESS;
        }
        else
        {
            CGXByteBuffer_Set_2(&bb, CGXDLMSLongTransaction_GetData(p->m_Transaction), 0, -1);
            unsigned char moreData = p->m_Settings.m_Index != p->m_Settings.m_Count;
            if (moreData)
            {
                // If there is multiple blocks on the buffer.
                // This might happen when Max PDU size is very small.
                if (bb.m_Size < p->m_Settings.m_MaxReceivePDUSize)
                {
                    CGXDLMSVariant value;
                    CGXDLMSVariant_1(&value);

                    // std::vector<CGXDLMSValueEventArg*>
                    Vector* vec = CGXDLMSLongTransaction_GetTargets(p->m_Transaction);
                    for (unsigned int a = Vector_begin(vec); a != Vector_end(vec); ++a)
                    {
                        CGXDLMSValueEventArg** arg = Vector_at(vec, a);

                        p->PreRead(p, CGXDLMSLongTransaction_GetTargets(p->m_Transaction));
                        if (!(*arg)->m_Handled)
                        {
                            if ((ret = (*arg)->m_Target->GetValue((*arg)->m_Target,
                                                                                      &p->m_Settings, *arg)) != 0)
                            {
                                CGXDLMSVariant_d(&value);
                                //CGXDLMSLNParameters_d(&para);
                                CGXByteBuffer_d(&bb);
                                return ret;
                            }

                            Vector arr; // std::vector<CGXDLMSValueEventArg*>
                            Vector_(&arr, sizeof(CGXDLMSValueEventArg*), NULL, NULL);

                            Vector_push_back(&arr, arg);
                            p->PostRead(p, &arr);

                            Vector_d(&arr);
                        }

                        CGXDLMSVariant_copy_1(&value, CGXDLMSValueEventArg_GetValue(*arg));

                        // Add data.
                        if ((*arg)->m_ByteArray && value.st.vt == DLMS_DATA_TYPE_OCTET_STRING)
                        {
                            // If byte array is added do not add type.
                            CGXByteBuffer_Set_1(&bb, value.st.un.byteArr, CGXDLMSVariant_GetSize_1(&value));
                        }
                        else if ((ret = CGXDLMS_AppendData((*arg)->m_Target,
                                                            (*arg)->m_Index, &bb, &value)) != 0)
                        {
                            CGXDLMSVariant_d(&value);
                            //CGXDLMSLNParameters_d(&para);
                            CGXByteBuffer_d(&bb);
                            return DLMS_ERROR_CODE_HARDWARE_FAULT;
                        }
                    }

                    CGXDLMSVariant_d(&value);
                }
            }
            para.m_MultipleBlocks = true;
            ret = CGXDLMS_GetLNPdu(&para, &p->m_ReplyData);
            moreData = p->m_Settings.m_Index != p->m_Settings.m_Count;
            if (moreData || bb.m_Size - bb.m_Position != 0)
            {
                CGXDLMSLongTransaction_SetData(p->m_Transaction, &bb);
            }
            else
            {
                //delete m_Transaction;
                CGXDLMSLongTransaction_d(p->m_Transaction);
                DLMSPort_free(p->m_Transaction);

                p->m_Transaction = NULL;

                p->m_Settings.m_BlockIndex = 1;;
            }
        }

        //CGXDLMSLNParameters_d(&para);
    }

    CGXByteBuffer_d(&bb);
    return ret;
}

int CGXDLMSServer_GetRequestWithList(CGXDLMSServer* p, CGXByteBuffer* data, unsigned char invokeID)
{
    int ret;
    unsigned char attributeIndex;
    unsigned short id;
    unsigned long pos, cnt;
    if ((ret = GXHelpers_GetObjectCount(data, &cnt)) != 0)
    {
        return ret;
    }

    CGXDLMSValueEventCollection list;
    CGXDLMSValueEventCollection_(&list);

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    GXHelpers_SetObjectCount(cnt, &bb);
    for (pos = 0; pos != cnt; ++pos)
    {
        if ((ret = CGXByteBuffer_GetUInt16_1(data, &id)) != 0)
        {
            CGXByteBuffer_d(&bb);
            CGXDLMSValueEventCollection_d(&list);
            return ret;
        }
        DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)id;
        unsigned char * ln;
        ln = data->m_Data + data->m_Position;
        CGXByteBuffer_SetPosition(data, data->m_Position + 6);
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &attributeIndex)) != 0)
        {
            CGXByteBuffer_d(&bb);
            CGXDLMSValueEventCollection_d(&list);
            return ret;
        }
        CGXDLMSObject* obj = CGXDLMSObjectCollection_FindByLN_2(CGXDLMSSettings_GetObjects(&(p->m_Settings)),
                                                                ci, ln);
        if (obj == NULL)
        {
            String name;
            String_(&name);

            GXHelpers_GetLogicalName_1(ln, &name);
            obj = p->FindObject(p, ci, 0, &name);

            String_d(&name);
        }
        if (obj == NULL)
        {
            // Access Error : Device reports a undefined object.
            // CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, obj, attributeIndex);
            CGXDLMSValueEventArg* e = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
            CGXDLMSValueEventArg_1(e, p, obj, attributeIndex);

            e->m_Error = DLMS_ERROR_CODE_UNDEFINED_OBJECT;
            CGXDLMSValueEventCollection_push_back(&list, &e);
        }
        else
        {
            // AccessSelection
            unsigned char selection, selector = 0;

            CGXDLMSVariant parameters;
            CGXDLMSVariant_1(&parameters);

            if ((ret = CGXByteBuffer_GetUInt8_1(data, &selection)) != 0)
            {
                CGXDLMSVariant_d(&parameters);
                CGXByteBuffer_d(&bb);
                CGXDLMSValueEventCollection_d(&list);
                return ret;
            }
            if (selection != 0)
            {
                if ((ret = CGXByteBuffer_GetUInt8_1(data, &selector)) != 0)
                {
                    CGXDLMSVariant_d(&parameters);
                    CGXByteBuffer_d(&bb);
                    CGXDLMSValueEventCollection_d(&list);
                    return ret;
                }

                CGXDataInfo i;
                CGXDataInfo_(&i);

                if ((ret = GXHelpers_GetData(data, &i, &parameters)) != 0)
                {
                    CGXDLMSVariant_d(&parameters);
                    CGXByteBuffer_d(&bb);
                    CGXDLMSValueEventCollection_d(&list);
                    return ret;
                }
            }

            // CGXDLMSValueEventArg *arg = new CGXDLMSValueEventArg(this, obj, attributeIndex, selector, parameters);
            CGXDLMSValueEventArg *arg = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
            CGXDLMSValueEventArg_2(arg, p, obj, attributeIndex, selector, &parameters);

            CGXDLMSValueEventCollection_push_back(&list, &arg);
            if (p->GetAttributeAccess(p, arg) == DLMS_ACCESS_MODE_NONE)
            {
                // Read Write denied.
                arg->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
            }

            CGXDLMSVariant_d(&parameters);
        }
    }
    p->PreRead(p, (Vector*) &list);
    pos = 0;

    // std::vector<CGXDLMSValueEventArg*>
    for (unsigned int i = CGXDLMSValueEventCollection_begin(&list);
         i != CGXDLMSValueEventCollection_end(&list); ++i)
    {
        CGXDLMSValueEventArg** it = CGXDLMSValueEventCollection_at(&list, i);

        if (!(*it)->m_Handled)
        {
            ret = (*it)->m_Target->GetValue((*it)->m_Target,
                                                                &p->m_Settings, *it);
        }

        CGXDLMSVariant* value = CGXDLMSValueEventArg_GetValue(*it);

        CGXByteBuffer_SetUInt8_1(&bb, (*it)->m_Error);
        if ((*it)->m_ByteArray && value->st.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            // If byte array is added do not add type.
            CGXByteBuffer_Set_1(&bb, value->st.un.byteArr, CGXDLMSVariant_GetSize_1(value));
        }
        else if ((ret = CGXDLMS_AppendData((*it)->m_Target,
                                           (*it)->m_Index, &bb, value)) != 0)
        {
            CGXByteBuffer_d(&bb);
            CGXDLMSValueEventCollection_d(&list);
            return DLMS_ERROR_CODE_HARDWARE_FAULT;
        }
        if (p->m_Settings.m_Index != p->m_Settings.m_Count)
        {
            if (p->m_Transaction != NULL)
            {
                // delete m_Transaction;
                CGXDLMSLongTransaction_d(p->m_Transaction);
                DLMSPort_free(p->m_Transaction);

                p->m_Transaction = NULL;
            }

            CGXByteBuffer empty;
            CGXByteBuffer_1(&empty);

            p->m_Transaction = DLMSPort_malloc(sizeof(CGXDLMSLongTransaction));
            CGXDLMSLongTransaction_(p->m_Transaction, &list, DLMS_COMMAND_GET_REQUEST, &empty);

            CGXByteBuffer_d(&empty);
        }
        ++pos;
    }
    p->PostRead(p, (Vector*) &list);

    //  CGXDLMSLNParameters p(&m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 3, NULL, &bb, 0xFF);
    CGXDLMSLNParameters para;
    CGXDLMSLNParameters_(&para, &p->m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE, 3,
                         NULL, &bb, 0xFF);

    ret = CGXDLMS_GetLNPdu(&para, &p->m_ReplyData);

    //CGXDLMSLNParameters_d(&para);

    CGXByteBuffer_d(&bb);
    CGXDLMSValueEventCollection_d(&list);
    return ret;
}

int CGXDLMSServer_HandleGetRequest(CGXDLMSServer* p, CGXByteBuffer* data)
{
    // Return error if connection is not established.
    if (!p->m_Settings.m_Connected)
    {
        CGXDLMSServer_GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
                                                    DLMS_SERVICE_ERROR_SERVICE, DLMS_SERVICE_UNSUPPORTED,
                                                    &p->m_ReplyData);
        return 0;
    }
    int ret;
    unsigned char ch, invokeID;
    // Get type.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    DLMS_GET_COMMAND_TYPE type = (DLMS_GET_COMMAND_TYPE)ch;
    // Get invoke ID and priority.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &invokeID)) != 0)
    {
        return ret;
    }
    // GetRequest normal
    if (type == DLMS_GET_COMMAND_TYPE_NORMAL)
    {
        ret = CGXDLMSServer_GetRequestNormal(p, data, invokeID);
    }
    else if (type == DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK)
    {
        // Get request for next data block
        ret = CGXDLMSServer_GetRequestNextDataBlock(p, data, invokeID);
    }
    else if (type == DLMS_GET_COMMAND_TYPE_WITH_LIST)
    {
        // Get request with a list.
        ret = CGXDLMSServer_GetRequestWithList(p, data, invokeID);
    }
    else
    {
        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        p->m_Settings.m_BlockIndex = 1;;
        // Access Error : Device reports a hardware fault.
        CGXByteBuffer_SetUInt8_1(&bb, DLMS_ERROR_CODE_HARDWARE_FAULT);

//        CGXDLMSLNParameters p(&m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE,
//            type, NULL, &bb, DLMS_ERROR_CODE_OK);
        CGXDLMSLNParameters para;
        CGXDLMSLNParameters_(&para, &p->m_Settings, invokeID, DLMS_COMMAND_GET_RESPONSE,
                             type, NULL, &bb, DLMS_ERROR_CODE_OK);

        ret = CGXDLMS_GetLNPdu(&para, &p->m_ReplyData);

        //CGXDLMSLNParameters_d(&para);
        CGXByteBuffer_d(&bb);
    }
    return ret;
}

/**
 * Find Short Name object.
 *
 * @param sn
 */
int CGXDLMSServer_FindSNObject(CGXDLMSServer* p, int sn, CGXSNInfo* i)
{
    unsigned char offset, count;

    // CGXDLMSObjectCollection::iterator
    for (unsigned a = CGXDLMSObjectCollection_begin(CGXDLMSServer_GetItems(p));
         a != CGXDLMSObjectCollection_end(CGXDLMSServer_GetItems(p)); ++a)
    {
        CGXDLMSObject** it = CGXDLMSObjectCollection_at(CGXDLMSServer_GetItems(p), a);

        if (sn >= (*it)->m_SN)
        {
            // If attribute is accessed.
            if (sn < (*it)->m_SN + (*it)->GetAttributeCount(*it) * 8)
            {
                i->m_Action = false;
                i->m_Item = *it;
                i->m_Index = ((sn - (*it)->m_SN) / 8) + 1;
                break;
            }
            else
            {
                // If method is accessed.
                CGXDLMS_GetActionInfo((*it)->m_ObjectType, &offset, &count);
                if (sn < (*it)->m_SN + offset + (8 * count))
                {
                    i->m_Item = *it;
                    i->m_Action = true;
                    i->m_Index = (sn - (*it)->m_SN - offset) / 8 + 1;
                    break;
                }
            }
        }
    }
    if (i->m_Item == NULL)
    {
        String ln;
        String_(&ln);

        i->m_Item = p->FindObject(p, DLMS_OBJECT_TYPE_NONE, sn, &ln);

        String_d(&ln);
    }
    return 0;
}

/**
* Get data for Read command.
*
* @param settings
*            DLMS settings.
* @param list
*            received objects.
* @param data
*            Data as byte array.
* @param type
*            Response type.
*/
int CGXDLMSServer_GetReadData(CGXDLMSSettings* settings,
                              Vector* list, // std::vector<CGXDLMSValueEventArg*>&
                              CGXByteBuffer* data,
                              DLMS_SINGLE_READ_RESPONSE* type)
{
    int ret = 0;
    unsigned char first = 1;
    *type = DLMS_SINGLE_READ_RESPONSE_DATA;

    // std::vector<CGXDLMSValueEventArg*>::iterator
    for (unsigned int ee = Vector_begin(list); ee != Vector_end(list); ++ee)
    {
        CGXDLMSValueEventArg** e = Vector_at(list, ee);

        if (!(*e)->m_Handled)
        {
            // If action.
            if ((*e)->m_Action)
            {
                ret = (*e)->m_Target->Invoke((*e)->m_Target,
                                                                 settings, (*e));
            }
            else
            {
                ret = (*e)->m_Target->GetValue((*e)->m_Target,
                                                                   settings, (*e));
            }
        }
        if (ret != 0)
        {
            return ret;
        }

        CGXDLMSVariant* value = CGXDLMSValueEventArg_GetValue(*e);

        if ((*e)->m_Error == DLMS_ERROR_CODE_OK)
        {
            if (!first && Vector_size(list) != 1)
            {
                CGXByteBuffer_SetUInt8_1(data, DLMS_SINGLE_READ_RESPONSE_DATA);
            }
            // If action.
            if ((*e)->m_Action)
            {
                ret = GXHelpers_SetData(data, value->st.vt, value);
            }
            else
            {
                ret = CGXDLMS_AppendData((*e)->m_Target,
                                         (*e)->m_Index, data, value);
            }
        }
        else
        {
            if (!first && Vector_size(list) != 1)
            {
                CGXByteBuffer_SetUInt8_1(data, DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR);
            }
            CGXByteBuffer_SetUInt8_1(data, (*e)->m_Error);
            *type = DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR;
        }
        first = false;
    }
    return ret;
}

int CGXDLMSServer_HandleRead(
    CGXDLMSServer* p,
    DLMS_VARIABLE_ACCESS_SPECIFICATION type,
    CGXByteBuffer* data,
    CGXDLMSValueEventCollection* list,
    Vector* reads, //std::vector<CGXDLMSValueEventArg*>&
    Vector* actions) //std::vector<CGXDLMSValueEventArg*>&
{
    CGXSNInfo i;
    CGXSNInfo_(&i);

    int ret;
    unsigned char ch;
    unsigned short sn;
    if ((ret = CGXByteBuffer_GetUInt16_1(data, &sn)) != 0)
    {
        return ret;
    }
    if ((ret = CGXDLMSServer_FindSNObject(p, sn, &i)) != 0)
    {
        return ret;
    }

    // CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, i.GetItem(), i.GetIndex());
    CGXDLMSValueEventArg* e = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
    CGXDLMSValueEventArg_1(e, p, i.m_Item, i.m_Index);

    e->m_Action = i.m_Action;
    CGXDLMSValueEventCollection_push_back(list, &e);
    if (type == DLMS_VARIABLE_ACCESS_SPECIFICATION_PARAMETERISED_ACCESS)
    {
        CGXDLMSVariant params;
        CGXDLMSVariant_1(&params);

        CGXDataInfo di;
        CGXDataInfo_(&di);

        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            CGXDLMSVariant_d(&params);
            return ret;
        }
        e->m_Selector = ch;
        if ((ret = GXHelpers_GetData(data, &di, &params)) != 0)
        {
            CGXDLMSVariant_d(&params);
            return ret;
        }
        CGXDLMSValueEventArg_SetParameters(e, &params);

        CGXDLMSVariant_d(&params);
    }
    // Return error if connection is not established.
    if (!p->m_Settings.m_Connected
        && (!e->m_Action
            || e->m_Target->m_SN != 0xFA00
            || e->m_Index != 8))
    {
        CGXDLMSServer_GenerateConfirmedServiceError(
            DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR, DLMS_SERVICE_ERROR_SERVICE,
            DLMS_SERVICE_UNSUPPORTED, &p->m_ReplyData);
        return 0;
    }

    if (p->GetAttributeAccess(p, e) == DLMS_ACCESS_MODE_NONE)
    {
        e->m_Error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
    }
    else
    {
        if (e->m_Target->m_ObjectType == DLMS_OBJECT_TYPE_PROFILE_GENERIC
                && e->m_Index == 2)
        {
            e->m_RowToPdu = CGXDLMSServer_GetRowsToPdu(p, (CGXDLMSProfileGeneric*)(e->m_Target));
        }
        if (e->m_Action)
        {
            Vector_push_back(actions, &e);
        }
        else
        {
            Vector_push_back(reads, &e);
        }
    }
    return ret;
}

int CGXDLMSServer_HandleReadBlockNumberAccess(CGXDLMSServer* p, CGXByteBuffer* data)
{
    unsigned short blockNumber;
    int ret;
    if ((ret = CGXByteBuffer_GetUInt16_1(data, &blockNumber)) != 0)
    {
        return ret;
    }
    if (blockNumber != p->m_Settings.m_BlockIndex)
    {
        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_SetUInt8_1(&bb, DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);

//        CGXDLMSSNParameters p(&m_Settings,
//            DLMS_COMMAND_READ_RESPONSE, 1,
//            DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);
        CGXDLMSSNParameters para;
        CGXDLMSSNParameters_(&para, &p->m_Settings,
                             DLMS_COMMAND_READ_RESPONSE, 1,
                             DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);

        ret = CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);
        p->m_Settings.m_BlockIndex = 1;;

        //CGXDLMSSNParameters_d(&para);
        CGXByteBuffer_d(&bb);
        return ret;
    }
    if (p->m_Settings.m_Index != p->m_Settings.m_Count
        && CGXDLMSLongTransaction_GetData(p->m_Transaction)->m_Size < p->m_Settings.m_MaxReceivePDUSize)
    {
        Vector reads; // std::vector<CGXDLMSValueEventArg*>
        Vector_(&reads, sizeof(CGXDLMSValueEventArg*), NULL, NULL);

        Vector actions; // std::vector<CGXDLMSValueEventArg*>
        Vector_(&actions, sizeof(CGXDLMSValueEventArg*), NULL, NULL);

        // std::vector<CGXDLMSValueEventArg*>
        Vector* vec = CGXDLMSLongTransaction_GetTargets(p->m_Transaction);
        for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
        {
            CGXDLMSValueEventArg** it = Vector_at(vec, i);

            if ((*it)->m_Action)
            {
                Vector_push_back(&actions, it);
            }
            else
            {
                Vector_push_back(&reads, it);

            }
        }
        if (Vector_size(&reads) != 0)
        {
            p->PreRead(p, &reads);
        }

        if (Vector_size(&actions) != 0)
        {
            p->PreAction(p, &actions);
        }
        DLMS_SINGLE_READ_RESPONSE requestType;

        Vector* list = CGXDLMSLongTransaction_GetTargets(p->m_Transaction); // std::vector<CGXDLMSValueEventArg*>&
        CGXByteBuffer* data2 = CGXDLMSLongTransaction_GetData(p->m_Transaction);

        ret = CGXDLMSServer_GetReadData(&p->m_Settings, list, data2, &requestType);
        if (Vector_size(&reads) != 0)
        {
            p->PostRead(p, &reads);
        }

        if (Vector_size(&actions) != 0)
        {
            p->PostAction(p, &actions);
        }

        Vector_d(&reads);
        Vector_d(&actions);
    }

    p->m_Settings.m_BlockIndex += 1;

    CGXByteBuffer* tmp = CGXDLMSLongTransaction_GetData(p->m_Transaction);

//    CGXDLMSSNParameters p(&m_Settings, DLMS_COMMAND_READ_RESPONSE, 1,
//        DLMS_SINGLE_READ_RESPONSE_DATA_BLOCK_RESULT, NULL, &tmp);
    CGXDLMSSNParameters para;
    CGXDLMSSNParameters_(&para, &p->m_Settings, DLMS_COMMAND_READ_RESPONSE, 1,
                         DLMS_SINGLE_READ_RESPONSE_DATA_BLOCK_RESULT, NULL, tmp);

    para.m_MultipleBlocks = true;
    ret = CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);

    //CGXDLMSSNParameters_d(&para);

    // If all data is sent.
    if (CGXDLMSLongTransaction_GetData(p->m_Transaction)->m_Size
            == CGXDLMSLongTransaction_GetData(p->m_Transaction)->m_Position)
    {
        // delete m_Transaction;
        CGXDLMSLongTransaction_d(p->m_Transaction);
        DLMSPort_free(p->m_Transaction);

        p->m_Transaction = NULL;

        p->m_Settings.m_BlockIndex = 1;;
    }
    else
    {
        CGXByteBuffer_Trim(CGXDLMSLongTransaction_GetData(p->m_Transaction));
    }
    return ret;
}

//int CGXDLMSServer::HandleReadDataBlockAccess(
//    DLMS_COMMAND command,
//    CGXByteBuffer& data,
//    int cnt)
int CGXDLMSServer_HandleReadDataBlockAccess(CGXDLMSServer* p,
                                            DLMS_COMMAND command,
                                            CGXByteBuffer* data,
                                            int cnt)
{
    int ret;
    unsigned long size;
    unsigned short blockNumber;
    unsigned char isLast, ch;

    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    isLast = ch != 0;
    if ((ret = CGXByteBuffer_GetUInt16_1(data, &blockNumber)) != 0)
    {
        return ret;
    }
    if (blockNumber != p->m_Settings.m_BlockIndex)
    {
        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_SetUInt8_1(&bb, DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);

        // CGXDLMSSNParameters p(&m_Settings, command, 1, DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);
        CGXDLMSSNParameters para;
        CGXDLMSSNParameters_(&para, &p->m_Settings, command, 1,
                             DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);

        ret = CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);
        p->m_Settings.m_BlockIndex = 1;;

        //CGXDLMSSNParameters_d(&para);
        CGXByteBuffer_d(&bb);
        return ret;
    }

    unsigned char count = 1, type = DLMS_DATA_TYPE_OCTET_STRING;

    if (command == DLMS_COMMAND_WRITE_RESPONSE)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &count)) != 0 ||
            (ret = CGXByteBuffer_GetUInt8_1(data, &type)) != 0)
        {
            return ret;
        }
    }
    if ((ret = GXHelpers_GetObjectCount(data, &size)) != 0)
    {
        return ret;
    }
    unsigned long realSize = data->m_Size - data->m_Position;
    if ((count != 1) || (type != DLMS_DATA_TYPE_OCTET_STRING) || (size != realSize))
    {
        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_SetUInt8_1(&bb, DLMS_ERROR_CODE_BLOCK_UNAVAILABLE);

//        CGXDLMSSNParameters p(&m_Settings, command, cnt,
//            DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);
        CGXDLMSSNParameters para;
        CGXDLMSSNParameters_(&para, &p->m_Settings, command, cnt,
                             DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);

        ret = CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);;
        p->m_Settings.m_BlockIndex = 1;;

        //CGXDLMSSNParameters_d(&para);
        CGXByteBuffer_d(&bb);
        return ret;
    }
    if (p->m_Transaction == NULL)
    {
        CGXDLMSValueEventCollection tmp;
        CGXDLMSValueEventCollection_(&tmp);

        p->m_Transaction = DLMSPort_malloc(sizeof(CGXDLMSLongTransaction));
        CGXDLMSLongTransaction_(p->m_Transaction, &tmp, command, data);

        CGXDLMSValueEventCollection_d(&tmp);
    }
    else
    {
        CGXByteBuffer_Set_2(CGXDLMSLongTransaction_GetData(p->m_Transaction),
                            data, data->m_Position, -1);
    }
    if (!isLast)
    {
        CGXByteBuffer bb;
        CGXByteBuffer_1(&bb);

        CGXByteBuffer_SetUInt16(&bb, blockNumber);
        p->m_Settings.m_BlockIndex += 1;
        if (command == DLMS_COMMAND_READ_RESPONSE)
        {
            type = DLMS_SINGLE_READ_RESPONSE_BLOCK_NUMBER;
        }
        else
        {
            type = DLMS_SINGLE_WRITE_RESPONSE_BLOCK_NUMBER;
        }

        // CGXDLMSSNParameters p(&m_Settings, command, cnt, type, NULL, &bb);
        CGXDLMSSNParameters para;
        CGXDLMSSNParameters_(&para, &p->m_Settings, command, cnt, type, NULL, &bb);

        ret = CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);

        //CGXDLMSSNParameters_d(&para);
        CGXByteBuffer_d(&bb);
    }
    else
    {
        if (p->m_Transaction != NULL)
        {
            CGXByteBuffer_SetSize(data, 0);
            CGXByteBuffer_Set_2(data, CGXDLMSLongTransaction_GetData(p->m_Transaction), 0, -1);

            // delete m_Transaction;
            CGXDLMSLongTransaction_d(p->m_Transaction);
            DLMSPort_free(p->m_Transaction);

            p->m_Transaction = NULL;
        }
        if (command == DLMS_COMMAND_READ_RESPONSE)
        {
            ret = CGXDLMSServer_HandleReadRequest(p, data);
        }
        else
        {
            ret = CGXDLMSServer_HandleWriteRequest(p, data);
        }
        p->m_Settings.m_BlockIndex = 1;;
    }
    return ret;
}

//int CGXDLMSServer::ReturnSNError(DLMS_COMMAND cmd, DLMS_ERROR_CODE error)
int CGXDLMSServer_ReturnSNError(CGXDLMSServer* p, DLMS_COMMAND cmd, DLMS_ERROR_CODE error)
{
    int ret;

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    CGXByteBuffer_SetUInt8_1(&bb, error);

//    CGXDLMSSNParameters p(&m_Settings, cmd, 1,
//        DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);
    CGXDLMSSNParameters para;
    CGXDLMSSNParameters_(&para, &p->m_Settings, cmd, 1,
                         DLMS_SINGLE_READ_RESPONSE_DATA_ACCESS_ERROR, &bb, NULL);

    ret = CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);;
    p->m_Settings.m_BlockIndex = 1;;

    //CGXDLMSSNParameters_d(&para);
    CGXByteBuffer_d(&bb);
    return ret;
}

//int CGXDLMSServer::HandleReadRequest(CGXByteBuffer& data)
int CGXDLMSServer_HandleReadRequest(CGXDLMSServer* p, CGXByteBuffer* data)
{
    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    int ret;
    unsigned char ch;
    unsigned long cnt = 0xFF;
    DLMS_VARIABLE_ACCESS_SPECIFICATION type;

    CGXDLMSValueEventCollection list;
    CGXDLMSValueEventCollection_(&list);

    Vector reads; // std::vector<CGXDLMSValueEventArg*>
    Vector_(&reads, sizeof(CGXDLMSValueEventArg*), NULL, NULL);

    Vector actions; // std::vector<CGXDLMSValueEventArg*>
    Vector_(&actions, sizeof(CGXDLMSValueEventArg*), NULL, NULL);

    // If get next frame.
    if (data->m_Size == 0)
    {
        if (p->m_Transaction != NULL)
        {
            CGXByteBuffer_d(&bb);
            CGXDLMSValueEventCollection_d(&list);
            Vector_d(&reads);
            Vector_d(&actions);
            return 0;
        }
        CGXByteBuffer_Set_2(&bb, &p->m_ReplyData, 0, -1);
        CGXByteBuffer_Clear(&p->m_ReplyData);

        // std::vector<CGXDLMSValueEventArg*>
        Vector* vec = CGXDLMSLongTransaction_GetTargets(p->m_Transaction);
        for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
        {
            CGXDLMSValueEventArg** it = Vector_at(vec, i);
            CGXDLMSValueEventCollection_push_back(&list, it);
        }
    }
    else
    {
        if ((ret = GXHelpers_GetObjectCount(data, &cnt)) != 0)
        {
            CGXByteBuffer_d(&bb);
            CGXDLMSValueEventCollection_d(&list);
            Vector_d(&reads);
            Vector_d(&actions);
            return ret;
        }

        CGXSNInfo info;
        CGXSNInfo_(&info);

        for (unsigned long pos = 0; pos != cnt; ++pos)
        {
            if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
            {
                CGXByteBuffer_d(&bb);
                CGXDLMSValueEventCollection_d(&list);
                Vector_d(&reads);
                Vector_d(&actions);
                return ret;
            }
            type = (DLMS_VARIABLE_ACCESS_SPECIFICATION)ch;
            switch (type)
            {
            case DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME:
            case DLMS_VARIABLE_ACCESS_SPECIFICATION_PARAMETERISED_ACCESS:
                ret = CGXDLMSServer_HandleRead(p, type, data, &list, &reads, &actions);
                break;
            case DLMS_VARIABLE_ACCESS_SPECIFICATION_BLOCK_NUMBER_ACCESS:
                CGXByteBuffer_d(&bb);
                CGXDLMSValueEventCollection_d(&list);
                Vector_d(&reads);
                Vector_d(&actions);
                return CGXDLMSServer_HandleReadBlockNumberAccess(p, data);
            case DLMS_VARIABLE_ACCESS_SPECIFICATION_READ_DATA_BLOCK_ACCESS:
                CGXByteBuffer_d(&bb);
                CGXDLMSValueEventCollection_d(&list);
                Vector_d(&reads);
                Vector_d(&actions);
                return CGXDLMSServer_HandleReadDataBlockAccess(p, DLMS_COMMAND_READ_RESPONSE, data, cnt);
            default:
                CGXByteBuffer_d(&bb);
                CGXDLMSValueEventCollection_d(&list);
                Vector_d(&reads);
                Vector_d(&actions);
                return CGXDLMSServer_ReturnSNError(p, DLMS_COMMAND_READ_RESPONSE, DLMS_ERROR_CODE_READ_WRITE_DENIED);
            }
        }
        if (Vector_size(&reads) != 0)
        {
            p->PreRead(p, &reads);
        }

        if (Vector_size(&actions) != 0)
        {
            p->PreAction(p, &actions);
        }
    }
    DLMS_SINGLE_READ_RESPONSE requestType;
    ret = CGXDLMSServer_GetReadData(&p->m_Settings, (Vector*) &list, &bb, &requestType);
    if (Vector_size(&reads) != 0)
    {
        p->PostRead(p, &reads);
    }

    if (Vector_size(&actions) != 0)
    {
        p->PostAction(p, &actions);
    }

//    CGXDLMSSNParameters p(&m_Settings, DLMS_COMMAND_READ_RESPONSE, cnt,
//        requestType, NULL, &bb);

    CGXDLMSSNParameters para;
    CGXDLMSSNParameters_(&para, &p->m_Settings, DLMS_COMMAND_READ_RESPONSE, cnt,
                         requestType, NULL, &bb);

    CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);

    //CGXDLMSSNParameters_d(&para);

    if (p->m_Transaction == NULL && (bb.m_Size != bb.m_Position
        || p->m_Settings.m_Count != p->m_Settings.m_Index))
    {
        p->m_Transaction = DLMSPort_malloc(sizeof(CGXDLMSLongTransaction));
        CGXDLMSLongTransaction_(p->m_Transaction, &list, DLMS_COMMAND_READ_REQUEST, &bb);
    }
    else if (p->m_Transaction != NULL)
    {
        CGXByteBuffer_Set_2(&p->m_ReplyData, &bb, 0, -1);
    }

    CGXByteBuffer_d(&bb);
    CGXDLMSValueEventCollection_d(&list);
    Vector_d(&reads);
    Vector_d(&actions);
    return 0;
}

//int CGXDLMSServer::HandleWriteRequest(CGXByteBuffer& data)
int CGXDLMSServer_HandleWriteRequest(CGXDLMSServer* p, CGXByteBuffer* data)
{
    // Return error if connection is not established.
    if (!p->m_Settings.m_Connected)
    {
        CGXDLMSServer_GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
                                                    DLMS_SERVICE_ERROR_SERVICE,
                                                    DLMS_SERVICE_UNSUPPORTED, &p->m_ReplyData);
        return 0;
    }
    int ret;
    unsigned char ch;
    unsigned short sn;
    unsigned long cnt, pos;
    DLMS_VARIABLE_ACCESS_SPECIFICATION type;

    // Get object count.
    if ((ret = GXHelpers_GetObjectCount(data, &cnt)) != 0)
    {
        return ret;
    }

    Vector targets; // std::vector<CGXSNInfo>
    Vector_(&targets, sizeof(CGXSNInfo), NULL, NULL);

    CGXByteBuffer results;
    CGXByteBuffer_2(&results, cnt);

    for (pos = 0; pos != cnt; ++pos)
    {
        if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
        {
            Vector_d(&targets);
            CGXByteBuffer_d(&results);
            return ret;
        }
        type = (DLMS_VARIABLE_ACCESS_SPECIFICATION)ch;

        CGXSNInfo i;
        CGXSNInfo_(&i);

        switch (type)
        {
        case DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME:
            if ((ret = CGXByteBuffer_GetUInt16_1(data, &sn)) != 0)
            {
                Vector_d(&targets);
                CGXByteBuffer_d(&results);
                return ret;
            }
            if ((ret = CGXDLMSServer_FindSNObject(p, sn, &i)) != 0)
            {
                Vector_d(&targets);
                CGXByteBuffer_d(&results);
                return ret;
            }
            Vector_push_back(&targets, &i);
            // If target is unknown.
            if (i.m_Item == NULL)
            {
                // Device reports a undefined object.
                CGXByteBuffer_SetUInt8_1(&results, DLMS_ERROR_CODE_UNDEFINED_OBJECT);
            }
            else
            {
                CGXByteBuffer_SetUInt8_1(&results, DLMS_ERROR_CODE_OK);
            }
            break;
        case DLMS_VARIABLE_ACCESS_SPECIFICATION_WRITE_DATA_BLOCK_ACCESS:
            Vector_d(&targets);
            CGXByteBuffer_d(&results);
            return CGXDLMSServer_HandleReadDataBlockAccess(p, DLMS_COMMAND_WRITE_RESPONSE, data, cnt);
        default:
            // Device reports a HW error.
            CGXByteBuffer_SetUInt8_1(&results, DLMS_ERROR_CODE_HARDWARE_FAULT);
        }
    }
    // Get data count.
    if ((ret = GXHelpers_GetObjectCount(data, &cnt)) != 0)
    {
        Vector_d(&targets);
        CGXByteBuffer_d(&results);
        return ret;
    }

    CGXDLMSVariant value;
    CGXDLMSVariant_1(&value);

    CGXDataInfo di;
    CGXDataInfo_(&di);

    for (pos = 0; pos != cnt; ++pos)
    {
        if ((ret = CGXByteBuffer_GetUInt8_2(&results, pos, &ch)) != 0)
        {
            CGXDLMSVariant_d(&value);
            Vector_d(&targets);
            CGXByteBuffer_d(&results);
            return ret;
        }
        if (ch == 0)
        {
            // If object has found.
            //CGXSNInfo target = *(targets.begin() + pos);
            CGXSNInfo target = *((CGXSNInfo*) Vector_at(&targets,  pos));

            ret = GXHelpers_GetData(data, &di, &value);
            if (value.st.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                DLMS_DATA_TYPE dt;
                ret = target.m_Item->GetDataType(target.m_Item,
                                                              target.m_Index, &dt);
                if (dt != DLMS_DATA_TYPE_NONE && dt != DLMS_DATA_TYPE_OCTET_STRING)
                {
                    CGXByteBuffer bb;
                    CGXByteBuffer_1(&bb);

                    CGXByteBuffer_Set_1(&bb, value.st.un.byteArr, CGXDLMSVariant_GetSize_1(&value));
                    CGXDLMSVariant_Clear(&value);
                    if ((ret = CGXDLMSClient_ChangeType_1(&bb, dt, &value)) != 0)
                    {
                        CGXByteBuffer_d(&bb);
                        CGXDLMSVariant_d(&value);
                        Vector_d(&targets);
                        CGXByteBuffer_d(&results);
                        return ret;
                    }

                    CGXByteBuffer_d(&bb);
                }
            }
            CGXDataInfo_Clear(&di);

            //CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, CGXSNInfo_GetItem(&target), CGXSNInfo_GetIndex(&target));
            CGXDLMSValueEventArg* e = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
            CGXDLMSValueEventArg_1(e, p, target.m_Item, target.m_Index);

            CGXDLMSValueEventArg_SetValue(e, &value);

            CGXDLMSValueEventCollection arr;
            CGXDLMSValueEventCollection_(&arr);

            CGXDLMSValueEventCollection_push_back(&arr, &e);
            p->PreWrite(p, (Vector*) &arr);
            DLMS_ACCESS_MODE am = p->GetAttributeAccess(p, e);
            // If write is denied.
            if (am != DLMS_ACCESS_MODE_WRITE && am != DLMS_ACCESS_MODE_READ_WRITE)
            {
                CGXByteBuffer_SetUInt8_2(&results, pos, DLMS_ERROR_CODE_READ_WRITE_DENIED);
            }
            else
            {
                if (e->m_Error != 0)
                {
                    CGXByteBuffer_SetUInt8_2(&results, pos, e->m_Error);
                }
                else if (!e->m_Handled)
                {
                    target.m_Item->SetValue(target.m_Item, &p->m_Settings, e);
                    p->PostWrite(p, (Vector*) &arr);
                }
            }

            CGXDLMSValueEventCollection_d(&arr);
        }
    }

    CGXDLMSVariant_d(&value);
    Vector_d(&targets);

    // CGXByteBuffer bb((2 * cnt));
    CGXByteBuffer bb;
    CGXByteBuffer_2(&bb, (2 * cnt));

    for (pos = 0; pos != cnt; ++pos)
    {
        if ((ret = CGXByteBuffer_GetUInt8_2(&results, pos, &ch)) != 0)
        {
            CGXByteBuffer_d(&bb);
            CGXByteBuffer_d(&results);
            return ret;
        }
        // If meter returns error.
        if (ch != 0)
        {
            CGXByteBuffer_SetUInt8_1(&bb, 1);
        }
        CGXByteBuffer_SetUInt8_1(&bb, ch);
    }

    // CGXDLMSSNParameters p(&m_Settings, DLMS_COMMAND_WRITE_RESPONSE, cnt, 0xFF, NULL, &bb);
    CGXDLMSSNParameters para;
    CGXDLMSSNParameters_(&para, &p->m_Settings, DLMS_COMMAND_WRITE_RESPONSE, cnt, 0xFF, NULL, &bb);

    ret = CGXDLMS_GetSNPdu(&para, &p->m_ReplyData);

    //CGXDLMSSNParameters_d(&para);
    CGXByteBuffer_d(&bb);
    CGXByteBuffer_d(&results);
    return ret;
}

/**
* Handles release request.
*
* @param data
*            Received data.
* @param connectionInfo
*            Connection info.
*/
//int CGXDLMSServer::HandleReleaseRequest(CGXByteBuffer& data)
int CGXDLMSServer_HandleReleaseRequest(CGXDLMSServer* p, CGXByteBuffer* data)
{
    if (p->m_Settings.m_InterfaceType == DLMS_INTERFACE_TYPE_HDLC)
    {
        CGXByteBuffer_Set_1(&(p->m_ReplyData), LLC_REPLY_BYTES, 3);
    }
    CGXByteBuffer_SetUInt8_1(&(p->m_ReplyData), 0x63);
    // LEN.
    CGXByteBuffer_SetUInt8_1(&(p->m_ReplyData), 0x03);
    CGXByteBuffer_SetUInt8_1(&(p->m_ReplyData), 0x80);
    CGXByteBuffer_SetUInt8_1(&(p->m_ReplyData), 0x01);
    CGXByteBuffer_SetUInt8_1(&(p->m_ReplyData), 0x00);
    return 0;
}

//int CGXDLMSServer::HandleCommand(
//    CGXDLMSConnectionEventArgs& connectionInfo,
//    DLMS_COMMAND cmd,
//    CGXByteBuffer& data,
//    CGXByteBuffer& reply)
int CGXDLMSServer_HandleCommand(CGXDLMSServer* p,
                                CGXDLMSConnectionEventArgs* connectionInfo,
                                DLMS_COMMAND cmd,
                                CGXByteBuffer* data,
                                CGXByteBuffer* reply)
{
    int ret = 0;
    unsigned char frame = 0;
    switch (cmd)
    {
    case DLMS_COMMAND_SET_REQUEST:
        ret = CGXDLMSServer_HandleSetRequest_2(p, data);
        break;
    case DLMS_COMMAND_WRITE_REQUEST:
        ret = CGXDLMSServer_HandleWriteRequest(p,data);
        break;
    case DLMS_COMMAND_GET_REQUEST:
        if (data->m_Size != 0)
        {
            ret = CGXDLMSServer_HandleGetRequest(p, data);
        }
        break;
    case DLMS_COMMAND_READ_REQUEST:
        ret = CGXDLMSServer_HandleReadRequest(p, data);
        break;
    case DLMS_COMMAND_METHOD_REQUEST:
        ret = CGXDLMSServer_HandleMethodRequest(p, data, connectionInfo);
        break;
    case DLMS_COMMAND_SNRM:
        ret = CGXDLMSServer_HandleSnrmRequest(p, &p->m_Settings, data, &p->m_ReplyData);
        frame = DLMS_COMMAND_UA;
        break;
    case DLMS_COMMAND_AARQ:
        ret = CGXDLMSServer_HandleAarqRequest(p, data, connectionInfo);
        break;
    case DLMS_COMMAND_RELEASE_REQUEST:
        ret = CGXDLMSServer_HandleReleaseRequest(p, data);
        break;
    case DLMS_COMMAND_DISC:
        ret = CGXDLMSServer_GenerateDisconnectRequest(&p->m_Settings, &p->m_ReplyData);
        p->m_Settings.m_Connected = false;
        p->Disconnected(p, connectionInfo);
        frame = DLMS_COMMAND_UA;
        break;
    case DLMS_COMMAND_NONE:
        //Get next frame.
        break;
    default:
        //Invalid command.
        break;
    }
    if (ret == 0)
    {
        if (p->m_Settings.m_InterfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
        {
            ret = CGXDLMS_GetWrapperFrame(&p->m_Settings, &p->m_ReplyData, reply);
        }
        else
        {
            ret = CGXDLMS_GetHdlcFrame(&p->m_Settings, frame, &p->m_ReplyData, reply);
        }
    }
    return ret;
}

/**
 * Handle action request.
 *
 * @param reply
 *            Received data from the client.
 * @return Reply.
 */
//int CGXDLMSServer::HandleMethodRequest(
//    CGXByteBuffer& data,
//    CGXDLMSConnectionEventArgs& connectionInfo)
int CGXDLMSServer_HandleMethodRequest(CGXDLMSServer* p,
                                      CGXByteBuffer* data,
                                      CGXDLMSConnectionEventArgs* connectionInfo)
{
    DLMS_ERROR_CODE error = DLMS_ERROR_CODE_OK;

    int ret;
    unsigned char ch, id, invokeId;
    unsigned short tmp;
    // Get type.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }
    // Get invoke ID and priority.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &invokeId)) != 0)
    {
        return ret;
    }
    // CI
    if ((ret = CGXByteBuffer_GetUInt16_1(data, &tmp)) != 0)
    {
        return ret;
    }

    DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)tmp;
    unsigned char * ln;

    ln = data->m_Data + data->m_Position;
    CGXByteBuffer_SetPosition(data, data->m_Position + 6);
    // Attribute
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &id)) != 0)
    {
        return ret;
    }
    // Get parameters.
    if ((ret = CGXByteBuffer_GetUInt8_1(data, &ch)) != 0)
    {
        return ret;
    }

    CGXDLMSVariant parameters;
    CGXDLMSVariant_1(&parameters);

    if (ch != 0)
    {
        CGXDataInfo i;
        CGXDataInfo_(&i);

        if ((ret = GXHelpers_GetData(data, &i, &parameters)) != 0)
        {
            CGXDLMSVariant_d(&parameters);
            return ret;
        }
    }

    CGXDLMSObject* obj = CGXDLMSObjectCollection_FindByLN_2(CGXDLMSSettings_GetObjects(&(p->m_Settings)),
                                                            ci, ln);

    if (obj == NULL)
    {
        String name;
        String_(&name);

        GXHelpers_GetLogicalName_1(ln, &name);

        obj = p->FindObject(p, ci, 0, &name);

        String_d(&name);
    }

    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    if (obj == NULL)
    {
        error = DLMS_ERROR_CODE_UNDEFINED_OBJECT;
    }
    else
    {
        CGXDLMSValueEventArg* e = DLMSPort_malloc(sizeof(CGXDLMSValueEventArg));
        CGXDLMSValueEventArg_2(e, p, obj, id, 0, &parameters);

        CGXDLMSValueEventCollection arr;
        CGXDLMSValueEventCollection_(&arr);

        CGXDLMSValueEventCollection_push_back(&arr, &e);
        if (p->GetMethodAccess(p, e) == DLMS_METHOD_ACCESS_MODE_NONE)
        {
            error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        }
        else
        {
            p->PreAction(p, (Vector*) &arr);
            if (!e->m_Handled)
            {
                if ((ret = obj->Invoke(obj, &p->m_Settings, e)) != 0)
                {
                    CGXDLMSValueEventCollection_d(&arr);
                    CGXByteBuffer_d(&bb);
                    CGXDLMSVariant_d(&parameters);
                    return ret;
                }
                p->PostAction(p, (Vector*) &arr);
            }

            CGXDLMSVariant* actionReply = CGXDLMSValueEventArg_GetValue(e);

            // Set default action reply if not given.
            if (actionReply->st.vt != DLMS_DATA_TYPE_NONE
                    && e->m_Error == DLMS_ERROR_CODE_OK)
            {
                // Add return parameters
                CGXByteBuffer_SetUInt8_1(&bb, 1);
                //Add parameters error code.
                CGXByteBuffer_SetUInt8_1(&bb, 0);
                GXHelpers_SetData(&bb, actionReply->st.vt, actionReply);
            }
            else
            {
                // Add parameters error code.
                error = e->m_Error;
                CGXByteBuffer_SetUInt8_1(&bb, 0);
            }
        }

        CGXDLMSValueEventCollection_d(&arr);
    }

    //CGXDLMSLNParameters p(&m_Settings, invokeId, DLMS_COMMAND_METHOD_RESPONSE, 1, NULL, &bb, error);
    CGXDLMSLNParameters para;
    CGXDLMSLNParameters_(&para, &p->m_Settings,  invokeId, DLMS_COMMAND_METHOD_RESPONSE, 1, NULL, &bb, error);

    ret = CGXDLMS_GetLNPdu(&para, &p->m_ReplyData);
    // If High level authentication fails.
    if (!p->m_Settings.m_Connected
            && obj->m_ObjectType == DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME && id == 1)
    {
        p->InvalidConnection(p, connectionInfo);
    }

    //CGXDLMSLNParameters_d(&para);
    CGXByteBuffer_d(&bb);
    CGXDLMSVariant_d(&parameters);
    return ret;
}

//int CGXDLMSServer::HandleRequest(
//    CGXByteBuffer& data,
//    CGXByteBuffer& reply)
int CGXDLMSServer_HandleRequest_1(CGXDLMSServer* p,
                                  CGXByteBuffer* data,
                                  CGXByteBuffer* reply)
{
    return CGXDLMSServer_HandleRequest_3(p,
                         data->m_Data,
                         (unsigned short)(data->m_Size - data->m_Position),
                         reply);
}

//int CGXDLMSServer::HandleRequest(
//    CGXDLMSConnectionEventArgs& connectionInfo,
//    CGXByteBuffer& data,
//    CGXByteBuffer& reply)
int CGXDLMSServer_HandleRequest_2(CGXDLMSServer* p,
                                  CGXDLMSConnectionEventArgs* connectionInfo,
                                  CGXByteBuffer* data,
                                  CGXByteBuffer* reply)
{
    return CGXDLMSServer_HandleRequest_4(p,
                         connectionInfo,
                         data->m_Data,
                         (unsigned short)(data->m_Size - data->m_Position),
                         reply);
}

//int CGXDLMSServer::HandleRequest(
//    unsigned char* buff,
//    unsigned short size,
//    CGXByteBuffer& reply)
int CGXDLMSServer_HandleRequest_3(CGXDLMSServer* p,
                                  unsigned char* buff,
                                  unsigned short size,
                                  CGXByteBuffer* reply)
{
    CGXDLMSConnectionEventArgs connectionInfo;
    CGXDLMSConnectionEventArgs_(&connectionInfo);

    return CGXDLMSServer_HandleRequest_4(p, &connectionInfo, buff, size, reply);
}

//int CGXDLMSServer::HandleRequest(
//    CGXDLMSConnectionEventArgs& connectionInfo,
//    unsigned char* buff,
//    unsigned short size,
//    CGXByteBuffer& reply)
int CGXDLMSServer_HandleRequest_4(CGXDLMSServer* p,
                                  CGXDLMSConnectionEventArgs* connectionInfo,
                                  unsigned char* buff,
                                  unsigned short size,
                                  CGXByteBuffer* reply)
{
    int ret;
    CGXByteBuffer_Clear(reply);
    if (buff == NULL || size == 0)
    {
        return 0;
    }
    if (!p->m_Initialized)
    {
        //Server not Initialized.
        return DLMS_ERROR_CODE_NOT_INITIALIZED;
    }
    CGXByteBuffer_Set_1(&p->m_ReceivedData, buff, size);
    bool first = p->m_Settings.m_ServerAddress == 0
              && p->m_Settings.m_ClientAddress == 0;
    if ((ret = CGXDLMS_GetData(&p->m_Settings, &p->m_ReceivedData, &p->m_Info)) != 0)
    {
        //If all data is not received yet.
        if (ret == DLMS_ERROR_CODE_FALSE)
        {
            ret = 0;
        }
        return ret;
    }
    // If all data is not received yet.
    if (!(p->m_Info.m_Complete))
    {
        return 0;
    }
    CGXByteBuffer_Clear(&p->m_ReceivedData);

    if (first)
    {
        // Check is data send to this server.
        if (!p->IsTarget(p, p->m_Settings.m_ServerAddress,
                            p->m_Settings.m_ClientAddress))
        {
            CGXReplyData_Clear(&p->m_Info);
            return 0;
        }
    }
    // If client want next frame.
    if ((p->m_Info.m_MoreData & DLMS_DATA_REQUEST_TYPES_FRAME)
                                                        == DLMS_DATA_REQUEST_TYPES_FRAME)
    {
        p->m_DataReceived = (long) time(NULL);
        return CGXDLMS_GetHdlcFrame(&p->m_Settings,
                                    CGXDLMSSettings_GetReceiverReady(&p->m_Settings),
                                    &p->m_ReplyData, reply);
    }
    // Update command if m_Transaction and next frame is asked.
    if (p->m_Info.m_Command == DLMS_COMMAND_NONE)
    {
        if (p->m_Transaction != NULL)
        {
            p->m_Info.m_Command = p->m_Transaction->m_Command;
        }
    }
    // Check inactivity time out.
    if (p->m_Hdlc != NULL && p->m_Hdlc->m_InactivityTimeout != 0)
    {
        if (p->m_Info.m_Command != DLMS_COMMAND_SNRM)
        {
            long elapsed = (long)(time(NULL) - p->m_DataReceived);
            // If inactivity time out is elapsed.
            if (elapsed >= p->m_Hdlc->m_InactivityTimeout)
            {
                CGXDLMSServer_Reset_2(p);
                p->m_DataReceived = 0;
                return 0;
            }
        }
    }
    else if (p->m_Wrapper != NULL && p->m_Wrapper->m_InactivityTimeout != 0)
    {
        if (p->m_Info.m_Command != DLMS_COMMAND_AARQ)
        {
            long elapsed = (long)(time(NULL) - p->m_DataReceived);
            // If inactivity time out is elapsed.
            if (elapsed >= p->m_Wrapper->m_InactivityTimeout)
            {
                CGXDLMSServer_Reset_2(p);
                p->m_DataReceived = 0;
                return 0;
            }
        }
    }
    ret = CGXDLMSServer_HandleCommand(p, connectionInfo,
                                      p->m_Info.m_Command,
                                      CGXReplyData_GetData(&p->m_Info),
                                      reply);
    CGXReplyData_Clear(&p->m_Info);
    p->m_DataReceived = (long) time(NULL);
    return ret;
}

DLMS_CONFORMANCE CGXDLMSServer_GetConformance(CGXDLMSServer* p)
{
    return p->m_Settings.m_ProposedConformance;
}

void CGXDLMSServer_SetConformance(CGXDLMSServer* p, DLMS_CONFORMANCE value)
{
    p->m_Settings.m_ProposedConformance = value;
}

//int CGXDLMSServer::AddData(
//    CGXDLMSObject* obj,
//    unsigned char index,
//    CGXByteBuffer& buff)
int CGXDLMSServer_AddData(CGXDLMSServer* p,
                          CGXDLMSObject* obj,
                          unsigned char index,
                          CGXByteBuffer* buff)
{
    int ret;
    DLMS_DATA_TYPE dt;

    //CGXDLMSValueEventArg e(NULL, obj, index);
    CGXDLMSValueEventArg e;
    CGXDLMSValueEventArg_1(&e, NULL, obj, index);

    if ((ret = obj->GetValue(obj, &p->m_Settings, &e)) != 0)
    {
        CGXDLMSValueEventArg_d(&e);
        return ret;
    }
    if ((ret = obj->GetDataType(obj, index, &dt)) != 0)
    {
        CGXDLMSValueEventArg_d(&e);
        return ret;
    }
    if (dt == DLMS_DATA_TYPE_ARRAY)
    {
        CGXByteBuffer_Set_1(buff, CGXDLMSValueEventArg_GetValue(&e)->st.un.byteArr,
                                  CGXDLMSVariant_GetSize_1(CGXDLMSValueEventArg_GetValue(&e)));

        CGXDLMSValueEventArg_d(&e);
        return 0;
    }
    if (dt == DLMS_DATA_TYPE_NONE)
    {
        dt = CGXDLMSValueEventArg_GetValue(&e)->st.vt;
    }

    ret = GXHelpers_SetData(buff, CGXDLMSValueEventArg_GetValue(&e)->st.vt,
                                  CGXDLMSValueEventArg_GetValue(&e));

    CGXDLMSValueEventArg_d(&e);
    return ret;
}

//int CGXDLMSServer::GenerateDataNotificationMessages(
//    struct tm* time,
//    CGXByteBuffer& data,
//    std::vector<CGXByteBuffer>& reply)
int CGXDLMSServer_GenerateDataNotificationMessages_1(CGXDLMSServer* p,
                                                     struct tm* time,
                                                     CGXByteBuffer* data,
                                                     Vector* reply) //std::vector<CGXByteBuffer>&
{
    int ret;
    if (CGXDLMSServer_GetUseLogicalNameReferencing(p))
    {
        //CGXDLMSLNParameters p(&m_Settings, 0, DLMS_COMMAND_DATA_NOTIFICATION, 0, NULL, &data, 0xff);
        CGXDLMSLNParameters para;
        CGXDLMSLNParameters_(&para, &p->m_Settings, 0,
                             DLMS_COMMAND_DATA_NOTIFICATION, 0, NULL, data, 0xff);

        para.m_Time = time;
        ret = CGXDLMS_GetLnMessages(&para, reply);

        //CGXDLMSLNParameters_d(&para);
    }
    else
    {
        // CGXDLMSSNParameters p(&m_Settings, DLMS_COMMAND_DATA_NOTIFICATION, 1, 0, &data, NULL);
        CGXDLMSSNParameters para;
        CGXDLMSSNParameters_(&para, &p->m_Settings,
                             DLMS_COMMAND_DATA_NOTIFICATION, 1, 0, data, NULL);

        ret = CGXDLMS_GetSnMessages(&para, reply);

        //CGXDLMSSNParameters_d(&para);
    }
    return ret;
}

//int CGXDLMSServer::GenerateDataNotificationMessages(
//    struct tm* date,
//    std::vector<std::pair<CGXDLMSObject*, unsigned char> >& objects,
//    std::vector<CGXByteBuffer>& reply)
int CGXDLMSServer_GenerateDataNotificationMessages_2(CGXDLMSServer* p,
                                                     struct tm* date,
                                                     Vector* objects, //std::vector<std::pair<CGXDLMSObject*, unsigned char> >&
                                                     Vector* reply) //std::vector<CGXByteBuffer>&
{
    CGXByteBuffer buff;
    CGXByteBuffer_1(&buff);

    CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
    GXHelpers_SetObjectCount((unsigned long)Vector_size(objects), &buff);

    // std::vector<std::pair<CGXDLMSObject*, unsigned char> >
    for (unsigned int i = Vector_begin(objects); i != Vector_end(objects); ++i)
    {
        Pair* it = Vector_at(objects, i);

        CGXDLMSServer_AddData(p, *((CGXDLMSObject**) (it->first)),
                              *((unsigned char*) (it->second)), &buff);
    }

    int ret = CGXDLMSServer_GenerateDataNotificationMessages_1(p, date, &buff, reply);

    CGXByteBuffer_d(&buff);
    return ret;
}

//int CGXDLMSServer::GeneratePushSetupMessages(
//    struct tm* date,
//    CGXDLMSPushSetup* push,
//    std::vector<CGXByteBuffer>& reply)
int CGXDLMSServer_GeneratePushSetupMessages(CGXDLMSServer* p,
                                            struct tm* date,
                                            CGXDLMSPushSetup* push,
                                            Vector* reply) //std::vector<CGXByteBuffer>&
{
    if (push == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    CGXByteBuffer buff;
    CGXByteBuffer_1(&buff);

    CGXByteBuffer_SetUInt8_1(&buff, DLMS_DATA_TYPE_STRUCTURE);
    GXHelpers_SetObjectCount((unsigned long)Vector_size(CGXDLMSPushSetup_GetPushObjectList(push)), &buff);

    // std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >
    Vector* vec = CGXDLMSPushSetup_GetPushObjectList(push);
    for (unsigned int i = Vector_begin(vec); i != Vector_end(vec); ++i)
    {
        Pair* it = Vector_at(vec, i);

        CGXDLMSServer_AddData(p, *((CGXDLMSObject**) (it->first)),
                              ((CGXDLMSCaptureObject*) (it->second))->m_AttributeIndex, &buff);
    }

    int ret = CGXDLMSServer_GenerateDataNotificationMessages_1(p, date, &buff, reply);

    CGXByteBuffer_d(&buff);
    return ret;
}
