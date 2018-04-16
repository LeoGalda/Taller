#include <iostream>
#include <stdio.h>
#include "Configurador.h"
#include "Empaquetador.h"
#include "ManejadorArch.h"
#include <vector>
#include <thread>

using std::cout;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "faltan archivos" << std::endl;
        return 1;
    }
    Empaquetador empaquetador;
    Configurador configurador(argv[1]);
    configurador.leerConfiguracion(&empaquetador);
    std::vector<Thread*> threads;
    for (int j = 2; j < argc; ++j) {
        threads.push_back(new ManejadorArch(&empaquetador, argv[j] ));
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
    return 0;
}
