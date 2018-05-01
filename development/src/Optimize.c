/*
 * Optimize.c
 *
 *  Created on: Mar 12, 2018
 *      Author: admin
 */

#include "../include/Optimize.h"
#include "../include/DLMSPort.h"
#include <stdbool.h>

void Vector_push_back_Str_LN(Vector *str_vec, CGXDLMSObject* p)
{
    String str;
    String_(&str);

    CGXDLMSObject_GetLogicalName_2(p, &str);
    Vector_push_back(str_vec, &str);

    String_d(&str);
}

void Vector_push_back_Str_1(Vector *str_vec, CGXDLMSVariant* var)
{
    String str = CGXDLMSVariant_ToString(var);

    Vector_push_back(str_vec, &str);

    String_d(&str);
}

// Only integer
void Vector_push_back_Str_2(Vector *str_vec, int i_var)
{
    CGXDLMSVariant var;
    CGXDLMSVariant_10(&var, i_var);

    Vector_push_back_Str_1(str_vec, &var);

    CGXDLMSVariant_d(&var);
}

// Const char*
void Vector_push_back_Str_3(Vector *str_vec, const char* str)
{
    String res;
    String_3(&res, str);

    Vector_push_back(str_vec, &res);

    String_d(&res);
}

void Vector_push_back_Str_4(Vector *str_vec, CGXByteBuffer* bb)
{
    String str = CGXByteBuffer_ToHexString(bb);

    Vector_push_back(str_vec, &str);

    String_d(&str);
}

void Vector_push_back_Str_5(Vector *str_vec, unsigned long ul_var)
{
    CGXDLMSVariant var;
    CGXDLMSVariant_21(&var, ul_var);

    Vector_push_back_Str_1(str_vec, &var);

    CGXDLMSVariant_d(&var);
}

// Only long
void Vector_push_back_Str_6(Vector *str_vec, long l_var)
{
    CGXDLMSVariant var;
    CGXDLMSVariant_11(&var, l_var);

    Vector_push_back_Str_1(str_vec, &var);

    CGXDLMSVariant_d(&var);
}

// Only bool
void Vector_push_back_Str_7(Vector *str_vec, bool b_var)
{
    CGXDLMSVariant var;
    CGXDLMSVariant_7(&var, b_var);

    Vector_push_back_Str_1(str_vec, &var);

    CGXDLMSVariant_d(&var);
}

// Only string
void Vector_push_back_Str_8(Vector *str_vec, String* str_var)
{
    CGXDLMSVariant var;
    CGXDLMSVariant_22(&var, *str_var);

    Vector_push_back_Str_1(str_vec, &var);

    CGXDLMSVariant_d(&var);
}

void CGXDLMSValueEventArg_SetValue_2(CGXDLMSValueEventArg* e, CGXByteBuffer *data)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_23(&tmp, data);

    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
}

void CGXDLMSValueEventArg_SetValue_3(CGXDLMSValueEventArg* e, int i_var)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_10(&tmp, i_var);

    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
}

// Only unsigned char
void CGXDLMSValueEventArg_SetValue_4(CGXDLMSValueEventArg* e, unsigned char uc_var)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_19(&tmp, uc_var);

    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
}

// Only unsigned long
void CGXDLMSValueEventArg_SetValue_5(CGXDLMSValueEventArg* e, unsigned long ul_var)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_21(&tmp, ul_var);

    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
}

// Only long
void CGXDLMSValueEventArg_SetValue_6(CGXDLMSValueEventArg* e, long l_var)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_11(&tmp, l_var);

    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
}

// Only bool
void CGXDLMSValueEventArg_SetValue_7(CGXDLMSValueEventArg* e, bool b_var)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_7(&tmp, b_var);

    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
}

// Only string
void CGXDLMSValueEventArg_SetValue_8(CGXDLMSValueEventArg* e, String* str_var)
{
    CGXDLMSVariant tmp;
    CGXDLMSVariant_22(&tmp, *str_var);

    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
}

int CGXDLMSObject_GetValue_1(CGXDLMSObject* p, CGXDLMSValueEventArg* e)
{
    int ret;

    CGXDLMSVariant tmp;
    CGXDLMSVariant_1(&tmp);

    if ((ret = CGXDLMSObject_GetLogicalName_1(p, &tmp)) != 0)
    {
        CGXDLMSVariant_d(&tmp);
        return ret;
    }
    CGXDLMSValueEventArg_SetValue(e, &tmp);

    CGXDLMSVariant_d(&tmp);
    return DLMS_ERROR_CODE_OK;
}

void String_append_int(String* s, int num)
{
    char buff[20];

    DLMSPort_sprintf(buff, "%d", num);
    String_append_1(s, buff);
}

void String_append_var_str(String* s, CGXDLMSVariant* var)
{
    String str = CGXDLMSVariant_ToString(var);

    String_append_3(s, &str);

    String_d(&str);
}

// Only integer
void String_append_var_int(String* s, int i_var)
{
    CGXDLMSVariant var;
    CGXDLMSVariant_10(&var, i_var);

    String_append_var_str(s, &var);

    CGXDLMSVariant_d(&var);
}

// Only unsigned long
void String_append_var_ulong(String* s, unsigned long ul_var)
{
    CGXDLMSVariant var;
    CGXDLMSVariant_21(&var, ul_var);

    String_append_var_str(s, &var);

    CGXDLMSVariant_d(&var);
}
