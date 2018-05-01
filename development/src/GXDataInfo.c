/*
 * GXDataInfo.c
 *
 *  Created on: Feb 23, 2018
 *      Author: admin
 */

#include "../include/GXDataInfo.h"

//Clear settings.
void CGXDataInfo_Clear(CGXDataInfo *p)
{
    p->m_Index = 0;
    p->m_Count = 0;
    p->m_Type = DLMS_DATA_TYPE_NONE;
    p->m_Compleate = true;
}

//Constructor.
void CGXDataInfo_(CGXDataInfo *p)
{
    CGXDataInfo_Clear(p);
}

