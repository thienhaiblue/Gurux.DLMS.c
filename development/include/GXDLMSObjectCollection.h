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

#ifndef GXDLMSOBJECTCOLLECTION_H
#define GXDLMSOBJECTCOLLECTION_H

#include "Vector.h"
#include "GXDLMSObject.h"

typedef struct CGXDLMSObjectCollection // class CGXDLMSObjectCollection : public std::vector<CGXDLMSObject*>
{
	///////////////////////////////////////////////////////////////////////////
    // (Vector<CGXDLMSObject*>)
    void **items;
    unsigned int capacity;
    unsigned int size;
    unsigned int elementSize;
    Item_c_FuncPtr _c_FuncPtr;
    Item_d_FuncPtr _d_FuncPtr;
} CGXDLMSObjectCollection;
#define CGXDLMSObjectCollection_push_back(v, element) Vector_push_back((Vector*) (v), (element))
#define CGXDLMSObjectCollection_begin(v)              Vector_begin((Vector*) (v))
#define CGXDLMSObjectCollection_end(v)                Vector_end((Vector*) (v))
#define CGXDLMSObjectCollection_at(v, index)          Vector_at((Vector*) (v), (index))
#define CGXDLMSObjectCollection_size(v)               Vector_size((Vector*) (v))
#define CGXDLMSObjectCollection_clear(v)              Vector_clear((Vector*) (v))

extern void CGXDLMSObjectCollection_(CGXDLMSObjectCollection *p);

extern void CGXDLMSObjectCollection_d(CGXDLMSObjectCollection *p);

extern CGXDLMSObject* CGXDLMSObjectCollection_FindByLN_1(CGXDLMSObjectCollection *p, DLMS_OBJECT_TYPE type, String* ln);

extern CGXDLMSObject* CGXDLMSObjectCollection_FindByLN_2(CGXDLMSObjectCollection *p, DLMS_OBJECT_TYPE type, unsigned char ln[6]);

extern CGXDLMSObject* CGXDLMSObjectCollection_FindBySN(CGXDLMSObjectCollection *p, unsigned short sn);

extern void CGXDLMSObjectCollection_GetObjects(CGXDLMSObjectCollection *p, DLMS_OBJECT_TYPE type, CGXDLMSObjectCollection* items);

// Do not use. Because it = Vector_push_back
//extern void CGXDLMSObjectCollection_push_back(CGXDLMSObjectCollection *p, CGXDLMSObject* item);

extern void CGXDLMSObjectCollection_Free(CGXDLMSObjectCollection *p);

extern String CGXDLMSObjectCollection_ToString(CGXDLMSObjectCollection *p);

#endif //GXDLMSOBJECTCOLLECTION_H
