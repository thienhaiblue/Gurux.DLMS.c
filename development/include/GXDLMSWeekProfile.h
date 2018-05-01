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
#ifndef GXDLMSWEEKPROFILE_H
#define GXDLMSWEEKPROFILE_H

#include "String.h"

typedef struct
{
    String m_Name;
    int m_Monday;
    int m_Tuesday;
    int m_Wednesday;
    int m_Thursday;
    int m_Friday;
    int m_Saturday;
    int m_Sunday;
} CGXDLMSWeekProfile;

/**
 Constructor.
*/
extern void CGXDLMSWeekProfile_1(CGXDLMSWeekProfile* p);

/**
 Constructor.
*/
extern void CGXDLMSWeekProfile_2(CGXDLMSWeekProfile* p, String name, int monday, int tuesday, int wednesday, int thursday, int friday, int saturday, int sunday);

extern String CGXDLMSWeekProfile_GetName(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetName(CGXDLMSWeekProfile* p, String value);

extern int CGXDLMSWeekProfile_GetMonday(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetMonday(CGXDLMSWeekProfile* p, int value);

extern int CGXDLMSWeekProfile_GetTuesday(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetTuesday(CGXDLMSWeekProfile* p, int value);

extern int CGXDLMSWeekProfile_GetWednesday(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetWednesday(CGXDLMSWeekProfile* p, int value);

extern int CGXDLMSWeekProfile_GetThursday(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetThursday(CGXDLMSWeekProfile* p, int value);

extern int CGXDLMSWeekProfile_GetFriday(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetFriday(CGXDLMSWeekProfile* p, int value);

extern int CGXDLMSWeekProfile_GetSaturday(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetSaturday(CGXDLMSWeekProfile* p, int value);

extern int CGXDLMSWeekProfile_GetSunday(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_SetSunday(CGXDLMSWeekProfile* p, int value);

extern String CGXDLMSWeekProfile_ToString(CGXDLMSWeekProfile* p);

extern void CGXDLMSWeekProfile_d(CGXDLMSWeekProfile* p);

#endif //GXDLMSWEEKPROFILE_H
