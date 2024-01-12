/**
 * @file Lab2.c
 * @author Bottini, Franco Nicolas
 * @brief Funciones auxiliares que implementan la resolucion de los ejercicios 1 y 2 del laboratorio 2, Sistemas Operativos I.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/Lab2.h"

/**
 * @brief Obtiene todas las palabras de un archivo dado.
 * 
 * Genera un array bidimensional dinamico con todas las palabras contenidas en el archivo 
 * especificado. Minimiza la memoria empleada para el almacenamiento de dichas palabras.
 * 
 * @param file_name archivo sobre del cual se quieren obtener las palabras.
 * @param n puntero donde se va a almacenar el numero de palabras obtenidas.
 * @return char** direccion de memoria del array bidimensional donde se encuentran las palabras obtenidas.
 */
char** getWords(char* file_name, u_int32_t* n)
{
    u_int32_t w_count = 0;
    u_int32_t c_count = 0;

    char last = ' ';
    char c;

  	FILE* file;

    char** words = malloc(sizeof(char*)); // En primera instancia se reserva memoria para alamacenar una palabra
    words[w_count] = malloc(sizeof(char)); // Se reserva memoria para al menos un caracter en la primera palabra

	file = fopen(file_name, "r");
    
  	if(file == NULL) 
		exit(EXIT_FAILURE);

    while ((c = (char)fgetc(file)) != EOF) // Se recorre todo el documento caracter por caracter
    {
        if(c == ' ' && last != ' ')  // Verifica si el digito actual es un espacio y el anterior no
        {
            words[w_count][c_count] = '\0'; // En caso de ser asi termina la palabra con el caracter de finalizacion

            w_count++;
            c_count = 0;

            words = realloc(words, (w_count + 1) * sizeof(char*)); // Se redimenciona la memoria reservada para almacenar una nueva palabra
            words[w_count] = malloc(sizeof(char)); // Se reserva espacio para el primer caracter de la nueva palabra
        } 
        else
        {
            if(c != '(' && c != ')') // Ignoramos los parentesis
            {
                words[w_count][c_count] = c; // Agrega el caracter a la palabra actual
                c_count++;
                words[w_count] = realloc(words[w_count], (c_count + 1) * sizeof(char)); // Se redimenciona la memoria reservada para la plabra actual para almacenar el siguiente caracter
            }
        }

        last = c;
    }

    words[w_count][c_count] = '\0'; // Finalizamos la ultima palabra con el caracter correspondiente

    *n = w_count; // Guardamos el numero de palabras obtenidas

  	fclose(file);

    return words;
}

/**
 * @brief Libera el espacio de memoria donde se almacenan las palabras.
 * 
 * @param words direccion de memoria donde se encuenta el array bidimensional de palabras.
 * @param n numero de palabras almacenadas en el array.
 */
void freeWords(char** words, u_int32_t n)
{
    for(int i = 0; i < n; i++) // Recorre todas las palabras del array
    {
        free(words[i]);
    }

    free(words);
}

/**
 * @brief Imprime por consola las palabras de un array en mayusculas (No altera el array de palabras). 
 * 
 * @param words direccion de memoria donde se encuenta el array bidimensional de palabras.
 * @param n numero de palabras almacenadas en el array.
 */
void upperCasePrintWords(char** words, u_int32_t n) 
{
    printf("- UPPER CASE WORDS (/proc/version):\n");
    
    for(int i = 0; i < n; i++)
    {
        printf("    ");

        for(int j = 0; words[i][j] != '\0'; j++) // Recorre todos los caracteres dentro de una palabra
		{ 
			printf("%c", toupper(words[i][j]));
        }

        printf("\n");
    }

    printf("\n");
}

/**
 * @brief Convierte a mayusculas todas las palabras del array bidimensional dado.
 * 
 * @param words direccion de memoria donde se encuenta el array bidimensional de palabras.
 * @param n numero de palabras almacenadas en el array.
 */
void toUpperCaseWords(char** words, u_int32_t n)
{
    for(u_int32_t i = 0; i < n; i++)
    {
        for(int j = 0; words[i][j] != '\0'; j++)
		{
        	words[i][j] = toupper(words[i][j]);
        }
    }
}

/**
 * @brief Imprime en consola información acerca de la memoria.
 * 
 */
