# Prácticas de Lenguaje C en GNU/Linux

Este repositorio tiene como objetivo familiarizarse con el diseño e implementación de librerías estáticas y dinámicas en el entorno de desarrollo GNU Toolchain y Linux Software. Se realizarán actividades que involucran el manejo de command line arguments, la implementación de una librería estática (cJSON) y una librería dinámica actuando como _plugin_.

### 1. Command Line Arguments

Se diseñó e implementó un programa en C que, al ejecutarse con argumentos específicos, realiza las siguientes acciones:

1. Si se ejecuta con la opción _-s_, ejecuta el ejercicio 1 del Laboratorio 2.
2. Si se ejecuta con la opción _-a_, ejecuta el ejercicio 2 del Laboratorio 2.

### 2. Static Library (cJSON)

Se implementó en el proyecto la librería estática cJSON, permitiendo:

2.1. Si se agrega la opción _-j_ junto a las opciones del **punto 1**, utilizar la librería estática cJSON y mostrar el resultado en formato JSON.

### 3. Dynamic Library

Se diseñó e implementó una librería dinámica que actúa como _plugin_, extendiendo las opciones y permitiendo:

- Cargar dinámicamente al ejecutarse con la opción _-d_.

- Mostrar, utilizando la librería cJSON del **punto 2**, información sobre los filesystems soportados por el kernel en uso (/proc/filesystems).

### 4. Cuestionario

#### 4.1. ¿Cuáles son los tipos de type descriptors que podemos encontrar en /proc//fd?

Cuando se abre un archivo, el sistema operativo crea una entrada que lo representa y le permite almacenar información sobre el mismo. Entonces, si tenemos 100 archivos abiertos, habrá 100 entradas en el sistema operativo (en algún lugar del kernel). Estas entradas están representadas por números enteros (100, 101, 102). Este número de entrada es el file descriptor. Por lo tanto, el file descriptor es solo un número entero que representa de manera única un archivo abierto por un proceso. Si un proceso abre 10 archivos, su tabla de procesos tendrá 10 entradas para file descriptors. Existen cuatro tipos de file descriptors, standard input, standard output, standard error y de archivo.

#### 4.2. Suponiendo que un usuario está ejecutando el proceso pid 1212, ¿Es válida la ejecución del siguiente comando desde una terminal nueva? % echo “Hello, world.” >> /proc/1212/fd/1

La ejecución del comando si es valida. El resultado del mismo escribirá el mensaje "Hello, world" sobre el archivo al cual hace referencia el file descriptor seleccionado. Si abrimos dos instancias de una terminal y posteriormente ejecutamos el comando dado en una de las terminales haciendo referencia al file descriptor de entrada de la otra terminal, podemos observar como escribimos el mensaje "Hello, world" desde la primera terminal en la segunda.

![Captura de pantalla de 2022-09-09 08-51-22](https://user-images.githubusercontent.com/101523922/189353428-36587fe4-b1dd-4356-a762-feaaa5fdec02.png)

#### 4.3. Qué diferencia hay entre hard y soft limits?

En Linux se pueden limitar los recursos a los cuales puede acceder un proceso o una sesión. Existen dos tipos de limites imponibles, los hard limits y los soft limits. Los hard limits son establecidos utilizando privilegios de súper usuario y son el limite máximo de recursos de los que puede disponer cualquier proceso o sesión, estos nunca pueden ser excedidos. Por otra parte, los soft limits pueden ser utilizados por los usuarios o por los mismos procesos para auto limitar su uso de recursos, siempre teniendo en cuenta que estos limites deben ser menores o iguales que el hard limit impuesto. Por tanto, podemos decir que el hard limit establece el limite superior a partir del cual, posteriormente, se pueden sublimitar los usuarios o procesos utilizando los soft limits.
