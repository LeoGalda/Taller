#ifndef COMMON_BUFFER_H
#define COMMON_BUFFER_H

class Buffer {
private:
    int tamanio;    
    unsigned char *data;
    
public:
    explicit Buffer(unsigned int tamanio);    
    unsigned char getDataEnPos(int pos);
//    unsigned char* getMoveData() const;
    unsigned char* getData();  
    int getTamanio();    
    virtual ~Buffer();
};

#endif

