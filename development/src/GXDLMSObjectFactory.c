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

#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSActionSchedule.h"
#include "../include/GXDLMSActivityCalendar.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSAssociationShortName.h"
#include "../include/GXDLMSAutoAnswer.h"
#include "../include/GXDLMSAutoConnect.h"
#include "../include/GXDLMSClock.h"
#include "../include/GXDLMSData.h"
#include "../include/GXDLMSRegister.h"
#include "../include/GXDLMSExtendedRegister.h"
#include "../include/GXDLMSDemandRegister.h"
#include "../include/GXDLMSRegisterMonitor.h"
#include "../include/GXDLMSProfileGeneric.h"
#include "../include/GXDLMSTcpUdpSetup.h"
#include "../include/GXDLMSGPRSSetup.h"
#include "../include/GXDLMSActionSchedule.h"
#include "../include/GXDLMSSpecialDaysTable.h"
#include "../include/GXDLMSImageTransfer.h"
#include "../include/GXDLMSDisconnectControl.h"
#include "../include/GXDLMSLimiter.h"
#include "../include/GXDLMSMBusClient.h"
#include "../include/GXDLMSScriptTable.h"
#include "../include/GXDLMSMBusSlavePortSetup.h"
#include "../include/GXDLMSSecuritySetup.h"
#include "../include/GXDLMSPppSetup.h"
#include "../include/GXDLMSMacAddressSetup.h"
#include "../include/GXDLMSHdlcSetup.h"
#include "../include/GXDLMSIECOpticalPortSetup.h"
#include "../include/GXDLMSIp4Setup.h"
#include "../include/GXDLMSRegisterActivation.h"
#include "../include/GXDLMSSchedule.h"
#include "../include/GXDLMSModemConfiguration.h"
#include "../include/GXDLMSSapAssignment.h"
#include "../include/GXDLMSMBusMasterPortSetup.h"
#include "../include/GXDLMSMessageHandler.h"
#include "../include/GXDLMSPushSetup.h"
#include "../include/GXDLMSGSMDiagnostic.h"

