#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <cstring>
#include "server_Indice.h"

#define ERROR 0
#define SUCCESS 1

Indice::Indice(char *ruta) : nombreArchivo(ruta) {
    File file(ruta, std::ios::in);
    while (!file.estaFin()) {
        std::vector<std::string> datos;
        std::string linea;
        file.getLinea(linea);
        if (!file.estaFin()) {
            this->explode(linea, datos);
            this->cargarDatosAMap(datos);
        }
    }
}

Indice::Indice(Indice&& other){
    this->convertidor = other.convertidor;
    this->hashDeArchivos = other.hashDeArchivos;
    this->hashDeTags = other.hashDeTags;
    this->nombreArchivo = other.nombreArchivo;
    other.hashDeArchivos.clear();
    other.hashDeTags.clear();
    other.nombreArchivo = nullptr;
}

void Indice::explode(const std::string &linea, std::vector<std::string> &datos){
    size_t pos1 = 0;
    size_t pos2 = 0;
    while (pos2 != linea.npos) {
        pos2 = linea.find(" ", pos1);
        if (pos2 != linea.npos) {
            if (pos2 > pos1) {
                datos.push_back(linea.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }
    }
    datos.push_back(linea.substr(pos1, linea.size() - pos1));
}

void Indice::cargarDatosAMap(std::vector<std::string>& datos) {
    string nomArch = datos[1];
    this->hashDeTags.insert(std::pair<string, string>(datos[0], nomArch));
    std::set<string> aux;
    datos.erase(datos.end());
    datos.erase(datos.begin());
    datos.erase(datos.begin());
    for (size_t i = 0; i < datos.size(); i++) {
        aux.insert(datos[i]);
    }
    this->hashDeArchivos[nomArch] = aux;
}

void Indice::actualizar() {
    printf("voy a actualizar gil\n");
    File file(this->nombreArchivo, std::ios::out);
    std::multiset<std::pair<string, string>> aux;
    multimap<string, string>::iterator i;
    std::multiset<std::pair<string, string>>::iterator i2;
    for (i = this->hashDeTags.begin(); i != this->hashDeTags.end(); i++) {
        printf("encontre elementos de hashDeTags");
        aux.insert(std::pair<string, string>((*i).first, (*i).second));
    }
    string infoAEnviar;
    std::set<string> vec;
    for (i2 = aux.begin(); i2 != aux.end(); i2++) {
        printf("entre al segundo forrrr\n");
        infoAEnviar = i2->first;
        infoAEnviar.append(" ");
        infoAEnviar.append(i2->second);
        infoAEnviar.append(" ");
        vec = this->hashDeArchivos[i2->second];
        for (std::set<string>::iterator itSet = vec.begin(); 
                                                itSet != vec.end(); ++itSet) {
            infoAEnviar.append(*itSet);
            infoAEnviar.append(" ");
        }
        infoAEnviar.append(";\n");        
//        file.escribirStr(infoAEnviar);
        file.escribir(infoAEnviar);
    }
}

void Indice::agregar(const std::string nombreArch, const std::string hash,
        string tipo) {
    std::set<string> aux;
    auto search = this->hashDeArchivos.find(nombreArch);
    if (search != this->hashDeArchivos.end()) {
        aux = this->hashDeArchivos[nombreArch];
        aux.insert(hash);
        this->hashDeArchivos[nombreArch] = aux;
    } else {
        aux.insert(hash);
        this->hashDeTags.insert(std::pair<string, string>(tipo, nombreArch));
        this->hashDeArchivos[nombreArch] = aux;
    }
}

void Indice::getArchivosTaggeados(Buffer *buffer,
        std::set<string>& archivosTaggeados) {     
    string tag = this->convertidor.convertirAString(buffer);            
    auto search = this->hashDeArchivos.find(tag);
    if (search != this->hashDeArchivos.end()) {
        archivosTaggeados = this->hashDeArchivos[tag];
    }
}

char Indice::validarHashes(Buffer *bufNombre, Buffer *bufHash) {
    string nombreABuscar = this->convertidor.convertirAString(bufNombre);
    string hashABuscar = this->convertidor.convertirAString(bufHash);
    auto search = this->hashDeArchivos.find(nombreABuscar);
    if (search != this->hashDeArchivos.end()) {
        auto search2 = this->hashDeArchivos[nombreABuscar].find(hashABuscar);
        if (search2 != this->hashDeArchivos[nombreABuscar].end()){
            return ERROR;
        }
    }
    return SUCCESS;
}

unsigned char Indice::validarVersion(Buffer* bufVersion){
    string versionABuscar = this->convertidor.convertirAString(bufVersion);
    auto search = this->hashDeArchivos.find(versionABuscar);
    if (search != this->hashDeArchivos.end()){
        return ERROR;
    }
    return SUCCESS;
}

unsigned char Indice::validarHashExiste(Buffer* bufHash) {    
    map<string,std::set<string>>::iterator it;
    string dataHash = this->convertidor.convertirAString(bufHash);
    for (it = this->hashDeArchivos.begin(); it!=this->hashDeArchivos.end();
                                                        ++it){
        std::set<string>::iterator search = 
                it->second.find(dataHash);
        if (search != it->second.end()){
            return SUCCESS;
        }
    }
    return ERROR;
}


Indice::~Indice() {
}

