#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"

void buffer_crear(Buffer *this, int tamanio) {
    this->tamanio = tamanio;
    this->usado = 0;
    this->data = (unsigned char*) malloc(sizeof(unsigned char) * tamanio);
}

int buffer_get_usado(Buffer *this) {
    return this->usado;
}

unsigned char* buffer_get_data(Buffer *this) {
    return this->data;
}

unsigned char buffer_get_data_pos(Buffer *this, int pos) {
    if (pos > this->tamanio) return 1;
    return this->data[pos];
}

int buffer_set_data_pos(Buffer *this, unsigned char data, int pos) {
    if (pos > this->tamanio) return 1;
    this->data[pos] = data;
    return 0;
}

void buffer_set_usado(Buffer *this, int cantidad) {
    if (cantidad > this->tamanio) return;
    this->usado = cantidad;
}

int buffer_get_tamanio(Buffer *this){
    return this->tamanio;
}

void buffer_destroy(Buffer *this) {
    free(this->data);
}
