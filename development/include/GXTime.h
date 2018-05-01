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

#ifndef GXTIME_H
#define GXTIME_H

#include <stdbool.h>

#include "GXDateTime.h"

/**
* Time object. Date part is ignored.
*/
typedef struct
{
    short m_Deviation;
    DATETIME_SKIPS m_Skip;
    struct tm m_Value;
    bool m_DaylightSavingsBegin;
    bool m_DaylightSavingsEnd;
    DLMS_CLOCK_STATUS m_Status;
} CGXTime;

#define CGXTime_ToString(p) CGXDateTime_ToString((CGXDateTime*) (p))

// Constructor.
extern void CGXTime_1(CGXTime* p);

// Constructor.
extern void CGXTime_2(CGXTime* p, struct tm value);

// Constructor.
extern void CGXTime_3(CGXTime* p, int hour, int minute, int second, int millisecond);

/**
* Constructor.
*
* @param value
*            Date value.
*/
extern void CGXTime_4(CGXTime* p, CGXDateTime* value);

// operator=
extern void CGXTime_copy_1(CGXTime* p, const CGXDateTime* value);

extern void CGXTime_copy_2(CGXTime* p, CGXDateTime value);

#endif //GXTIME_H
