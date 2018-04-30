#ifndef COMMON_BUFFER_H
#define COMMON_BUFFER_H

class Buffer {
private:
    int tamanio;
    int usado;
    unsigned char *data;
    
public:
    explicit Buffer(int tamanio);
    int setDataEnPosicion(unsigned int data, int pos);
    unsigned char getDataEnPos(int pos) const;
    unsigned char* getData();
    void setUsado(int usado);    
    int getUsado();
    int getTamanio();    
    virtual ~Buffer();


};

#endif

