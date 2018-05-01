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
#ifndef IGXDLMSBASE_H
#define IGXDLMSBASE_H

typedef struct CGXDLMSValueEventArg CGXDLMSValueEventArg;
typedef struct CGXDLMSSettings CGXDLMSSettings;

typedef int (*GetAttributeCount_FuncPtr)(void* p);
typedef int (*GetMethodCount_FuncPtr)(void* p);
typedef int (*GetValue_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);
typedef int (*SetValue_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);
typedef int (*Invoke_FuncPtr)(void* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

typedef struct
{
	///////////////////////////////////////////////////////////////////////////
    // Returns amount of attributes.
	GetAttributeCount_FuncPtr GetAttributeCount;

    // Returns amount of methods.
	GetMethodCount_FuncPtr GetMethodCount;

    // Returns value of given attribute.
	GetValue_FuncPtr GetValue;

    // Set value of given attribute.
	SetValue_FuncPtr SetValue;

    // Invokes method.
	Invoke_FuncPtr Invoke;
	///////////////////////////////////////////////////////////////////////////

//	virtual DLMS_DATA_TYPE GetUIDataType(int index) = 0;
} IGXDLMSBase;

#endif //IGXDLMSBASE_H
