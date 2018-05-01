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

#include "../include/GXAuthenticationMechanismName.h"
#include "../include/GXDLMSVariant.h"
#include "../include/Optimize.h"

void CGXAuthenticationMechanismName_(CGXAuthenticationMechanismName* p)
{
    p->m_MechanismId = DLMS_AUTHENTICATION_NONE;
    p->m_JointIsoCtt = p->m_Country = p->m_CountryName = 0;
    p->m_IdentifiedOrganization = p->m_DlmsUA = p->m_AuthenticationMechanismName = 0;
}

String CGXAuthenticationMechanismName_ToString(CGXAuthenticationMechanismName* p)
{
    String sb;
    String_(&sb);

    String_append_var_int(&sb, p->m_JointIsoCtt);

    String_append_1(&sb, " ");

    String_append_var_int(&sb, p->m_Country);

    String_append_1(&sb, " ");

    String_append_var_int(&sb, p->m_CountryName);

    String_append_1(&sb, " ");

    String_append_var_int(&sb, p->m_IdentifiedOrganization);

    String_append_1(&sb, " ");

    String_append_var_int(&sb, p->m_DlmsUA);

    String_append_1(&sb, " ");

    String_append_var_int(&sb, p->m_AuthenticationMechanismName);

    String_append_1(&sb, " ");

    String_append_var_int(&sb, p->m_MechanismId);

    return sb; // = copy cons + des
}
