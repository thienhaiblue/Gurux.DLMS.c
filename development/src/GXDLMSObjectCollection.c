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

#include "../include/GXDLMSObjectCollection.h"
#include "../include/GXHelpers.h"
#include "../include/DLMSPort.h"
#include "../include/Optimize.h"

void CGXDLMSObjectCollection_(CGXDLMSObjectCollection *p)
{
	Vector_((Vector*) p, sizeof(CGXDLMSObject*), NULL, NULL);
}

void CGXDLMSObjectCollection_d(CGXDLMSObjectCollection *p)
{
    Vector_d((Vector*) p);
}

CGXDLMSObject* CGXDLMSObjectCollection_FindByLN_1(CGXDLMSObjectCollection *p, DLMS_OBJECT_TYPE type, String* ln)
{
    unsigned char tmp[6];
    GXHelpers_SetLogicalName_2(String_c_str(ln), tmp);
    for (unsigned int it = CGXDLMSObjectCollection_begin(p);
         it != CGXDLMSObjectCollection_end(p); ++it)
    {
        CGXDLMSObject **t_temp = CGXDLMSObjectCollection_at(p, it);
        if ((type == DLMS_OBJECT_TYPE_ALL)
         || ((*t_temp)->m_ObjectType == type))
        {
            if (memcmp(tmp, (*t_temp)->m_LN, 6) == 0)
            {
                return *t_temp;
            }
        }
    }
    return NULL;
}

CGXDLMSObject* CGXDLMSObjectCollection_FindByLN_2(CGXDLMSObjectCollection *p, DLMS_OBJECT_TYPE type, unsigned char ln[6])
{
    for (unsigned int it = CGXDLMSObjectCollection_begin(p);
         it != CGXDLMSObjectCollection_end(p); ++it)
    {
        CGXDLMSObject **t_temp = CGXDLMSObjectCollection_at(p, it);
        if ((type == DLMS_OBJECT_TYPE_ALL)
         || ((*t_temp)->m_ObjectType == type))
        {
            if (memcmp(ln, (*t_temp)->m_LN, 6) == 0)
            {
                return *t_temp;
            }
        }
    }
    return NULL;
}

CGXDLMSObject* CGXDLMSObjectCollection_FindBySN(CGXDLMSObjectCollection *p, unsigned short sn)
{
    for (unsigned int it = CGXDLMSObjectCollection_begin(p);
         it != CGXDLMSObjectCollection_end(p); ++it)
    {
        CGXDLMSObject **t_temp = CGXDLMSObjectCollection_at(p, it);
        if ((*t_temp)->m_SN == sn)
        {
            return *t_temp;
        }
    }
    return NULL;
}

void CGXDLMSObjectCollection_GetObjects(CGXDLMSObjectCollection *p, DLMS_OBJECT_TYPE type, CGXDLMSObjectCollection* items)
{
    for (unsigned int it = CGXDLMSObjectCollection_begin(p);
         it != CGXDLMSObjectCollection_end(p); ++it)
    {
        CGXDLMSObject **t_temp = CGXDLMSObjectCollection_at(p, it);
        if ((*t_temp)->m_ObjectType == type)
        {
            CGXDLMSObjectCollection_push_back(items, &(*t_temp));
        }
    }
}

// Do not use. Because it = Vector_push_back
//void CGXDLMSObjectCollection::push_back(CGXDLMSObject* item)
//{
//    std::vector<CGXDLMSObject*>::push_back(item);
//}

void CGXDLMSObjectCollection_Free(CGXDLMSObjectCollection *p)
{
    for (unsigned int it = CGXDLMSObjectCollection_begin(p);
         it != CGXDLMSObjectCollection_end(p); ++it)
    {
        CGXDLMSObject **t_temp = CGXDLMSObjectCollection_at(p, it);

        (*t_temp)->d(*t_temp);
        DLMSPort_free(*t_temp);
    }
    Vector_clear((Vector*) p);
}

String CGXDLMSObjectCollection_ToString(CGXDLMSObjectCollection *p)
{
    String sb;
    String_(&sb);

    String_append_1(&sb, "[");
    bool empty = true;
    for (unsigned int it = CGXDLMSObjectCollection_begin(p);
         it != CGXDLMSObjectCollection_end(p); ++it)
    {
        if (!empty)
        {
            String_append_1(&sb, ", ");
        }
        empty = false;
        CGXDLMSObject **t_temp = CGXDLMSObjectCollection_at(p, it);

        CGXDLMSVariant t_Variant = CGXDLMSObject_GetName(*t_temp);

        String_append_var_str(&sb, &t_Variant);

        CGXDLMSVariant_d(&t_Variant);
    }
    String_append_1(&sb, "]");

    return sb; // copy cons + des
}
