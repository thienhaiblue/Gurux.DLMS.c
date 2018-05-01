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

#ifndef GXDLMSCONVERTER_H
#define GXDLMSCONVERTER_H

#include "enums.h"

//This class is used to convert enum and error values to std::string.
    //Get Unit as String.
    extern  const char* CGXDLMSConverter_GetUnitAsString(int unit);
    //Get baudrate enum balue as std::string.
    extern  const char* CGXDLMSConverter_ToString_1(DLMS_BAUD_RATE value);
    //Get clock base enum value as std::string.
    extern  const char* CGXDLMSConverter_ToString_2(DLMS_CLOCK_BASE value);
    //Get clock status enum value as std::string.
    extern  const char* CGXDLMSConverter_ToString_3(DLMS_CLOCK_STATUS value);

    //Get error message as std::string.
    extern  const char* CGXDLMSConverter_GetErrorMessage(int error);

    //Get address state enum value as std::string.
    extern  const char* CGXDLMSConverter_ToString_4(DLMS_ADDRESS_STATE value);

    //Get Disconnect control control state as a std::string.
    extern  const char* CGXDLMSConverter_ToString_5(DLMS_CONTROL_STATE value);

    //Get Disconnect control control mode as a std::string.
    extern  const char* CGXDLMSConverter_ToString_6(DLMS_CONTROL_MODE value);

    //Get Security Setup security policy as a std::string.
    extern  const char* CGXDLMSConverter_ToString_7(DLMS_SECURITY_POLICY value);

    //Get Security Setup security suite as a std::string.
    extern  const char* CGXDLMSConverter_ToString_8(DLMS_SECURITY_SUITE value);

    //Get Logical Name association status as a std::string.
    extern  const char* CGXDLMSConverter_ToString_9(DLMS_DLMS_ASSOCIATION_STATUS value);

    //Get optical port protocol mode as a std::string.
    extern  const char* CGXDLMSConverter_ToString_10(DLMS_OPTICAL_PROTOCOL_MODE value);

    //Get optical port response time as a std::string.
    extern  const char* CGXDLMSConverter_ToString_11(DLMS_LOCAL_PORT_RESPONSE_TIME value);

    //GSM status to string.
    extern  const char* CGXDLMSConverter_ToString_12(DLMS_GSM_STATUS value);

    //GSM circuit switced status to string.
    extern  const char* CGXDLMSConverter_ToString_13(DLMS_GSM_CIRCUIT_SWITCH_STATUS value);

    // Packet switched status to the string.
    extern  const char* CGXDLMSConverter_ToString_14(DLMS_GSM_PACKET_SWITCH_STATUS value);

#endif //GXDLMSCONVERTER_H
