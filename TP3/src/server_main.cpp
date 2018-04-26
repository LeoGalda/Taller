#include <cstdlib>
#include <exception>
#include <iostream>
#include <syslog.h>
#include <stdio.h>
#include "client_Accion.h"
#include "client_AccionPush.h"
#include "server.h"

using std::cout;

int main(int argc, char** argv) {
    try{
        Server server(argv[1],argv[2]);    
        server.aceptarClientes();
    } catch(std::exception &exc){
        syslog(LOG_ERR,"Error: %s", exc.what());   
        return 1;
    } catch(...){
        syslog(LOG_ERR,"Error: NO TENGO NI PUTA IDEA QUE PASO");        
        return 1;
    }
//    Accion *unaAccion = new AccionPush();
//    unaAccion->ejecutar();
    return 0;
}

