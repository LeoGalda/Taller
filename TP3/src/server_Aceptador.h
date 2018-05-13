#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include "server_Thread.h"
#include "server_Indice.h"
#include "common_Socket.h"
#include <mutex>
#include <vector>

class Aceptador : public Thread {
private:
    Indice *indice;
    bool finalizado;
    Socket socket;
    std::vector<Thread*> threads;
    
public:
//constructor del aceptador y realiza el bind y el listen    
    Aceptador(char *puerto,Indice *indice);
    
//ejecuta la logica del hilo aceptador    
    virtual void run();
    
//finaliza la logica y destruye el socket    
    void finalizar();
    
//finaliza los threads    
    void finalizarThreads();
    
//destructor del aceptador   
    virtual ~Aceptador();
};

#endif

