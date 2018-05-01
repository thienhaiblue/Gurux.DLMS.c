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

#include "../include/GXDLMSImageActivateInfo.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

void CGXDLMSImageActivateInfo__(CGXDLMSImageActivateInfo *p)
{
    String_(&p->m_Identification);
    String_(&p->m_Signature);
}

/**
 * Constructor.
 */
void CGXDLMSImageActivateInfo_1(CGXDLMSImageActivateInfo *p)
{
    CGXDLMSImageActivateInfo__(p);
}

/**
 * Constructor.
 */
void CGXDLMSImageActivateInfo_2(CGXDLMSImageActivateInfo *p, long size, String identification, String signature)
{
    CGXDLMSImageActivateInfo__(p);

    p->m_Size = size;
    String_copy_1(&(p->m_Identification), &identification);
    String_copy_1(&(p->m_Signature), &signature);
}

/**
 * Image identification is the identification of the Image(s)
 * to be activated, and may contain information like
 * manufacturer, device type, version information, etc.
*/
String CGXDLMSImageActivateInfo_GetIdentification(CGXDLMSImageActivateInfo *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_Identification));

    return t_Str; // = copy cons + des
}
void CGXDLMSImageActivateInfo_SetIdentification(CGXDLMSImageActivateInfo *p, String value)
{
    String_copy_1(&(p->m_Identification), &value);
}

/**
 * Image signature is the signature of the Image(s) to be activated.
*/
String CGXDLMSImageActivateInfo_GetSignature(CGXDLMSImageActivateInfo *p)
{
    String t_Str;
    String_2(&t_Str, &(p->m_Signature));

    return t_Str; // = copy cons + des
}
void CGXDLMSImageActivateInfo_SetSignature(CGXDLMSImageActivateInfo *p, String value)
{
    String_copy_1(&(p->m_Signature), &value);
}

String CGXDLMSImageActivateInfo_ToString(CGXDLMSImageActivateInfo *p)
{
    String sb;
    String_(&sb);

    String_append_3(&sb, &(p->m_Identification));
    String_append_1(&sb, " ");
    String_append_3(&sb, &(p->m_Signature));
    String_append_1(&sb, " ");

    String_append_int(&sb, p->m_Size);

    return sb; // = copy cons + des
}

void CGXDLMSImageActivateInfo_d(CGXDLMSImageActivateInfo *p)
{
    String_d(&p->m_Identification);
    String_d(&p->m_Signature);
}
