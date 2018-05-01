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

#include "../include/errorcodes.h"
#include "../include/GXSerialNumberCounter.h"
#include "../include/DLMSPort.h"
#include "../include/String.h"

char toLower(char ch)
{
    if (ch <= 'Z' && ch >= 'A')
    {
        return ch - ('Z' - 'z');
    }
    return ch;
}

/**
* Produce formatted String by the given math expression.
*
* @param expression
*            Unformatted math expression.
* @return Formatted math expression.
*/
static int CGXSerialNumberCounter_FormatString(String* expression, String* value)
{
    if (String_length(expression) == 0)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    String_copy_2(value, "");
    char ch;
    for (unsigned short pos = 0; pos != String_length(expression); ++pos)
    {
        ch = toLower(*String_at(expression, pos));
        if (ch == '(' || ch == ')')
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        // Is white space.
        if (ch == ' ')
        {
            continue;
        }
        else
        {
            char tmp[2] = {ch, '\0'};
        	String_append_1(value, tmp);
        }
    }
    return 0;
}

/*
 * Get values to count together.
 */
static int CGXSerialNumberCounter_GetValues(String* expressions, Vector* values)
{
    int last = 0, index = 0;
    int count = (int)String_size(expressions);
    char ch;

    for (int pos = 0; pos != count; ++pos)
    {
        String tmp;
        ch = *String_at(expressions, pos);
        switch (ch)
        {
        case '%':
        case '+':
        case '-':
        case '*':
        case '/':
            tmp = String_substr_1(expressions, last, index - last);
        	Vector_push_back(values, &tmp);
        	String_d(&tmp);

        	char tmp2[2] = {ch, '\0'};
            String_copy_2(&tmp, tmp2);
            Vector_push_back(values, &tmp);
            String_d(&tmp);
            last = index + 1;
            break;
        default:
            break;
        }
        ++index;
    }
    if (index != last)
    {
        String tmp = String_substr_1(expressions, last, index - last);

        Vector_push_back(values, &tmp);

        String_d(&tmp);
    }
    return 0;
}

static int CGXSerialNumberCounter_GetValue(String* value, int sn)
{
    if (String_compare(value, "sn") == 0)
    {
        return sn;
    }
#if _MSC_VER > 1000
    if (DLMSPort_sscanf_s(String_c_str(value), "%d", &sn) == 1)
#else
    if (DLMSPort_sscanf(String_c_str(value), "%d", &sn) == 1)
#endif
    {
        return sn;
    }
    return -1;
}

/// <summary>
/// Count serial number using formula.
/// </summary>
/// <param name="sn">Serial number</param>
/// <param name="formula">Formula to used.</param>
/// <returns></returns>
int CGXSerialNumberCounter_Count(unsigned long sn, const char* formula)
{
    int ret;

    String str;
    String_(&str);

    Vector values; // std::vector<std::string>
    Vector_(&values, sizeof(String), String_v_c, String_v_d);

    String tmp;
    String_3(&tmp, formula);

    unsigned long value;

    if ((ret = CGXSerialNumberCounter_FormatString(&tmp, &str)) != 0)
    {
        String_d(&tmp);
        String_d(&str);
        Vector_d(&values);
        return -1;
    }

    String_d(&tmp);

    if ((ret = CGXSerialNumberCounter_GetValues(&str, &values)) != 0)
    {
        String_d(&str);
        Vector_d(&values);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (Vector_size(&values) % 2 == 0)
    {
        String_d(&str);
        Vector_d(&values);
        return -1;
    }
    String_clear(&str);
    value = CGXSerialNumberCounter_GetValue(Vector_at(&values, 0), sn);
    for (unsigned short index = 1; index != Vector_size(&values); index += 2)
    {
        String_copy_1(&str, Vector_at(&values, index));
        if (String_compare(&str, "%") == 0)
        {
            value = value % CGXSerialNumberCounter_GetValue(Vector_at(&values, index + 1), sn);
        }
        else if (String_compare(&str, "+") == 0)
        {
            value = value + CGXSerialNumberCounter_GetValue(Vector_at(&values, index + 1), sn);
        }
        else if (String_compare(&str, "-") == 0)
        {
            value = value - CGXSerialNumberCounter_GetValue(Vector_at(&values, index + 1), sn);
        }
        else if (String_compare(&str, "*") == 0)
        {
            value = value * CGXSerialNumberCounter_GetValue(Vector_at(&values, index + 1), sn);
        }
        else if (String_compare(&str, "/") == 0)
        {
            value = value / CGXSerialNumberCounter_GetValue(Vector_at(&values, index + 1), sn);
        }
        else
        {
            String_d(&str);
            Vector_d(&values);
            //"Invalid serial number formula.
            return -1;
        }
    }

    String_d(&str);
    Vector_d(&values);
    return value;
}
