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

#ifndef GXDLMSMONITOREDVALUE_H
#define GXDLMSMONITOREDVALUE_H

#include "GXDLMSObject.h"

typedef struct
{
    DLMS_OBJECT_TYPE m_ObjectType;
    String m_LogicalName;
    int m_AttributeIndex;
} CGXDLMSMonitoredValue;

extern void CGXDLMSMonitoredValue_(CGXDLMSMonitoredValue *p);
extern void CGXDLMSMonitoredValue_Update(CGXDLMSMonitoredValue *p, CGXDLMSObject* pObj, int attributeIndex);

DLMS_OBJECT_TYPE CGXDLMSMonitoredValue_GetObjectType(CGXDLMSMonitoredValue *p);
extern void CGXDLMSMonitoredValue_SetObjectType(CGXDLMSMonitoredValue *p, DLMS_OBJECT_TYPE value);

extern String CGXDLMSMonitoredValue_GetLogicalName(CGXDLMSMonitoredValue *p);
extern void CGXDLMSMonitoredValue_SetLogicalName(CGXDLMSMonitoredValue *p, String value);

extern int CGXDLMSMonitoredValue_GetAttributeIndex(CGXDLMSMonitoredValue *p);
extern void CGXDLMSMonitoredValue_SetAttributeIndex(CGXDLMSMonitoredValue *p, int value);

extern String CGXDLMSMonitoredValue_ToString(CGXDLMSMonitoredValue *p);

extern void CGXDLMSMonitoredValue_d(CGXDLMSMonitoredValue *p);

#endif //GXDLMSMONITOREDVALUE_H
