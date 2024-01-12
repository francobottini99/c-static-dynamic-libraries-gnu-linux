/**
 * @file JSON-Utils.h
 * @author Bottini, Franco Nicolas
 * @brief Encabezado de JSON-Utils.c.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __JSON_UTILITIES_H__
#define __JSON_UTILITIES_H__

#include "Lab2.h"
#include "cJSON.h"

char* getJsonMemInfo(MEM_INFO memInfo);
char* getJsonCpuInfo(CPU_INFO cpuInfo);
char* getJsonWordsArray(char** wordsArray, u_int32_t n);

#endif //__JSON_UTILITIES_H__