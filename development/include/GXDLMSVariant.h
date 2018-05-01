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

#ifndef GXDLMSVARIANT_H
#define GXDLMSVARIANT_H

#include "GXDate.h"
#include "GXTime.h"
#include "GXDateTime.h"
#include "GXBytebuffer.h"
#include "String.h"
#include "WString.h"
#include "Vector.h"

#define __tagVARIANT
#define __VARIANT_NAME_1
#define __VARIANT_NAME_2
#define __VARIANT_NAME_3

typedef struct dlmsVARIANT
{
    struct __tagVARIANT
    {
        DLMS_DATA_TYPE vt;
        union __VARIANT_NAME_3
        {
            unsigned char bVal;
            char cVal;
            short iVal;
            long lVal;
            long long llVal;
            float fltVal;
            double dblVal;
            bool boolVal;
            unsigned short uiVal;
            unsigned long ulVal;
            unsigned long long ullVal;
            unsigned char *byteArr;
        } un;
    } st;
    CGXDateTime dateTime;
    //Size of byte array.
    unsigned short size;
    String strVal;
    WString strUtfVal;
    Vector Arr; // std::vector<CGXDLMSVariant>
} dlmsVARIANT;

extern void dlmsVARIANT_2(dlmsVARIANT* p, dlmsVARIANT* src);

typedef struct CGXDLMSVariant// class CGXDLMSVariant : public dlmsVARIANT
{
    struct __tagVARIANT
    {
        DLMS_DATA_TYPE vt;
        union
        {
            unsigned char bVal;
            char cVal;
            short iVal;
            long lVal;
            long long llVal;
            float fltVal;
            double dblVal;
            bool boolVal;
            unsigned short uiVal;
            unsigned long ulVal;
            unsigned long long ullVal;
            unsigned char *byteArr;
        } un;
    } st;
    CGXDateTime dateTime;
    //Size of byte array.
    unsigned short size;
    String strVal;
    WString strUtfVal;
    Vector Arr; // std::vector<CGXDLMSVariant>
} CGXDLMSVariant;

extern void CGXDLMSVariant_Clear(CGXDLMSVariant* p);
extern void CGXDLMSVariant_1(CGXDLMSVariant* p);

    //Copy constructor.
extern void CGXDLMSVariant_2(CGXDLMSVariant* p, const CGXDLMSVariant* value);

extern void CGXDLMSVariant_3(CGXDLMSVariant* p, float value);
extern void CGXDLMSVariant_4(CGXDLMSVariant* p, double value);

extern void CGXDLMSVariant_5(CGXDLMSVariant* p, unsigned long long value);
extern void CGXDLMSVariant_6(CGXDLMSVariant* p, long long value);
extern void CGXDLMSVariant_7(CGXDLMSVariant* p, bool value);
extern void CGXDLMSVariant_8(CGXDLMSVariant* p, char value);
extern void CGXDLMSVariant_9(CGXDLMSVariant* p, short value);
extern void CGXDLMSVariant_10(CGXDLMSVariant* p, int value);
extern void CGXDLMSVariant_11(CGXDLMSVariant* p, long value);
extern void CGXDLMSVariant_12(CGXDLMSVariant* p, struct tm* value);
extern void CGXDLMSVariant_13(CGXDLMSVariant* p, unsigned char* value, int count);
extern void CGXDLMSVariant_14(CGXDLMSVariant* p, CGXDate* value);
extern void CGXDLMSVariant_15(CGXDLMSVariant* p, CGXTime* value);
extern void CGXDLMSVariant_16(CGXDLMSVariant* p, CGXDateTime* value);
extern void CGXDLMSVariant_17(CGXDLMSVariant* p, CGXDLMSVariant* value);
extern void CGXDLMSVariant_18(CGXDLMSVariant* p, unsigned char* pValue, int count, DLMS_DATA_TYPE type);
extern void CGXDLMSVariant_19(CGXDLMSVariant* p, unsigned char value);
extern void CGXDLMSVariant_20(CGXDLMSVariant* p, unsigned short value);
extern void CGXDLMSVariant_21(CGXDLMSVariant* p, unsigned long value);
extern void CGXDLMSVariant_22(CGXDLMSVariant* p, String value);
extern void CGXDLMSVariant_23(CGXDLMSVariant* p, CGXByteBuffer* value);
extern void CGXDLMSVariant_24(CGXDLMSVariant* p, const char* value);

    //Destructor.
