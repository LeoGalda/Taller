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
        Accion *accion;
        if (strcmp(argv[3], "push") == 0) {
            if (argc != 6) {
                std::cout << "Error: argumentos invalidos." << std::endl;
                throw -1;
            }
            accion = new AccionPush(argv[4], argv[5]);
            //            AccionPush push(argv[4],argv[5]);
            //            accion = &push;
        } else if (strcmp(argv[3], "tag") == 0) {
            accion = new AccionTag(argv[4]);
            //            AccionTag tag(argv[4]);            
            for (int i = 5; i < argc; ++i) {
                static_cast<AccionTag*> (accion)->agregarHash(argv[i]);
            }
            //            accion = &tag;            
        } else if (strcmp(argv[3], "pull") == 0) {
            if (argc != 5) {
                std::cout << "Error: argumentos invalidos." << std::endl;
                throw -1;
            }
//            AccionPull pull(argv[4]);
//            accion = &pull;
             accion = new AccionPull(argv[4]);
        } else {
            std::cout << "Error: argumentos invalidos." << std::endl;
            throw -1;
        }
        Cliente cliente(argv[1], argv[2]);
        cliente.ejecutar(accion);

        delete accion;
    } catch(const std::exception &exc) {
        syslog(LOG_ERR, "Error: %s", exc.what());
        return 0;
    } catch(...) {
        syslog(LOG_ERR, "Error en cliente");
        return 0;
    }
    return 0;
}

