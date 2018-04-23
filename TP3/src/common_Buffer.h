#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
private:
    int tamanio;
    int usado;
    unsigned int *data;
    
public:
    explicit Buffer(int tamanio);
    void setData();
    void setUsado(int usado);
//    int almacenarDatos();
    virtual ~Buffer();


};

#endif

