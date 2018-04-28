#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
private:
    int tamanio;
    int usado;
    unsigned int *data;
    
public:
    explicit Buffer(int tamanio);
    int setDataEnPosicion(unsigned int data, int pos);
    unsigned char getDataEnPos(int pos) const;
    unsigned int* getData(int pos);
    void setUsado(int usado);    
    int getUsado();
    int getTamanio();    
    virtual ~Buffer();


};

#endif

