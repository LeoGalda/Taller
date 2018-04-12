#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"

void buffer_crear(Buffer *this,size_t tamanio) {    
    this->tamanio = tamanio;
    this->usado = tamanio;
    this->data = NULL;     
}

void buffer_destroy(Buffer *this) {
    free(this->data);
    free(this);
}