extern void CGXDLMSVariant_d(CGXDLMSVariant* p);


extern void CGXDLMSVariant_copy_1(CGXDLMSVariant* p, const CGXDLMSVariant* value);

extern void CGXDLMSVariant_copy_2(CGXDLMSVariant* p, String value);
extern void CGXDLMSVariant_copy_3(CGXDLMSVariant* p, const char* value);
extern void CGXDLMSVariant_copy_4(CGXDLMSVariant* p, CGXByteBuffer* value);
extern void CGXDLMSVariant_copy_5(CGXDLMSVariant* p, float value);
extern void CGXDLMSVariant_copy_6(CGXDLMSVariant* p, double value);
extern void CGXDLMSVariant_copy_7(CGXDLMSVariant* p, unsigned long long value);
extern void CGXDLMSVariant_copy_8(CGXDLMSVariant* p, long long value);
extern void CGXDLMSVariant_copy_9(CGXDLMSVariant* p, const bool value);
extern void CGXDLMSVariant_copy_10(CGXDLMSVariant* p, char value);
extern void CGXDLMSVariant_copy_11(CGXDLMSVariant* p, short value);
extern void CGXDLMSVariant_copy_12(CGXDLMSVariant* p, int value);
extern void CGXDLMSVariant_copy_13(CGXDLMSVariant* p, long value);
extern void CGXDLMSVariant_copy_14(CGXDLMSVariant* p, unsigned char value);
extern void CGXDLMSVariant_copy_15(CGXDLMSVariant* p, unsigned short value);
extern void CGXDLMSVariant_copy_16(CGXDLMSVariant* p, unsigned int value);
extern void CGXDLMSVariant_copy_17(CGXDLMSVariant* p, unsigned long value);
extern void CGXDLMSVariant_copy_18(CGXDLMSVariant* p, struct tm value);
extern void CGXDLMSVariant_copy_19(CGXDLMSVariant* p, CGXDate* value);
extern void CGXDLMSVariant_copy_20(CGXDLMSVariant* p, CGXTime* value);
extern void CGXDLMSVariant_copy_21(CGXDLMSVariant* p, CGXDateTime* value);
extern void CGXDLMSVariant_Add_1(CGXDLMSVariant* p, const unsigned char*, int count);
extern void CGXDLMSVariant_Add_2(CGXDLMSVariant* p, const char*, int count);
extern void CGXDLMSVariant_Add_3(CGXDLMSVariant* p, String value);
extern bool CGXDLMSVariant_Equals(CGXDLMSVariant* p, CGXDLMSVariant* item);
extern int CGXDLMSVariant_ChangeType(CGXDLMSVariant* p, DLMS_DATA_TYPE newType);
    //Get size in bytes.
extern int CGXDLMSVariant_GetSize_1(CGXDLMSVariant* p);
    //Get size in bytes.
extern int CGXDLMSVariant_GetSize_2(DLMS_DATA_TYPE vt);
extern String CGXDLMSVariant_ToString(CGXDLMSVariant* p);
extern int CGXDLMSVariant_ToInteger(CGXDLMSVariant* p);
extern double CGXDLMSVariant_ToDouble(CGXDLMSVariant* p);
extern int CGXDLMSVariant_GetBytes(CGXDLMSVariant* p, CGXByteBuffer* value);

extern void CGXDLMSVariant_v_c(void* p1, const void* p2);
extern void CGXDLMSVariant_v_d(void* p);

#endif //GXDLMSVARIANT_H
