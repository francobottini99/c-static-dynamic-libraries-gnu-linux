/**
 * @file Plugin.h
 * @author Bottini, Franco Nicolas
 * @brief Encabezado de Plugin.c.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include <stdio.h>
#include <stdlib.h>

#include "cJSON.h"

char** getFileSystemsInfo(u_int32_t* n);

#endif //__PLUGIN_H__