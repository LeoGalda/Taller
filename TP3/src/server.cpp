#include "server.h"
#include <string>

Server::Server() {
}

void Server::aceptarCliente(Aceptador& aceptador) {
    aceptador.start();
    string linea("");
    while (linea != "q") {
        getline(std::cin, linea);        
    }
    aceptador.finalizar();
}

Server::~Server() {
}

