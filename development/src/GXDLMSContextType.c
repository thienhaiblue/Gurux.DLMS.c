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

#include "../include/GXDLMSContextType.h"
#include "../include/GXDLMSVariant.h"
#include "../include/GXHelpers.h"
#include "../include/String.h"

void CGXDLMSContextType_(CGXDLMSContextType *p)
{
    CGXByteBuffer_1(&p->m_CypheringInfo);

    p->m_Conformance = (DLMS_CONFORMANCE)0;
    p->m_MaxReceivePduSize = 0;
    p->m_MaxSendPpuSize = 0;
    p->m_DlmsVersionNumber = 0;
    p->m_QualityOfService = 0;
}

void CGXDLMSContextType_SetCypheringInfo(CGXDLMSContextType *p, CGXByteBuffer* value)
{
    CGXByteBuffer_copy(&(p->m_CypheringInfo), value);
}

String CGXDLMSContextType_ToString(CGXDLMSContextType *p)
{
    CGXByteBuffer bb;
    CGXByteBuffer_1(&bb);

    CGXByteBuffer_AddIntAsString(&bb, p->m_Conformance);
    CGXByteBuffer_SetInt8(&bb, ' ');
    CGXByteBuffer_AddIntAsString(&bb, p->m_MaxReceivePduSize);
    CGXByteBuffer_SetInt8(&bb, ' ');
    CGXByteBuffer_AddIntAsString(&bb, p->m_MaxSendPpuSize);
    CGXByteBuffer_SetInt8(&bb, ' ');
    CGXByteBuffer_AddIntAsString(&bb, p->m_DlmsVersionNumber);
    CGXByteBuffer_SetInt8(&bb, ' ');
    CGXByteBuffer_AddIntAsString(&bb, p->m_QualityOfService);
    CGXByteBuffer_SetInt8(&bb, ' ');
    CGXByteBuffer_Set_2(&bb, &p->m_CypheringInfo, 0, -1);

    String str;
    CGXByteBuffer_ToString(&bb, &str);

    CGXByteBuffer_d(&bb);

    return str; // = copy cons + des
}

void CGXDLMSContextType_d(CGXDLMSContextType *p)
{
    CGXByteBuffer_d(&p->m_CypheringInfo);
}
