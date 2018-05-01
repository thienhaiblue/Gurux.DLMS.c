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

#ifndef GXDLMSNOTIFY_H
#define GXDLMSNOTIFY_H

#include "Vector.h"
#include "GXReplyData.h"
#include "GXDLMSSettings.h"
#include "GXDLMSLimits.h"
#include "GXDLMSPushSetup.h"
#include "GXDLMS.h"

#include "GXDLMSClient.h"
#include "GXDLMSObjectFactory.h"

typedef struct CGXDLMSNotify
{
	CGXDLMSSettings m_Settings;
} CGXDLMSNotify;

/**
  * @param value
  *            Cipher interface that is used to cipher PDU.
  */
extern void CGXDLMSNotify_SetCipher(CGXDLMSNotify *p, CGXCipher* value);

 /**
 * @return Get m_Settings.
 */
extern CGXDLMSSettings* CGXDLMSNotify_GetSettings(CGXDLMSNotify *p);

 /**
      * Constructor.
      *
      * @param useLogicalNameReferencing
      *            Is Logical Name referencing used.
      * @param clientAddress
      *            Server address.
      * @param serverAddress
      *            Client address.
      * @param interfaceType
      *            Object type.
      */
extern void CGXDLMSNotify_(CGXDLMSNotify *p,
                           bool useLogicalNameReferencing,
                           int clientAddress,
                           int serverAddress,
                           DLMS_INTERFACE_TYPE interfaceType);

 /**
  * @return Get list of meter's objects.
  */
extern CGXDLMSObjectCollection* CGXDLMSNotify_GetObjects(CGXDLMSNotify *p);

 /**
  * @return Information from the connection size that server can handle.
  */
extern CGXDLMSLimits* CGXDLMSNotify_GetLimits(CGXDLMSNotify *p);

 /**
  * Retrieves the maximum size of received PDU. PDU size tells maximum size
  * of PDU packet. Value can be from 0 to 0xFFFF. By default the value is
  * 0xFFFF.
  *
  * @see GXDLMSClient#getClientAddress
  * @see GXDLMSClient#getServerAddress
  * @see GXDLMSClient#getDLMSVersion
  * @see GXDLMSClient#getUseLogicalNameReferencing
  * @return Maximum size of received PDU.
  */
extern int CGXDLMSNotify_GetMaxPduSize(CGXDLMSNotify *p);

 /**
  * @param value
  *            Maximum size of received PDU.
  */
extern void CGXDLMSNotify_SetMaxReceivePDUSize(CGXDLMSNotify *p, int value);

 /**
  * Determines, whether Logical, or Short name, referencing is used.
  * Referencing depends on the device to communicate with. Normally, a device
  * supports only either Logical or Short name referencing. The referencing
  * is defined by the device manufacturer. If the referencing is wrong, the
  * SNMR message will fail.
  *
  * @return Is Logical Name referencing used.
  */
extern bool CGXDLMSNotify_GetUseLogicalNameReferencing(CGXDLMSNotify *p);

 /**
  * @param value
  *            Is Logical Name referencing used.
  */
extern void CGXDLMSNotify_SetUseLogicalNameReferencing(CGXDLMSNotify *p, bool value);

 /**
  * @return Used Priority.
  */
extern DLMS_PRIORITY CGXDLMSNotify_GetPriority(CGXDLMSNotify *p);

 /**
  * @param value
  *            Used Priority.
  */
extern void CGXDLMSNotify_SetPriority(CGXDLMSNotify *p, DLMS_PRIORITY value);

 /**
  * @return Used service class.
  */
extern DLMS_SERVICE_CLASS CGXDLMSNotify_GetServiceClass(CGXDLMSNotify *p);

 /**
  * @param value
  *            Used service class.
  */
extern void CGXDLMSNotify_SetServiceClass(CGXDLMSNotify *p, DLMS_SERVICE_CLASS value);

 /**
  * @return Invoke ID.
  */
extern unsigned char CGXDLMSNotify_GetInvokeID(CGXDLMSNotify *p);

 /**
  * @param value
  *            Invoke ID.
  */
extern void CGXDLMSNotify_SetInvokeID(CGXDLMSNotify *p, unsigned char value);

 /**
  * Removes the HDLC frame from the packet, and returns COSEM data only.
  *
  * @param reply
  *            The received data from the device.
  * @param data
  *            Information from the received data.
  * @return Is frame complete.
  */
extern int CGXDLMSNotify_GetData(CGXDLMSNotify *p, CGXByteBuffer* reply, CGXReplyData* data);

 /**
  * Add value of COSEM object to byte buffer. AddData method can be used with
  * GetDataNotificationMessage -method. DLMS specification do not specify the
  * structure of Data-Notification body. So each manufacture can sent
  * different data.
  *
  * @param obj
  *            COSEM object.
  * @param index
  *            Attribute index.
  * @param buff
  *            Byte buffer.
  */
extern int CGXDLMSNotify_AddData(
	 CGXDLMSNotify *p,
     CGXDLMSObject* obj,
     unsigned char index,
     CGXByteBuffer* buff);

 /**
  * Generates data notification message.
  *
  * @param date
  *            Date time. Set to null or Date(0) if not used
  * @param data
  *            Notification body.
  * @return Generated data notification message(s).
  */
extern int CGXDLMSNotify_GenerateDataNotificationMessages_1(
	 CGXDLMSNotify *p,
     struct tm* date,
     CGXByteBuffer* data,
     Vector* reply); // std::vector<CGXByteBuffer>&

 /**
  * Generates data notification message.
  *
  * @param date
  *            Date time. Set To Min or Max if not added.
  * @param objects
  *            List of objects and attribute indexes to notify.
  * @return Generated data notification message(s).
  */
extern int CGXDLMSNotify_GenerateDataNotificationMessages_2(
	 CGXDLMSNotify *p,
     struct tm* date,
     Vector* objects, // std::vector<std::pair<CGXDLMSObject*, unsigned char> >& objects
     Vector* reply);  // std::vector<CGXByteBuffer>& reply

 /**
  * Generates push setup message.
  *
  * @param date
  *            Date time. Set to null or Date(0) if not used.
  * @param push
  *            Target Push object.
  * @return Generated data notification message(s).
  */
extern int CGXDLMSNotify_GeneratePushSetupMessages(
	 CGXDLMSNotify *p,
     struct tm* date,
     CGXDLMSPushSetup* push,
     Vector* reply); // std::vector<CGXByteBuffer>&

 /**
 * Returns collection of push objects. If this method is used Push object
 * must be set for first object on push object list.
 *
 * @param data
 *            Received value.
 * @return Array of objects and called indexes.
 */
extern int CGXDLMSNotify_ParsePush(
	 CGXDLMSNotify *p,
     Vector* data,   // std::vector<CGXDLMSVariant>& data
     Vector* items); // std::vector<std::pair<CGXDLMSObject*, unsigned char> >& items

extern void CGXDLMSNotify_d(CGXDLMSNotify *p);

#endif //GXDLMSNOTIFY_H
