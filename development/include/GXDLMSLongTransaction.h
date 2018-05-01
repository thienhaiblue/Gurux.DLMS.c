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

#ifndef GXDLMSLONGTRANSACTION_H
#define GXDLMSLONGTRANSACTION_H

#include "Vector.h"
#include "enums.h"
#include "GXBytebuffer.h"
#include "GXDLMSValueEventArg.h"
#include "GXDLMSValueEventCollection.h"

typedef struct
{
    /**
    * Executed command.
    */
    DLMS_COMMAND m_Command;

    /**
     * Targets.
     */
    CGXDLMSValueEventCollection m_Targets;

    /**
     * Extra data from PDU.
     */
    CGXByteBuffer m_Data;

} CGXDLMSLongTransaction;

/**
 * Destructor.
 */
extern void CGXDLMSLongTransaction_d(CGXDLMSLongTransaction *p);

/**
 * Constructor.
 *
 * @param targets
 * @param command
 * @param data
 */
extern void CGXDLMSLongTransaction_(CGXDLMSLongTransaction *p, CGXDLMSValueEventCollection* targets,
                                    DLMS_COMMAND command, CGXByteBuffer* data);

/**
 * @return Executed command.
 */
extern DLMS_COMMAND CGXDLMSLongTransaction_GetCommand(CGXDLMSLongTransaction *p);

/**
 * @return Targets.
 */
extern Vector* CGXDLMSLongTransaction_GetTargets(CGXDLMSLongTransaction *p); // std::vector<CGXDLMSValueEventArg*>&

/**
 * @return data.
 */
extern CGXByteBuffer* CGXDLMSLongTransaction_GetData(CGXDLMSLongTransaction *p);

/**
 * @param value
 *            New data.
 */
extern void CGXDLMSLongTransaction_SetData(CGXDLMSLongTransaction *p, CGXByteBuffer* value);

#endif //GXDLMSLONGTRANSACTION_H
