/*
 * Pair.c
 *
 *  Created on: Feb 27, 2018
 *      Author: sontn
 */

#include "../include/Pair.h"
#include "../include/DLMSPort.h"

#include <string.h>

void Pair_(Pair* p, unsigned int fSize, unsigned int sSize,
		   Item_c_FuncPtr f_c_FuncPtr, Item_d_FuncPtr f_d_FuncPtr,
		   Item_c_FuncPtr s_c_FuncPtr, Item_d_FuncPtr s_d_FuncPtr,
		   void* f, void* s)
{
    p->firstSize = fSize;
    p->secondSize = sSize;

    p->f_c_FuncPtr = f_c_FuncPtr;
    p->f_d_FuncPtr = f_d_FuncPtr;
    p->s_c_FuncPtr = s_c_FuncPtr;
    p->s_d_FuncPtr = s_d_FuncPtr;

    p->first = DLMSPort_malloc(p->firstSize);
    if (p->first != NULL)
    {
        p->second = DLMSPort_malloc(p->secondSize);
        if (p->second != NULL)
        {
        	if (p->f_c_FuncPtr == NULL)
        	{
        		memcpy(p->first, f, p->firstSize);
        	}
        	else
        	{
        		p->f_c_FuncPtr(p->first, f);
        	}

        	if (p->s_c_FuncPtr == NULL)
        	{
        		memcpy(p->second, s, p->secondSize);
        	}
        	else
        	{
        		p->s_c_FuncPtr(p->second, s);
        	}
        }
        else
        {
            DLMSPort_free(p->first);
            p->first = NULL;
        }
    }
    else
    {
    	p->second = NULL;
    }
}

void Pair_2(Pair* p, Pair *src)
{
	Pair_(p, src->firstSize, src->secondSize,
	      src->f_c_FuncPtr, src->f_d_FuncPtr,
		  src->s_c_FuncPtr, src->s_d_FuncPtr,
		  src->first, src->second);
}

void Pair_copy(Pair* p, Pair *src)
{
    Pair_d(p);
    Pair_2(p, src);
}

void Pair_d(Pair* p)
{
    if (p->first != NULL)
    {
    	if (p->f_d_FuncPtr != NULL)
    	{
    		p->f_d_FuncPtr(p->first);
    	}
        DLMSPort_free(p->first);
        p->first = NULL;
    }
    if (p->second != NULL)
    {
    	if (p->s_d_FuncPtr != NULL)
    	{
    		p->s_d_FuncPtr(p->second);
    	}
        DLMSPort_free(p->second);
        p->second = NULL;
    }
}

void Pair_v_c(void* p1, const void* p2)
{
	Pair_2((Pair*) p1, (Pair*) p2);
}

void Pair_v_d(void* p)
{
	Pair_d((Pair*) p);
}

