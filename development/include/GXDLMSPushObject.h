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

#ifndef GXDLMSPUSHOBJECT_H
#define GXDLMSPUSHOBJECT_H

#include "enums.h"
#include "String.h"

typedef struct
{
    DLMS_OBJECT_TYPE m_Type;
    String m_LogicalName;
    int m_AttributeIndex;
    int m_DataIndex;
} CGXDLMSPushObject;

extern DLMS_OBJECT_TYPE CGXDLMSPushObject_GetType(CGXDLMSPushObject *p);
extern void CGXDLMSPushObject_SetType(CGXDLMSPushObject *p, DLMS_OBJECT_TYPE value);

extern String CGXDLMSPushObject_GetLogicalName(CGXDLMSPushObject *p);
extern void CGXDLMSPushObject_SetLogicalName(CGXDLMSPushObject *p, String value);

extern int CGXDLMSPushObject_GetAttributeIndex(CGXDLMSPushObject *p);
extern void CGXDLMSPushObject_SetAttributeIndex(CGXDLMSPushObject *p, int value);

extern int CGXDLMSPushObject_GetDataIndex(CGXDLMSPushObject *p);
extern void CGXDLMSPushObject_SetDataIndex(CGXDLMSPushObject *p, int value);

extern String CGXDLMSPushObject_ToString(CGXDLMSPushObject *p);

extern void CGXDLMSPushObject_(CGXDLMSPushObject *p);
extern void CGXDLMSPushObject_d(CGXDLMSPushObject *p);

#endif //GXDLMSPUSHOBJECT_H
