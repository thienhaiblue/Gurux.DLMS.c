#ifndef WSTRING_H_
#define WSTRING_H_

#include <stddef.h>

typedef struct
{
	wchar_t* c;
} WString;

extern void WString_(WString *s);

extern size_t WString_length(const WString *s);

extern WString* WString_append_1(WString *s, const wchar_t* str);

extern WString* WString_append_2(WString *s, const wchar_t* str, size_t count);

extern WString* WString_erase(WString *s, size_t pos, size_t len);

extern void WString_clear(WString *s);

extern const wchar_t* WString_c_str(WString *s);

#endif /* WSTRING_H_ */
