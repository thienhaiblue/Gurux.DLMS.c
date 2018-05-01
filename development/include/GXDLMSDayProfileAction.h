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

#ifndef GXDLMSDAYPROFILEACTION_H
#define GXDLMSDAYPROFILEACTION_H

#include "GXTime.h"
#include "String.h"

typedef struct CGXDLMSDayProfileAction
{
    CGXTime m_StartTime;
    String m_ScriptLogicalName;
    int m_ScriptSelector;
} CGXDLMSDayProfileAction;

/**
 Constructor.
*/
extern void CGXDLMSDayProfileAction_1(CGXDLMSDayProfileAction *p);

/**
 Constructor.
*/
extern void CGXDLMSDayProfileAction_2(CGXDLMSDayProfileAction *p, CGXTime* startTime, String scriptLogicalName, int scriptSelector);

/**
 Defines the time when the script is to be executed.
*/
extern CGXTime* CGXDLMSDayProfileAction_GetStartTime(CGXDLMSDayProfileAction *p);
extern void CGXDLMSDayProfileAction_SetStartTime(CGXDLMSDayProfileAction *p, CGXTime* value);

/**
 Defines the logical name of the "Script table" object;
*/
extern String CGXDLMSDayProfileAction_GetScriptLogicalName(CGXDLMSDayProfileAction *p);
extern void CGXDLMSDayProfileAction_SetScriptLogicalName(CGXDLMSDayProfileAction *p, String value);

/**
 Defines the script_identifier of the script to be executed.
*/
extern int CGXDLMSDayProfileAction_GetScriptSelector(CGXDLMSDayProfileAction *p);
extern void CGXDLMSDayProfileAction_SetScriptSelector(CGXDLMSDayProfileAction *p, int value);

extern String CGXDLMSDayProfileAction_ToString(CGXDLMSDayProfileAction *p);

extern void CGXDLMSDayProfileAction_d(CGXDLMSDayProfileAction *p);

#endif //GXDLMSDAYPROFILEACTION_H
