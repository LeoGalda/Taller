#include <cstdlib>
#include <exception>
#include <iostream>
#include <syslog.h>
#include <stdio.h>
#include "common_Accion.h"
#include "client_AccionPush.h"
#include "server_Thread.h"
#include "server.h"

using std::cout;

int main(int argc, char** argv) {
    try{
        Server server(argv[1]);  
        Indice indice(argv[2]);        
        std::vector<Thread*> threads;
        
        server.aceptarClientes(&indice);
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