// Reserved for internal use.
CGXDLMSObject* CGXDLMSObjectFactory_CreateObject_1(DLMS_OBJECT_TYPE type)
{
    void* t_Obj;

    switch (type)
    {
    case DLMS_OBJECT_TYPE_ACTION_SCHEDULE:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSActionSchedule));
        CGXDLMSActionSchedule_1((CGXDLMSActionSchedule*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSActivityCalendar));
        CGXDLMSActivityCalendar_1((CGXDLMSActivityCalendar*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSAssociationLogicalName));
        CGXDLMSAssociationLogicalName_1((CGXDLMSAssociationLogicalName*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSAssociationShortName));
        CGXDLMSAssociationShortName_((CGXDLMSAssociationShortName*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_AUTO_ANSWER:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSAutoAnswer));
        CGXDLMSAutoAnswer_1((CGXDLMSAutoAnswer*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_AUTO_CONNECT:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSAutoConnect));
        CGXDLMSAutoConnect_1((CGXDLMSAutoConnect*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_CLOCK:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSClock));
        CGXDLMSClock_1((CGXDLMSClock*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_DATA:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSData));
        CGXDLMSData_1((CGXDLMSData*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_DEMAND_REGISTER:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSDemandRegister));
        CGXDLMSDemandRegister_1((CGXDLMSDemandRegister*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSMacAddressSetup));
        CGXDLMSMacAddressSetup_1((CGXDLMSMacAddressSetup*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_EXTENDED_REGISTER:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSExtendedRegister));
        CGXDLMSExtendedRegister_1((CGXDLMSExtendedRegister*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
//    case DLMS_OBJECT_TYPE_GPRS_SETUP:
//        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSGPRSSetup));
//        CGXDLMSGPRSSetup_1((CGXDLMSGPRSSetup*) t_Obj);
//        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_DLMS_SECURITY_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSSecuritySetup));
        CGXDLMSSecuritySetup_1((CGXDLMSSecuritySetup*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_IEC_HDLC_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSIecHdlcSetup));
        CGXDLMSIecHdlcSetup_1((CGXDLMSIecHdlcSetup*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSIECOpticalPortSetup));
        CGXDLMSIECOpticalPortSetup_1((CGXDLMSIECOpticalPortSetup*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_IEC_TWISTED_PAIR_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_IP4_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSIp4Setup));
        CGXDLMSIp4Setup_1((CGXDLMSIp4Setup*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
//    case DLMS_OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP:
//        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSMBusSlavePortSetup));
//        CGXDLMSMBusSlavePortSetup_1((CGXDLMSMBusSlavePortSetup*) t_Obj);
//        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_IMAGE_TRANSFER:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSImageTransfer));
        CGXDLMSImageTransfer_1((CGXDLMSImageTransfer*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_DISCONNECT_CONTROL:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSDisconnectControl));
        CGXDLMSDisconnectControl_1((CGXDLMSDisconnectControl*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_LIMITER:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSLimiter));
        CGXDLMSLimiter_1((CGXDLMSLimiter*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
//    case DLMS_OBJECT_TYPE_MBUS_CLIENT:
//        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSMBusClient));
//        CGXDLMSMBusClient_1((CGXDLMSMBusClient*) t_Obj);
//        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_MODEM_CONFIGURATION:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSModemConfiguration));
        CGXDLMSModemConfiguration_1((CGXDLMSModemConfiguration*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
//    case DLMS_OBJECT_TYPE_PPP_SETUP:
//        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSPppSetup));
//        CGXDLMSPppSetup_1((CGXDLMSPppSetup*) t_Obj);
//        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_PROFILE_GENERIC:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSProfileGeneric));
        CGXDLMSProfileGeneric_1((CGXDLMSProfileGeneric*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_REGISTER:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSRegister));
        CGXDLMSRegister_2((CGXDLMSRegister*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_REGISTER_ACTIVATION:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSRegisterActivation));
        CGXDLMSRegisterActivation_1((CGXDLMSRegisterActivation*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_REGISTER_MONITOR:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSRegisterMonitor));
        CGXDLMSRegisterMonitor_1((CGXDLMSRegisterMonitor*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_REGISTER_TABLE:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_STARTUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_JOIN:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_APS_FRAGMENTATION:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_SAP_ASSIGNMENT:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSSapAssignment));
        CGXDLMSSapAssignment_1((CGXDLMSSapAssignment*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_SCHEDULE:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSSchedule));
        CGXDLMSSchedule_1((CGXDLMSSchedule*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_SCRIPT_TABLE:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSScriptTable));
        CGXDLMSScriptTable_1((CGXDLMSScriptTable*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_SMTP_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSSpecialDaysTable));
        CGXDLMSSpecialDaysTable_1((CGXDLMSSpecialDaysTable*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_STATUS_MAPPING:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_TCP_UDP_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSTcpUdpSetup));
        CGXDLMSTcpUdpSetup_1((CGXDLMSTcpUdpSetup*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_UTILITY_TABLES:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSCustomObject));
        CGXDLMSCustomObject_((CGXDLMSCustomObject*) t_Obj, type);
        return (CGXDLMSObject*) t_Obj;
//    case DLMS_OBJECT_TYPE_MBUS_MASTER_PORT_SETUP:
//        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSMBusMasterPortSetup));
//        CGXDLMSMBusMasterPortSetup_1((CGXDLMSMBusMasterPortSetup*) t_Obj);
//        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_MESSAGE_HANDLER:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSMessageHandler));
        CGXDLMSMessageHandler_1((CGXDLMSMessageHandler*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
    case DLMS_OBJECT_TYPE_PUSH_SETUP:
        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSPushSetup));
        CGXDLMSPushSetup_1((CGXDLMSPushSetup*) t_Obj);
        return (CGXDLMSObject*) t_Obj;
//    case DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC:
//        t_Obj = DLMSPort_malloc(sizeof(CGXDLMSGSMDiagnostic));
//        CGXDLMSGSMDiagnostic_1((CGXDLMSGSMDiagnostic*) t_Obj);
//        return (CGXDLMSObject*) t_Obj;
    default:
#ifdef _DEBUG
        DLMSPort_printf("Unknown object: %d\r\n", type);
#endif //_DEBUG
        return NULL;
    }
}

CGXDLMSObject* CGXDLMSObjectFactory_CreateObject_2(DLMS_OBJECT_TYPE type, String ln)
{
    CGXDLMSObject* pObj = CGXDLMSObjectFactory_CreateObject_1(type);
    if (pObj != NULL)
    {
        GXHelpers_SetLogicalName_2(String_c_str(&ln), pObj->m_LN);
    }
    return pObj;
}

String CGXDLMSObjectFactory_ObjectTypeToString(DLMS_OBJECT_TYPE type)
{
    String t_Str;

    switch (type)
    {
    case DLMS_OBJECT_TYPE_ACTION_SCHEDULE:
        String_3(&t_Str, "GXDLMSActionSchedule");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR:
        String_3(&t_Str, "GXDLMSActivityCalendar");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME:
        String_3(&t_Str, "GXDLMSAssociationLogicalName");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME:
        String_3(&t_Str, "GXDLMSAssociationShortName");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_AUTO_ANSWER:
        String_3(&t_Str, "GXDLMSAutoAnswer");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_AUTO_CONNECT:
        String_3(&t_Str, "GXDLMSAutoConnect");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_CLOCK:
        String_3(&t_Str, "GXDLMSClock");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_DATA:
        String_3(&t_Str, "GXDLMSData");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_DEMAND_REGISTER:
        String_3(&t_Str, "GXDLMSDemandRegister");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP:
        String_3(&t_Str, "GXDLMSMacAddressSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_EXTENDED_REGISTER:
        String_3(&t_Str, "GXDLMSExtendedRegister");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_GPRS_SETUP:
        String_3(&t_Str, "GXDLMSGprsSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_DLMS_SECURITY_SETUP:
        String_3(&t_Str, "GXDLMSSecuritySetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_IEC_HDLC_SETUP:
        String_3(&t_Str, "GXDLMSHdlcSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP:
        String_3(&t_Str, "GXDLMSIECOpticalPortSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_IEC_TWISTED_PAIR_SETUP:
        String_3(&t_Str, "GXDLMSIEC_TWISTED_PAIR_SETUP");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_IP4_SETUP:
        String_3(&t_Str, "GXDLMSIp4Setup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP:
        String_3(&t_Str, "GXDLMSMBusSlavePortSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_IMAGE_TRANSFER:
        String_3(&t_Str, "GXDLMSImageTransfer");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_DISCONNECT_CONTROL:
        String_3(&t_Str, "GXDLMSDisconnectControl");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_LIMITER:
        String_3(&t_Str, "GXDLMSLimiter");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_MBUS_CLIENT:
        String_3(&t_Str, "GXDLMSMBusClient");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_MODEM_CONFIGURATION:
        String_3(&t_Str, "GXDLMSModemConfiguration");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_PPP_SETUP:
        String_3(&t_Str, "GXDLMSPppSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_PROFILE_GENERIC:
        String_3(&t_Str, "GXDLMSProfileGeneric");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_REGISTER:
        String_3(&t_Str, "GXDLMSRegister");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_REGISTER_ACTIVATION:
        String_3(&t_Str, "GXDLMSRegisterActivation");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_REGISTER_MONITOR:
        String_3(&t_Str, "GXDLMSRegisterMonitor");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_REGISTER_TABLE:
        String_3(&t_Str, "GXDLMSRegisterTable");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_STARTUP:
        String_3(&t_Str, "GXDLMSZigBeeSasStartup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_JOIN:
        String_3(&t_Str, "GXDLMSZigBeeSasJoin");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_ZIG_BEE_SAS_APS_FRAGMENTATION:
        String_3(&t_Str, "GXDLMSZigBeeSasApsFragmentation");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_ZIG_BEE_NETWORK_CONTROL:
        String_3(&t_Str, "GXDLMSZigBeeNetworkControl");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_SAP_ASSIGNMENT:
        String_3(&t_Str, "GXDLMSSapAssignment");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_SCHEDULE:
        String_3(&t_Str, "GXDLMSSchedule");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_SCRIPT_TABLE:
        String_3(&t_Str, "GXDLMSScriptTable");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_SMTP_SETUP:
        String_3(&t_Str, "GXDLMSSMTPSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE:
        String_3(&t_Str, "GXDLMSSpecialDaysTable");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_STATUS_MAPPING:
        String_3(&t_Str, "GXDLMSStatusMapping");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_TCP_UDP_SETUP:
        String_3(&t_Str, "GXDLMSTcpUdpSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_UTILITY_TABLES:
        String_3(&t_Str, "GXDLMSUtilityTables");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_MBUS_MASTER_PORT_SETUP:
        String_3(&t_Str, "GXDLMSMBusMasterPortSetup");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_MESSAGE_HANDLER:
        String_3(&t_Str, "GXDLMSMessageHandler");
        return t_Str; // = copy cons + des
    case DLMS_OBJECT_TYPE_PUSH_SETUP:
        String_3(&t_Str, "GXDLMSPushSetup");
        return t_Str; // = copy cons + des
    default:
        String_3(&t_Str, "Manufacture spesific.");
        return t_Str; // = copy cons + des
    }
}
