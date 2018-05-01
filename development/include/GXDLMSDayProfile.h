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

#ifndef GXDLMSDAYPROFILE_H
#define GXDLMSDAYPROFILE_H

#include "Vector.h"
#include "String.h"
#include "GXDLMSDayProfileAction.h"

typedef struct
{
    short m_DayId;
    Vector m_DaySchedules; // std::vector<CGXDLMSDayProfileAction*>
} CGXDLMSDayProfile;

/**
 Constructor.
*/
extern void CGXDLMSDayProfile_1(CGXDLMSDayProfile *p);

/**
 Constructor.
*/
extern void CGXDLMSDayProfile_2(CGXDLMSDayProfile *p, short dayId, Vector* schedules);

//Destructor.
extern void CGXDLMSDayProfile_d(CGXDLMSDayProfile *p);


/**
 User defined identifier, identifying the currentday_profile.
*/
extern short CGXDLMSDayProfile_GetDayId(CGXDLMSDayProfile *p);
extern void CGXDLMSDayProfile_SetDayId(CGXDLMSDayProfile *p, short value);

extern Vector* CGXDLMSDayProfile_GetDaySchedules(CGXDLMSDayProfile *p);
extern void CGXDLMSDayProfile_SetDaySchedules(CGXDLMSDayProfile *p, Vector* value);
extern String CGXDLMSDayProfile_ToString(CGXDLMSDayProfile *p);
#endif //GXDLMSDAYPROFILE_H
