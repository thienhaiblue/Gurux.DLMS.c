/*
 * Optimize.h
 *
 *  Created on: Mar 12, 2018
 *      Author: admin
 */

#ifndef OPTIMIZE_H_
#define OPTIMIZE_H_

#include "GXDLMSVariant.h"
#include "GXDLMSValueEventArg.h"
#include "GXBytebuffer.h"
#include "GXDLMSObject.h"
#include "String.h"
#include "Vector.h"
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////////////////
extern void Vector_push_back_Str_LN(Vector *str_vec, CGXDLMSObject* p);

extern void Vector_push_back_Str_1(Vector *str_vec, CGXDLMSVariant* var);

// Only integer
extern void Vector_push_back_Str_2(Vector *str_vec, int i_var);

// Const char*
extern void Vector_push_back_Str_3(Vector *str_vec, const char* str);

extern void Vector_push_back_Str_4(Vector *str_vec, CGXByteBuffer* bb);

// Only unsigned long
extern void Vector_push_back_Str_5(Vector *str_vec, unsigned long ul_var);

// Only long
extern void Vector_push_back_Str_6(Vector *str_vec, long l_var);

// Only bool
extern void Vector_push_back_Str_7(Vector *str_vec, bool b_var);

// Only string
extern void Vector_push_back_Str_8(Vector *str_vec, String* str_var);
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
extern void CGXDLMSValueEventArg_SetValue_2(CGXDLMSValueEventArg* e, CGXByteBuffer *data);

// Only integer
extern void CGXDLMSValueEventArg_SetValue_3(CGXDLMSValueEventArg* e, int i_var);

// Only unsigned char
extern void CGXDLMSValueEventArg_SetValue_4(CGXDLMSValueEventArg* e, unsigned char uc_var);

// Only unsigned long
extern void CGXDLMSValueEventArg_SetValue_5(CGXDLMSValueEventArg* e, unsigned long ul_var);

// Only long
extern void CGXDLMSValueEventArg_SetValue_6(CGXDLMSValueEventArg* e, long l_var);

// Only bool
extern void CGXDLMSValueEventArg_SetValue_7(CGXDLMSValueEventArg* e, bool b_var);

// Only string
extern void CGXDLMSValueEventArg_SetValue_8(CGXDLMSValueEventArg* e, String* str_var);
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
extern int CGXDLMSObject_GetValue_1(CGXDLMSObject* p, CGXDLMSValueEventArg* e);
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
extern void String_append_int(String* s, int num);

extern void String_append_var_str(String* s, CGXDLMSVariant* var);

// Only integer
extern void String_append_var_int(String* s, int i_var);

// Only unsigned long
extern void String_append_var_ulong(String* s, unsigned long ul_var);
//////////////////////////////////////////////////////////////////////////////////////////

#endif /* OPTIMIZE_H_ */
