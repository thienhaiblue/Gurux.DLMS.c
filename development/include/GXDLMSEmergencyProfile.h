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

#ifndef GXDLMSEMERGENCYPROFILE_H
#define GXDLMSEMERGENCYPROFILE_H

typedef struct
{
    int m_ID;
    CGXDateTime m_ActivationTime;
    int m_Duration;

} CGXDLMSEmergencyProfile;

extern int CGXDLMSEmergencyProfile_GetID(CGXDLMSEmergencyProfile *p);
extern void CGXDLMSEmergencyProfile_SetID(CGXDLMSEmergencyProfile *p, int value);

extern CGXDateTime* CGXDLMSEmergencyProfile_GetActivationTime(CGXDLMSEmergencyProfile *p);
extern void CGXDLMSEmergencyProfile_SetActivationTime(CGXDLMSEmergencyProfile *p, CGXDateTime value);

extern int CGXDLMSEmergencyProfile_GetDuration(CGXDLMSEmergencyProfile *p);
extern void CGXDLMSEmergencyProfile_SetDuration(CGXDLMSEmergencyProfile *p, int value);

extern String CGXDLMSEmergencyProfile_ToString(CGXDLMSEmergencyProfile *p);

extern void CGXDLMSEmergencyProfile_(CGXDLMSEmergencyProfile *p);

#endif //GXDLMSEMERGENCYPROFILE_H
