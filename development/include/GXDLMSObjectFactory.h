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

#ifndef GXDLMSOBJECTFACTORY_H
#define GXDLMSOBJECTFACTORY_H

#include "GXDLMSObject.h"

extern CGXDLMSObject* CGXDLMSObjectFactory_CreateObject_1(DLMS_OBJECT_TYPE type);
extern CGXDLMSObject* CGXDLMSObjectFactory_CreateObject_2(DLMS_OBJECT_TYPE type, String ln);
extern String CGXDLMSObjectFactory_ObjectTypeToString(DLMS_OBJECT_TYPE type);

#endif //GXDLMSOBJECTFACTORY_H
