#ifndef __BUFFER_H__
#define __BUFFER_H__

typedef struct {
    size_t tamanio;
    size_t usado;
    char *data;
} Buffer;

//crea un buffer
void buffer_crear(Buffer *this,size_t tamanio);

//destruye un buffer
void buffer_destroy(Buffer * this);

#endif

