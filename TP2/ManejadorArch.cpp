#include <arpa/inet.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include "Paquete.h"
#include "Empaquetador.h"
#include "ManejadorArch.h"

using std::string;

ManejadorArch::ManejadorArch() {
}

std::string leerNombre(std::ifstream &arch) {
    char input[128];
    for (int i = 0; i < 128; i++) {
        input[i] = 00;
    }
    std::string nombreClasificador;
    arch.getline(input, sizeof(input), '\0');
    nombreClasificador = input;
    return nombreClasificador;
}

ManejadorArch::ManejadorArch(Empaquetador *emp, char *arch) 
                                : ruta(arch), emp(emp) {
    this->archivo.open(arch);
    if (this->archivo.fail()) {
        fprintf(stderr, "%s: no se pudo conectar con el dispositivo\n", 
                        this->ruta);
    } else {
        std::string nombreClasificador = leerNombre(this->archivo);
        this->nombreClasificador = nombreClasificador;
        fprintf(stdout, "%s: se establece conexion con el dispositivo %s\n",
                this->ruta, nombreClasificador.c_str());
    }
}

bool ManejadorArch::estaFin() {
    return this->archivo.eof();
}

void procesarBinarios(int &info, Empaquetador *empaquetador) {
    unsigned int tipoTornillo;
    unsigned int cantidad;
    unsigned int ancho;
    int cantidadDeBitAMoverTornillos = 27;
    int cantidadDeBitAMoverAncho = 27;
    int cantidadDeBitAMoverIzquierdaCantidad = 5;
    int cantidadDeBitAMoverDerechaCantidad = 10;
    tipoTornillo = cantidad = ancho = info;
    tipoTornillo >>= cantidadDeBitAMoverTornillos;
    cantidad <<= cantidadDeBitAMoverIzquierdaCantidad;
    cantidad >>= cantidadDeBitAMoverDerechaCantidad;
    ancho <<= cantidadDeBitAMoverAncho;
    ancho >>= cantidadDeBitAMoverAncho;
    empaquetador->actualizarDatos(tipoTornillo, cantidad, ancho);
}

void ManejadorArch::run() {
    if (!this->archivo.fail()) {        
        char input[4];
        while (!estaFin()) {
            int magicus;   
            int cantidadBytesALeer = 4;
            this->archivo.read(input,cantidadBytesALeer);
            if (estaFin()) return;
            memcpy(&magicus, &input, sizeof(magicus));
            if (magicus == -1) {
                fprintf(stderr, "%s atascado\n",
                        this->nombreClasificador.c_str());
            } else {
                magicus = htonl(magicus);
                procesarBinarios(magicus, this->emp);
            }
        }
    }
}

ManejadorArch::~ManejadorArch() {
    archivo.close();
}

