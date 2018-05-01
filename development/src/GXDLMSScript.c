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

#include "../include/GXDLMSScript.h"
#include "../include/DLMSPort.h"

void CGXDLMSScript_(CGXDLMSScript* p)
{
    Vector_(&p->m_Actions, sizeof(CGXDLMSScriptAction*), NULL, NULL); //std::vector<CGXDLMSScriptAction*>
}

void CGXDLMSScript_d(CGXDLMSScript* p)
{
    // std::vector<CGXDLMSScriptAction*>
    for (unsigned i = Vector_begin(&p->m_Actions); i != Vector_end(&p->m_Actions); ++i)
    {
        //delete *it;
        CGXDLMSScriptAction** it = (CGXDLMSScriptAction**) Vector_at(&p->m_Actions, i);

        CGXDLMSScriptAction_d(*it);
        DLMSPort_free(*it);
    }
    Vector_clear(&p->m_Actions);
}

Vector* CGXDLMSScript_GetActions(CGXDLMSScript* p) //std::vector<CGXDLMSScriptAction*>&
{
    return &p->m_Actions;
}
