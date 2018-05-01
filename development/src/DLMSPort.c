/*
 * DLMSPort.c
 *
 *  Created on: Feb 23, 2018
 *      Author: admin
 */

#include "../include/DLMSPort.h"

void DLMSPort_fwrite(DLMSPort_FILE* file, const void* ptr, size_t len)
{
    fwrite(ptr, 1, len, file);
}
