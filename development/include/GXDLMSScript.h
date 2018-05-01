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

#ifndef GXDLMSSCRIPT_H
#define GXDLMSSCRIPT_H

#include "GXDLMSScriptAction.h"

#include "Vector.h"

typedef struct
{
    /**
     * Script identifier.
     */
    int m_ID;

    /**
     * Script actions.
     */
    Vector m_Actions; //std::vector<CGXDLMSScriptAction*>

} CGXDLMSScript;

/**
 * Constructor.
 */
extern void CGXDLMSScript_(CGXDLMSScript* p);

/**
* Destructor.
*/
extern void CGXDLMSScript_d(CGXDLMSScript* p);

/**
 * @return Script identifier.
 */
extern int CGXDLMSScript_GetID(CGXDLMSScript* p);

/**
 * @param value
 *            Script identifier.
 */
extern void CGXDLMSScript_SetID(CGXDLMSScript* p, int value);

/**
 * @return Script actions.
 */
extern Vector* CGXDLMSScript_GetActions(CGXDLMSScript* p);//std::vector<CGXDLMSScriptAction*>&

#endif //GXDLMSSCRIPT_H
