#include <algorithm>
#include "Empaquetador.h"
#include <cstdio>
#include <string.h>
#include "Lock.h"

Empaquetador::Empaquetador() {
}

void Empaquetador::agregarPaquete(unsigned int id, const std::string nombre,
        int limite) {
    Paquete paquete(nombre, limite);
    this->empaquetador.insert(std::pair<int, Paquete>(id, std::move(paquete)));
}

void Empaquetador::mostrarRemanentes() {
    fprintf(stdout, "# Informe de remanentes\n");
    for (std::map<int, Paquete>::iterator it = this->empaquetador.begin();
            it != this->empaquetador.end(); ++it) {
        fprintf(stdout, "* %i tornillos de tipo %s\n", it->second.getCantidad(),
                it->second.getNombre().c_str());
    }
}


void Empaquetador::actualizarDatos(unsigned int tipo, unsigned int cant,
        unsigned int ancho) {
    Lock l(mute);
    if (this->empaquetador.find(tipo) == this->empaquetador.end()) {
        fprintf(stderr, "Tipo de tornillo invalido: %i\n", tipo);
    } else {
        Paquete paquete;
        paquete = this->empaquetador[tipo];
        if ((paquete.getCantidad() + cant) >= paquete.getLimite()) {
            while ((paquete.getCantidad() + cant) >= paquete.getLimite()) {
                unsigned int agregar = paquete.getLimite() -
                        paquete.getCantidad();
                cant -= agregar;
                paquete.setCantidad(paquete.getCantidad() + agregar);
                paquete.addAnchos(ancho, agregar);
                int mediana = paquete.calcularMediana();
                fprintf(stdout, "Paquete listo: %i tornillos de tipo %s "
                        "(mediana: %i)\n", paquete.getLimite(),
                        paquete.getNombre().c_str(), mediana);
                paquete.limpiarAnchos();
                paquete.setCantidad(0);
                if (cant > 0 && cant < paquete.getLimite()) {
                    paquete.setCantidad(paquete.getCantidad() + cant);
                    paquete.addAnchos(ancho, cant);
                    cant = 0;
                }
            }
        } else {
            paquete.setCantidad(paquete.getCantidad() + cant);
            paquete.addAnchos(ancho, cant);
        }
        paquete.swap(this->empaquetador[tipo]);
    }
}

Empaquetador::~Empaquetador() {
}