void printMemoryInfo(void)
{
    MEM_INFO memInfo;

    getMemInfo(&memInfo);

	printf("- MEM INFO (/proc/meminfo):\n");
    printf("	Memoria Total      : %*lu [MB]\n", 7, memInfo.MemTotal     / 1024);
    printf("	Memoria Libre      : %*lu [MB]\n", 7, memInfo.MemFree 	   / 1024);
    printf("	Memoria Disponible : %*lu [MB]\n", 7, memInfo.MemAvailable / 1024);
    printf("	Swap Total         : %*lu [MB]\n", 7, memInfo.SwapTotal    / 1024);
    printf("	Swap Libre         : %*lu [MB]\n\n", 7, memInfo.SwapFree   / 1024);
}

/**
 * @brief Imprime en consola información acerca del CPU.
 * 
 */
void printCpuInfo(void)
{
    CPU_INFO cpuInfo;

    getCpuInfo(&cpuInfo);

	printf("- CPU INFO (/proc/cpuinfo):\n");
    printf("	Modelo             : %s\n", cpuInfo.ModelName);
    printf("	Nucleos            : %d\n", cpuInfo.Cores);
    printf("	Hilos              : %d\n\n", cpuInfo.Threads);
}

/**
 * @brief Obtiene informacion acerca de la memoria.
 * 
 * Realiza la lectura y procesamiento de la informacion almacenada en el archivo "/proc/meminfo" 
 * para posteriormente almacenarla en el puntero a la estructura dada como parametro.
 * 
 * @param memInfo puntero a la estructura donde se quiere almacenar la informacion obtenida.
 */
void getMemInfo(MEM_INFO* memInfo)
{
	char* line = NULL;
	ssize_t read;
	size_t len;
  	FILE *file;

	file = fopen("/proc/meminfo", "r");
  
  	if(file == NULL) 
		exit(EXIT_FAILURE); // Si ocurrio un error al intentar abrir el archivo finaliza la ejecucion del programa

	while ((read = getline(&line, &len, file)) != -1) // Recorre linea por linea el archivo
	{
		char* token = strtok(line, ":"); // Divide la linea en dos por medio del simbolo ":"
		
		// Compara la primer subcadena obtenida en busca de la informacion deseada
		if (strncmp(token, "MemTotal", 8) == 0) {
			token = strtok(NULL, ":"); // Selecciona la segunda subcadena, la cual contiene el dato de interes
			memInfo->MemTotal = atol(strtok(token, " ")); // Almacena el dato en la locacion correspondiente
		}

		if (strncmp(token, "MemFree", 7) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->MemFree = atol(strtok(token, " "));
		}

		if (strncmp(token, "MemAvailable", 12) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->MemAvailable = atol(strtok(token, " "));
		}

		if (strncmp(token, "SwapTotal", 9) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->SwapTotal = atol(strtok(token, " "));
		}

		if (strncmp(token, "SwapFree", 8) == 0)  
		{
			token = strtok(NULL, ":"); 
			memInfo->SwapFree = atol(strtok(token, " "));
		}
	}

  	fclose(file);

	if (line)
        free(line);
}

/**
 * @brief Obtiene informacion acerca de la CPU.
 * 
 * Realiza la lectura y procesamiento de la informacion almacenada en el archivo "/proc/cpuinfo" 
 * para posteriormente almacenarla en el puntero a la estructura dada como parametro.
 * 
 * @param cpuInfo puntero a la estructura donde se quiere almacenar la informacion obtenida.
 */
void getCpuInfo(CPU_INFO* cpuInfo)
{
	char* line = NULL;
	ssize_t read;
	size_t len;
  	FILE *file;

	file = fopen("/proc/cpuinfo", "r");
  
  	if(file == NULL) 
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, file)) != -1)
	{
		char* token = strtok(line, ":");
		
		if (strncmp(token, "model name", 10) == 0) {	
			/* Este bloque de codigo se encarga de eliminar los espacios en blanco al principio
			 y al final de la cadena que contiene la informacion del modelo del CPU */	

  			const char *end;
  			token = strtok(NULL, ":"); 

    		while(isspace((unsigned char)*token)) token++;

	 		end = token + strlen(token) - 1;
  			while(end > token && isspace((unsigned char)*end)) end--;
  			end++;

  			memcpy(cpuInfo->ModelName, token, (end - token));
  			cpuInfo->ModelName[(end - token)] = 0;
		}

		if (strncmp(token, "cpu cores", 9) == 0)  
		{
			token = strtok(NULL, ":"); 
			cpuInfo->Cores = atoi(strtok(token, " "));
		}

		if (strncmp(token, "siblings", 8) == 0)  
		{
			token = strtok(NULL, ":"); 
			cpuInfo->Threads = atoi(strtok(token, " "));
		}
	}

  	fclose(file);

	if (line)
        free(line);
}