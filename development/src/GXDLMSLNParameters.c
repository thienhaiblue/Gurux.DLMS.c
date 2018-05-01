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

#include "../include/GXDLMSLNParameters.h"

void CGXDLMSLNParameters_(CGXDLMSLNParameters* p,
                          CGXDLMSSettings* settings,
                          unsigned long invokeId,
                          DLMS_COMMAND command,
                          int commandType,
                          CGXByteBuffer* attributeDescriptor,
                          CGXByteBuffer* data,
                          int status)
{
    p->m_Settings = settings;
    p->m_BlockIndex = settings->m_BlockIndex;
    p->m_Command = command;
    p->m_RequestType = commandType;
    p->m_AttributeDescriptor = attributeDescriptor;
    p->m_Data = data;
    p->m_Time = NULL;
    p->m_Status = status;
    p->m_MultipleBlocks = settings->m_Count != settings->m_Index;
    p->m_LastBlock = settings->m_Count == settings->m_Index;
    p->m_InvokeId = invokeId;
}
