#ifndef CLIENT_ACCIONPUSH_H
#define CLIENT_ACCIONPUSH_H

#include "client_Accion.h"
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
    int ejecutar();
    unsigned int getValorNumerico();    
    int getTamanio();    
    std::vector<unsigned char> getData();
    unsigned char* getDataEnPos(int pos);
    void procesarArch(char *data);
    int getSizeFile();
    ~AccionPush();
};

#endif 

