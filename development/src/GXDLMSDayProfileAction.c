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

#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSDayProfileAction.h"

void CGXDLMSDayProfileAction__(CGXDLMSDayProfileAction *p)
{
    CGXTime_1(&p->m_StartTime);
    String_(&p->m_ScriptLogicalName);
}

/**
 Constructor.
*/
void CGXDLMSDayProfileAction_1(CGXDLMSDayProfileAction *p)
{
    CGXDLMSDayProfileAction__(p);

    p->m_ScriptSelector = 0;
}

/**
 Constructor.
*/
void CGXDLMSDayProfileAction_2(CGXDLMSDayProfileAction *p, CGXTime* startTime, String scriptLogicalName, int scriptSelector)
{
    CGXDLMSDayProfileAction__(p);

	CGXDLMSDayProfileAction_SetStartTime(p, startTime);
	CGXDLMSDayProfileAction_SetScriptLogicalName(p, scriptLogicalName);
	p->m_ScriptSelector = scriptSelector;
}

/**
 Defines the time when the script is to be executed.
*/
CGXTime* CGXDLMSDayProfileAction_GetStartTime(CGXDLMSDayProfileAction *p)
{
    return &(p->m_StartTime);
}
void CGXDLMSDayProfileAction_SetStartTime(CGXDLMSDayProfileAction *p, CGXTime* value)
{
    CGXTime_copy_1(&(p->m_StartTime), (CGXDateTime*) value);
}

/**
 Defines the logical name of the "Script table" object;
*/
String CGXDLMSDayProfileAction_GetScriptLogicalName(CGXDLMSDayProfileAction *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_ScriptLogicalName));

    return t_Str; // = copy cons + des
}
void CGXDLMSDayProfileAction_SetScriptLogicalName(CGXDLMSDayProfileAction *p, String value)
{
    String_copy_1(&(p->m_ScriptLogicalName), &value);
}

String CGXDLMSDayProfileAction_ToString(CGXDLMSDayProfileAction *p)
{
    String t_Str = CGXTime_ToString(&(p->m_StartTime));

    String_append_1(&t_Str, " ");
    String_append_3(&t_Str, &(p->m_ScriptLogicalName));

    return t_Str; // = copy cons + des
}

void CGXDLMSDayProfileAction_d(CGXDLMSDayProfileAction *p)
{
    String_d(&p->m_ScriptLogicalName);
}
