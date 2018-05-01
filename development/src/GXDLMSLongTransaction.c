/*
 * GXDLMSLongTransaction.c
 *
 *  Created on: Mar 4, 2018
 *      Author: admin
 */

#include "../include/GXDLMSLongTransaction.h"

void CGXDLMSLongTransaction_d(CGXDLMSLongTransaction *p)
{
    CGXDLMSValueEventCollection_d(&p->m_Targets);
    CGXByteBuffer_d(&p->m_Data);
}

void CGXDLMSLongTransaction_(CGXDLMSLongTransaction *p, CGXDLMSValueEventCollection* targets,
                             DLMS_COMMAND command, CGXByteBuffer* data)
{
    CGXDLMSValueEventCollection_(&p->m_Targets);
    CGXByteBuffer_1(&p->m_Data);

    // p->m_Targets.insert(p->m_Targets.end(), targets.begin(), targets.end());
    for (unsigned int it = CGXDLMSValueEventCollection_begin(targets);
         it != CGXDLMSValueEventCollection_end(targets); ++it)
    {
        CGXDLMSValueEventCollection_push_back(&(p->m_Targets),
                                              CGXDLMSValueEventCollection_at(targets,it));
    }
    CGXDLMSValueEventCollection_clear(targets);
    p->m_Command = command;
    CGXByteBuffer_Set_2(&(p->m_Data), data, data->m_Position, -1);
}

Vector* CGXDLMSLongTransaction_GetTargets(CGXDLMSLongTransaction *p) // std::vector<CGXDLMSValueEventArg*>&
{
    return (Vector*) &(p->m_Targets);
}

CGXByteBuffer* CGXDLMSLongTransaction_GetData(CGXDLMSLongTransaction *p)
{
    return &(p->m_Data);
}

void CGXDLMSLongTransaction_SetData(CGXDLMSLongTransaction *p, CGXByteBuffer* value)
{
    CGXByteBuffer_Clear(&(p->m_Data));
    CGXByteBuffer_Set_2(&(p->m_Data), value, value->m_Position, -1);
}
