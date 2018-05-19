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
    
public:
//constructor del AccionPush    
    AccionPush(char *arch, char *hash);
    
//ejecuta la logica del push.        
    void ejecutar(Protocolo *protocolo);
    

//envia el contenido del archivo al server    
    void responder(Protocolo *protocolo);
    
//devuelve el valor numerico que le corresponde       
    unsigned char getValorNumerico();    
    
//realiza una lectura del archivo y lo guarda en data    
    void procesarArch(char *data);
        
//devuelve el tamaño del archivo    
    int getSizeFile();

//envia por el socket la informacion del archivo
//teniendo como maximo la constante de MAX_TAMANIO_BUFFER
    int enviarDataDeArchivo(Protocolo *protocolo,int tamanio);
    
//destructor del AccionPush        
    virtual ~AccionPush();
};

#endif 

