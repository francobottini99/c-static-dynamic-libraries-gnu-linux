/**
 * @file Lab3.c
 * @author Bottini, Franco Nicolas
 * @brief Se implementa la resolucion de todos los ejercicios del laboratiorio 3, Sistemas Operativos I.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/Lab3.h"

int main(int argc, char* argv[])
{    
    if(argc < 2) //Si se ejecuta el programa sin argumentos, muestro informacion de uso valido
    {
        fprintf(stderr, "Requires arguments:\n");
        fprintf(stderr, "    -a (-j): excute Lab2 excersie 1. Optional -j: result ouput in json format.\n");
        fprintf(stderr, "    -s (-j): excute Lab2 excersie 2. Optional -j: result ouput in json format.\n");
        fprintf(stderr, "    -d     : [plugin function] show file system information in json format.\n");
        exit(EXIT_FAILURE);
    }

    if(argc > 3) //Verifico que no se supere el numero maximo de argumentos
    {
        fprintf(stderr, "Invalid number of arguments (must be less than 3)!\n");
        exit(EXIT_FAILURE);
    }

    const char* valid_arguments = "-a -s -j -d"; //Listado de argumentos validos para el programa
    for(u_int8_t i = 1; i < argc; i++)
    {
        if(!strstr(valid_arguments, argv[i])) //Verifica que cada uno de los argumentos dados se corresponda con uno valido del listado
        {
            fprintf(stderr, "Invalid arguments input !\n");
            exit(EXIT_FAILURE);
        }
    }

    //Determina que accion va a ejecutar el programa dependiendo del primer argumento introducido
    if(strstr(argv[1], "-d"))
        function_d(argv[2]);
    else if(strstr(argv[1], "-a"))
        function_a(argv[2]);
    else if(strstr(argv[1], "-s"))
        function_s(argv[2]);
    else
    {
        fprintf(stderr, "-j can only be used as secondary argument !\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/**
 * @brief Ejecuta el ejercicio 1 del laboratorio 2.
 * 
 *  Imprime en consola información acerca del CPU y la memoria. Ademas,
 *  si recibe como parametro "-j" muestra dicha información en formato json.
 * 
 * @param arg argumentos de entrada extras (ej: "-j").
 */
void function_a(char* arg)
{
    if(!arg) //Si no hay argumentos extra ejecuta el ejercicio 1 del Lab2
    {
        printCpuInfo();
        printMemoryInfo();
    }
    else 
    {
        if(strcmp(arg, "-j")) //Si el argumento extra no es valido finaliza con error
        {
            fprintf(stderr, "Invalid argument combination !\n");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            MEM_INFO memInfo;
            CPU_INFO cpuInfo;

            getMemInfo(&memInfo);
            getCpuInfo(&cpuInfo);

            //Muestra la informacion del ejercicio 1 del Lab2 con formato Json
            printf("%s\n\n", getJsonMemInfo(memInfo));
            printf("%s\n", getJsonCpuInfo(cpuInfo));
        }
    }
}

/**
 * @brief Ejecuta el ejercicio 2 del laboratorio 2.
 * 
 *  Imprime por consola todas las palabras del archivo /proc/version en mayusculas. 
 *  Ademas, si recibe como parametro "-j" muestra dicha información en formato json.
 * 
 * @param arg argumentos de entrada extras (ej: "-j").
 */
void function_s(char* arg)
{
    if(!arg) //Si no hay argumentos extra ejecuta el ejercicio 2 del Lab2
    {
        u_int32_t n;
        char** words = getWords("/proc/version", &n); 

        upperCasePrintWords(words, n);

        freeWords(words, n);
    }
    else
    {
        if(strcmp(arg, "-j")) //Si el argumento extra no es valido finaliza con error
        {
            fprintf(stderr, "Invalid argument combination !\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            u_int32_t n;
            char** words = getWords("/proc/version", &n); 

            toUpperCaseWords(words, n);
            
            printf("%s\n", getJsonWordsArray(words, n)); //Muestra la informacion del ejercicio 2 del Lab2 con formato Json
            
            freeWords(words, n);
        }
    }
}

/**
 * @brief Imprime por consola informacion acerca de los sistemas de archivos soportados por
 *        el kernel del sistema operativo, haciendo uso de la libreria dinamica "libplugin.so".
 * 
 * @param arg argumentos de entrada extras (ej: "-j").
 */
void function_d(char* arg)
{
    if(arg) //Esta funcion no admite argumentos extra. En caso de haberlos finaliza con error
    {
        fprintf(stderr, "Invalid argument combination !\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        void *libhandle = dlopen("libplugin.so", RTLD_LAZY); //Carga la libreria del plugin

        if (!libhandle) 
        {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        char** (*getFileSystemsInfo) (u_int32_t*);

        *(void**) (&getFileSystemsInfo) = dlsym(libhandle, "getFileSystemsInfo"); //Carga el simbolos a utilizar

        u_int32_t n;
        char** words = getFileSystemsInfo(&n);
    
        printf("%s\n", getJsonWordsArray(words, n)); //Muestra la informacion solicitado en el ejercicio 3 del Lab3 haciendo uso de una funcion implementada en la libreria dinamica de plugin
            
        freeWords(words, n);
        dlclose(libhandle);
    }
}