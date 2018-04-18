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

Configurador::Configurador(){    
}

Configurador::Configurador(char *ent) : entrada(ent) {
}

Paquete* procesarLinea(const std::string linea) {
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
    Paquete* paquete = new Paquete((unsigned int) id, nombre, limite);
    return paquete;
}

bool Configurador::estaFin() {
    return this->archivo.eof();
}

void Configurador::leerConfiguracion(Empaquetador *empaquetador) {
    this->archivo.open(this->entrada);
    char input[128];
    while (!estaFin()) {
        this->archivo.getline(input, sizeof(input));
        std::string linea = input;
        if (!linea.empty()) {
            empaquetador->agregarPaquete(procesarLinea(linea));
        }
    }
}

Configurador::~Configurador() {
    this->archivo.close();
}

