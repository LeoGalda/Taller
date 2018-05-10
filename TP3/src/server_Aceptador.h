#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include "server_Thread.h"
#include "server_Indice.h"
#include "common_Socket.h"
#include <mutex>

class Aceptador : public Thread {
private:
    Indice indice;
    bool finalizado;
    Socket socket;
//    std::vector<Conexion*> conexiones;
    std::vector<Thread*> threads;
    
public:
    Aceptador(char *puerto,Indice &indice);
    virtual void run();
    void finalizar();
    void finalizarThreads();
    virtual ~Aceptador();
};

#endif

