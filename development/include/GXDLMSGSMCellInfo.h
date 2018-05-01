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

#ifndef GXDLMSGSMCELLINFO_H
#define GXDLMSGSMCELLINFO_H

#include "String.h"

typedef struct CGXDLMSGSMCellInfo
{
    /**
    * Four byte cell ID.
    */
    unsigned int m_CellId;

    /**
    * Two byte location area code (LAC).
    */
    unsigned short m_LocationId;
    /**
    * Signal quality.
    */
    unsigned char m_SignalQuality;
    /**
    * Bit Error Rate.
    */
    unsigned char m_Ber;

} CGXDLMSGSMCellInfo;
/**
* @return Two byte cell ID.
*/
extern unsigned int CGXDLMSGSMCellInfo_GetCellId(CGXDLMSGSMCellInfo *p);

/**
* @param value
*            Four byte cell ID.
*/
extern void CGXDLMSGSMCellInfo_SetCellId(CGXDLMSGSMCellInfo *p, unsigned int value);

/**
* @return Two byte location area code (LAC).
*/
extern unsigned short CGXDLMSGSMCellInfo_GetLocationId(CGXDLMSGSMCellInfo *p);

/**
* @param value
*            Two byte location area code (LAC).
*/
extern void CGXDLMSGSMCellInfo_SetLocationId(CGXDLMSGSMCellInfo *p, unsigned short value);

/**
* @return Signal quality.
*/
extern unsigned char CGXDLMSGSMCellInfo_GetSignalQuality(CGXDLMSGSMCellInfo *p);

/**
* @param value
*            Signal quality.
*/
extern void CGXDLMSGSMCellInfo_SetSignalQuality(CGXDLMSGSMCellInfo *p, unsigned char value);

/**
* @return Bit Error Rate.
*/
extern unsigned char CGXDLMSGSMCellInfo_GetBer(CGXDLMSGSMCellInfo *p);

/**
* @param value
*            Bit Error Rate.
*/
extern void CGXDLMSGSMCellInfo_SetBer(CGXDLMSGSMCellInfo *p, unsigned char value);

extern String CGXDLMSGSMCellInfo_ToString(CGXDLMSGSMCellInfo *p);

#endif //GXDLMSGSMCELLINFO_H
