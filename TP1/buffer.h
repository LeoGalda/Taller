#ifndef __BUFFER_H__
#define __BUFFER_H__

typedef struct {
    int tamanio;
    int usado;
    unsigned char *data;
} Buffer;

//crea un buffer
void buffer_crear(Buffer * this, int tamanio);

//devuelve cuanto se uso del buffer
int buffer_get_usado(Buffer * this);

//devuelve el valor de data en la posicion deseada si la posicion es erronea
//devuelve 0
unsigned char buffer_get_data_pos(Buffer * this, int pos);

//setea el valor de data en la posicion deseada si la posicion es erronea
//devuelve 0
int buffer_set_data_pos(Buffer * this, unsigned char data, int pos);

//setea el uso del buffer
void buffer_set_usado(Buffer * this, int cantidad);

//devuelve data
unsigned char* buffer_get_data(Buffer * this);

//destruye un buffer
void buffer_destroy(Buffer * this);

#endif

