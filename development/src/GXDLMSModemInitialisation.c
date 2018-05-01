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

#include "../include/GXDLMSModemInitialisation.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

void CGXDLMSModemInitialisation_(CGXDLMSModemInitialisation *p)
{
    String_(&p->m_Request);
    String_(&p->m_Response);
    p->m_Delay = 0;
}

String CGXDLMSModemInitialisation_GetRequest(CGXDLMSModemInitialisation *p)
{
    String res;
    String_2(&res, &(p->m_Request));

    return res; // = copy cons + des
}
void CGXDLMSModemInitialisation_SetRequest(CGXDLMSModemInitialisation *p, String value)
{
    String_copy_1(&(p->m_Request), &value);
}

String CGXDLMSModemInitialisation_GetResponse(CGXDLMSModemInitialisation *p)
{
    String res;
    String_2(&res, &(p->m_Response));

    return res; // = copy cons + des
}
void CGXDLMSModemInitialisation_SetResponse(CGXDLMSModemInitialisation *p, String value)
{
    String_copy_1(&(p->m_Response), &value);
}

String CGXDLMSModemInitialisation_ToString(CGXDLMSModemInitialisation *p)
{
	String sb;
	String_(&sb);

	String_append_3(&sb, &(p->m_Request));
	String_append_1(&sb, " ");

	String_append_3(&sb, &(p->m_Response));
	String_append_1(&sb, " ");

	String_append_int(&sb, p->m_Delay);

	return sb; // = copy cons + des
}

void CGXDLMSModemInitialisation_d(CGXDLMSModemInitialisation *p)
{
    String_d(&p->m_Request);
    String_d(&p->m_Response);
}

void CGXDLMSModemInitialisation_v_c(void* p1, const void* p2)
{
    CGXDLMSModemInitialisation* t_p1 = (CGXDLMSModemInitialisation*) p1;
    CGXDLMSModemInitialisation* t_p2 = (CGXDLMSModemInitialisation*) p2;
	String_(&t_p1->m_Request);
	String_(&t_p1->m_Response);
    String_copy_1(&t_p1->m_Request, &t_p2->m_Request);
    String_copy_1(&t_p1->m_Response, &t_p2->m_Response);
    t_p1->m_Delay = t_p2->m_Delay;
}

void CGXDLMSModemInitialisation_v_d(void* p)
{
    CGXDLMSModemInitialisation_d((CGXDLMSModemInitialisation*) p);
}
