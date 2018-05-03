#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "server_Indice.h"

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
    std::vector<string> aux;
    aux = datos;
    aux.erase(aux.end());
    aux.erase(aux.begin());
    aux.erase(aux.begin());
    this->hashDeTags.insert(std::pair<string, string>(datos[0], datos[1]));
    this->hashDeArchivos[datos[1]] = aux;
}

void Indice::actualizar() {
    File file(this->nombreArchivo, std::ios::out);
    std::multiset<std::pair<string, string>> aux;
    multimap<string, string>::iterator i;
    std::multiset<std::pair<string, string>>::iterator i2;
    for (i = this->hashDeTags.begin(); i != this->hashDeTags.end(); i++) {
        aux.insert(std::pair<string, string>((*i).first, (*i).second));
    }
    string infoAEnviar;
    std::vector<string> vec;    
    for (i2 = aux.begin(); i2 != aux.end(); i2++) {
        infoAEnviar = i2->first;
        infoAEnviar.append(" ");
        infoAEnviar.append(i2->second);
        infoAEnviar.append(" ");
        vec = this->hashDeArchivos[i2->second];
        std::sort(vec.begin(), vec.end());
        for (size_t i = 0; i < vec.size(); i++) {
            infoAEnviar.append(vec[i]);
            infoAEnviar.append(" ");
        }
        infoAEnviar.append(";\n");
        file.escribirStr(infoAEnviar);
    }
}

void Indice::agregar(const std::string nombreArch, const std::string hash,string tipo) {
    std::vector<string> aux;
    std::cout << "NOMBRE QUE LLEGO:\n" << nombreArch << std::endl;
    std::cout << "HASH QUE LLEGO:\n" << hash << std::endl;
    auto search = this->hashDeArchivos.find(nombreArch);
    if (search != this->hashDeArchivos.end()) {        
        aux = this->hashDeArchivos[nombreArch];
        aux.push_back(hash);
        this->hashDeArchivos[nombreArch] = aux;
    } else {
        aux.push_back(hash);
        this->hashDeTags.insert(std::pair<string, string>(tipo, nombreArch));
        this->hashDeArchivos[nombreArch] = aux;
    }
}

Indice::~Indice() {
}

