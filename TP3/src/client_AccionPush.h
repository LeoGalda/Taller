#ifndef CLIENT_ACCIONPUSH_H
#define CLIENT_ACCIONPUSH_H

#include "common_Accion.h"
#include "common_File.h"
#include <vector>
#include <fstream>
#include <string>

class AccionPush : public Accion {
private: 
    std::string hash;    
    File file;
    std::vector<unsigned char> data;
public:
    AccionPush(char *arch, char *hash);
    void ejecutar();
    void enviar(Socket *socket);
    void responder(Socket *socket);
    int getValorNumerico();
    int getTamanio();
    void procesarArch(char *data);
    int getSizeFile();
    virtual ~AccionPush();
};

#endif 

