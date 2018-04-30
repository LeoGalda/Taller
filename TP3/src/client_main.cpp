#include <cstdlib>
#include <iostream>
#include <syslog.h>
#include <string.h>
#include "cliente.h"
#include "common_ExcpError.h"
#include "client_AccionPull.h"
#include "client_AccionPush.h"
#include "client_AccionTag.h"
#include <exception>

int main(int argc, char* argv[]) {
    try {
        Cliente cliente(argv[1], argv[2]);        
        Accion *accion;
        if (strcmp(argv[3], "push") == 0) {
//           AccionPush push(argv[4],argv[5]);      
//           accion = &push;
            accion = new AccionPush(argv[4],argv[5]);
        } else if (strcmp(argv[3], "pull") == 0) {
            throw -1;
//            AccionPull pull(argv[4]);
//            accion = &pull;
        } else if (strcmp(argv[3], "tag") == 0) {
//            AccionTag tag(argv[4]);
//            for(int i = 4;i < argc;++i){
//                tag.agregarHash(argv[i]);
//            }
//            accion = &tag;
            throw -1;
        } else {
            throw -1;
        }    
        cliente.ejecutar(accion);
        delete accion;
    } catch (const std::exception &exc) {
        syslog(LOG_ERR, "Error: %s", exc.what());
        return 1;
    } catch (...) {
        syslog(LOG_ERR, "Error en cliente: NO TENGO NI PUTA IDEA QUE PASO");
        return 1;
    }
    return 0;
}

