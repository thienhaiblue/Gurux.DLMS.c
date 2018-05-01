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

#ifndef GXDLMSGSMDIAGNOSTIC_H
#define GXDLMSGSMDIAGNOSTIC_H

#include "GXDLMSObject.h"
#include "GXAdjacentCell.h"
#include "GXDLMSGSMCellInfo.h"
#include "String.h"
#include "Vector.h"

typedef struct CGXDLMSGSMCellInfo CGXDLMSGSMCellInfo;

typedef struct // class CGXDLMSGSMDiagnostic : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
	GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSGSMDiagnostic_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSGSMDiagnostic_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSGSMDiagnostic_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSGSMDiagnostic_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSObject_Invoke

    // (CGXDLMSObject)
    CGXAttributeCollection m_Attributes;
    CGXAttributeCollection m_MethodAttributes;
    String m_Description;
    DLMS_OBJECT_TYPE m_ObjectType;
    char m_AttributeIndex;
    unsigned short m_DataIndex;
    unsigned short m_Version;

    Map m_ReadTimes; // std::map<int, time_t> m_ReadTimes;
    unsigned short m_SN;
    unsigned char m_LN[6];

    // Override CGXDLMSObject
    d_FuncPtr d; // = CGXDLMSGSMDiagnostic_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSGSMDiagnostic_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSGSMDiagnostic_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSGSMDiagnostic_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    /**
    * Name of network operator.
    */
    String m_Operator;

    /**
    * Registration status of the modem.
    */
    DLMS_GSM_STATUS m_Status;

    /**
    * Registration status of the modem.
    */
    DLMS_GSM_CIRCUIT_SWITCH_STATUS m_CircuitSwitchStatus;

    /**
    * Registration status of the modem.
    */
    DLMS_GSM_PACKET_SWITCH_STATUS m_PacketSwitchStatus;

    /**
    * Registration status of the modem.
    */
    CGXDLMSGSMCellInfo m_CellInfo;

    /**
    * Adjacent cells.
    */
    Vector m_AdjacentCells; // std::vector<GXAdjacentCell*>

    /**
    * Date and time when the data have been last captured.
    */
    CGXDateTime m_CaptureTime;

} CGXDLMSGSMDiagnostic;

#define CGXDLMSGSMDiagnostic_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSGSMDiagnostic_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

   //public
   //Constructor.
   extern void CGXDLMSGSMDiagnostic_1(CGXDLMSGSMDiagnostic *p);

   //SN Constructor.
   extern void CGXDLMSGSMDiagnostic_2(CGXDLMSGSMDiagnostic *p, String ln, unsigned short sn);

   //LN Constructor.
   extern void CGXDLMSGSMDiagnostic_3(CGXDLMSGSMDiagnostic *p, String ln);

   //Destructor.
   extern void CGXDLMSGSMDiagnostic_d(CGXDLMSGSMDiagnostic *p);

   /**
   * @return Name of network operator.
   */
   extern String CGXDLMSGSMDiagnostic_GetOperator(CGXDLMSGSMDiagnostic *p);

   /**
   * @param value
   *            Name of network operator.
   */
   extern void CGXDLMSGSMDiagnostic_SetOperator(CGXDLMSGSMDiagnostic *p, String value);

   /**
   * @return Registration status of the modem.
   */
   extern DLMS_GSM_STATUS CGXDLMSGSMDiagnostic_GetStatus(CGXDLMSGSMDiagnostic *p);

   /**
   * @param value
   *            Registration status of the modem.
   */
   extern void CGXDLMSGSMDiagnostic_SetStatus(CGXDLMSGSMDiagnostic *p, DLMS_GSM_STATUS value);

   /**
   * @return Registration status of the modem.
   */
   extern DLMS_GSM_CIRCUIT_SWITCH_STATUS CGXDLMSGSMDiagnostic_GetCircuitSwitchStatus(CGXDLMSGSMDiagnostic *p);

   /**
   * @param value
   *            Registration status of the modem.
   */
   extern void CGXDLMSGSMDiagnostic_SetCircuitSwitchStatus(CGXDLMSGSMDiagnostic *p, DLMS_GSM_CIRCUIT_SWITCH_STATUS value);

   /**
   * @return Registration status of the modem.
   */
   extern DLMS_GSM_PACKET_SWITCH_STATUS CGXDLMSGSMDiagnostic_GetPacketSwitchStatus(CGXDLMSGSMDiagnostic *p);

   /**
   * @param value
   *            Registration status of the modem.
   */
   extern void CGXDLMSGSMDiagnostic_SetPacketSwitchStatus(CGXDLMSGSMDiagnostic *p, DLMS_GSM_PACKET_SWITCH_STATUS value);

   extern CGXDLMSGSMCellInfo* CGXDLMSGSMDiagnostic_GetCellInfo(CGXDLMSGSMDiagnostic *p);

   /**
   * @return Adjacent cells.
   */
   extern Vector* CGXDLMSGSMDiagnostic_GetAdjacentCells(CGXDLMSGSMDiagnostic *p);//std::vector<GXAdjacentCell*>&

   /**
   * @return Date and time when the data have been last captured.
   */
   extern CGXDateTime CGXDLMSGSMDiagnostic_GetCaptureTime(CGXDLMSGSMDiagnostic *p);

   /**
   * @param value
   *            Date and time when the data have been last captured.
   */
   extern void CGXDLMSGSMDiagnostic_SetCaptureTime(CGXDLMSGSMDiagnostic *p, CGXDateTime* value);

   // Returns amount of attributes.
   extern int CGXDLMSGSMDiagnostic_GetAttributeCount(CGXDLMSGSMDiagnostic *p);

   // Returns amount of methods.
   extern int CGXDLMSGSMDiagnostic_GetMethodCount(CGXDLMSGSMDiagnostic *p);

   //Get attribute values of object.
   extern void CGXDLMSGSMDiagnostic_GetValues(CGXDLMSGSMDiagnostic *p, Vector* values);//std::vector<std::string>&

   extern void CGXDLMSGSMDiagnostic_GetAttributeIndexToRead(CGXDLMSGSMDiagnostic *p, Vector* attributes);//std::vector<int>&

   extern int CGXDLMSGSMDiagnostic_GetDataType(CGXDLMSGSMDiagnostic *p, int index, DLMS_DATA_TYPE* type);

   // Returns value of given attribute.
   extern int CGXDLMSGSMDiagnostic_GetValue(CGXDLMSGSMDiagnostic *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

   // Set value of given attribute.
   extern int CGXDLMSGSMDiagnostic_SetValue(CGXDLMSGSMDiagnostic *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSGSMDIAGNOSTIC_H
