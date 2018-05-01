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
#include "../include/GXStandardObisCodeCollection.h"
#include "../include/DLMSPort.h"
#include "../include/Vector.h"

//Convert logican name std::string to bytes.
static int CGXStandardObisCodeCollection_GetUInt8(String ln, unsigned char* bytes)
{
    Vector tmp = GXHelpers_Split_1(&ln, '.'); // std::vector< std::string >

    if (Vector_size(&tmp) != 6)
    {
        //Invalid OBIS Code.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    int value;
#if _MSC_VER > 1000
    DLMSPort_sscanf_s(String_c_str((String*) Vector_at(&tmp, 0)), "%d", &value);
#else
    DLMSPort_sscanf(String_c_str((String*) Vector_at(&tmp, 0)), "%d", &value);
#endif
    bytes[0] = value;
#if _MSC_VER > 1000
    DLMSPort_sscanf_s(String_c_str((String*) Vector_at(&tmp, 1)), "%d", &value);
#else
    DLMSPort_sscanf(String_c_str((String*) Vector_at(&tmp, 1)), "%d", &value);
#endif
    bytes[1] = value;
#if _MSC_VER > 1000
    DLMSPort_sscanf_s(String_c_str((String*) Vector_at(&tmp, 2)), "%d", &value);
#else
    DLMSPort_sscanf(String_c_str((String*) Vector_at(&tmp, 2)), "%d", &value);
#endif
    bytes[2] = value;
#if _MSC_VER > 1000
    DLMSPort_sscanf_s(String_c_str((String*) Vector_at(&tmp, 3)), "%d", &value);
#else
    DLMSPort_sscanf(String_c_str((String*) Vector_at(&tmp, 3)), "%d", &value);
#endif
    bytes[3] = value;
#if _MSC_VER > 1000
    DLMSPort_sscanf_s(String_c_str((String*) Vector_at(&tmp, 4)), "%d", &value);
#else
    DLMSPort_sscanf(String_c_str((String*) Vector_at(&tmp, 4)), "%d", &value);
#endif
    bytes[4] = value;
#if _MSC_VER > 1000
    DLMSPort_sscanf_s(String_c_str((String*) Vector_at(&tmp, 5)), "%d", &value);
#else
    DLMSPort_sscanf(String_c_str((String*) Vector_at(&tmp, 5)), "%d", &value);
#endif
    bytes[5] = value;

    Vector_d(&tmp);
    return DLMS_ERROR_CODE_OK;
}

// Check is interface included to standard.
static bool CGXStandardObisCodeCollection_EqualsInterface(CGXStandardObisCodeCollection *p, CGXStandardObisCode item, int ic)
{
    //If all interfaces are allowed.
    if (String_compare(CGXStandardObisCode_GetInterfaces(&item), "*") == 0)
    {
        return true;
    }
    char type[10];
#if _MSC_VER > 1000
    DLMSPort_sprintf_s(type, 10, "%d", ic);
#else
    DLMSPort_sprintf(type, "%d", ic);
#endif
    Vector tmp = GXHelpers_Split_1(CGXStandardObisCode_GetInterfaces(&item), ','); // std::vector< std::string >

    for (unsigned int it = Vector_begin(&tmp); it != Vector_end(&tmp); ++it)
    {
        if (String_compare(Vector_at(&tmp, it), "*") == 0)
        {
            Vector_d(&tmp);
            return true;
        }
    }

    Vector_d(&tmp);
    return false;
}

// Check OBIS codes.
static bool CGXStandardObisCodeCollection_EqualsMask_1(String obis, int ic)
{
    bool number = true;
    int value;

    if (String_find_1(&obis, ',', 0) != STRING_NPOS)
    {
        Vector tmp = GXHelpers_Split_1(&obis, ','); // std::vector< std::string >

        for (unsigned int it = Vector_begin(&tmp); it != Vector_end(&tmp); ++it)
        {
            if (String_find_1(Vector_at(&tmp, it), '-', 0) != STRING_NPOS)
            {
                if (CGXStandardObisCodeCollection_EqualsMask_1(*((String*) Vector_at(&tmp, it)), ic))
                {
                    Vector_d(&tmp);
                    return true;
                }
            }
            else
            {
#if _MSC_VER > 1000
                DLMSPort_sscanf_s(String_c_str(Vector_at(&tmp, it)), "%d", &value);
#else
                DLMSPort_sscanf(String_c_str(Vector_at(&tmp, it)), "%d", &value);
#endif
                if (value == ic)
                {
                    Vector_d(&tmp);
                    return true;
                }
            }
        }

        Vector_d(&tmp);
        return false;
    }
    else if (String_find_1(&obis, '-', 0) != STRING_NPOS)
    {
        number = false;

        Vector tmp = GXHelpers_Split_1(&obis, '-'); // std::vector< std::string >

        int value1, value2;
#if _MSC_VER > 1000
        DLMSPort_sscanf_s(String_c_str(Vector_at(&tmp, 0)), "%d", &value1);
        DLMSPort_sscanf_s(String_c_str(Vector_at(&tmp, 1)), "%d", &value2);
#else
        DLMSPort_sscanf(String_c_str(Vector_at(&tmp, 0)), "%d", &value1);
        DLMSPort_sscanf(String_c_str(Vector_at(&tmp, 1)), "%d", &value2);
#endif

        Vector_d(&tmp);
        return (ic >= value1) && (ic <= value2);
    }
    if (number)
    {
        if (String_compare(&obis, "&") == 0)
        {
            return (ic == 0) || (ic == 1) || (ic == 7);
        }
#if _MSC_VER > 1000
        DLMSPort_sscanf_s(String_c_str(&obis), "%d", &value);
#else
        DLMSPort_sscanf(String_c_str(&obis), "%d", &value);
#endif
        return value == ic;
    }
    return false;
}

// Check OBIS code.
static bool CGXStandardObisCodeCollection_EqualsObisCode(Vector* obisMask, unsigned char* ic) //std::vector< std::string >&
{
    if (!CGXStandardObisCodeCollection_EqualsMask_1(*((String*) Vector_at(obisMask, 0)), ic[0]))
    {
        return false;
    }
    if (!CGXStandardObisCodeCollection_EqualsMask_1(*((String*) Vector_at(obisMask, 1)), ic[1]))
    {
        return false;
    }
    if (!CGXStandardObisCodeCollection_EqualsMask_1(*((String*) Vector_at(obisMask, 2)), ic[2]))
    {
        return false;
    }
    if (!CGXStandardObisCodeCollection_EqualsMask_1(*((String*) Vector_at(obisMask, 3)), ic[3]))
    {
        return false;
    }
    if (!CGXStandardObisCodeCollection_EqualsMask_1(*((String*) Vector_at(obisMask, 4)), ic[4]))
    {
        return false;
    }
    if (!CGXStandardObisCodeCollection_EqualsMask_1(*((String*) Vector_at(obisMask, 5)), ic[5]))
    {
        return false;
    }
    return true;
}

// Get description.
static String CGXStandardObisCodeCollection_GetDescription(CGXStandardObisCodeCollection *p, String* str)
{
    String tmp;

    str = GXHelpers_trim(str);
    if ((String_size(str) == 0) || ((*String_at(str, 0)) != '$'))
    {
        String_3(&tmp, "");
        return tmp; // copy cons + des
    }
    int value;

    String t_Str = String_substr_2(str, 1);

#if _MSC_VER > 1000
    DLMSPort_sscanf_s(String_c_str(&t_Str), "%d", &value);
#else
    DLMSPort_sscanf(String_c_str(&t_Str), "%d", &value);
#endif

    String_d(&t_Str);

    switch (value)
    {
    case 1:
        String_3(&tmp, "Sum Li Active power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 2:
        String_3(&tmp, "Sum Li Active power- (QII+QIII)");
        return tmp; // copy cons + des
    case 3:
        String_3(&tmp, "Sum Li Reactive power+ (QI+QII)");
        return tmp; // copy cons + des
    case 4:
        String_3(&tmp, "Sum Li Reactive power- (QIII+QIV)");
        return tmp; // copy cons + des
    case 5:
        String_3(&tmp, "Sum Li Reactive power QI");
        return tmp; // copy cons + des
    case 6:
        String_3(&tmp, "Sum Li Reactive power QII");
        return tmp; // copy cons + des
    case 7:
        String_3(&tmp, "Sum Li Reactive power QIII");
        return tmp; // copy cons + des
    case 8:
        String_3(&tmp, "Sum Li Reactive power QIV");
        return tmp; // copy cons + des
    case 9:
        String_3(&tmp, "Sum Li Apparent power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 10:
        String_3(&tmp, "Sum Li Apparent power- (QII+QIII)");
        return tmp; // copy cons + des
    case 11:
        String_3(&tmp, "Current: any phase");
        return tmp; // copy cons + des
    case 12:
        String_3(&tmp, "Voltage: any phase");
        return tmp; // copy cons + des
    case 13:
        String_3(&tmp, "Sum Li Power factor");
        return tmp; // copy cons + des
    case 14:
        String_3(&tmp, "Supply frequency");
        return tmp; // copy cons + des
    case 15:
        String_3(&tmp, "Sum LI Active power (abs(QI+QIV)+abs(QII+QIII))");
        return tmp; // copy cons + des
    case 16:
        String_3(&tmp, "Sum LI Active power        (abs(QI+QIV)-abs(QII+QIII))");
        return tmp; // copy cons + des
    case 17:
        String_3(&tmp, "Sum Li Active power QI");
        return tmp; // copy cons + des
    case 18:
        String_3(&tmp, "Sum Li Active power QII");
        return tmp; // copy cons + des
    case 19:
        String_3(&tmp, "Sum Li Active power QIII");
        return tmp; // copy cons + des
    case 20:
        String_3(&tmp, "Sum Li Active power QIV");
        return tmp; // copy cons + des
    case 21:
        String_3(&tmp, "L1 Active power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 22:
        String_3(&tmp, "L1 Active power- (QII+QIII)");
        return tmp; // copy cons + des
    case 23:
        String_3(&tmp, "L1 Reactive power+ (QI+QII)");
        return tmp; // copy cons + des
    case 24:
        String_3(&tmp, "L1 Reactive power- (QIII+QIV)");
        return tmp; // copy cons + des
    case 25:
        String_3(&tmp, "L1 Reactive power QI");
        return tmp; // copy cons + des
    case 26:
        String_3(&tmp, "L1 Reactive power QII");
        return tmp; // copy cons + des
    case 27:
        String_3(&tmp, "L1 Reactive power QIII");
        return tmp; // copy cons + des
    case 28:
        String_3(&tmp, "L1 Reactive power QIV");
        return tmp; // copy cons + des
    case 29:
        String_3(&tmp, "L1 Apparent power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 30:
        String_3(&tmp, "L1 Apparent power- (QII+QIII)");
        return tmp; // copy cons + des
    case 31:
        String_3(&tmp, "L1 Current");
        return tmp; // copy cons + des
    case 32:
        String_3(&tmp, "L1 Voltage");
        return tmp; // copy cons + des
    case 33:
        String_3(&tmp, "L1 Power factor");
        return tmp; // copy cons + des
    case 34:
        String_3(&tmp, "L1 Supply frequency");
        return tmp; // copy cons + des
    case 35:
        String_3(&tmp, "L1 Active power (abs(QI+QIV)+abs(QII+QIII))");
        return tmp; // copy cons + des
    case 36:
        String_3(&tmp, "L1 Active power (abs(QI+QIV)-abs(QII+QIII))");
        return tmp; // copy cons + des
    case 37:
        String_3(&tmp, "L1 Active power QI");
        return tmp; // copy cons + des
    case 38:
        String_3(&tmp, "L1 Active power QII");
        return tmp; // copy cons + des
    case 39:
        String_3(&tmp, "L1 Active power QIII");
        return tmp; // copy cons + des
    case 40:
        String_3(&tmp, "L1 Active power QIV");
        return tmp; // copy cons + des
    case 41:
        String_3(&tmp, "L2 Active power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 42:
        String_3(&tmp, "L2 Active power- (QII+QIII)");
        return tmp; // copy cons + des
    case 43:
        String_3(&tmp, "L2 Reactive power+ (QI+QII)");
        return tmp; // copy cons + des
    case 44:
        String_3(&tmp, "L2 Reactive power- (QIII+QIV)");
        return tmp; // copy cons + des
    case 45:
        String_3(&tmp, "L2 Reactive power QI");
        return tmp; // copy cons + des
    case 46:
        String_3(&tmp, "L2 Reactive power QII");
        return tmp; // copy cons + des
    case 47:
        String_3(&tmp, "L2 Reactive power QIII");
        return tmp; // copy cons + des
    case 48:
        String_3(&tmp, "L2 Reactive power QIV");
        return tmp; // copy cons + des
    case 49:
        String_3(&tmp, "L2 Apparent power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 50:
        String_3(&tmp, "L2 Apparent power- (QII+QIII)");
        return tmp; // copy cons + des
    case 51:
        String_3(&tmp, "L2 Current");
        return tmp; // copy cons + des
    case 52:
        String_3(&tmp, "L2 Voltage");
        return tmp; // copy cons + des
    case 53:
        String_3(&tmp, "L2 Power factor");
        return tmp; // copy cons + des
    case 54:
        String_3(&tmp, "L2 Supply frequency");
        return tmp; // copy cons + des
    case 55:
        String_3(&tmp, "L2 Active power (abs(QI+QIV)+abs(QII+QIII))");
        return tmp; // copy cons + des
    case 56:
        String_3(&tmp, "L2 Active power (abs(QI+QIV)-abs(QI+QIII))");
        return tmp; // copy cons + des
    case 57:
        String_3(&tmp, "L2 Active power QI");
        return tmp; // copy cons + des
    case 58:
        String_3(&tmp, "L2 Active power QII");
        return tmp; // copy cons + des
    case 59:
        String_3(&tmp, "L2 Active power QIII");
        return tmp; // copy cons + des
    case 60:
        String_3(&tmp, "L2 Active power QIV");
        return tmp; // copy cons + des
    case 61:
        String_3(&tmp, "L3 Active power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 62:
        String_3(&tmp, "L3 Active power- (QII+QIII)");
        return tmp; // copy cons + des
    case 63:
        String_3(&tmp, "L3 Reactive power+ (QI+QII)");
        return tmp; // copy cons + des
    case 64:
        String_3(&tmp, "L3 Reactive power- (QIII+QIV)");
        return tmp; // copy cons + des
    case 65:
        String_3(&tmp, "L3 Reactive power QI");
        return tmp; // copy cons + des
    case 66:
        String_3(&tmp, "L3 Reactive power QII");
        return tmp; // copy cons + des
    case 67:
        String_3(&tmp, "L3 Reactive power QIII");
        return tmp; // copy cons + des
    case 68:
        String_3(&tmp, "L3 Reactive power QIV");
        return tmp; // copy cons + des
    case 69:
        String_3(&tmp, "L3 Apparent power+ (QI+QIV)");
        return tmp; // copy cons + des
    case 70:
        String_3(&tmp, "L3 Apparent power- (QII+QIII)");
        return tmp; // copy cons + des
    case 71:
        String_3(&tmp, "L3 Current");
        return tmp; // copy cons + des
    case 72:
        String_3(&tmp, "L3 Voltage");
        return tmp; // copy cons + des
    case 73:
        String_3(&tmp, "L3 Power factor");
        return tmp; // copy cons + des
    case 74:
        String_3(&tmp, "L3 Supply frequency");
        return tmp; // copy cons + des
    case 75:
        String_3(&tmp, "L3 Active power (abs(QI+QIV)+abs(QII+QIII))");
        return tmp; // copy cons + des
    case 76:
        String_3(&tmp, "L3 Active power (abs(QI+QIV)-abs(QI+QIII))");
        return tmp; // copy cons + des
    case 77:
        String_3(&tmp, "L3 Active power QI");
        return tmp; // copy cons + des
    case 78:
        String_3(&tmp, "L3 Active power QII");
        return tmp; // copy cons + des
    case 79:
        String_3(&tmp, "L3 Active power QIII");
        return tmp; // copy cons + des
    case 80:
        String_3(&tmp, "L3 Active power QIV");
        return tmp; // copy cons + des
    case 82:
        String_3(&tmp, "Unitless quantities (pulses or pieces)");
        return tmp; // copy cons + des
    case 84:
        String_3(&tmp, "Sum Li Power factor-");
        return tmp; // copy cons + des
    case 85:
        String_3(&tmp, "L1 Power factor-");
        return tmp; // copy cons + des
    case 86:
        String_3(&tmp, "L2 Power factor-");
        return tmp; // copy cons + des
    case 87:
        String_3(&tmp, "L3 Power factor-");
        return tmp; // copy cons + des
    case 88:
        String_3(&tmp, "Sum Li A2h QI+QII+QIII+QIV");
        return tmp; // copy cons + des
    case 89:
        String_3(&tmp, "Sum Li V2h QI+QII+QIII+QIV");
        return tmp; // copy cons + des
    case 90:
        String_3(&tmp, "SLi current (algebraic sum of the � unsigned � value of the currents in all phases)");
        return tmp; // copy cons + des
    case 91:
        String_3(&tmp, "Lo Current (neutral)");
        return tmp; // copy cons + des
    case 92:
        String_3(&tmp, "Lo Voltage (neutral)");
        return tmp; // copy cons + des
    }

    String_3(&tmp, "");
    return tmp; // copy cons + des
}

bool CGXStandardObisCodeCollection_Find_1(CGXStandardObisCodeCollection *p, String ln, DLMS_OBJECT_TYPE objectType, CGXStandardObisCode* item)
{
    unsigned char bytes[6];
    if (CGXStandardObisCodeCollection_GetUInt8(ln, bytes) != DLMS_ERROR_CODE_OK)
    {
        return NULL;
    }
    return CGXStandardObisCodeCollection_Find_2(p, bytes, objectType, item);
}

bool CGXStandardObisCodeCollection_EqualsMask_2(String obisMask, String ln)
{
    unsigned char bytes[6];
    if (CGXStandardObisCodeCollection_GetUInt8(ln, bytes) != DLMS_ERROR_CODE_OK)
    {
        return NULL;
    }
    Vector tmp = GXHelpers_Split_1(&obisMask, '.'); // std::vector< std::string >

    bool t_res = CGXStandardObisCodeCollection_EqualsObisCode(&tmp, bytes);

    Vector_d(&tmp);
    return t_res;
}

// Find Standard OBIS Code description.
bool CGXStandardObisCodeCollection_Find_2(CGXStandardObisCodeCollection *p, unsigned char* pObisCode, int IC, CGXStandardObisCode* tmp)
{
    char buff[6];
    for (unsigned int it = CGXStandardObisCodeCollection_begin(p);
         it != CGXStandardObisCodeCollection_end(p); ++it) // std::vector<CGXStandardObisCode>
    {
        CGXStandardObisCode* t_ppOCode = (CGXStandardObisCode*) CGXStandardObisCodeCollection_at(p, it);

        //Interface is tested first because it's faster.
        if (CGXStandardObisCodeCollection_EqualsInterface(p, *t_ppOCode, IC)
         && CGXStandardObisCodeCollection_EqualsObisCode(CGXStandardObisCode_GetOBIS(t_ppOCode), pObisCode))
        {
            CGXStandardObisCode_SetOBIS(tmp, CGXStandardObisCode_GetOBIS(t_ppOCode));
            CGXStandardObisCode_SetDescription(tmp, *CGXStandardObisCode_GetDescription(t_ppOCode));
            CGXStandardObisCode_SetInterfaces(tmp, *CGXStandardObisCode_GetInterfaces(t_ppOCode));
            CGXStandardObisCode_SetDataType(tmp, *CGXStandardObisCode_GetDataType(t_ppOCode));

            Vector tmp2 = GXHelpers_Split_1(CGXStandardObisCode_GetDescription(t_ppOCode), ';'); // std::vector< std::string >

            if (Vector_size(&tmp2) > 1)
            {
                String desc = CGXStandardObisCodeCollection_GetDescription(p, Vector_at(&tmp2, 1));

                if (String_compare(&desc, "") != 0)
                {
                    // tmp2[1] = desc;
                    String_copy_1(Vector_at(&tmp2, 1), &desc);

                    String builder;
                    String_(&builder);

                    for (unsigned int s = Vector_begin(&tmp2); s != Vector_end(&tmp2); ++s) // std::vector< std::string >
                    {
                        if (String_size(&builder) != 0)
                        {
                            String_append_1(&builder, ";");
                        }
                        String_append_3(&builder, Vector_at(&tmp2, s));
                    }
                    CGXStandardObisCode_SetDescription(tmp, builder);

                    String_d(&builder);
                }

                String_d(&desc);
            }

            Vector_d(&tmp2);

            Vector obis; // std::vector< std::string >
            Vector_2(&obis, CGXStandardObisCode_GetOBIS(tmp));

#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[0]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[0]);
#endif

            String_copy_2(Vector_at(&obis, 0), buff);
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[1]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[1]);
#endif

            String_copy_2(Vector_at(&obis, 1), buff);
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[2]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[2]);
#endif

            String_copy_2(Vector_at(&obis, 2), buff);
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[3]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[3]);
#endif

            String_copy_2(Vector_at(&obis, 3), buff);
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[4]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[4]);
#endif

            String_copy_2(Vector_at(&obis, 4), buff);
#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[5]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[5]);
#endif

            String_copy_2(Vector_at(&obis, 5), buff);
            CGXStandardObisCode_SetOBIS(tmp, &obis);

            Vector_d(&obis);

            String desc;
            String_2(&desc, CGXStandardObisCode_GetDescription(tmp));

#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[0]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[0]);
#endif

            String t_Str1, t_Str2;
            String_3(&t_Str1, "$A");
            String_3(&t_Str2, buff);

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);

#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[1]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[1]);
#endif

            String_3(&t_Str1, "$B");

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);

#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[2]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[2]);
#endif

            String_3(&t_Str1, "$C");

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);

#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[3]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[3]);
#endif

            String_3(&t_Str1, "$D");

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);

#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[4]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[4]);
#endif

            String_3(&t_Str1, "$E");

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);

#if _MSC_VER > 1000
            DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[5]);
#else
            DLMSPort_sprintf(buff, "%d", pObisCode[5]);
#endif

            String_3(&t_Str1, "$F");

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);
            String_d(&t_Str2);

            //Increase value
            int begin = (int)String_find_2(&desc, "#$");
            if (begin != -1)
            {
                int start = (int)String_find_1(&desc, '(', 0);
                int end = (int)String_find_1(&desc, ')', 0);
                char channel = *String_at(&desc, start + 1);
                int ch = 0;
                if (channel == 'A')
                {
                    ch = pObisCode[0];
                }
                else if (channel == 'B')
                {
                    ch = pObisCode[1];
                }
                else if (channel == 'C')
                {
                    ch = pObisCode[2];
                }
                else if (channel == 'D')
                {
                    ch = pObisCode[3];
                }
                else if (channel == 'E')
                {
                    ch = pObisCode[4];
                }
                else if (channel == 'F')
                {
                    ch = pObisCode[5];
                }
                int plus = (int)String_find_1(&desc, '+', 0);

                String t_tmp;

                if (plus != -1)
                {
                    int value;

                    t_tmp = String_substr_1(&desc, plus + 1, plus + 1 + end - plus - 1);

#if _MSC_VER > 1000
                    DLMSPort_sscanf_s(String_c_str(&t_tmp), "%d", &value);
#else
                    DLMSPort_sscanf(String_c_str(&t_tmp), "%d", &value);
#endif
                    ch += value;

                    String_d(&t_tmp);
                }
#if _MSC_VER > 1000
                DLMSPort_sprintf_s(buff, 6, "%d", ch);
#else
                DLMSPort_sprintf(buff, "%d", ch);
#endif
                t_tmp = String_substr_1(&desc, 0, begin);

                String_append_1(&t_tmp, buff);

                String_copy_1(&desc, String_append_1(&t_tmp, buff));

                String_d(&t_tmp);
            }

            String_3(&t_Str1, ";");
            String_3(&t_Str2, " ");

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);

            String_3(&t_Str1, "  ");

            GXHelpers_Replace(&desc, t_Str1, t_Str2);

            String_d(&t_Str1);
            String_d(&t_Str2);

            GXHelpers_rtrim(&desc);
            CGXStandardObisCode_SetDescription(tmp, desc);

            String_d(&desc);
            return true;
        }
    }

    String t_Str3;
    String_3(&t_Str3, "Manufacturer specific");

    CGXStandardObisCode_SetDescription(tmp, t_Str3);

    String_d(&t_Str3);

#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 6, "%d", IC);
#else
    DLMSPort_sprintf(buff, "%d", IC);
#endif

    String_3(&t_Str3, buff);

    CGXStandardObisCode_SetInterfaces(tmp, t_Str3);

    String_d(&t_Str3);

    String_3(&t_Str3, "");

    CGXStandardObisCode_SetDataType(tmp, t_Str3);

    String_d(&t_Str3);

    Vector obis; // std::vector <std::string >
    Vector_(&obis, sizeof(String), String_v_c, String_v_d);

    //Pois
#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[0]);
#else
    DLMSPort_sprintf(buff, "%d", pObisCode[0]);
#endif

    String_3(&t_Str3, buff);

    Vector_push_back(&obis, &t_Str3);

    String_d(&t_Str3);

#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[1]);
#else
    DLMSPort_sprintf(buff, "%d", pObisCode[1]);
#endif

    String_3(&t_Str3, buff);

    Vector_push_back(&obis, &t_Str3);

    String_d(&t_Str3);

#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[2]);
#else
    DLMSPort_sprintf(buff, "%d", pObisCode[2]);
#endif

    String_3(&t_Str3, buff);

    Vector_push_back(&obis, &t_Str3);

    String_d(&t_Str3);

#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[3]);
#else
    DLMSPort_sprintf(buff, "%d", pObisCode[3]);
#endif

    String_3(&t_Str3, buff);

    Vector_push_back(&obis, &t_Str3);

    String_d(&t_Str3);

#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[4]);
#else
    DLMSPort_sprintf(buff, "%d", pObisCode[4]);
#endif

    String_3(&t_Str3, buff);

    Vector_push_back(&obis, &t_Str3);

    String_d(&t_Str3);

#if _MSC_VER > 1000
    DLMSPort_sprintf_s(buff, 6, "%d", pObisCode[5]);
#else
    DLMSPort_sprintf(buff, "%d", pObisCode[5]);
#endif

    String_3(&t_Str3, buff);

    Vector_push_back(&obis, &t_Str3);

    String_d(&t_Str3);

    CGXStandardObisCode_SetOBIS(tmp, &obis);

    Vector_d(&obis);
    return true;
}

void CGXStandardObisCodeCollection_(CGXStandardObisCodeCollection *p)
{
    Vector_((Vector*) p, sizeof(CGXStandardObisCode), CGXStandardObisCode_v_c, CGXStandardObisCode_v_d);
}

void CGXStandardObisCodeCollection_d(CGXStandardObisCodeCollection *p)
{
    Vector_d((Vector*) p);
}
