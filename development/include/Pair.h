/*
 * Pair.h
 *
 *  Created on: Feb 26, 2018
 *      Author: son
 */

#ifndef PAIR_H_
#define PAIR_H_

typedef void (*Item_c_FuncPtr)(void*, const void*);
typedef void (*Item_d_FuncPtr)(void*);

typedef struct Pair
{
    void* first;
    void* second;
    unsigned int firstSize;
    unsigned int secondSize;
    Item_c_FuncPtr f_c_FuncPtr;
    Item_d_FuncPtr f_d_FuncPtr;
    Item_c_FuncPtr s_c_FuncPtr;
    Item_d_FuncPtr s_d_FuncPtr;
} Pair;

#define Pair_first(p) ((p)->first)
#define Pair_second(p) ((p)->second)

extern void Pair_(Pair* p, unsigned int fSize, unsigned int sSize,
				  Item_c_FuncPtr f_c_FuncPtr, Item_d_FuncPtr f_d_FuncPtr,
				  Item_c_FuncPtr s_c_FuncPtr, Item_d_FuncPtr s_d_FuncPtr,
				  void* f, void* s);

extern void Pair_2(Pair* p, Pair *src);

extern void Pair_copy(Pair* p, Pair *src);

extern void Pair_d(Pair* p);

extern void Pair_v_c(void* p1, const void* p2);
extern void Pair_v_d(void* p);

#endif /* PAIR_H_ */
