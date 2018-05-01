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

#ifndef GXDLMSOBJECTDEFINITION_H
#define GXDLMSOBJECTDEFINITION_H

#include "String.h"
#include "enums.h"

typedef struct {
    DLMS_OBJECT_TYPE m_ClassId;
    String m_LogicalName;
} CGXDLMSObjectDefinition;

extern DLMS_OBJECT_TYPE CGXDLMSObjectDefinition_GetClassId(CGXDLMSObjectDefinition *p);
extern void CGXDLMSObjectDefinition_SetClassId(CGXDLMSObjectDefinition *p, DLMS_OBJECT_TYPE value);

extern String CGXDLMSObjectDefinition_GetLogicalName(CGXDLMSObjectDefinition *p);
extern void CGXDLMSObjectDefinition_SetLogicalName(CGXDLMSObjectDefinition *p, String value);

/*
 * Constructor
 */
extern void CGXDLMSObjectDefinition_1(CGXDLMSObjectDefinition *p);

/*
 * Constructor
 */
extern void CGXDLMSObjectDefinition_2(CGXDLMSObjectDefinition *p, DLMS_OBJECT_TYPE classId, String logicalName);

extern String CGXDLMSObjectDefinition_ToString(CGXDLMSObjectDefinition* p);

extern void CGXDLMSObjectDefinition_d(CGXDLMSObjectDefinition* p);

extern void CGXDLMSObjectDefinition_v_c(void *p1, const void* p2);
extern void CGXDLMSObjectDefinition_v_d(void *p);

#endif //GXDLMSOBJECTDEFINITION_H
