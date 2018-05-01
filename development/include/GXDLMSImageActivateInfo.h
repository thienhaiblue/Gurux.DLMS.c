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

#ifndef GXDLMSIMAGEACTIVATEINFO_H
#define GXDLMSIMAGEACTIVATEINFO_H

#include "String.h"

typedef struct CGXDLMSImageActivateInfo
{
    long m_Size;
    String m_Identification;
    String m_Signature;
} CGXDLMSImageActivateInfo;

/**
 * Constructor.
 */
extern void CGXDLMSImageActivateInfo_1(CGXDLMSImageActivateInfo *p);

/**
 * Constructor.
 */
extern void CGXDLMSImageActivateInfo_2(CGXDLMSImageActivateInfo *p, long size, String identification, String signature);

/**
 *  Image_size is the size of the Image(s) to be activated.
 *  Expressed in octets;
*/
extern long CGXDLMSImageActivateInfo_GetSize(CGXDLMSImageActivateInfo *p);
extern void CGXDLMSImageActivateInfo_SetSize(CGXDLMSImageActivateInfo *p, long value);

/**
 * Image identification is the identification of the Image(s)
 * to be activated, and may contain information like
 * manufacturer, device type, version information, etc.
*/
extern String CGXDLMSImageActivateInfo_GetIdentification(CGXDLMSImageActivateInfo *p);
extern void CGXDLMSImageActivateInfo_SetIdentification(CGXDLMSImageActivateInfo *p, String value);

/**
 * Image signature is the signature of the Image(s) to be activated.
*/
extern String CGXDLMSImageActivateInfo_GetSignature(CGXDLMSImageActivateInfo *p);
extern void CGXDLMSImageActivateInfo_SetSignature(CGXDLMSImageActivateInfo *p, String value);

extern String CGXDLMSImageActivateInfo_ToString(CGXDLMSImageActivateInfo *p);

extern void CGXDLMSImageActivateInfo_d(CGXDLMSImageActivateInfo *p);

#endif //GXDLMSIMAGEACTIVATEINFO_H
