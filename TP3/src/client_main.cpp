#include <cstdlib>
#include <iostream>
#include <syslog.h>
#include <string.h>
#include "cliente.h"
//#include "common_ExcpError.h"
#include "client_AccionPull.h"
#include "client_AccionPush.h"
#include "client_AccionTag.h"
#include <exception>
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        Accion *accion;
        if (strcmp(argv[3], "push") == 0) {
            if (argc != 6) {
                throw std::invalid_argument("");
            }
            //            accion = new AccionPush(argv[4], argv[5]);
            AccionPush push(argv[4], argv[5]);
            accion = &push;
        } else if (strcmp(argv[3], "tag") == 0) {
            //            accion = new AccionTag(argv[4]);         
            //            for (int i = 5; i < argc; ++i) {
            //                static_cast<AccionTag*> (accion)->agregarHash(argv[i]);
            //            }
            AccionTag tag(argv[4]);
            for (int i = 5; i < argc; ++i) {
                std::string sarasa = argv[i];
                tag.agregarHash(sarasa);
            }
            accion = &tag;
        } else if (strcmp(argv[3], "pull") == 0) {
            if (argc != 5) {
                throw std::invalid_argument("");
            }
            AccionPull pull(argv[4]);
            accion = &pull;
            //             accion = new AccionPull(argv[4]);
        } else {
            throw std::invalid_argument("");
        }
        Cliente cliente(argv[1], argv[2]);
        cliente.ejecutar(accion);

        //        delete accion;

    } catch (const std::invalid_argument &exc) {
        std::cout << "Error: argumentos invalidos." << std::endl;
    } catch (const std::exception &exc) {
        std::cout << exc.what() << std::endl;
    } catch (...) {
        std::cout << "Error no capturado" << std::endl;
    }
    return 0;
}

