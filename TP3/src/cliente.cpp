#include "cliente.h"

Cliente::Cliente() {
}

Cliente::Cliente(char *ip, char *puerto):socket(ip,puerto) {
    
}

Cliente::~Cliente() {
}

