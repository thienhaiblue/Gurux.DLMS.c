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

#ifndef GXDLMSPPPSETUPIPCPOPTION_H
#define GXDLMSPPPSETUPIPCPOPTION_H

#include "IGXDLMSBase.h"
#include "GXDLMSObject.h"
#include "GXHelpers.h"

typedef enum
{
    PPP_SETUP_IPCP_OPTION_TYPE_IPCOMPRESSIONPROTOCOL = 2,
    PPP_SETUP_IPCP_OPTION_TYPE_PREFLOCALIP = 3,
    PPP_SETUP_IPCP_OPTION_TYPE_PREFPEERIP = 20,
    PPP_SETUP_IPCP_OPTION_TYPE_GAO = 21,
    PPP_SETUP_IPCP_OPTION_TYPE_USIP = 22
} PPP_SETUP_IPCP_OPTION_TYPE;

typedef struct
{
    PPP_SETUP_IPCP_OPTION_TYPE m_Type;
    int m_Length;
    CGXDLMSVariant m_Data;

} CGXDLMSPppSetupIPCPOption;


extern PPP_SETUP_IPCP_OPTION_TYPE CGXDLMSPppSetupIPCPOption_GetType(CGXDLMSPppSetupIPCPOption *p);
extern void CGXDLMSPppSetupIPCPOptionSetType(CGXDLMSPppSetupIPCPOption *p, PPP_SETUP_IPCP_OPTION_TYPE value);

extern int CGXDLMSPppSetupIPCPOption_GetLength(CGXDLMSPppSetupIPCPOption *p);
extern void CGXDLMSPppSetupIPCPOption_SetLength(CGXDLMSPppSetupIPCPOption *p, int value);

extern CGXDLMSVariant CGXDLMSPppSetupIPCPOption_GetData(CGXDLMSPppSetupIPCPOption *p);
extern void CGXDLMSPppSetupIPCPOption_SetData(CGXDLMSPppSetupIPCPOption *p, CGXDLMSVariant value);

extern String CGXDLMSPppSetupIPCPOption_ToString(CGXDLMSPppSetupIPCPOption *p);

extern void CGXDLMSPppSetupIPCPOption_(CGXDLMSPppSetupIPCPOption *p);
extern void CGXDLMSPppSetupIPCPOption_d(CGXDLMSPppSetupIPCPOption *p);

#endif //GXDLMSPPPSETUPIPCPOPTION_H
