#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>
#include <stdbool.h>

#define VECTOR_CAP 20

typedef void (*Item_c_FuncPtr)(void*, const void*);
typedef void (*Item_d_FuncPtr)(void*);

typedef struct Vector
{
    void **items;
    unsigned int capacity;
    unsigned int size;
    unsigned int elementSize;
    Item_c_FuncPtr _c_FuncPtr;
    Item_d_FuncPtr _d_FuncPtr;
} Vector;

/**
 * Constructor.
*/
extern void Vector_(Vector* v, unsigned int elementSize,
                    Item_c_FuncPtr _c_FuncPtr, Item_d_FuncPtr _d_FuncPtr);

/**
 * Copy Constructor.
*/
extern void Vector_2(Vector* v, Vector* src);

/**
 * Get size of the vector
*/
#define Vector_size(v) ((v)->size)

/**
 * Get begin index of the vector
*/
#define Vector_begin(v) (0)

/**
 * Get end index of the vector
*/
#define Vector_end(v) ((v)->size)

/**
 * Add new element to the vector
*/
extern bool Vector_push_back(Vector *v, void *element);

/**
 * Get the vector's element at specific index
*/
extern void* Vector_at(Vector *v, unsigned int index);

/**
 * Remove from the vector a range of elements [first, last)
*/
extern unsigned int Vector_erase(Vector *v, unsigned int first, unsigned int last);

/**
 * Free memory of vector
*/
extern void Vector_clear(Vector* v);

#define Vector_d Vector_clear

extern void Vector_copy_1(Vector* v, Vector* src);

extern void Vector_v_c(void* v1, const void* v2);
extern void Vector_v_d(void* v);

#endif /* VECTOR_H_ */
