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
// and/or modify it under the terms of the GNU General License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXAPPLICATIONCONTEXTNAME_H
#define GXAPPLICATIONCONTEXTNAME_H

#include "enums.h"
#include "String.h"

typedef struct
{
    String m_LogicalName;
    unsigned char m_JointIsoCtt;
    unsigned char m_Country;
    unsigned short m_CountryName;
    unsigned char m_IdentifiedOrganization;
    unsigned char m_DlmsUA;
    unsigned char m_ApplicationContext;
    unsigned char m_ContextId;
} CGXApplicationContextName;

extern String CGXApplicationContextName_GetLogicalName(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetLogicalName(CGXApplicationContextName *p, String value);

extern unsigned char CGXApplicationContextName_GetJointIsoCtt(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetJointIsoCtt(CGXApplicationContextName *p, unsigned char value);

extern unsigned char CGXApplicationContextName_GetCountry(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetCountry(CGXApplicationContextName *p, unsigned char value);

extern unsigned short CGXApplicationContextName_GetCountryName(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetCountryName(CGXApplicationContextName *p, unsigned short value);

extern unsigned char CGXApplicationContextName_GetIdentifiedOrganization(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetIdentifiedOrganization(CGXApplicationContextName *p, unsigned char value);

extern unsigned char CGXApplicationContextName_GetDlmsUA(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetDlmsUA(CGXApplicationContextName *p, unsigned char value);

extern unsigned char CGXApplicationContextName_GetApplicationContext(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetApplicationContext(CGXApplicationContextName *p, unsigned char value);

extern unsigned char CGXApplicationContextName_GetContextId(CGXApplicationContextName *p);
extern void CGXApplicationContextName_SetContextId(CGXApplicationContextName *p, unsigned char value);

extern String CGXApplicationContextName_ToString(CGXApplicationContextName *p);

extern void CGXApplicationContextName_(CGXApplicationContextName *p);
extern void CGXApplicationContextName_d(CGXApplicationContextName *p);

#endif //GXAPPLICATIONCONTEXTNAME_H
