#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"

void buffer_crear(Buffer *this,size_t tamanio) {    
    this->tamanio = tamanio;
    this->usado = 0;
    this->data = (unsigned char*) malloc(sizeof (unsigned char) * tamanio);     
}

void buffer_destroy(Buffer *this) {
    free(this->data);
}