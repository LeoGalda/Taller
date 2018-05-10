#include "server_Aceptador.h"
#include "server_Conexion.h"
#include "server_Versionador.h"

Aceptador::Aceptador(char *puerto,Indice &indice): 
                                            indice(indice),finalizado(false){
    this->socket.doBind(puerto);
    this->socket.doListen();
}

void Aceptador::run(){
    while(!this->finalizado){
        Socket peerskt;
        this->socket.aceptar(&peerskt);
        if (!peerskt.isOnError()){
            Versionador *versionador = new Versionador(peerskt,this->indice);            
            versionador->start();
            this->threads.push_back(versionador);
        }        
        peerskt.destruir();
    }
}

void Aceptador::finalizar(){
    finalizado = true;
//    this->socket.cerrar();
    this->finalizarThreads();
}

void Aceptador::finalizarThreads(){
    for(size_t i = 0; i < this->threads.size(); i++){
        this->threads[i]->join();
        delete this->threads[i];        
    }    
}

Aceptador::~Aceptador() {
    this->finalizarThreads();
}

