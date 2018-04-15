#include <algorithm>
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

bool ManejadorArch::estaFin() {
    return this->archivo.eof();
}

Paquete* ManejadorArch::procesarLinea(const std::string linea) {
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
    Paquete* paquete = new Paquete(id, nombre, limite);
    return paquete;
}

void ManejadorArch::leerConfiguracion(Empaquetador *empaquetador, char *entrada) {
    this->archivo.open(entrada);
    char input[128];
    while (!estaFin()) {
        this->archivo.getline(input, sizeof (input));
        std::string linea = input;
        if (!linea.empty()) {
            empaquetador->agregarPaquete(procesarLinea(linea));
        }
    }
}

bool getEndiannes() {
    int16_t i = 1;
    int8_t *p = (int8_t *) & i;

    if (p[0] == 1) {
        return false;
    }
    return true;
}

int calcularMediana(std::vector<int> anchos) {
    std::sort(anchos.begin(), anchos.end());
    int cantidad = anchos.size();
    if ((cantidad % 2) == 0) {
        int mitad = cantidad / 2;
        int dato = (int) floor((float) (anchos[mitad] + anchos[mitad - 1]) / 2);
        return dato;
    } else {
        return anchos[(int) floor(cantidad / 2)];
    }
}

void procesarBinarios(int &info, Empaquetador *empaquetador) {
//    printf("informacion:%02X\n",info);
    unsigned int tipoTornillo;
    unsigned int cantidad;
    unsigned int ancho;
    tipoTornillo = cantidad = ancho = info;
    tipoTornillo >>= 27;
    cantidad <<= 5;
    cantidad >>= 10;
    ancho <<= 27;
    ancho >>= 27;
//        std::cout<<"el tipo de tornillo es: "<< tipoTornillo<<std::endl;
//        std::cout<<"la cantidad es: "<<cantidad<<std::endl;
//        std::cout<<"el ancho es: "<<ancho<<std::endl;
//    if (empaquetador->existeTornillo(tipoTornillo)) {        
//        fprintf(stderr, "Tipo de tornillo invalido: <%i>\n",
//                   tipoTornillo);
//    } else {
        Paquete *paquete;
        paquete = empaquetador->getPaquetePorTipo(tipoTornillo);
        paquete->setCantidad(paquete->getCantidad() + cantidad);
        paquete->addAncho(ancho);
        while (paquete->getCantidad() >= paquete->getLimite()) {            
            int mediana = calcularMediana(paquete->getAnchos());
            fprintf(stdout, "Paquete listo: %i tornillos de tipo %s "
                    "(mediana: %i)\n",paquete->getLimite(), 
                    paquete->getNombre().c_str(), mediana);
            paquete->limpiarAnchos();
            paquete->setCantidad(paquete->getCantidad() - paquete->getLimite());
            if (paquete->getCantidad() > 0) {
                paquete->addAncho(ancho);
            }
        }
//    }
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

void ManejadorArch::parsearArchivo(Empaquetador *empaquetador, char *ruta) {
    bool soyBigEndian = getEndiannes();
    int magicus;
    this->archivo.open(ruta, std::ifstream::binary);
    if (this->archivo.fail()) {
        fprintf(stderr, "%s: no se pudo conectar con el dispositivo\n", ruta);
    } else {
        std::string nombreClasificador = leerNombre(this->archivo);
        fprintf(stdout, "%s: se establece conexion con el dispositivo %s\n",
                ruta, nombreClasificador.c_str());
        char input[4];        
        while (!estaFin()) {
            this->archivo.get(input, sizeof(input)+1);
            memcpy(&magicus, &input, sizeof(magicus));
            if (magicus == -1) {
                fprintf(stderr, "%s atascado\n", nombreClasificador.c_str());
            } else if (soyBigEndian) {
                procesarBinarios(magicus, empaquetador);
            } else {
                magicus = htonl(magicus);
                procesarBinarios(magicus, empaquetador);
            }
        }
        this->archivo.close();
    }
}

ManejadorArch::~ManejadorArch() {
    archivo.close();
}

