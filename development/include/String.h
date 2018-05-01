#ifndef STRING_H_
#define STRING_H_

#include <stddef.h>
#include <stdbool.h>

#define STRING_NPOS ((size_t) (-1))

typedef struct
{
    char* c;
} String;

extern void String_(String *s);

// Copy constructor
extern bool String_2(String* s, const String* src);
extern bool String_3(String* s, const char* src);

extern void String_4(String* s, size_t n, char c);

// Destructor
#define String_d String_clear

extern size_t String_length(const String *s);

#define String_size String_length

#define String_begin(v) (0)
#define String_end String_length

#define String_at(s, i) ((s)->c + (i))

extern String* String_append_1(String *s, const char* str);

extern String* String_append_2(String *s, const char* str, size_t count);

extern String* String_append_3(String *s, const String* str);

extern String* String_append_4(String *s, const String* str, size_t subpos, size_t sublen);

extern String* String_erase(String *s, size_t pos, size_t len);

extern void String_clear(String *s);

extern const char* String_c_str(String *s);

// operator=
extern void String_copy_1(String* s, const String* src);
extern void String_copy_2(String* s, const char* src);

extern int String_compare(String* s, const char* str);

extern size_t String_find_1(const String* s, char c, size_t pos);
extern size_t String_find_2(const String* s, const char* str);

extern size_t String_find_first_of_1(const String* s, const String* str, size_t pos);

extern size_t String_rfind_1(const String* s, const String* str, size_t pos);

extern String* String_replace_1(String* s, size_t pos, size_t len, const String* str);

extern void String_resize(String* s, size_t n);

extern String String_substr_1(const String* s, size_t pos, size_t len);
extern String String_substr_2(const String* s, size_t pos);

extern void String_v_c(void* s1, const void* s2);
extern void String_v_d(void* s);

#endif /* STRING_H_ */
