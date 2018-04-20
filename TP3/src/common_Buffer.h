#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
private:
    int tamanio;
    int usado;
    unsigned int *data;
    
public:
    Buffer();
    explicit Buffer(int tamanio);
    virtual ~Buffer();


};

#endif

