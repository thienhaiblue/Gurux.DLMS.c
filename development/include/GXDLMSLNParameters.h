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
#ifndef GXDLMSLNPARAMETERS_H
#define GXDLMSLNPARAMETERS_H

#include "GXBytebuffer.h"
#include "GXDLMSSettings.h"

/**
 * LN Parameters
 */
typedef struct
{

    /**
     * DLMS settings.
     */
    CGXDLMSSettings *m_Settings;
    /**
     * DLMS command.
     */
    DLMS_COMMAND m_Command;
    /**
     * Request type.
     */
    int m_RequestType;
    /**
     * Attribute descriptor.
     */
    CGXByteBuffer* m_AttributeDescriptor;
    /**
     * Data.
     */
    CGXByteBuffer* m_Data;
    /**
     * Send date and time. This is used in Data notification messages.
     */
    struct tm* m_Time;
    /**
     * Reply status.
     */
    int m_Status;
    /**
     * Are there more data to send or more data to receive.
     */
    bool m_MultipleBlocks;
    /**
     * Is this last block in send.
     */
    bool m_LastBlock;
    /**
     * Block index.
     */
    unsigned long m_BlockIndex;
    /**
    * Invoke ID.
    */
    unsigned long m_InvokeId;
} CGXDLMSLNParameters;

/**
 * Constructor.
 *
 * @param settings
 *            DLMS settings.
 * @param command
 *            Command.
 * @param commandType
 *            DLMS_COMMAND type.
 * @param attributeDescriptor
 *            Attribute descriptor.
 * @param data
 *            Data.
 */
extern void CGXDLMSLNParameters_(CGXDLMSLNParameters* p,
                                 CGXDLMSSettings* settings,
                                 unsigned long invokeId,
                                 DLMS_COMMAND command,
                                 int commandType,
                                 CGXByteBuffer* attributeDescriptor,
                                 CGXByteBuffer* data,
                                 int status);

/**
 * @return DLMS settings.
 */
extern CGXDLMSSettings* CGXDLMSLNParameters_GetSettings(CGXDLMSLNParameters *p);

/**
 * @return DLMS command.
 */
extern DLMS_COMMAND CGXDLMSLNParameters_GetCommand(CGXDLMSLNParameters *p);

/**
 * @return Request type.
 */
extern int CGXDLMSLNParameters_GetRequestType(CGXDLMSLNParameters *p);

/**
 * @param value
 *            the requestType to set
 */
extern void CGXDLMSLNParameters_SetRequestType(CGXDLMSLNParameters *p, int value);

/**
 * @return the attributeDescriptor
 */
extern CGXByteBuffer* CGXDLMSLNParameters_GetAttributeDescriptor(CGXDLMSLNParameters *p);

/**
 * @return the data
 */
extern CGXByteBuffer* CGXDLMSLNParameters_GetData(CGXDLMSLNParameters *p);

/**
 * @return the time
 */
extern struct tm* CGXDLMSLNParameters_GetTime(CGXDLMSLNParameters *p);

/**
 * @param value
 *            the time to set
 */
extern void CGXDLMSLNParameters_SetTime(CGXDLMSLNParameters *p, struct tm* value);

/**
 * @return Status.
 */
extern int CGXDLMSLNParameters_GetStatus(CGXDLMSLNParameters *p);

/**
 * @param value
 *            Status to set
 */
extern void CGXDLMSLNParameters_SetStatus(CGXDLMSLNParameters *p, int value);

/**
 * @return the multipleBlocks
 */
extern bool CGXDLMSLNParameters_IsMultipleBlocks(CGXDLMSLNParameters *p);

/**
 * @param value
 *            the multipleBlocks to set
 */
extern void CGXDLMSLNParameters_SetMultipleBlocks(CGXDLMSLNParameters *p, bool value);

/**
 * @return the lastBlock
 */
extern bool CGXDLMSLNParameters_IsLastBlock(CGXDLMSLNParameters *p);

/**
 * @param value
 *            Block index.
 */
extern void CGXDLMSLNParameters_SetLastBlock(CGXDLMSLNParameters *p, bool value);

/**
 * @return Block index.
 */
extern unsigned long CGXDLMSLNParameters_GetBlockIndex(CGXDLMSLNParameters *p);

/**
 * @param value
 *            the blockIndex to set
 */
extern void CGXDLMSLNParameters_SetBlockIndex(CGXDLMSLNParameters *p, unsigned long value);

/**
* @return Get Invoke ID and priority. This can be used for Priority
*         Management.
*/
extern unsigned long CGXDLMSLNParameters_GetInvokeId(CGXDLMSLNParameters *p);

/**
* @param value
*            Set Invoke ID and priority. This can be used for Priority
*            Management.
*/
extern void CGXDLMSLNParameters_SetInvokeId(CGXDLMSLNParameters *p, unsigned long value);

extern void CGXDLMSLNParameters_d(CGXDLMSLNParameters *p);

#endif //GXDLMSLNPARAMETERS_H
