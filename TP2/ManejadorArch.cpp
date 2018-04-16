#include <arpa/inet.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Paquete.h"
#include "Empaquetador.h"
#include "ManejadorArch.h"

using std::string;

ManejadorArch::ManejadorArch() {
}

ManejadorArch::ManejadorArch(Empaquetador *emp, char *arch) : ruta(arch), emp(emp) {
    this->archivo.open(arch);
}

bool ManejadorArch::estaFin() {
    return this->archivo.eof();
}

bool getEndiannes() {
    int16_t i = 1;
    int8_t *p = (int8_t *) & i;

    if (p[0] == 1) {
        return false;
    }
    return true;
}

void procesarBinarios(int &info, Empaquetador *empaquetador) {
    unsigned int tipoTornillo;
    unsigned int cantidad;
    unsigned int ancho;
    tipoTornillo = cantidad = ancho = info;
    tipoTornillo >>= 27;
    cantidad <<= 5;
    cantidad >>= 10;
    ancho <<= 27;
    ancho >>= 27;
    std::cout << "tornillo:" << tipoTornillo << std::endl;
    std::cout << "cantidad:" << cantidad << std::endl;
    std::cout << "ancho:" << ancho << std::endl;
    empaquetador->actualizarDatos(tipoTornillo, cantidad, ancho);
}

std::string leerNombre(std::ifstream &arch) {
    char input[128];
    for (int i = 0; i < 128; i++) {
        input[i] = 00;
    }
    std::string nombreClasificador;
    arch.getline(input, sizeof (input), '\0');
    nombreClasificador = input;
    return nombreClasificador;
}

void ManejadorArch::run() {
    bool soyBigEndian = getEndiannes();
    if (this->archivo.fail()) {
        fprintf(stderr, "%s: no se pudo conectar con el dispositivo\n", this->ruta);
    } else {
        std::string nombreClasificador = leerNombre(this->archivo);
        fprintf(stdout, "%s: se establece conexion con el dispositivo %s\n",
                this->ruta, nombreClasificador.c_str());        
        char input[4];        
        while (!estaFin()) {
            int magicus;
//            this->archivo.get(input, sizeof(input) + 1);
            this->archivo.get(input[0]);
            this->archivo.get(input[1]);
            this->archivo.get(input[2]);
            this->archivo.get(input[3]);
            if(estaFin()) return;
            printf("%02X\n",input[0]);
            printf("%02X\n",input[1]);
            printf("%02X\n",input[2]);
            printf("%02X\n",input[3]);
            memcpy(&magicus, &input, sizeof(magicus));
            if (magicus == -1) {
                fprintf(stderr, "%s atascado\n", nombreClasificador.c_str());
            } else if (soyBigEndian) {
                procesarBinarios(magicus, this->emp);
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

