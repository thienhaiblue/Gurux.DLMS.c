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

#ifndef GXDLMSPPPSETUP_H
#define GXDLMSPPPSETUP_H

#include "GXDLMSPppSetupIPCPOption.h"
#include "GXDLMSPppSetupLcpOption.h"
#include "Vector.h"
#include "GXDLMSObject.h"
#include "String.h"
/**
PPP Authentication Type
 */
typedef enum
{
    /**
     No authentication.
    */
    PPP_AUTHENTICATION_TYPE_NONE = 0,
    /**
     PAP Login
    */
    PPP_AUTHENTICATION_TYPE_PAP = 1,
    /**
     CHAP-algorithm
    */
    PPP_AUTHENTICATION_TYPE_CHAP = 2

} PPP_AUTHENTICATION_TYPE;

typedef struct // class CGXDLMSPppSetup : public CGXDLMSObject
{
	///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSPppSetup_GetAttributeCount
    GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSPppSetup_GetMethodCount
    GetValue_FuncPtr GetValue; // = CGXDLMSPppSetup_GetValue
    SetValue_FuncPtr SetValue; // = CGXDLMSPppSetup_SetValue
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
    d_FuncPtr d; // = CGXDLMSPppSetup_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSPppSetup_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSPppSetup_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSPppSetup_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    Vector m_IPCPOptions; //std::vector<CGXDLMSPppSetupIPCPOption>
    String m_PHYReference;
    Vector m_LCPOptions;//std::vector<CGXDLMSPppSetupLcpOption>
    CGXByteBuffer m_UserName;
    CGXByteBuffer m_Password;
    PPP_AUTHENTICATION_TYPE m_Authentication;

} CGXDLMSPppSetup;

//Constructor.
extern void CGXDLMSPppSetup_1(CGXDLMSPppSetup *p);

//SN Constructor.
extern void CGXDLMSPppSetup_2(CGXDLMSPppSetup *p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSPppSetup_3(CGXDLMSPppSetup *p, String ln);

extern PPP_AUTHENTICATION_TYPE CGXDLMSPppSetup_GetAuthentication(CGXDLMSPppSetup *p);
extern void CGXDLMSPppSetup_SetAuthentication(CGXDLMSPppSetup *p, PPP_AUTHENTICATION_TYPE value);

/**
PPP authentication procedure user name.
*/
extern CGXByteBuffer CGXDLMSPppSetup_GetUserName(CGXDLMSPppSetup *p);
extern void CGXDLMSPppSetup_SetUserName(CGXDLMSPppSetup *p, CGXByteBuffer value);

/**
 PPP authentication procedure password.
*/
extern CGXByteBuffer* CGXDLMSPppSetup_GetPassword(CGXDLMSPppSetup *p);
extern void CGXDLMSPppSetup_SetPassword(CGXDLMSPppSetup *p, CGXByteBuffer value);

extern String CGXDLMSPppSetup_GetPHYReference(CGXDLMSPppSetup *p);
extern void CGXDLMSPppSetup_SetPHYReference(CGXDLMSPppSetup *p, String value);

extern Vector* CGXDLMSPppSetup_GetLCPOptions(CGXDLMSPppSetup *p);//std::vector<CGXDLMSPppSetupLcpOption>&
extern Vector* CGXDLMSPppSetup_GetIPCPOptions(CGXDLMSPppSetup *p);//std::vector<CGXDLMSPppSetupIPCPOption>&

// Returns amount of attributes.
extern int CGXDLMSPppSetup_GetAttributeCount(CGXDLMSPppSetup *p);
// Returns amount of methods.
extern int CGXDLMSPppSetup_GetMethodCount(CGXDLMSPppSetup *p);

//Get attribute values of object.
extern void CGXDLMSPppSetup_GetValues(CGXDLMSPppSetup *p, Vector* values);//std::vector<std::string>&

extern void CGXDLMSPppSetup_GetAttributeIndexToRead(CGXDLMSPppSetup *p, Vector* attributes);//std::vector<int>&

extern int CGXDLMSPppSetup_GetDataType(CGXDLMSPppSetup *p, int index, DLMS_DATA_TYPE* type);

// Returns value of given attribute.
extern int CGXDLMSPppSetup_GetValue(CGXDLMSPppSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSPppSetup_SetValue(CGXDLMSPppSetup *p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

extern void CGXDLMSPppSetup_d(CGXDLMSPppSetup *p);

#endif //GXDLMSPPPSETUP_H
