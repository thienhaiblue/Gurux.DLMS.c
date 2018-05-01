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

#ifndef GXDLMSLIMITER_H
#define GXDLMSLIMITER_H

#include "GXDLMSObject.h"
#include "GXDLMSEmergencyProfile.h"
#include "GXDLMSActionItem.h"

#include "String.h"
#include "Vector.h"

typedef struct //class CGXDLMSLimiter : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSLimiter_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSLimiter_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSLimiter_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSLimiter_SetValue
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
    d_FuncPtr d; // = CGXDLMSLimiter_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSLimiter_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSLimiter_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSLimiter_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    CGXDLMSObject* m_MonitoredValue;
    int m_MonitoredAttributeIndex;
    CGXDLMSVariant m_ThresholdActive;
    CGXDLMSVariant m_ThresholdNormal;
    CGXDLMSVariant m_ThresholdEmergency;
    long m_MinOverThresholdDuration;
    long m_MinUnderThresholdDuration;
    CGXDLMSEmergencyProfile m_EmergencyProfile;
    Vector m_EmergencyProfileGroupIDs; // std::vector<int>
    bool m_EmergencyProfileActive;
    CGXDLMSActionItem m_ActionOverThreshold;
    CGXDLMSActionItem m_ActionUnderThreshold;

} CGXDLMSLimiter;

#define CGXDLMSLimiter_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSLimiter_CanRead(p, index)              CGXDLMSObject_CanRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSLimiter_1(CGXDLMSLimiter* p);

//SN Constructor.
extern void CGXDLMSLimiter_2(CGXDLMSLimiter* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSLimiter_3(CGXDLMSLimiter* p, String ln);

/**
 Defines an attribute of an object to be monitored.
*/
extern CGXDLMSObject* CGXDLMSLimiter_GetMonitoredValue(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetMonitoredValue(CGXDLMSLimiter* p, CGXDLMSObject* value);

/**
 Provides the active threshold value to which the attribute monitored is compared.
*/
extern CGXDLMSVariant* CGXDLMSLimiter_GetThresholdActive(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetThresholdActive(CGXDLMSLimiter* p, CGXDLMSVariant value);

/**
 Provides the threshold value to which the attribute monitored
    is compared when in normal operation.
*/
extern CGXDLMSVariant* CGXDLMSLimiter_GetThresholdNormal(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetThresholdNormal(CGXDLMSLimiter* p, CGXDLMSVariant value);

/**
 Provides the threshold value to which the attribute monitored
    is compared when an emergency profile is active.
*/
extern CGXDLMSVariant* CGXDLMSLimiter_GetThresholdEmergency(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetThresholdEmergency(CGXDLMSLimiter* p, CGXDLMSVariant value);

/**
 Defines minimal over threshold duration in seconds required
    to execute the over threshold action.
*/
extern long CGXDLMSLimiter_GetMinOverThresholdDuration(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetMinOverThresholdDuration(CGXDLMSLimiter* p, long value);

/**
 Defines minimal under threshold duration in seconds required to
    execute the under threshold action.
*/
extern long CGXDLMSLimiter_GetMinUnderThresholdDuration(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetMinUnderThresholdDuration(CGXDLMSLimiter* p, long value);

extern CGXDLMSEmergencyProfile* CGXDLMSLimiter_GetEmergencyProfile(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetEmergencyProfile(CGXDLMSLimiter* p, CGXDLMSEmergencyProfile value);

extern Vector* CGXDLMSLimiter_GetEmergencyProfileGroupIDs(CGXDLMSLimiter* p); //std::vector<int>&
extern void CGXDLMSLimiter_SetEmergencyProfileGroupIDs(CGXDLMSLimiter* p, Vector value); //std::vector<int>

/**
 Is Emergency Profile active.
*/
extern bool CGXDLMSLimiter_GetEmergencyProfileActive(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetEmergencyProfileActive(CGXDLMSLimiter* p, bool value);

/**
 Defines the scripts to be executed when the monitored value
    crosses the threshold for minimal duration time.
*/
extern CGXDLMSActionItem* CGXDLMSLimiter_GetActionOverThreshold(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetActionOverThreshold(CGXDLMSLimiter* p, CGXDLMSActionItem value);

/**
 Defines the scripts to be executed when the monitored value
    crosses the threshold for minimal duration time.
*/
extern CGXDLMSActionItem* CGXDLMSLimiter_GetActionUnderThreshold(CGXDLMSLimiter* p);
extern void CGXDLMSLimiter_SetActionUnderThreshold(CGXDLMSLimiter* p, CGXDLMSActionItem value);

// Returns amount of attributes.
extern int CGXDLMSLimiter_GetAttributeCount(CGXDLMSLimiter* p);

// Returns amount of methods.
extern int CGXDLMSLimiter_GetMethodCount(CGXDLMSLimiter* p);

//Get attribute values of object.
extern void CGXDLMSLimiter_GetValues(CGXDLMSLimiter* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSLimiter_GetAttributeIndexToRead(CGXDLMSLimiter* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSLimiter_GetDataType(CGXDLMSLimiter* p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSLimiter_GetValue(CGXDLMSLimiter* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSLimiter_SetValue(CGXDLMSLimiter* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSLimiter_d(CGXDLMSLimiter* p);

#endif //GXDLMSLIMITER_H
