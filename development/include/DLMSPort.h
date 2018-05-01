/*
 * DLMSPort.h
 *
 *  Created on: Feb 1, 2018
 *      Author: sontn
 */

#ifndef DLMSPORT_H_
#define DLMSPORT_H_

#if defined(__unix__) || defined(_WIN32) || defined(_WIN64) // Port for Window and Linux

#include <stdio.h>
#include <stdlib.h>

#define DLMSPort_printf printf
#define DLMSPort_sprintf sprintf
#define DLMSPort_sprintf_s sprintf_s
#define DLMSPort_snprintf snprintf
#define DLMSPort_sscanf sscanf
#define DLMSPort_sscanf_s sscanf_s

#define DLMSPort_malloc malloc
#define DLMSPort_realloc realloc
#define DLMSPort_calloc calloc
#define DLMSPort_free free

typedef FILE DLMSPort_FILE;
#define DLMSPort_wa "wa"
#define DLMSPort_fopen fopen
extern void DLMSPort_fwrite(DLMSPort_FILE* file, const void* ptr, size_t len);
#define DLMSPort_fclose fclose

#else

#error "No Supported Port"

#endif

#endif /* DLMSPORT_H_ */
