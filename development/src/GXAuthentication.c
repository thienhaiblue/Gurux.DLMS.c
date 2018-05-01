/*
 * GXAuthentication.c
 *
 *  Created on: Mar 4, 2018
 *      Author: admin
 */

#include "../include/GXAuthentication.h"

static void GXAuthentication__(GXAuthentication *p)
{
    CGXDLMSVariant_1(&p->m_ClientID);
    String_(&p->m_Password);
}

void GXAuthentication_1(GXAuthentication *p)
{
    GXAuthentication__(p);
}

void GXAuthentication_2(GXAuthentication *p, DLMS_AUTHENTICATION type,
                        String password, CGXDLMSVariant clientID)
{
    GXAuthentication__(p);

    p->m_Type = type;

    CGXDLMSVariant_copy_1(&(p->m_ClientID), &clientID);
}

void GXAuthentication_GetClientID(GXAuthentication *p, CGXDLMSVariant *out)
{
    CGXDLMSVariant_d(out);
    CGXDLMSVariant_2(out, &(p->m_ClientID));
}

void GXAuthentication_SetClientID(GXAuthentication *p, CGXDLMSVariant value)
{
    CGXDLMSVariant_copy_1(&(p->m_ClientID), &value);
}

void GXAuthentication_GetPassword(GXAuthentication *p, String *out)
{
    String_d(out);
    String_2(out, &(p->m_Password));
}

void GXAuthentication_SetPassword(GXAuthentication *p, String value)
{
    String_copy_1(&(p->m_Password), &value);
}

void GXAuthentication_d(GXAuthentication *p)
{
    CGXDLMSVariant_d(&p->m_ClientID);
    String_d(&p->m_Password);
}
