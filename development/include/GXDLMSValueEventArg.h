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

#ifndef GXDLMSVALUEEVENTARGS_H
#define GXDLMSVALUEEVENTARGS_H

#include "enums.h"
#include "errorcodes.h"
#include "GXDLMSVariant.h"

typedef struct CGXDLMSObject CGXDLMSObject;
typedef struct CGXDLMSServer CGXDLMSServer;
typedef struct CGXDLMSClient CGXDLMSClient;
typedef struct CGXDLMSNotify CGXDLMSNotify;
typedef struct CGXDLMSSettings CGXDLMSSettings;
typedef struct CGXDLMSAssociationLogicalName CGXDLMSAssociationLogicalName;

typedef struct CGXDLMSValueEventArg
{
    /**
    * CGXDLMSVariant value.
    */
    CGXDLMSVariant m_Value;
    /**
    * Is request handled.
    */
    bool m_Handled;
    /**
    * Target DLMS object
    */
    CGXDLMSObject* m_Target;
    /**
    * Attribute index.
    */
    int m_Index;
    /**
    * Optional selector.
    */
    int m_Selector;
    /**
    * Optional parameters.
    */
    CGXDLMSVariant m_Parameters;

    /**
     * Occurred error.
     */
    DLMS_ERROR_CODE m_Error;
    /**
    * Is action. This is reserved for internal use.
    */
    bool m_Action;

    /**
    * Is data handled as byte array.
    */
    bool m_ByteArray;

    /**
    * Is value max PDU size skipped.
    */
    bool m_SkipMaxPduSize;

    /**
    * Row to PDU is used with Profile Generic to tell how many rows are fit to
    * one PDU.
    */
    unsigned short m_RowToPdu;
    /**
    * Rows begin index.
    */
    unsigned short m_RowBeginIndex;
    /**
    * Rows end index.
    */
    unsigned short m_RowEndIndex;

    /**
    * DLMS settings.
    */
    CGXDLMSSettings* m_Settings;

    /**
    * DLMS server.
    */
    CGXDLMSServer* m_Server;

    /**
    * Received invoke ID.
    */
    unsigned int m_InvokeId;

} CGXDLMSValueEventArg;

extern void CGXDLMSValueEventArg_Init(
    CGXDLMSValueEventArg* p,
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index,
    int selector);

/**
* Constructor.
*
* @param target
*            Event target.
* @param index
*            Event index.
*/
extern void CGXDLMSValueEventArg_1(
    CGXDLMSValueEventArg* p,
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index);

/**
* Constructor.
*
* @param target
*            Event target.
* @param index
*            Event index.
* @param selector
*            Optional read event selector.
* @param parameters
*            Optional parameters.
*/
extern void CGXDLMSValueEventArg_2(
    CGXDLMSValueEventArg* p,
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index,
    int selector,
    CGXDLMSVariant* parameters);

/**
* DLMS server.
*/
extern CGXDLMSServer* CGXDLMSValueEventArg_GetServer(CGXDLMSValueEventArg* p);

/**
* @return Target DLMS object.
*/
extern CGXDLMSObject* CGXDLMSValueEventArg_GetTarget(CGXDLMSValueEventArg* p);

extern void CGXDLMSValueEventArg_SetTarget(CGXDLMSValueEventArg* p, CGXDLMSObject* value);

/**
* @return Attribute index of queried object.
*/
extern int CGXDLMSValueEventArg_GetIndex(CGXDLMSValueEventArg* p);

extern void CGXDLMSValueEventArg_SetIndex(CGXDLMSValueEventArg* p, int value);

/**
* @return CGXDLMSVariant value.
*/
extern CGXDLMSVariant* CGXDLMSValueEventArg_GetValue(CGXDLMSValueEventArg* p);

/**
* @param value
*            CGXDLMSVariant value.
*/
extern void CGXDLMSValueEventArg_SetValue(CGXDLMSValueEventArg* p, CGXDLMSVariant* value);

/**
* @return Is request handled.
*/
extern bool CGXDLMSValueEventArg_GetHandled(CGXDLMSValueEventArg* p);

/**
* @param value
*            Is request handled.
*/
extern void CGXDLMSValueEventArg_SetHandled(CGXDLMSValueEventArg* p, bool value);

