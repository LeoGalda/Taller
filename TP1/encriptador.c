#include "encriptador.h"
#include "cliente.h"
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

unsigned char encriptarDato(unsigned char key_stream, unsigned char unCaracter);

unsigned char fasePRGA(Encriptador *this);

void encriptador_crear(Encriptador *this) {
    this->prgaI = 0;
    this->prgaJ = 0;
}

void imprimirSalidaEstandar(unsigned char dato) {
    fprintf(stdout, "%02x", dato);
}

void imprimirSalidaErrores(unsigned char ks) {
    fprintf(stderr, "%02X", ks);
}

void encriptador_encriptar(Encriptador *this, Buffer *buffer) {
    unsigned char unCaracter;
    unsigned char key_stream;
    unsigned char datoEncriptado;
    for (int c = 0; c < buffer_get_usado(buffer); c++) {
        unCaracter = buffer_get_data_pos(buffer, c);
        key_stream = fasePRGA(this);
        datoEncriptado = encriptarDato(key_stream, unCaracter);
        buffer_set_data_pos(buffer, datoEncriptado, c);
        imprimirSalidaEstandar(datoEncriptado);
        imprimirSalidaErrores(key_stream);
    }
}

void encriptador_desencriptar(Encriptador *this, FILE *salida, Buffer *buffer){
    unsigned char unCaracter;
    unsigned char key_stream;
    unsigned char datoEncriptado;
    for (int c = 0; c < buffer_get_usado(buffer); c++) {
        unCaracter = buffer_get_data_pos(buffer, c);
        key_stream = fasePRGA(this);
        datoEncriptado = encriptarDato(key_stream, unCaracter);
        imprimirSalidaEstandar(datoEncriptado);
        imprimirSalidaErrores(key_stream);
        buffer_set_data_pos(buffer, datoEncriptado, c);
    }
}

void encriptador_destroy(Encriptador *this) {
}

unsigned char encriptarDato(unsigned char key_stream, unsigned char unCaracter){
    return key_stream ^ unCaracter;
}

void intercambiar(char *s, int i, int j) {
    char auxiliar = s[i];
    s[i] = s[j];
    s[j] = auxiliar;
}

void encriptador_fase_KSA(Encriptador *this, char *key) {
    int tamanio = strlen((char*) key);
    int i, j;
    for (i = 0; i < 256; i++) {
        this->arrayDeEstados[i] = i;
    }
    j = 0;
    for (i = 0; i < 256; i++) {
        j = (j + this->arrayDeEstados[i] + key[i % tamanio]) & 255;
        intercambiar(this->arrayDeEstados, i, j);
    }
}

unsigned char fasePRGA(Encriptador *this) {
    unsigned char k;
    this->prgaI = (this->prgaI + 1) & 255;
    this->prgaJ = (this->prgaJ + this->arrayDeEstados[this->prgaI]) & 255;
    intercambiar(this->arrayDeEstados, this->prgaI, this->prgaJ);
    k = this->arrayDeEstados[(this->arrayDeEstados[this->prgaI] +
            this->arrayDeEstados[this->prgaJ]) & 255];
    return k;
}
