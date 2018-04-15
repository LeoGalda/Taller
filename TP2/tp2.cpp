#include <iostream>
#include <stdio.h>
#include "Empaquetador.h"
#include "ManejadorArch.h"

using std::cout;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "faltan archivos"<<std::endl;
        return 1;
    }
    Empaquetador empaquetador;
    ManejadorArch manejador;
    manejador.leerConfiguracion(&empaquetador, argv[1]);
    for (int j = 2; j < argc; j++) {        
        ManejadorArch manejador;
        manejador.parsearArchivo(&empaquetador, argv[j]);
    }
    empaquetador.mostrarRemanentes();
    return 0;
}
