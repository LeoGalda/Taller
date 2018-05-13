#include <cstdlib>
#include <exception>
#include <iostream>
#include <syslog.h>
#include <stdio.h>
#include "common_Accion.h"
#include "client_AccionPush.h"
#include "server_Thread.h"
#include "server_Versionador.h"
#include "server_Aceptador.h"
#include "server.h"

using std::cout;

int main(int argc, char** argv) {
    try{
        Indice indice(argv[2]);        
        Server server;
        Aceptador aceptador(argv[1],&indice);    
        server.aceptarCliente(aceptador);
        aceptador.join();  
        indice.actualizar();
    } catch(std::exception &exc){
        syslog(LOG_ERR,"Error: %s", exc.what());   
        return 1;
    } catch(...){
        syslog(LOG_ERR,"Error: VERIFICAR");        
        return 1;
    }
    return 0;
}

