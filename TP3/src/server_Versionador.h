#ifndef SERVER_VERSIONADOR_H
#define SERVER_VERSIONADOR_H
#include <stdbool.h>
#include <fstream>
#include <vector>
#include "common_Socket.h"
#include "server_Indice.h"
#include "server_Thread.h"

class Versionador : public Thread{
private:
    Socket socket;
    Indice indice;
public:
    Versionador(Socket &socket, Indice &indice);
    int pushea();
    int tagea();
    int pullea();
    virtual void run();
    void enviarInfoDeTags(std::string nomArchivo);
    virtual ~Versionador();
};

#endif

