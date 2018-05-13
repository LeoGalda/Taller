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
//constructor del AccionPush    
    AccionPush(char *arch, char *hash);
    
//ejecuta la logica del push y guarda en data los datos a enviar.        
    void ejecutar();
    
//envia los datos qeu se encuetran en data;     
    void enviar(Socket *socket);

//envia el contenido del archivo al server    
    void responder(Socket *socket);
    
//devuelve el valor numerico que le corresponde       
    int getValorNumerico();
    
//devuelve el tamanio de data     
    int getTamanio();
    
//realiza una lectura del archivo y lo guarda en data    
    void procesarArch(char *data);
        
//devuelve el tamaño del archivo    
    int getSizeFile();

//envia por el socket la informacion del archivo
//teniendo como maximo la constante de MAX_TAMANIO_BUFFER
    int enviarDataDeArchivo(Socket *socket,int tamanio);
    
//destructor del AccionPush        
    virtual ~AccionPush();
};

#endif 

