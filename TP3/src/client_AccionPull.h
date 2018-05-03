#ifndef CLIENT_ACCIONPULL_H
#define CLIENT_ACCIONPULL_H

#include "common_Accion.h"
#include "common_Socket.h"
#include <string>

//class AccionPull : public Accion {
class AccionPull{
private:    
    std::string hash;
public:
    explicit AccionPull(char *hash);
    int ejecutar();
    unsigned int getValorNumerico();
//    virtual int getTamanio();
    virtual ~AccionPull();
//    virtual std::string getNombreArchivo() const;
//    virtual std::vector<unsigned char> getData();  
//    virtual unsigned char* getDataEnPos(int pos);
//    virtual void procesarArch(char *data);
//    virtual int getSizeFile();
};

#endif 

