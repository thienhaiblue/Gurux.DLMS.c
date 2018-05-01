//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXATTRIBUTECOLLECTION_H
#define GXATTRIBUTECOLLECTION_H

#include "GXDLMSAttribute.h"
#include "Vector.h"

typedef struct // class CGXAttributeCollection : public std::vector<CGXDLMSAttribute>
{
    void **items;
    unsigned int capacity;
    unsigned int size;
    unsigned int elementSize; // = sizeof(CGXDLMSAttribute)
    Item_c_FuncPtr _c_FuncPtr;
    Item_d_FuncPtr _d_FuncPtr;
} CGXAttributeCollection;

#define CGXAttributeCollection_push_back(v, element) Vector_push_back((Vector*) (v), (element))
#define CGXAttributeCollection_begin(v)              Vector_begin((Vector*) (v))
#define CGXAttributeCollection_end(v)                Vector_end((Vector*) (v))
#define CGXAttributeCollection_at(v, index)          Vector_at((Vector*) (v), (index))
#define CGXAttributeCollection_clear(v)              Vector_clear((Vector*) (v))

extern void CGXAttributeCollection_(CGXAttributeCollection* p);
extern void CGXAttributeCollection_d(CGXAttributeCollection* p);

#endif //GXATTRIBUTECOLLECTION_H
