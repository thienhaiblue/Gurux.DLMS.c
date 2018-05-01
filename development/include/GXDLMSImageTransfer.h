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

#ifndef GXDLMSIMAGETRANSFER_H
#define GXDLMSIMAGETRANSFER_H

#include "GXDLMSObject.h"
#include "GXDLMSImageActivateInfo.h"

#include "Vector.h"
#include "String.h"

typedef struct //class CGXDLMSImageTransfer : public CGXDLMSObject
{
    ///////////////////////////////////////////////////////////////////////////
    // Override IGXDLMSBase
    GetAttributeCount_FuncPtr GetAttributeCount; // = CGXDLMSImageTransfer_GetAttributeCount
	GetMethodCount_FuncPtr GetMethodCount; // = CGXDLMSImageTransfer_GetMethodCount
	GetValue_FuncPtr GetValue; // = CGXDLMSImageTransfer_GetValue
	SetValue_FuncPtr SetValue; // = CGXDLMSImageTransfer_SetValue
	Invoke_FuncPtr Invoke; // = CGXDLMSImageTransfer_Invoke

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
    d_FuncPtr d; // = CGXDLMSImageTransfer_d
    SetDataType_FuncPtr SetDataType; // = CGXDLMSObject_SetDataType
    GetDataType_FuncPtr GetDataType; // = CGXDLMSImageTransfer_GetDataType
    GetUIDataType_FuncPtr GetUIDataType; // = CGXDLMSObject_GetUIDataType
    GetValues_FuncPtr GetValues; // = CGXDLMSImageTransfer_GetValues
    GetAttributeIndexToRead_FuncPtr GetAttributeIndexToRead; // = CGXDLMSImageTransfer_GetAttributeIndexToRead
    ///////////////////////////////////////////////////////////////////////////

    long m_ImageBlockSize;
    String m_ImageTransferredBlocksStatus;
    long m_ImageFirstNotTransferredBlockNumber;
    bool m_ImageTransferEnabled;
    DLMS_IMAGE_TRANSFER_STATUS m_ImageTransferStatus;
    Vector m_ImageActivateInfo; //std::vector<CGXDLMSImageActivateInfo*>

} CGXDLMSImageTransfer;

#define CGXDLMSImageTransfer_GetLogicalName_2(p, ln) CGXDLMSObject_GetLogicalName_2((CGXDLMSObject*) (p), (ln))
#define CGXDLMSImageTransfer_IsRead(p, index)        CGXDLMSObject_IsRead((CGXDLMSObject*) (p), (index))

//Constructor.
extern void CGXDLMSImageTransfer_1(CGXDLMSImageTransfer* p);

//SN Constructor.
extern void CGXDLMSImageTransfer_2(CGXDLMSImageTransfer* p, String ln, unsigned short sn);

//LN Constructor.
extern void CGXDLMSImageTransfer_3(CGXDLMSImageTransfer* p, String ln);

extern void CGXDLMSImageTransfer_d(CGXDLMSImageTransfer* p);

/**
 Holds the ImageBlockSize, expressed in octets,
    * which can be handled by the server
*/
extern long CGXDLMSImageTransfer_GetImageBlockSize(CGXDLMSImageTransfer* p);
extern void CGXDLMSImageTransfer_SetImageBlockSize(CGXDLMSImageTransfer* p, long value);

/**
 * Provides information about the transfer status of each
 * ImageBlock. Each bit in the bit-std::string provides information about
 * one individual ImageBlock.
*/
extern String* CGXDLMSImageTransfer_GetImageTransferredBlocksStatus(CGXDLMSImageTransfer* p);
extern void CGXDLMSImageTransfer_SetImageTransferredBlocksStatus(CGXDLMSImageTransfer* p, String value);

/**
 Provides the ImageBlockNumber of the first ImageBlock not transferred.
    * NOTE If the Image is complete, the value returned should be above the
    * number of blocks calculated from the Image size and the ImageBlockSize
*/
extern long CGXDLMSImageTransfer_GetImageFirstNotTransferredBlockNumber(CGXDLMSImageTransfer* p);
extern void CGXDLMSImageTransfer_SetImageFirstNotTransferredBlockNumber(CGXDLMSImageTransfer* p, long value);

/**
 * Controls enabling the Image transfer process. The method can
 * be invoked successfully only if the value of this attribute is true.
 */
extern bool CGXDLMSImageTransfer_GetImageTransferEnabled(CGXDLMSImageTransfer* p);
extern void CGXDLMSImageTransfer_SetImageTransferEnabled(CGXDLMSImageTransfer* p, bool value);

/**
 * Holds the status of the Image transfer process.
 */
extern DLMS_IMAGE_TRANSFER_STATUS CGXDLMSImageTransfer_GetImageTransferStatus(CGXDLMSImageTransfer* p);
extern void CGXDLMSImageTransfer_SetImageTransferStatus(CGXDLMSImageTransfer* p, DLMS_IMAGE_TRANSFER_STATUS value);

extern Vector* CGXDLMSImageTransfer_GetImageActivateInfo(CGXDLMSImageTransfer* p); // std::vector<CGXDLMSImageActivateInfo*>&

// Returns amount of attributes.
extern int CGXDLMSImageTransfer_GetAttributeCount(CGXDLMSImageTransfer* p);

// Returns amount of methods.
extern int CGXDLMSImageTransfer_GetMethodCount(CGXDLMSImageTransfer* p);

//Get attribute values of object.
extern void CGXDLMSImageTransfer_GetValues(CGXDLMSImageTransfer* p, Vector* values); //std::vector<std::string>&

extern void CGXDLMSImageTransfer_GetAttributeIndexToRead(CGXDLMSImageTransfer* p, Vector* attributes); //std::vector<int>& 

extern int CGXDLMSImageTransfer_GetDataType(CGXDLMSImageTransfer* p, int index, DLMS_DATA_TYPE* type);

extern int CGXDLMSImageTransfer_Invoke(CGXDLMSImageTransfer* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Returns value of given attribute.
extern int CGXDLMSImageTransfer_GetValue(CGXDLMSImageTransfer* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

// Set value of given attribute.
extern int CGXDLMSImageTransfer_SetValue(CGXDLMSImageTransfer* p, CGXDLMSSettings* settings, CGXDLMSValueEventArg* e);

#endif //GXDLMSIMAGETRANSFER_H
