#include <algorithm>
#include <arpa/inet.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Paquete.h"
#include "Empaquetador.h"
#include "Configurador.h"

using std::string;

Configurador::Configurador() {
}

Configurador::Configurador(char *ent) : entrada(ent) {
}

bool Configurador::estaFin() {
    return this->archivo.eof();
}

void Configurador::leerConfiguracion(Empaquetador *empaquetador) {
    this->archivo.open(this->entrada);
    std::string input;
    while (!estaFin()) {
        getline(this->archivo, input, '\n');
        std::string linea = input;
        if (!linea.empty()) {
            std::string substring;
            size_t inicio = 0;
            size_t siguiente = linea.find("=");
            substring = linea.substr(inicio, siguiente - inicio);
            int id = atoi(substring.c_str());
            inicio = siguiente + 1;
            siguiente = linea.find(",");
            std::string nombre = linea.substr(inicio, siguiente - inicio);
            inicio = siguiente + 1;
            int limite = atoi(linea.substr(inicio).c_str());
            empaquetador->agregarPaquete((unsigned int) id,nombre,limite);
        }
    }
}

Configurador::~Configurador() {
    this->archivo.close();
}


