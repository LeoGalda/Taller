#ifndef SERVER_INDICE_H
#define SERVER_INDICE_H

#include <map>
#include <string>
#include <vector>

#include "common_File.h"

using std::vector;
using std::map;
using std::multimap;
using std::string;

class Indice {
private:
    char *nombreArchivo;
    multimap<string,string> hashDeTags;
    map<string,vector<string>> hashDeArchivos;    
    
    void explode(const string &linea, 
                 vector<string> &vectoresDeString);
    void cargarDatosAMap(vector<string> &datos);
public:
    explicit Indice(char *ruta);    
    void actualizar();
    void agregar(const std::string nombreArch,const std::string hash,
                const std::string tipo);
    virtual ~Indice();
};

#endif
