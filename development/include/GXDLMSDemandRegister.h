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

#ifndef GXDLMSDEMANDREGISTER_H
#define GXDLMSDEMANDREGISTER_H

#include "GXDLMSObject.h"

#include "Vector.h"
#include "String.h"

typedef struct//class CGXDLMSDemandRegister : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // =CGXDLMSDemandRegister_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSDemandRegister_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSDemandRegister_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSDemandRegister_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSDemandRegister_Invoke

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
    d_FuncPtr d; // = CGXDLMSDemandRegister_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSDemandRegister_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSDemandRegister_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSDemandRegister_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    CGXDLMSVariant m_CurrentAvarageValue;
    CGXDLMSVariant m_LastAvarageValue;
    signed char m_Scaler;
    unsigned char m_Unit;
    CGXDLMSVariant m_Status;
    CGXDateTime m_CaptureTime;
    CGXDateTime m_StartTimeCurrent;
    int m_NumberOfPeriods;
    unsigned long m_Period;
} CGXDLMSDemandRegister;

#define CGXDLMSDemandRegister_CanRead(p, index)       CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))
#define CGXDLMSDemandRegister_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))

//protected:
extern bool CGXDLMSDemandRegister_IsRead(CGXDLMSDemandRegister* p, int index);

//public:
/**
 Constructor.
*/
extern void CGXDLMSDemandRegister_1(CGXDLMSDemandRegister* p);

/**
 Constructor.

    @param ln Logical Name of the object.
*/
extern void CGXDLMSDemandRegister_2(CGXDLMSDemandRegister* p, String ln);

/**
 Constructor.

    @param ln Logical Name of the object.
    @param sn Short Name of the object.
*/
extern void CGXDLMSDemandRegister_3(CGXDLMSDemandRegister* p, String ln, unsigned short sn);

/**
 Current avarage value of COSEM Data object.
*/
extern CGXDLMSVariant CGXDLMSDemandRegister_GetCurrentAvarageValue(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetCurrentAvarageValue(CGXDLMSDemandRegister* p, CGXDLMSVariant value);

/**
 Last avarage value of COSEM Data object.
*/
extern CGXDLMSVariant CGXDLMSDemandRegister_GetLastAvarageValue(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetLastAvarageValue(CGXDLMSDemandRegister* p, CGXDLMSVariant value);

/**
 Scaler of COSEM Register object.
*/
extern double CGXDLMSDemandRegister_GetScaler(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetScaler(CGXDLMSDemandRegister* p, double value);

// Unit of COSEM Register object.
extern int CGXDLMSDemandRegister_GetUnit(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetUnit(CGXDLMSDemandRegister* p, unsigned char value);

/**
 Scaler of COSEM Register object.
*/
extern CGXDLMSVariant CGXDLMSDemandRegister_GetStatus(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetStatus(CGXDLMSDemandRegister* p, CGXDLMSVariant value);

/**
 Capture time of COSEM Register object.
*/
extern CGXDateTime CGXDLMSDemandRegister_GetCaptureTime(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetCaptureTime(CGXDLMSDemandRegister* p, CGXDateTime value);

/**
 Current start time of COSEM Register object.
*/
extern CGXDateTime CGXDLMSDemandRegister_GetStartTimeCurrent(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetStartTimeCurrent(CGXDLMSDemandRegister* p, CGXDateTime value);

extern unsigned long CGXDLMSDemandRegister_GetPeriod(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetPeriod(CGXDLMSDemandRegister* p, unsigned long value);

extern int CGXDLMSDemandRegister_GetNumberOfPeriods(CGXDLMSDemandRegister* p);
extern void CGXDLMSDemandRegister_SetNumberOfPeriods(CGXDLMSDemandRegister* p, int value);

/*
    * Reset value.
    */
extern void CGXDLMSDemandRegister_Reset(CGXDLMSDemandRegister* p);

/*
    * Next period.
    */
extern void CGXDLMSDemandRegister_NextPeriod(CGXDLMSDemandRegister* p);

//Get attribute values of object.
extern void CGXDLMSDemandRegister_GetValues(CGXDLMSDemandRegister* p, Vector* values); //std::vector<std::string>&

void CGXDLMSDemandRegister_GetAttributeIndexToRead(CGXDLMSDemandRegister* p, Vector* attributes); //std::vector<int>&

// Returns amount of attributes.
extern int CGXDLMSDemandRegister_GetAttributeCount(CGXDLMSDemandRegister* p);

// Returns amount of methods.
extern int CGXDLMSDemandRegister_GetMethodCount(CGXDLMSDemandRegister* p);

extern int CGXDLMSDemandRegister_Invoke(CGXDLMSDemandRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern int CGXDLMSDemandRegister_GetDataType(CGXDLMSDemandRegister* p, int index, DLMS_DATA_TYPE* type);

extern int CGXDLMSDemandRegister_GetValue(CGXDLMSDemandRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern int CGXDLMSDemandRegister_SetValue(CGXDLMSDemandRegister* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSDemandRegister_d(CGXDLMSDemandRegister* p);

#endif //GXDLMSDEMANDREGISTER_H