/**
* @return Optional selector.
*/
extern int CGXDLMSValueEventArg_GetSelector(CGXDLMSValueEventArg* p);

/**
* @param value
*           Selector.
*/
extern void CGXDLMSValueEventArg_SetSelector(CGXDLMSValueEventArg* p, int value);

/**
* @return Optional parameters.
*/
extern CGXDLMSVariant* CGXDLMSValueEventArg_GetParameters(CGXDLMSValueEventArg* p);

/**
* @param value
*           Parameters.
*/
extern void CGXDLMSValueEventArg_SetParameters(CGXDLMSValueEventArg* p, CGXDLMSVariant* value);


/**
* Constructor.
*
* @param target
*            Event target.
* @param index
*            Event index.
*/
extern void CGXDLMSValueEventArg_3(
    CGXDLMSValueEventArg* p,
    CGXDLMSObject* target,
    int index);

/**
* Constructor.
*
* @param target
*            Event target.
* @param index
*            Event index.
* @param selector
*            Optional read event selector.
* @param parameters
*            Optional parameters.
*/
extern void CGXDLMSValueEventArg_4(
    CGXDLMSValueEventArg* p,
    CGXDLMSObject* target,
    int index,
    int selector,
    CGXDLMSVariant* parameters);

/**
* @return Occurred error.
*/
extern DLMS_ERROR_CODE CGXDLMSValueEventArg_GetError(CGXDLMSValueEventArg* p);

/**
 * @param error
 *            Occurred error.
 */
extern void CGXDLMSValueEventArg_SetError(CGXDLMSValueEventArg* p, DLMS_ERROR_CODE value);

/**
* @return Is action.
*/
extern bool CGXDLMSValueEventArg_IsAction(CGXDLMSValueEventArg* p);

/**
* @param value
*            Is action.
*/
extern void CGXDLMSValueEventArg_SetAction(CGXDLMSValueEventArg* p, bool value);

/**
     * @return Is byte array.
     */
extern bool CGXDLMSValueEventArg_IsByteArray(CGXDLMSValueEventArg* p);

/**
* @param value
*            Is byte array.
*/
extern void CGXDLMSValueEventArg_SetByteArray(CGXDLMSValueEventArg* p, bool value);

/**
* @return Is value max PDU size skipped.
*/
extern bool CGXDLMSValueEventArg_GetSkipMaxPduSize(CGXDLMSValueEventArg* p);

/**
 * @param value
 *            Is value max PDU size skipped.
 */
extern void CGXDLMSValueEventArg_SetSkipMaxPduSize(CGXDLMSValueEventArg* p, bool value);


/**
* @return How many rows are read to one PDU.
*/
extern unsigned short CGXDLMSValueEventArg_GetRowToPdu(CGXDLMSValueEventArg* p);

/**
* @param value
*            How many rows are read to one PDU.
*/
extern void CGXDLMSValueEventArg_SetRowToPdu(CGXDLMSValueEventArg* p, unsigned short value);

/**
* @return Rows end index.
*/
extern unsigned int CGXDLMSValueEventArg_GetRowEndIndex(CGXDLMSValueEventArg* p);

/**
* @param value
*            Rows end index.
*/
extern void CGXDLMSValueEventArg_SetRowEndIndex(CGXDLMSValueEventArg* p, unsigned int value);

/**
* @return Rows begin index.
*/
extern unsigned int CGXDLMSValueEventArg_GetRowBeginIndex(CGXDLMSValueEventArg* p);

/**
* @param value
*            Rows begin index.
*/
extern void CGXDLMSValueEventArg_SetRowBeginIndex(CGXDLMSValueEventArg* p, unsigned int value);

/**
* DLMS settings.
*/
extern CGXDLMSSettings* CGXDLMSValueEventArg_GetSettings(CGXDLMSValueEventArg* p);

/**
* @param value
*            Received invoke ID.
*/
extern void CGXDLMSValueEventArg_SetInvokeId(CGXDLMSValueEventArg* p, unsigned int value);

/**
* @return Received invoke ID.
*/
extern unsigned int CGXDLMSValueEventArg_GetInvokeId(CGXDLMSValueEventArg* p);

extern void CGXDLMSValueEventArg_d(CGXDLMSValueEventArg* p);

#endif //GXDLMSVALUEEVENTARGS_H
