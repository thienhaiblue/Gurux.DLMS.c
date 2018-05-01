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
#ifndef GXDLMSSNPARAMETERS_H
#define GXDLMSSNPARAMETERS_H

#include "GXBytebuffer.h"
#include "GXDLMSSettings.h"

/**
 * SN Parameters
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
     * Item Count.
     */
    int m_Count;

    /**
     * Are there more data to send or more data to receive.
     */
    bool m_MultipleBlocks;

    /**
     * Block index.
     */
    unsigned short m_BlockIndex;

} CGXDLMSSNParameters;
/**
 * Constructor.
 *
 * @param settings
 *            DLMS settings.
 * @param command
 *            Command.
 * @param commandType
 *            command type.
 * @param attributeDescriptor
 * @param data
 *            Attribute descriptor
 */
extern void CGXDLMSSNParameters_(CGXDLMSSNParameters *p, CGXDLMSSettings* settings,
                                 DLMS_COMMAND command,
                                 int count,
                                 int commandType,
                                 CGXByteBuffer* attributeDescriptor,
                                 CGXByteBuffer* data);

//destructor
extern void CGXDLMSSNParameters_d(CGXDLMSSNParameters *p);
/**
 * @return DLMS settings.
 */
extern CGXDLMSSettings* CGXDLMSSNParameters_GetSettings(CGXDLMSSNParameters *p);

/**
 * @return DLMS command.
 */
extern DLMS_COMMAND CGXDLMSSNParameters_GetCommand(CGXDLMSSNParameters *p);

/**
 * @return Request type.
 */
extern int CGXDLMSSNParameters_GetRequestType(CGXDLMSSNParameters *p);

/**
 * @param value
 *            Request type.
 */
extern void CGXDLMSSNParameters_SetRequestType(CGXDLMSSNParameters *p, int value);

/**
 * @return the attributeDescriptor
 */
extern CGXByteBuffer* CGXDLMSSNParameters_GetAttributeDescriptor(CGXDLMSSNParameters *p);

/**
 * @return the data
 */
extern CGXByteBuffer* CGXDLMSSNParameters_GetData(CGXDLMSSNParameters *p);

/**
 * @return the time
 */
extern struct tm* CGXDLMSSNParameters_GetTime(CGXDLMSSNParameters *p);

/**
 * @param value
 *            the time to set
 */
extern void CGXDLMSSNParameters_SetTime(CGXDLMSSNParameters *p, struct tm* value);

/**
 * @return the multipleBlocks
 */
extern bool CGXDLMSSNParameters_IsMultipleBlocks(CGXDLMSSNParameters *p);

/**
 * @param value
 *            the multipleBlocks to set
 */
extern void CGXDLMSSNParameters_SetMultipleBlocks(CGXDLMSSNParameters *p, bool value);

/**
 * @return Block index.
 */
extern unsigned short CGXDLMSSNParameters_GetBlockIndex(CGXDLMSSNParameters *p);

/**
 * @param value
 *            Block index.
 */
extern void CGXDLMSSNParameters_SetBlockIndex(CGXDLMSSNParameters *p, unsigned short value);

/**
 * @return Item Count.
 */
extern int CGXDLMSSNParameters_GetCount(CGXDLMSSNParameters *p);

#endif //GXDLMSSNPARAMETERS_H
