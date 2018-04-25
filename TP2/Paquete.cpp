#include <algorithm>
#include "Paquete.h"
#include <cstdio>
#include <string>
#include <vector>

Paquete::Paquete(unsigned int id, const std::string& nombre,
        unsigned int limite) : id(id), nombre(nombre),
limite(limite), cantidad(0) {
}

unsigned int Paquete::getId() {
    return this->id;
}

void Paquete::setId(unsigned int id) {
    this->id = id;
}

std::string Paquete::getNombre() const{
    return this->nombre;
}

void Paquete::setNombre(const std::string &nombre) {
    this->nombre = nombre;
}

unsigned int Paquete::getLimite() const{
    return this->limite;
}

void Paquete::setLimite(unsigned int limite) {
    this->limite = limite;
}

unsigned int Paquete::getCantidad() const{
    return this->cantidad;
}

void Paquete::setCantidad(unsigned int cantidad) {
    this->cantidad = cantidad;
}

void Paquete::addAncho(unsigned int ancho) {
    this->ancho.push_back(ancho);
}

void Paquete::addAnchos(unsigned int ancho, unsigned int cantidad) {
    for (int i = 0; i < (int) cantidad; ++i) addAncho(ancho);
}

std::vector<unsigned int> Paquete::getAnchos() const{
    return ancho;
}

void Paquete::limpiarAnchos() {
    this->ancho.clear();
}

int Paquete::calcularMediana() {
    std::vector<unsigned int> aux = this->getAnchos();
    std::sort(aux.begin(), aux.end());
    int cantidad = aux.size();
    if ((cantidad % 2) == 0) {
        int mitad = cantidad / 2;
        int dato = ceil(((float) aux[mitad] +
                aux[mitad - 1]) / 2);
        return dato;
    } else {
        return aux[(int) floor(cantidad / 2)];
    }
}

Paquete::~Paquete() {
}
