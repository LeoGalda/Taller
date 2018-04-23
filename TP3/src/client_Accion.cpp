#include "client_Accion.h"
#include <arpa/inet.h>

Accion::Accion() {
}

Accion::Accion(const Accion& orig) {
}

bool Accion::getEndiannes() {
    int16_t i = 1;
    int8_t *p = (int8_t *) & i;

    if (p[0] == 1) {
        return false;
    }
    return true;
}

Accion::~Accion() {
}

