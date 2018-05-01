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

#ifndef GXDLMSCONTEXTTYPE_H
#define GXDLMSCONTEXTTYPE_H

#include "String.h"
#include "GXBytebuffer.h"

typedef struct
{
    DLMS_CONFORMANCE m_Conformance;
    int m_MaxReceivePduSize;
    int m_MaxSendPpuSize;
    int m_DlmsVersionNumber;
    int m_QualityOfService;
    CGXByteBuffer m_CypheringInfo;
}CGXDLMSContextType;

/*Constructor.*/
extern void CGXDLMSContextType_(CGXDLMSContextType *p);
/**
* Server will tell what functionality is available for the client.
* @return Available functionality.
*/
extern DLMS_CONFORMANCE CGXDLMSContextType_GetConformance(CGXDLMSContextType *p);

/**
* Server will tell what functionality is available for the client.
*
* @param value
*            Available functionality.
*/
extern void CGXDLMSContextType_SetConformance(CGXDLMSContextType *p, DLMS_CONFORMANCE value);

extern int CGXDLMSContextType_GetMaxPduSize(CGXDLMSContextType *p);
extern void CGXDLMSContextType_SetMaxReceivePduSize(CGXDLMSContextType *p, int value);

extern int CGXDLMSContextType_GetMaxSendPpuSize(CGXDLMSContextType *p);
extern void CGXDLMSContextType_SetMaxSendPpuSize(CGXDLMSContextType *p, int value);

extern int CGXDLMSContextType_GetDlmsVersionNumber(CGXDLMSContextType *p);
extern void CGXDLMSContextType_SetDlmsVersionNumber(CGXDLMSContextType *p, int value);

extern int CGXDLMSContextType_GetQualityOfService(CGXDLMSContextType *p);
extern void CGXDLMSContextType_SetQualityOfService(CGXDLMSContextType *p, int value);

extern CGXByteBuffer* CGXDLMSContextType_GetCypheringInfo(CGXDLMSContextType *p);
extern void CGXDLMSContextType_SetCypheringInfo(CGXDLMSContextType *p, CGXByteBuffer* value);

extern String CGXDLMSContextType_ToString(CGXDLMSContextType *p);

extern void CGXDLMSContextType_d(CGXDLMSContextType *p);

#endif //GXDLMSCONTEXTTYPE_H
