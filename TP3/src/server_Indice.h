#ifndef SERVER_INDICE_H
#define SERVER_INDICE_H

#include <map>
#include <string>
#include <vector>
#include <set>

#include "common_Buffer.h"
#include "common_Conversor.h"
#include "common_File.h"

using std::vector;
using std::map;
using std::multimap;
using std::string;

class Indice {
private:
    char *nombreArchivo;
    multimap<string,string> hashDeTags;
    map<string,std::set<string>> hashDeArchivos;    
    Conversor convertidor;    
    
    void explode(const string &linea, vector<string> &vectoresDeString);
    void cargarDatosAMap(vector<string> &datos);
public:
    explicit Indice(char *ruta);    
    void actualizar();
    void agregar(const std::string nombreArch,const std::string hash,
                const std::string tipo);
    void getArchivosTaggeados(Buffer *buffer,std::set<string> &archivosTaggeados);
    char validarHashes(Buffer *bufNombre,Buffer *bufHash);
    unsigned char validarVersion(Buffer *bufVersion);
    unsigned char validarHashExiste(Buffer *bufHash);
    virtual ~Indice();
};

#endif
