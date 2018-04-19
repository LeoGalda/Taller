#include <cstdlib>
#include <iostream>
#include "cliente.h"

using std::cout;

int main(int argc, char* argv[]) {
    try{
        Cliente cliente(argv[0],argv[1]);    
        cliente.ejecutar(argv)
    } catch(const std::exception &exc){
        syslog(LOG_ERR,"Error: %s", exc.what());   
        return 1;
    } catch(...){
        syslog(LOG_ERR,"Error en cliente: NO TENGO NI PUTA IDEA QUE PASO");        
        return 1;
    }
    return 0;
}

