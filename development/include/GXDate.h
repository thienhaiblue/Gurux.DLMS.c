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

#ifndef GXDATE_H
#define GXDATE_H

#include "GXDateTime.h"

/**
* Date object. Time part is ignored.
*/
typedef struct
{
    short m_Deviation;
    DATETIME_SKIPS m_Skip;
    struct tm m_Value;
    bool m_DaylightSavingsBegin;
    bool m_DaylightSavingsEnd;
    DLMS_CLOCK_STATUS m_Status;
} CGXDate;

#define CGXDate_SetSkip(p, value) CGXDateTime_SetSkip((CGXDateTime*) (p), (value))
#define CGXDate_GetSkip(p)        CGXDateTime_GetSkip((CGXDateTime*) (p))

// Constructor.
extern void CGXDate_1(CGXDate* p);

// Constructor.
extern void CGXDate_2(CGXDate* p, struct tm value);

// Constructor.
extern void CGXDate_3(CGXDate* p, int year, int month, int day);

/**
* Constructor.
*
* @param forvalue
*            Date value.
*/
/// <summary>
/// Constructor.
/// </summary>
extern void CGXDate_4(CGXDate* p, CGXDateTime* value);

// operator=
extern void CGXDate_copy_1(CGXDate* p, const CGXDateTime* value);

extern void CGXDate_copy_2(CGXDate* p, CGXDateTime value);

#endif //GXDATE_H
