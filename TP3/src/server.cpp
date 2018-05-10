#include "server.h"

Server::Server() {
}

void Server::aceptarCliente(Aceptador& aceptador) {
    aceptador.start();
    string line("");
    while (line != "q") {
        getline(std::cin, line);
    }
    aceptador.finalizar();
}

Server::~Server() {
}

