/**
 * @file JSON-Utils.c
 * @author Bottini, Franco Nicolas
 * @brief Implementa funciones que hacen uso de la libreria cJSON para generar cadenas con formato json.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/JSON-Utils.h"

/**
 * @brief Genera una cadena con formato json apartir de una estructura MEM_INFO que contiene informacion de la memoria.
 * 
 * @param memInfo estructura que contiene la informacion a formatear en json.
 * @return char* puntero a la cadena json resultante.
 */
char* getJsonMemInfo(MEM_INFO memInfo)
{
    cJSON *memInfoJson = NULL;

    cJSON *memTotal = NULL;
    cJSON *memFree = NULL;
    cJSON *memAvailable = NULL;
    cJSON *swapTotal = NULL;
    cJSON *swapFree = NULL;

    char *json = NULL;

    memInfoJson = cJSON_CreateObject(); //crea la estructura json a rellenar
    if (!memInfoJson) return NULL;

    /* A partir de cada elemento de la estructura memeInfo se crea una estructura json auxiliar 
    que se anexa a la estructura memInfoJson. En caso de producirse un error se retorna NULL*/

    memTotal = cJSON_CreateNumber(memInfo.MemTotal / 1024); // Creo el item cJSON con el formato adecuado
    if (!memTotal) { cJSON_Delete(memInfoJson); return NULL; }
    else cJSON_AddItemToObject(memInfoJson, "MemTotal", memTotal); // Anexo el item a la estructura principal

    memFree = cJSON_CreateNumber(memInfo.MemFree / 1024);
    if (!memFree) { cJSON_Delete(memInfoJson); return NULL; }
    else cJSON_AddItemToObject(memInfoJson, "MemFree", memFree);

    memAvailable = cJSON_CreateNumber(memInfo.MemAvailable / 1024);
    if (!memAvailable) { cJSON_Delete(memInfoJson); return NULL; }
    else cJSON_AddItemToObject(memInfoJson, "MemAvailable", memAvailable);

    swapTotal = cJSON_CreateNumber(memInfo.SwapTotal / 1024);
    if (!swapTotal) { cJSON_Delete(memInfoJson); return NULL; }
    else cJSON_AddItemToObject(memInfoJson, "SwapTotal", swapTotal);

    swapFree = cJSON_CreateNumber(memInfo.SwapFree / 1024);
    if (!swapFree) { cJSON_Delete(memInfoJson); return NULL; }
    else cJSON_AddItemToObject(memInfoJson, "SwapFree", swapFree);

    json = cJSON_Print(memInfoJson); // A partir de la estructura cJSON se crea la cadena con el formato deseado

    cJSON_Delete(memInfoJson); // Liberamos la memoria utilizada por la estructura

    return json;
}

/**
 * @brief Genera una cadena con formato json apartir de una estructura CPU_INFO que contiene informacion del CPU.
 * 
 * @param cpuInfo estructura que contiene la informacion a formatear en json.
 * @return char* puntero a la cadena json resultante.
 */
char* getJsonCpuInfo(CPU_INFO cpuInfo)
{
    cJSON *cpuInfoJson = NULL;

    cJSON *cores = NULL;
    cJSON *threads = NULL;
    cJSON *modelName = NULL;

    char *json = NULL;

    cpuInfoJson = cJSON_CreateObject();
    if (!cpuInfoJson) return NULL;

    cores = cJSON_CreateNumber(cpuInfo.Cores);
    if (!cores) { cJSON_Delete(cpuInfoJson); return NULL; }
    else cJSON_AddItemToObject(cpuInfoJson, "Cores", cores);

    threads = cJSON_CreateNumber(cpuInfo.Threads);
    if (!threads) { cJSON_Delete(cpuInfoJson); return NULL; }
    else cJSON_AddItemToObject(cpuInfoJson, "Threads", threads);

    modelName = cJSON_CreateString(cpuInfo.ModelName);
    if (!modelName) { cJSON_Delete(cpuInfoJson); return NULL; }
    else cJSON_AddItemToObject(cpuInfoJson, "ModelName", modelName);

    json = cJSON_Print(cpuInfoJson);

    cJSON_Delete(cpuInfoJson);

    return json;
}

/**
 * @brief Genera una cadena en formato json con una lista de palabras a partir de un array bidimensional.
 * 
 * @param wordsArray direccion de memoria del array bidimensional donde se encuentran las palabras a agregar a la lista json.
 * @param n numero de palabras en el array dado.
 * @return char* puntero a la cadena json resultante.
 */
char* getJsonWordsArray(char** wordsArray, u_int32_t n) 
{
    cJSON *wordsJson = NULL;

    cJSON *words = NULL;
    cJSON *word = NULL;

    char *json = NULL;

    wordsJson = cJSON_CreateObject();
    if (!wordsJson) return NULL;

    words = cJSON_CreateArray(); // Array json principal
    if (!words) { cJSON_Delete(wordsJson); return NULL; }
    else cJSON_AddItemToObject(wordsJson, "Words", words);

    for(u_int32_t i = 0; i < n; i++) // Itero completamente el array
    {
        word = cJSON_CreateString(wordsArray[i]); // Para cada palabra del arreglo creo una estructura cJSON adecuada
        if (!word) { cJSON_Delete(wordsJson); return NULL; }
        else cJSON_AddItemToArray(words, word); // Añado el elemento creado al array json principal
    }

    json = cJSON_Print(wordsJson); // Doy formato de cadena al array json de palabras

    cJSON_Delete(wordsJson);

    return json;
}