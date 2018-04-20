#include "cliente.h"

Cliente::Cliente(char *ip, char *puerto):socket(puerto,ip) {
    
}

Cliente::~Cliente() {
}

