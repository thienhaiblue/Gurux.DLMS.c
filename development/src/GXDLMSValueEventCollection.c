/*
 * GXDLMSValueEventCollection.c
 *
 *  Created on: Mar 4, 2018
 *      Author: admin
 */

#include "../include/GXDLMSValueEventCollection.h"

void CGXDLMSValueEventCollection_(CGXDLMSValueEventCollection *p)
{
    Vector_((Vector*) p, sizeof(CGXDLMSValueEventArg*), NULL, NULL);
}

void CGXDLMSValueEventCollection_d(CGXDLMSValueEventCollection *p)
{
    for(unsigned i = CGXDLMSValueEventCollection_begin(p);
        i != CGXDLMSValueEventCollection_end(p); ++i)
    {
        CGXDLMSValueEventArg** it = CGXDLMSValueEventCollection_at(p, i);

        CGXDLMSValueEventArg_d(*it);
        DLMSPort_free(*it);
    }
    CGXDLMSValueEventCollection_clear(p);
}
