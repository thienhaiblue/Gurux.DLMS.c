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

#include "../include/GXDLMSIp4SetupIpOption.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

CGXByteBuffer* CGXDLMSIp4SetupIpOption_GetData(CGXDLMSIp4SetupIpOption *p)
{
    return &(p->m_Data);
}

void CGXDLMSIp4SetupIpOption_SetData(CGXDLMSIp4SetupIpOption *p, CGXByteBuffer* value)
{
    CGXByteBuffer_copy(&(p->m_Data), value);
}

String CGXDLMSIp4SetupIpOption_ToString(CGXDLMSIp4SetupIpOption *p)
{
    String sb;
    String_(&sb);

    String_append_int(&sb, (int) p->m_Type);

    return sb; // = copy cons + des
}


void CGXDLMSIp4SetupIpOption_(CGXDLMSIp4SetupIpOption *p)
{
    CGXByteBuffer_1(&p->m_Data);
}

void CGXDLMSIp4SetupIpOption_d(CGXDLMSIp4SetupIpOption *p)
{
    CGXByteBuffer_d(&p->m_Data);
}

void CGXDLMSIp4SetupIpOption_v_c(void* p1, const void* p2)
{
    CGXDLMSIp4SetupIpOption* t_p1 = (CGXDLMSIp4SetupIpOption*) p1;
    CGXDLMSIp4SetupIpOption* t_p2 = (CGXDLMSIp4SetupIpOption*) p2;

    CGXByteBuffer_3(&t_p1->m_Data, &t_p2->m_Data);
}

void CGXDLMSIp4SetupIpOption_v_d(void* p)
{
    CGXDLMSIp4SetupIpOption_d((CGXDLMSIp4SetupIpOption*) p);
}
