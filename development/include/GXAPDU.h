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

#ifndef GXAPDU_H
#define GXAPDU_H

#include "enums.h"
#include "errorcodes.h"
#include "GXHelpers.h"
#include "GXDLMSSettings.h"

extern const unsigned char LOGICAL_NAME_OBJECT_ID[7]; // = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01 };
extern const unsigned char SHORT_NAME_OBJECT_ID[7]; // = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x02 };
extern const unsigned char LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING[7]; // = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x03 };
extern const unsigned char SHORT_NAME_OBJECT_ID_WITH_CIPHERING[7]; // = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x04 };

/////////////////////////////////////////////////////////////////////////////
// The services to access the attributes and methods of COSEM objects are
// determined on DLMS/COSEM Application layer. The services are carried by
// Application Protocol Data Units (APDUs).
// <p />
// In DLMS/COSEM the meter is primarily a server, and the controlling system is
// a client. Also unsolicited (received without a request) messages are
// available.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Constructor.
/////////////////////////////////////////////////////////////////////////////
//static void CGXAPDU_();
/**
     * Generates Aarq.
     */
    extern  int CGXAPDU_GenerateAarq(
        CGXDLMSSettings* settings,
        CGXCipher* cipher,
        CGXByteBuffer* encryptedData,
        CGXByteBuffer* data);

    /**
    * Generate user information.
    *
    * @param settings
    *            DLMS settings.
    * @param cipher
    * @param data
    *            Generated user information.
    */
    extern  int CGXAPDU_GenerateUserInformation(
        CGXDLMSSettings* settings,
        CGXCipher* cipher,
        CGXByteBuffer* encryptedData,
        CGXByteBuffer* data);

    /**
     * Parse APDU.
     */
    extern  int CGXAPDU_ParsePDU(CGXDLMSSettings* settings,
        CGXCipher* cipher,
        CGXByteBuffer* buff,
        DLMS_ASSOCIATION_RESULT *result,
        DLMS_SOURCE_DIAGNOSTIC* diagnostic);

    /**
     * Server generates AARE message.
     */
    extern  int CGXAPDU_GenerateAARE(
        CGXDLMSSettings* settings,
        CGXByteBuffer* data,
        DLMS_ASSOCIATION_RESULT result,
        DLMS_SOURCE_DIAGNOSTIC diagnostic,
        CGXCipher* cipher,
        CGXByteBuffer *errorData,
        CGXByteBuffer *encryptedData);

#endif //GXAPDU_H
