#include <iostream>
#include <stdio.h>
#include "Configurador.h"
#include "Empaquetador.h"
#include "ManejadorArch.h"
#include <vector>
#include <thread>

#define SUCCESS 0;
#define ERROR 1;

using std::cout;

int main(int argc, char *argv[]) {
    int cantidadMinimaDeParametros = 3;
    if (argc < cantidadMinimaDeParametros) {
        cout << "faltan archivos" << std::endl;
        return ERROR;
    }
    Empaquetador empaquetador;
    Configurador configurador(argv[1]);
    configurador.leerConfiguracion(&empaquetador);
    std::vector<Thread*> threads;
    int inicioDeParametrosALeer = 2;
    for (int j = inicioDeParametrosALeer; j < argc; ++j) {
        threads.push_back(new ManejadorArch(&empaquetador, argv[j]));
    }    
    size_t cantidad = threads.size();
    for (size_t i = 0; i < cantidad; ++i) {
        threads[i]->start();
    }
    
    for (size_t i = 0; i < cantidad; ++i) {
        threads[i]->join();
        delete threads[i];
    }
    empaquetador.mostrarRemanentes();
    return SUCCESS;
}
