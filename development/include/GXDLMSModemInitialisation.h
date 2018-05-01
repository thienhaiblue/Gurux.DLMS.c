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

#ifndef GXDLMSMODEMINITIALISATION_H
#define GXDLMSMODEMINITIALISATION_H

#include "String.h"

typedef struct
{
    String m_Request;
    String m_Response;
    int m_Delay;

} CGXDLMSModemInitialisation;

extern void CGXDLMSModemInitialisation_(CGXDLMSModemInitialisation *p);
extern String CGXDLMSModemInitialisation_GetRequest(CGXDLMSModemInitialisation *p);
extern void CGXDLMSModemInitialisation_SetRequest(CGXDLMSModemInitialisation *p, String value);
extern String CGXDLMSModemInitialisation_GetResponse(CGXDLMSModemInitialisation *p);
extern void CGXDLMSModemInitialisation_SetResponse(CGXDLMSModemInitialisation *p, String value);
extern int CGXDLMSModemInitialisation_GetDelay(CGXDLMSModemInitialisation *p);
extern void CGXDLMSModemInitialisation_SetDelay(CGXDLMSModemInitialisation *p, int value);

extern String CGXDLMSModemInitialisation_ToString(CGXDLMSModemInitialisation *p);

extern void CGXDLMSModemInitialisation_d(CGXDLMSModemInitialisation *p);

extern void CGXDLMSModemInitialisation_v_c(void* p1, const void* p2);
extern void CGXDLMSModemInitialisation_v_d(void* p);

#endif //GXDLMSMODEMINITIALISATION_H
