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

#ifndef GXSTANDARDOBISCODECOLLECTION_H
#define GXSTANDARDOBISCODECOLLECTION_H

#include "errorcodes.h"
#include "GXStandardObisCode.h"
#include "GXHelpers.h"
#include "Vector.h"
#include "String.h"
/////////////////////////////////////////////////////////////////////////////
// Obis Code Collection is used to save all default OBIS Codes.
/////////////////////////////////////////////////////////////////////////////
typedef struct // class CGXStandardObisCodeCollection : public std::vector<CGXStandardObisCode>
{
	///////////////////////////////////////////////////////////////////////////
    // (Vector<CGXStandardObisCode>)
    void **items;
    unsigned int capacity;
    unsigned int size;
    unsigned int elementSize;
    Item_c_FuncPtr _c_FuncPtr;
    Item_d_FuncPtr _d_FuncPtr;
} CGXStandardObisCodeCollection;
#define CGXStandardObisCodeCollection_push_back(v, element) Vector_push_back((Vector*) (v), (element))
#define CGXStandardObisCodeCollection_begin(v)              Vector_begin((Vector*) (v))
#define CGXStandardObisCodeCollection_end(v)                Vector_end((Vector*) (v))
#define CGXStandardObisCodeCollection_at(v, index)          Vector_at((Vector*) (v), (index))

//public
extern void CGXStandardObisCodeCollection_(CGXStandardObisCodeCollection *p);

extern bool CGXStandardObisCodeCollection_Find_1(CGXStandardObisCodeCollection *p, String ln, DLMS_OBJECT_TYPE objectType, CGXStandardObisCode* item);

extern bool CGXStandardObisCodeCollection_EqualsMask_2(String obisMask, String ln);

// Find Standard OBIS Code description.
extern bool CGXStandardObisCodeCollection_Find_2(CGXStandardObisCodeCollection *p, unsigned char* pObisCode, int IC, CGXStandardObisCode* tmp);

#endif //GXSTANDARDOBISCODECOLLECTION_H
