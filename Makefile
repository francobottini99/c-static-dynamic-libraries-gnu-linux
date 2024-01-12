#Makefile
#Genera el ejecutable junto con todas las dependencias necesarias para el programa del Laboratorio 3.

.DELETE_ON_ERROR:

#Directorio y nombre de salida.
TARGET = $(BIN_DIR)/Lab3

#Directorios que intervienen en el proceso de compilacion.
BIN_DIR = bin
OBJ_DIR = obj
INC_DIR = inc
LIB_DIR = lib
SRC_DIR = src

#Archivos que se van a generar y utilizar para compilar el programa.
TARGET_OBJ = $(OBJ_DIR)/JSON-Utils.o \
	   		 $(OBJ_DIR)/Lab3.o

TARGET_DEP = $(TARGET_OBJ)           \
	   		 $(LIB_DIR)/libplugin.so \
 			 $(LIB_DIR)/liblab2.a

TARGET_LIB = -llab2  \
			 -lcjson \
			 -lplugin

LAB3_DEP = $(SRC_DIR)/Lab3.c       \
		   $(INC_DIR)/JSON-Utils.h \
		   $(INC_DIR)/Lab2.h       \
		   $(INC_DIR)/cJSON.h

JSUT_DEP = $(SRC_DIR)/JSON-Utils.c \
		   $(INC_DIR)/JSON-Utils.h \
		   $(INC_DIR)/Lab2.h       \
		   $(INC_DIR)/cJSON.h

PLUG_DEP = $(SRC_DIR)/Plugin.c \
		   $(INC_DIR)/Plugin.h

LAB2_DEP = $(SRC_DIR)/Lab2.c \
		   $(INC_DIR)/Lab2.h

PLUG_LIB = $(OBJ_DIR)/Plugin.o

LAB2_LIB = $(OBJ_DIR)/Lab2.o

#Banderas de compilacion.
CFLAGS = -Wall -Werror -pedantic
LIBPATH = -Wl,-rpath,'$(shell pwd)/$(LIB_DIR)'

#Compila el programa con todas sus dependencias.
$(TARGET) : $(TARGET_DEP)
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) -ldl $(TARGET_OBJ) -L./$(LIB_DIR) $(LIBPATH) $(TARGET_LIB) -o $(TARGET)

#Generan los objetos necesarios para el proceso.
$(OBJ_DIR)/JSON-Utils.o : $(JSUT_DEP)
	mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) -c $(SRC_DIR)/JSON-Utils.c -o $(OBJ_DIR)/JSON-Utils.o

$(OBJ_DIR)/Lab3.o : $(LAB3_DEP)
	gcc $(CFLAGS) -c $(SRC_DIR)/Lab3.c -o $(OBJ_DIR)/Lab3.o

$(OBJ_DIR)/Plugin.o : $(PLUG_DEP)
	gcc $(CFLAGS) -c $(SRC_DIR)/Plugin.c -fpic -o $(OBJ_DIR)/Plugin.o

$(OBJ_DIR)/Lab2.o : $(LAB2_DEP)
	gcc $(CFLAGS) -c $(SRC_DIR)/Lab2.c -o $(OBJ_DIR)/Lab2.o

#Genera la libreria dinamica para el Plugin.
$(LIB_DIR)/libplugin.so : $(PLUG_LIB)
	mkdir -p $(LIB_DIR)
	gcc $(CFLAGS) $(PLUG_LIB) -shared -o $(LIB_DIR)/libplugin.so 

#Genera libreria estatica para las funciones del Laboratorio 2.
$(LIB_DIR)/liblab2.a : $(LAB2_LIB)
	ar rs $(LIB_DIR)/liblab2.a $(OBJ_DIR)/Lab2.o

#Rutina de limpieza.
#Cuando se ejecuta se eliminan todos los elementos generados por este archivo.
.PHONY: clean
clean:
	rm -f -r $(OBJ_DIR)
	rm -f -r $(BIN_DIR)
	rm -f $(LIB_DIR)/liblab2.a
	rm -f $(LIB_DIR)/libplugin.so
#sudo rm -f /usr/lib/libplugin.so
	
