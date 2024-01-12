/**
 * @file Plugin.c
 * @author Bottini, Franco Nicolas
 * @brief Implementacion del la caratieriztica extra (plugin) del ejercio 3 del laboratorio 3 de Sistemas Operativos I.
 * @version 1.0
 * @date Septiembre de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/Plugin.h"

/**
 * @brief Obtiene todos los sistemas de archivos soportados por el kernel que figuran en el /proc/filesystems.
 * 
 * Genera un array bidimensional dinamico con todas los sistemas de archivos que figuran en el 
 * directorio mencionado. Minimiza la memoria empleada para el almacenamiento de dichas informacion.
 * 
 * @param n puntero donde se va a almacenar el numero de sistemas de archivos soportados.
 * @return char** direccion de memoria del array bidimensional donde se encuentran almacenados los sistemas de archivos obtenidos.
 */
char** getFileSystemsInfo(u_int32_t* n)
{
    u_int32_t w_count = 0; //Contador del numero de palabras

	ssize_t read;
	size_t len;

	char* line = NULL;

  	FILE* file;

    char** words = malloc(sizeof(char*)); // En primera instancia se reserva memoria para alamacenar una palabra
    words[w_count] = malloc(sizeof(char)); // Se reserva memoria para al menos un caracter en la primera palabra

	file = fopen("/proc/filesystems", "r");
    
  	if(file == NULL) 
		exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, file)) != EOF) //Recorre todo el archivo linea por linea
    {
        u_int32_t c_count = 0; //Contador para el numero de caracter en una palabra

        for(int i = 0; line[i] != '\0'; i++) //Recorre todos los caracteres de una linea
        {
            if(line[i] == 9 && i > 0) line[i] = ' '; //Remplazamos las tabulaciones por espacios para separar dos palabras (mientras que no se encuentre al comienzo de la palabra)

            if(line[i] != '\n' && line[i] != 9) //ignoramos saltos de linea y tabulaciones al comienzo de una palabra
            {
                words[w_count][c_count] = line[i]; // Agrega el caracter a la palabra actual
                c_count++;
                words[w_count] = realloc(words[w_count], (c_count + 1) * sizeof(char)); // Se redimenciona la memoria reservada para la plabra actual para almacenar el siguiente caracter     
            }
        }

        words[w_count][c_count] = '\0'; //Finzalizamos la palabra con el caracter correspondiente

        w_count++;

        words = realloc(words, (w_count + 1) * sizeof(char*)); //Redimiencionamos la memoria reservada para contener una nueva palabra
        words[w_count] = malloc(sizeof(char)); //Memoria para el primer caracter
    }
    
    //En el ultimo ciclo se reserva memoria que no se va a usar, por lo tanto la liberamos
    free(words[w_count]);
    w_count--;
    words = realloc(words, (w_count + 1) * sizeof(char*));

    *n = w_count; // Guardamos el numero de palabras obtenidas

  	fclose(file);

    return words;
}