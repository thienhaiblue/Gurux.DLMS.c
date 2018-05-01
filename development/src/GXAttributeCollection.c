/*
 * GXAttributeCollection.c
 *
 *  Created on: Mar 4, 2018
 *      Author: admin
 */

#include "../include/GXAttributeCollection.h"

void CGXAttributeCollection_(CGXAttributeCollection* p)
{
    Vector_((Vector*) p, sizeof(CGXDLMSAttribute), NULL, NULL);
}

void CGXAttributeCollection_d(CGXAttributeCollection* p)
{
    Vector_d((Vector*) p);
}
