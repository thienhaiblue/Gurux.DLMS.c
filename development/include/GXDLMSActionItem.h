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
#ifndef GXDLMSACTIONITEM_H
#define GXDLMSACTIONITEM_H

#include "enums.h"
#include "DLMSPort.h"
#include "String.h"

typedef struct CGXDLMSActionItem
{
    String m_LogicalName;
    int m_ScriptSelector;
} CGXDLMSActionItem;

//Constructor.
extern void CGXDLMSActionItem_(CGXDLMSActionItem* p);

//Destructor.
extern void CGXDLMSActionItem_d(CGXDLMSActionItem* p);

extern String CGXDLMSActionItem_GetLogicalName(CGXDLMSActionItem* p);

extern void CGXDLMSActionItem_SetLogicalName(CGXDLMSActionItem* p, String value);

extern int CGXDLMSActionItem_GetScriptSelector(CGXDLMSActionItem* p);

extern void CGXDLMSActionItem_SetScriptSelector(CGXDLMSActionItem* p, int value);

extern String CGXDLMSActionItem_ToString(CGXDLMSActionItem* p);

extern void CGXDLMSActionItem_copy(CGXDLMSActionItem* p, CGXDLMSActionItem* src);

#endif //GXDLMSACTIONITEM_H
