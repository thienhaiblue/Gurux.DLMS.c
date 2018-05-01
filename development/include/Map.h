#ifndef MAP_H_
#define MAP_H_

#include <stddef.h>
#include <stdbool.h>

#include "Vector.h"

typedef void (*Item_c_FuncPtr)(void*, const void*);
typedef void (*Item_d_FuncPtr)(void*);

typedef struct
{
	Vector vec;
	unsigned int keySize;
	unsigned int itemSize;
	Item_c_FuncPtr k_c_FuncPtr;
	Item_d_FuncPtr k_d_FuncPtr;
	Item_c_FuncPtr i_c_FuncPtr;
	Item_d_FuncPtr i_d_FuncPtr;
} Map;

/**
 Constructor.
*/
extern void Map_(Map* m, unsigned int keySize, unsigned int itemSize,
		  	  	 Item_c_FuncPtr k_c_FuncPtr, Item_d_FuncPtr k_d_FuncPtr,
				 Item_c_FuncPtr i_c_FuncPtr, Item_d_FuncPtr i_d_FuncPtr);

/**
 Copy Constructor.
*/
extern void Map_2(Map* m, Map* src);

/**
 * Get size of the map
*/
#define Map_size(m) ((m)->vec.size)

/**
 * Get begin index of the map
*/
#define Map_begin(m) (0)

/**
 * Get end index of the map
*/
#define Map_end(m) ((m)->vec.size)

/**
 * Add new element to the map
*/
extern bool Map_insert(Map* m, const void* key, const void* item);

/**
 * Find element in the map
*/
extern unsigned int Map_find(Map* m, const void* key);

/**
 * Get the map's element at specific index
*/
extern void* Map_at(Map* m, unsigned int index);

#define Map_key_at(m, index) (Map_at((m), (index)))
#define Map_item_at(m, index) ((void*) ((char*) Map_at((m), (index)) + (m)->keySize))

#define Map_first_at Map_key_at
#define Map_second_at Map_item_at

/**
 * Remove from the map a elements at index
*/
extern unsigned int Map_erase(Map* m, unsigned int index);

/**
 * Free memory of map
*/
extern void Map_clear(Map* m);

#define Map_d Map_clear

extern void Map_copy_1(Map* m, Map* src);

#endif /* MAP_H_ */
