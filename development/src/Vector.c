#include <string.h>

#include "../include/Vector.h"
#include "../include/DLMSPort.h"

void Vector_(Vector* v, unsigned int elementSize,
             Item_c_FuncPtr _c_FuncPtr, Item_d_FuncPtr _d_FuncPtr)
{
    v->capacity = 0;
    v->size = 0;
    v->elementSize = elementSize;
    v->_c_FuncPtr = _c_FuncPtr;
    v->_d_FuncPtr = _d_FuncPtr;
    v->items = DLMSPort_malloc(sizeof(void*) * VECTOR_CAP);
    if (v->items != NULL)
    {
        v->capacity = VECTOR_CAP;
    }
}

void Vector_2(Vector* v, Vector* src)
{
    Vector_(v, src->elementSize, src->_c_FuncPtr, src->_d_FuncPtr);
    for (int i = 0; i < src->size; i++)
    {
        if (Vector_push_back(v, Vector_at(src, i)) == false)
        {
            break;
        }
    }
}

bool Vector_push_back(Vector *v, void *element)
{
    void** temp;

    if (v->size == v->capacity)
    {
        temp = DLMSPort_malloc(sizeof(void*) * (v->capacity + VECTOR_CAP));
        if (temp != NULL)
        {
            memcpy(temp, v->items, sizeof(void*) * v->capacity);
            DLMSPort_free(v->items);
            v->items = temp;
            v->capacity += VECTOR_CAP;
        }
        else
        {
            return false; // No memory for alloc array
        }
    }

    if (v->size < v->capacity)
    {
        v->items[v->size] = DLMSPort_malloc(v->elementSize);

        if (v->items[v->size] != NULL)
        {
            if (v->_c_FuncPtr == NULL)
            {
                memcpy(v->items[v->size], element, v->elementSize);
            }
            else
            {
                v->_c_FuncPtr(v->items[v->size], element);
            }

            v->size++;
        }
        else
        {
            return false; // No memory for alloc element
        }
    }

    return true;
}

void* Vector_at(Vector *v, unsigned int index)
{
    if (index >= v->size)
    {        
        return NULL;
    }
    return v->items[index];
}

unsigned int Vector_erase(Vector *v, unsigned int first, unsigned int last)
{
    unsigned int t_last;
    unsigned int t_capacity;

    if (first >= v->size)
    {
        return v->size;
    }
    else
    {
        if (last <= first)
        {
            return v->size;
        }
        else
        {
            // Free elements
            t_last = (last >= v->size)? v->size: last;
            for (int i = first; i < t_last; i++)
            {
                if (v->_d_FuncPtr != NULL)
                {
                    v->_d_FuncPtr(v->items[i]);
                }
                DLMSPort_free(v->items[i]);
            }

            // Ship elements
            v->size -= t_last - first;
            for (int i = first; i < v->size; i++)
            {
                v->items[i] = v->items[i + t_last - first];
            }

            // Realloc
            t_capacity = v->capacity;
            while (v->size < t_capacity - VECTOR_CAP)
            {
                t_capacity -= VECTOR_CAP;
            }
            if (t_capacity < v->capacity)
            {
                v->capacity = t_capacity;
                v->items = DLMSPort_realloc(v->items, sizeof(void*) * v->capacity);
            }

            return (t_last - 1);
        }
    }
}

void Vector_clear(Vector *v)
{
    if (v->capacity > 0)
    {
        for (int i = 0; i < v->size; i++)
        {
            if (v->_d_FuncPtr != NULL)
            {
                v->_d_FuncPtr(v->items[i]);
            }
            DLMSPort_free(v->items[i]);
        }
        DLMSPort_free(v->items);
    }
    v->items = NULL;
    v->capacity = 0;
    v->size = 0;
}

void Vector_copy_1(Vector* v, Vector* src)
{
    Vector_clear(v);
    Vector_2(v, src);
}

void Vector_v_c(void* v1, const void* v2)
{
    Vector_2((Vector*) v1, (Vector*) v2);
}

void Vector_v_d(void* v)
{
    Vector_d((Vector*) v);
}
