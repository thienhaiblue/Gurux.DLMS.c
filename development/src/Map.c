#include <string.h>

#include "../include/Map.h"
#include "../include/DLMSPort.h"

void Map_(Map* m, unsigned int keySize, unsigned int itemSize,
		  Item_c_FuncPtr k_c_FuncPtr, Item_d_FuncPtr k_d_FuncPtr,
		  Item_c_FuncPtr i_c_FuncPtr, Item_d_FuncPtr i_d_FuncPtr)
{
	m->keySize = keySize;
	m->itemSize = itemSize;

	m->k_c_FuncPtr = k_c_FuncPtr;
	m->k_d_FuncPtr = k_d_FuncPtr;
	m->i_c_FuncPtr = i_c_FuncPtr;
	m->i_d_FuncPtr = i_d_FuncPtr;

	Vector_(&(m->vec), keySize + itemSize, NULL, NULL);
}

void Map_2(Map* m, Map* src)
{
    m->keySize = src->keySize;
    m->itemSize = src->itemSize;

    m->k_c_FuncPtr = src->k_c_FuncPtr;
    m->k_d_FuncPtr = src->k_d_FuncPtr;
    m->i_c_FuncPtr = src->i_c_FuncPtr;
    m->i_d_FuncPtr = src->i_d_FuncPtr;

    Vector_(&(m->vec), src->vec.elementSize, NULL, NULL);

    for (unsigned int i = Vector_begin(&(src->vec)); i != Vector_end(&(src->vec)); i++)
    {
    	void* it = Vector_at(&(src->vec), i);

    	Map_insert(m, it, (char*)it + src->keySize);
    }
}

bool Map_insert(Map* m, const void* key, const void* item)
{
	bool result;

	void* mapItem = DLMSPort_malloc(m->keySize + m->itemSize);

	if (mapItem == NULL)
	{
		return false; // No memory for alloc temp map item
	}
	else
	{
		if (m->k_c_FuncPtr == NULL)
		{
			memcpy(mapItem, key, m->keySize);
		}
		else
		{
			m->k_c_FuncPtr(mapItem, key);
		}

		if (m->i_c_FuncPtr == NULL)
		{
			memcpy((char*) mapItem + m->keySize, item, m->itemSize);
		}
		else
		{
			m->i_c_FuncPtr((char*) mapItem + m->keySize, item);
		}

		result = Vector_push_back(&(m->vec), mapItem);
		DLMSPort_free(mapItem);

		return result;
	}
}

unsigned int Map_find(Map* m, const void* key)
{
	for (unsigned int i = Map_begin(m); i != Map_end(m); i++)
	{
		if (memcmp(Map_at(m, i), key, m->keySize) == 0)
		{
			return i;
		}
	}

	return Map_end(m);
}

void* Map_at(Map* m, unsigned int index)
{
    if (index >= Map_end(m))
    {
        return NULL;
    }
    return m->vec.items[index];
}

unsigned int Map_erase(Map* m, unsigned int index)
{
	if (m->k_d_FuncPtr != NULL)
	{
		m->k_d_FuncPtr(m->vec.items[index]);
	}

	if (m->i_d_FuncPtr != NULL)
	{
		m->i_d_FuncPtr((char*) m->vec.items[index] + m->keySize);
	}

	return Vector_erase(&(m->vec), index, index + 1);
}

void Map_clear(Map* m)
{
    for (unsigned int i = Vector_begin(&(m->vec)); i != Vector_end(&(m->vec)); i++)
    {
    	if (m->k_d_FuncPtr != NULL)
    	{
    		m->k_d_FuncPtr(m->vec.items[i]);
    	}

    	if (m->i_d_FuncPtr != NULL)
    	{
    		m->i_d_FuncPtr((char*) m->vec.items[i] + m->keySize);
    	}
    }

	Vector_clear(&(m->vec));
}

void Map_copy_1(Map* m, Map* src)
{
    Map_clear(m);
    Map_2(m, src);
}
