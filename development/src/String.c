#include "../include/String.h"
#include "../include/DLMSPort.h"

#include <string.h>

// Constructor
void String_(String *s)
{
    s->c = DLMSPort_malloc(1);
    if (s->c != NULL)
    {
        s->c[0] = '\0';
    }
}

// Copy Constructor
bool String_2(String* s, const String* src)
{
    return String_3(s, src->c);
}

bool String_3(String* s, const char* src)
{
    if (src == NULL)
    {
        s->c = NULL;
        return true;
    }

    s->c = DLMSPort_malloc(strlen(src) + 1);
    if (s->c == NULL)
    {
        return false;
    }
    else
    {
        strcpy(s->c, src);
        return true;
    }
}

void String_4(String* s, size_t n, char c)
{
    s->c = DLMSPort_malloc(n + 1);
    if (s->c != NULL)
    {
        memset(s->c, c, n);
        s->c[n] = '\0';
    }
}

size_t String_length(const String *s)
{
    if (s->c == NULL)
    {
        return 0;
    }
    else
    {
        return strlen(s->c);
    }
}

String* String_append_1(String *s, const char* str)
{
    return String_append_2(s, str, strlen(str));
}

String* String_append_2(String *s, const char* str, size_t count)
{
    size_t length = String_length(s);

    s->c = DLMSPort_realloc(s->c, length + count + 1);

    if (s->c != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            s->c[length + i] = str[i];
        }
        s->c[length + count] = '\0';
    }

    return s;
}

String* String_append_3(String *s, const String* str)
{
    return String_append_1(s, str->c);
}

String* String_append_4(String *s, const String* str, size_t subpos, size_t sublen)
{
    size_t sublength = String_length(str);

    if (subpos < sublength)
    {
        if (subpos + sublen <= sublength)
        {
            String_append_2(s, str->c + subpos, sublen);
        }
        else
        {
            String_append_1(s, str->c + subpos);
        }
    }

    return s;
}

String* String_erase(String *s, size_t pos, size_t len)
{
    size_t length = String_length(s);

    if (pos < length)
    {
        if (pos + len <= length)
        {
            for (int i = pos; i < length - len; i++)
            {
                s->c[i] = s->c[i + len];
            }
            s->c = DLMSPort_realloc(s->c, length - len + 1);
            s->c[length - len] = '\0';
        }
        else
        {
            s->c = DLMSPort_realloc(s->c, pos + 1);
            s->c[pos] = '\0';
        }
    }

    return s;
}

void String_clear(String *s)
{
    if (s->c != NULL)
    {
        DLMSPort_free(s->c);
        s->c = NULL;
    }
}

const char* String_c_str(String *s)
{
    return s->c;
}

// operator=
void String_copy_1(String* s, const String* src)
{
    String_copy_2(s, src->c);
}

void String_copy_2(String* s, const char* src)
{
    String_d(s);
    String_3(s, src);
}

int String_compare(String* s, const char* str)
{
    return strcmp(s->c, str);
}

size_t String_find_1(const String* s, char c, size_t pos)
{
    for (size_t i = pos; i < String_length(s); i++)
    {
        if (s->c[i] == c)
        {
            return i;
        }
    }

    return STRING_NPOS;
}

size_t String_find_2(const String* s, const char* str)
{
    for (size_t i = 0; i < String_length(s); i++)
    {
        for (size_t j = 0; j < strlen(str); j++)
        {
            if (s->c[i] == str[j])
            {
                return i;
            }
        }
    }

    return STRING_NPOS;
}

size_t String_find_first_of_1(const String* s, const String* str, size_t pos)
{
    for (size_t i = pos; i < String_length(s); i++)
    {
        for (size_t j = 0; j < String_length(str); j++)
        {
            if (s->c[i] == str->c[j])
            {
                return i;
            }
        }
    }

    return STRING_NPOS;
}

size_t String_rfind_1(const String* s, const String* str, size_t pos)
{
    int t_Start = (pos + 1 < String_length(s))? pos: (int) String_length(s) - 1;
    t_Start -= (int) String_length(str) - 1;

    for (int i = t_Start; i >= 0; i--)
    {
        bool isFind = true;
        for (size_t j = 0; j < String_length(str); j++)
        {
            if (s->c[i + j] != str->c[j])
            {
                isFind = false;
                break;
            }
        }
        if (isFind == true)
        {
            return i;
        }
    }

    return STRING_NPOS;
}

String* String_replace_1(String* s, size_t pos, size_t len, const String* str)
{
	size_t length = String_length(s);

    if (pos < length)
    {
    	int t_end = (pos + len <= length)? (pos + len): length;
    	String resultStr;
    	String_(&resultStr);

    	String_append_4(&resultStr, s, 0, pos);
    	String_append_3(&resultStr, str);
    	String_append_1(&resultStr, s->c + t_end);

    	String_d(s);
    	*s = resultStr;
    }

    return s;
}

void String_resize(String* s, size_t n)
{
    if (n <= String_size(s))
    {
        s->c = DLMSPort_realloc(s->c, n + 1);
        s->c[n] = '\0';
    }
}

String String_substr_1(const String* s, size_t pos, size_t len)
{
    String t_Str;
    String_(&t_Str);

    String_append_4(&t_Str, s, pos, len);

    return t_Str; // copy cons + des
}

String String_substr_2(const String* s, size_t pos)
{
    return String_substr_1(s, pos, STRING_NPOS);
}

void String_v_c(void* s1, const void* s2)
{
    String_2((String*) s1, (String*) s2);
}

extern void String_v_d(void* s)
{
    String_d((String*) s);
}
