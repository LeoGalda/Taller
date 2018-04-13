#ifndef __COMMON_BUFFER_H__
#define __COMMON_BUFFER_H__

typedef struct {
    int tamanio;
    int usado;
    unsigned char *data;
} Buffer;

//crea un buffer
void buffer_crear(Buffer *this,size_t tamanio);

//destruye un buffer
void buffer_destroy(Buffer * this);

#endif

