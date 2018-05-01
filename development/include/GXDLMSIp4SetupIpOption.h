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

#ifndef GXDLMSIP4SETUPIPOPTION_H
#define GXDLMSIP4SETUPIPOPTION_H

#include "GXDLMSObject.h"

typedef struct CGXDLMSIp4SetupIpOption
{
    IP_OPTION_TYPE m_Type;
    short m_Length;
    CGXByteBuffer m_Data;
} CGXDLMSIp4SetupIpOption;

extern IP_OPTION_TYPE CGXDLMSIp4SetupIpOption_GetType(CGXDLMSIp4SetupIpOption *p);
extern void CGXDLMSIp4SetupIpOption_SetType(CGXDLMSIp4SetupIpOption *p, IP_OPTION_TYPE value);

extern short CGXDLMSIp4SetupIpOption_GetLength(CGXDLMSIp4SetupIpOption *p);
extern void CGXDLMSIp4SetupIpOption_SetLength(CGXDLMSIp4SetupIpOption *p, short value);
extern CGXByteBuffer* CGXDLMSIp4SetupIpOption_GetData(CGXDLMSIp4SetupIpOption *p);
extern void CGXDLMSIp4SetupIpOption_SetData(CGXDLMSIp4SetupIpOption *p, CGXByteBuffer* value);

extern String CGXDLMSIp4SetupIpOption_ToString(CGXDLMSIp4SetupIpOption *p);

extern void CGXDLMSIp4SetupIpOption_(CGXDLMSIp4SetupIpOption *p);

extern void CGXDLMSIp4SetupIpOption_d(CGXDLMSIp4SetupIpOption *p);

extern void CGXDLMSIp4SetupIpOption_v_c(void* p1, const void* p2);
extern void CGXDLMSIp4SetupIpOption_v_d(void* p);

#endif //GXDLMSIP4SETUPIPOPTION_H
