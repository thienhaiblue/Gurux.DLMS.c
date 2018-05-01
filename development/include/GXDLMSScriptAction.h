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

#ifndef GXDLMSSCRIPTACTION_H
#define GXDLMSSCRIPTACTION_H

#include "enums.h"
#include "GXDLMSVariant.h"
#include "String.h"

typedef enum
{
    /*
     * Write attribute.
     */
    SCRIPT_ACTION_TYPE_WRITE = 1,
    /*
     * Execute specific method
     */
    SCRIPT_ACTION_TYPE_EXECUTE = 2
} SCRIPT_ACTION_TYPE;

typedef struct
{
    SCRIPT_ACTION_TYPE m_Type;
    DLMS_OBJECT_TYPE m_ObjectType;
    String m_LogicalName;
    int m_Index;
    CGXDLMSVariant m_Parameter;
} CGXDLMSScriptAction;

/**
 Defines which action to be applied to the referenced object.
*/
extern SCRIPT_ACTION_TYPE CGXDLMSScriptAction_GetType(CGXDLMSScriptAction* p);
extern void CGXDLMSScriptAction_SetType(CGXDLMSScriptAction* p, SCRIPT_ACTION_TYPE value);

/**
 Executed object type.
*/
extern DLMS_OBJECT_TYPE CGXDLMSScriptAction_GetObjectType(CGXDLMSScriptAction* p);
extern void CGXDLMSScriptAction_SetObjectType(CGXDLMSScriptAction* p, DLMS_OBJECT_TYPE value);

/**
 Logical name of executed object.
*/
extern String CGXDLMSScriptAction_GetLogicalName(CGXDLMSScriptAction* p);
extern void CGXDLMSScriptAction_SetLogicalName(CGXDLMSScriptAction* p, String value);

/**
 defines which attribute of the selected object is affected; or
    * which specific method is to be executed.
*/
extern int CGXDLMSScriptAction_GetIndex(CGXDLMSScriptAction* p);
extern void CGXDLMSScriptAction_SetIndex(CGXDLMSScriptAction* p, int value);

/**
 Parameter is service spesific.
*/
extern CGXDLMSVariant CGXDLMSScriptAction_GetParameter(CGXDLMSScriptAction* p);
extern void CGXDLMSScriptAction_SetParameter(CGXDLMSScriptAction* p, CGXDLMSVariant value);

extern String CGXDLMSScriptAction_ToString(CGXDLMSScriptAction* p);

extern void CGXDLMSScriptAction_(CGXDLMSScriptAction* p);
extern void CGXDLMSScriptAction_d(CGXDLMSScriptAction* p);

#endif //GXDLMSSCRIPTACTION_H
