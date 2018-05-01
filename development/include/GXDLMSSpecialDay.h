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

#ifndef GXDLMSSPECIALDAY_H
#define GXDLMSSPECIALDAY_H

#include "GXDateTime.h"
#include "String.h"

typedef struct
{
    int m_Index;
    CGXDateTime m_Date;
    int m_DayId;

} CGXDLMSSpecialDay;

extern int CGXDLMSSpecialDay_GetIndex(CGXDLMSSpecialDay *p);
extern void CGXDLMSSpecialDay_SetIndex(CGXDLMSSpecialDay *p, int value);

extern CGXDateTime* CGXDLMSSpecialDay_GetDate(CGXDLMSSpecialDay *p);
extern void CGXDLMSSpecialDay_SetDate(CGXDLMSSpecialDay *p, CGXDateTime value);

extern int CGXDLMSSpecialDay_GetDayId(CGXDLMSSpecialDay *p);
extern void CGXDLMSSpecialDay_SetDayId(CGXDLMSSpecialDay *p, int value);

extern String CGXDLMSSpecialDay_ToString(CGXDLMSSpecialDay *p);

extern void CGXDLMSSpecialDay_(CGXDLMSSpecialDay *p);

#endif //GXDLMSSPECIALDAY_H
