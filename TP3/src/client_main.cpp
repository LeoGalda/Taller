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
            accion = new AccionPull(argv[4]);
        } else {
            throw -1;
        }
        cliente.ejecutar(accion);

        delete accion;
    } catch (const std::exception &exc) {
        syslog(LOG_ERR, "Error: %s", exc.what());
        return 1;
    } catch (...) {
        syslog(LOG_ERR, "Error en cliente: NO TENGO NI IDEA QUE PASO");
        return 1;
    }
    return 0;
}

