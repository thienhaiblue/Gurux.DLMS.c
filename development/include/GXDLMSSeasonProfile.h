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

#ifndef GXDLMSSEASONPROFILE_H
#define GXDLMSSEASONPROFILE_H

#include "GXDateTime.h"

#include "String.h"

typedef struct
{
    String m_Name;
    CGXDateTime m_Start;
    String m_WeekName;
} CGXDLMSSeasonProfile;

/**
 Constructor.
*/
extern void CGXDLMSSeasonProfile_1(CGXDLMSSeasonProfile* p);

/**
 Constructor.
*/
extern void CGXDLMSSeasonProfile_2(CGXDLMSSeasonProfile* p, String name, CGXDateTime start, String weekName);

/**
 Name of season profile.
*/
extern String CGXDLMSSeasonProfile_GetName(CGXDLMSSeasonProfile* p);
extern void CGXDLMSSeasonProfile_SetName(CGXDLMSSeasonProfile* p, String value);

/**
 Season Profile start time.
*/
extern CGXDateTime* CGXDLMSSeasonProfile_GetStart(CGXDLMSSeasonProfile* p);
extern void CGXDLMSSeasonProfile_SetStart(CGXDLMSSeasonProfile* p, CGXDateTime value);

/**
 Week name of season profile.
*/
extern String CGXDLMSSeasonProfile_GetWeekName(CGXDLMSSeasonProfile* p);
extern void CGXDLMSSeasonProfile_SetWeekName(CGXDLMSSeasonProfile* p, String value);

extern String CGXDLMSSeasonProfile_ToString(CGXDLMSSeasonProfile* p);

extern void CGXDLMSSeasonProfile_d(CGXDLMSSeasonProfile* p);

#endif //GXDLMSSEASONPROFILE_H
