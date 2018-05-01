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
#ifndef GXDLMSQUALITYOFSERVICE_H
#define GXDLMSQUALITYOFSERVICE_H

#include "enums.h"
#include "String.h"

typedef struct
{
    int m_Precedence;
    int m_Delay;
    int m_Reliability;
    int m_PeakThroughput;
    int m_MeanThroughput;

} CGXDLMSQualityOfService;

extern int CGXDLMSQualityOfService_GetPrecedence(CGXDLMSQualityOfService *p);
extern void CGXDLMSQualityOfService_SetPrecedence(CGXDLMSQualityOfService *p, int value);

extern int CGXDLMSQualityOfService_GetDelay(CGXDLMSQualityOfService *p);
extern void CGXDLMSQualityOfService_SetDelay(CGXDLMSQualityOfService *p, int value);

extern int CGXDLMSQualityOfService_GetReliability(CGXDLMSQualityOfService *p);
extern void CGXDLMSQualityOfService_SetReliability(CGXDLMSQualityOfService *p, int value);

extern int CGXDLMSQualityOfService_GetPeakThroughput(CGXDLMSQualityOfService *p);
extern void CGXDLMSQualityOfService_SetPeakThroughput(CGXDLMSQualityOfService *p, int value);

extern int CGXDLMSQualityOfService_GetMeanThroughput(CGXDLMSQualityOfService *p);
extern void CGXDLMSQualityOfService_SetMeanThroughput(CGXDLMSQualityOfService *p, int value);

extern String CGXDLMSQualityOfService_ToString(CGXDLMSQualityOfService *p);

#endif //GXDLMSQUALITYOFSERVICE_H
