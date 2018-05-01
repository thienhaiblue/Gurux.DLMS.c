/*
 * WString.c
 *
 *  Created on: Feb 27, 2018
 *      Author: son
 */

#include "../include/WString.h"
#include "../include/DLMSPort.h"

size_t WString_length(const WString *s)
{
    if (s->c == NULL)
    {
        return 0;
    }
    else
    {
        size_t tmp = 0;

        while (s->c[tmp] != 0)
        {
            tmp++;
        }

        return tmp;
    }
}

WString* WString_append_2(WString *s, const wchar_t* str, size_t count)
{
    size_t length = WString_length(s);

    s->c = DLMSPort_realloc(s->c, sizeof(wchar_t) * (length + count + 1));

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
