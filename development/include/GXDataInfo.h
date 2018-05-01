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

#pragma once
#include <stdbool.h>

#include "enums.h"

//This class is used in DLMS data parsing.
typedef struct
{
    // Last array index.
    int m_Index;

    // Items count in array.
    int m_Count;
    // Object data type.
    DLMS_DATA_TYPE m_Type;
    // Is data parsed to the end.
    bool m_Compleate;
} CGXDataInfo;

//Set Last array index.
extern void CGXDataInfo_SetIndex(CGXDataInfo *p, int value);

// Get items count in array.
extern int CGXDataInfo_GetCount(CGXDataInfo *p);

// Set Items count in array.
extern void CGXDataInfo_SetCount(CGXDataInfo *p, int value);
//Get Object data type.
extern DLMS_DATA_TYPE CGXDataInfo_GetType(CGXDataInfo *p);

// Set Object data type.
extern void CGXDataInfo_SetType(CGXDataInfo *p, DLMS_DATA_TYPE value);

// Is all data parsed.
extern bool CGXDataInfo_IsCompleate(CGXDataInfo *p);

//Is all data parsed.
extern void CGXDataInfo_SetCompleate(CGXDataInfo *p, bool value);
//Clear settings.
extern void CGXDataInfo_Clear(CGXDataInfo *p);

//Constructor.
extern void CGXDataInfo_(CGXDataInfo *p);
