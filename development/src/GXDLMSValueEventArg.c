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

#include "../include/GXDLMSValueEventArg.h"
#include "../include/GXDLMSSettings.h"
#include "../include/GXDLMSServer.h"

CGXDLMSVariant* CGXDLMSValueEventArg_GetValue(CGXDLMSValueEventArg* p)
{
    return &(p->m_Value);
}

void CGXDLMSValueEventArg_SetValue(CGXDLMSValueEventArg* p, CGXDLMSVariant* value)
{
    CGXDLMSVariant_copy_1(&(p->m_Value), value);
}

CGXDLMSVariant* CGXDLMSValueEventArg_GetParameters(CGXDLMSValueEventArg* p)
{
    return &(p->m_Parameters);
}

void CGXDLMSValueEventArg_SetParameters(CGXDLMSValueEventArg* p, CGXDLMSVariant* value)
{
    CGXDLMSVariant_copy_1(&(p->m_Parameters), value);
}

void CGXDLMSValueEventArg_Init(
	CGXDLMSValueEventArg* p,
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index,
    int selector)
{
	p->m_Server = server;
    p->m_Settings = CGXDLMSServer_GetSettings(server);
    p->m_Handled = false;
    p->m_Target = target;
    p->m_Index = index;
    p->m_Selector = selector;
    p->m_Error = DLMS_ERROR_CODE_OK;
    p->m_ByteArray = false;
    p->m_SkipMaxPduSize = false;
    p->m_RowToPdu = 0;
    p->m_RowBeginIndex = 0;
    p->m_RowEndIndex = 0;
}

static void CGXDLMSValueEventArg__(CGXDLMSValueEventArg* p)
{
    CGXDLMSVariant_1(&p->m_Value);
    CGXDLMSVariant_1(&p->m_Parameters);
}

void CGXDLMSValueEventArg_1(
    CGXDLMSValueEventArg* p,
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index)
{
    CGXDLMSValueEventArg__(p);

	CGXDLMSValueEventArg_Init(p, server, target, index, 0);
}

void CGXDLMSValueEventArg_2(
    CGXDLMSValueEventArg* p,
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index,
    int selector,
    CGXDLMSVariant* parameters)
{
    CGXDLMSValueEventArg__(p);

	CGXDLMSValueEventArg_Init(p, server, target, index, selector);
	CGXDLMSVariant_copy_1(&(p->m_Parameters), parameters);
}

void CGXDLMSValueEventArg_3(
    CGXDLMSValueEventArg* p,
    CGXDLMSObject* target,
    int index)
{
    CGXDLMSValueEventArg__(p);

	CGXDLMSValueEventArg_Init(p, NULL, target, index, 0);
}

void CGXDLMSValueEventArg_4(
    CGXDLMSValueEventArg* p,
    CGXDLMSObject* target,
    int index,
    int selector,
    CGXDLMSVariant* parameters)
{
    CGXDLMSValueEventArg__(p);

	CGXDLMSValueEventArg_Init(p, NULL, target, index, selector);
	CGXDLMSVariant_copy_1(&(p->m_Parameters), parameters);
}

void CGXDLMSValueEventArg_d(CGXDLMSValueEventArg* p)
{
    CGXDLMSVariant_d(&p->m_Value);
    CGXDLMSVariant_d(&p->m_Parameters);
}
