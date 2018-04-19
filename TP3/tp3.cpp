#include <cstdlib>
#include <exception>
#include <iostream>
#include <syslog.h>
#include <stdio.h>
#include "Accion.h"
#include "AccionPush.h"
#include "Servidor.h"

using std::cout;

int main(int argc, char** argv) {
    try{
        Servidor server(argv[0],argv[1]);    
    } catch(const std::exception &exc){
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

