#ifndef SERVER_VERSIONADOR_H
#define SERVER_VERSIONADOR_H
#include <stdbool.h>
#include <fstream>
#include <vector>
#include <string>
#include <mutex>
#include "common_Socket.h"
#include "server_Indice.h"
#include "server_Thread.h"


class Versionador : public Thread{
private:
    Socket socket;
    Indice *indice;
    
public:
//llama al constructor del versionador    
    Versionador(Socket &socket, Indice *indice);
    
//ejecuta la logica del push    
    int pushea();

//ejecuta la logica del tag    
    int tagea();
    
//ejecuta la logica del pull    
    int pullea();
    
//ejecuta la logica del versionador    
    virtual void run();
    
//envia la informacion de los tags    
    void enviarInfoDeTags(const std::string nomArchivo);
    
//envia por el socket la informacion del archivo
//teniendo como maximo la constante de MAX_TAMANIO_BUFFER
    int enviarDataDeArchivo(int tamanio,File *file);    
    
//llama al destructor del versionador    
    virtual ~Versionador();
};

#endif

