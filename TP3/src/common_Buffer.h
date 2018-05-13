#ifndef COMMON_BUFFER_H
#define COMMON_BUFFER_H

class Buffer {
private:
    int tamanio;    
    unsigned char *data;
    
public:
//constructor del buffer y crea data segun el tamanio pasado por parametro    
    explicit Buffer(unsigned int tamanio);    
    
//devuelve el valor de data en la posicion pasada por parametro    
    unsigned char getDataEnPos(int pos);
    
//devuelve un puntero a la posicion de data    
    unsigned char* getData();  
    
//devuelve el tamanio de data    
    int getTamanio();    
    
//destructor del buffer    
    virtual ~Buffer();
};

#endif

