/**
 * @file Lab2.h
 * @author Bottini, Franco Nicolas
 * @brief Encabezado de Lab2.c.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LAB2_H__
#define __LAB2_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>

typedef struct MEM_INFO        
{      
    u_int64_t MemTotal;   
    u_int64_t MemFree;  
    u_int64_t MemAvailable;
    u_int64_t SwapTotal;
    u_int64_t SwapFree;
} MEM_INFO;

typedef struct CPU_INFO
{
    u_int32_t Cores;
    u_int32_t Threads;
    char ModelName[1024];
} CPU_INFO;

void getMemInfo(MEM_INFO* memInfo);
void getCpuInfo(CPU_INFO* cpuInfo);
void printMemoryInfo(void);
void printCpuInfo(void);
void freeWords(char** words, u_int32_t n);
void upperCasePrintWords(char** words, u_int32_t n);
char** getWords(char* file_name, u_int32_t* n);
void toUpperCaseWords(char** words, u_int32_t n);

#endif //__LAB2_H__