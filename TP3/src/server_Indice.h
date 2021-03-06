#ifndef SERVER_INDICE_H
#define SERVER_INDICE_H

#include <map>
#include <string>
#include <vector>
#include <set>
#include <mutex>
#include "common_Buffer.h"
#include "common_File.h"
#include "server_Lock.h"

using std::vector;
using std::map;
using std::multimap;
using std::string;

class Indice {
private:
    char *nombreArchivo;
    multimap<string,string> hashDeTags;
    map<string,std::set<string>> hashDeArchivos;      
    std::mutex mute;
    
    void explode(const string &linea, vector<string> &vectoresDeString);
    void cargarDatosAMap(vector<string> &datos);
    
public:
//llama al constructor del indice y abre el archivo y lo guarda
//en sus atributos
    explicit Indice(char *ruta);    
       
//    Indice(Indice&& other);
    
//actualiza el indice    
    void actualizar();
    
//agrega un nuevo hash al indice    
    void agregar(const std::string nombreArch,const std::string hash,
                const std::string tipo);
    
//guarda en el segundo parametro los archivos de 
//los tagg que fueron pasado en el primer parametro
    void getArchivosTaggeados(const std::string tag,
                                std::set<string> &archivosTaggeados);
    
//valida si existe en nombre y el hash pasado por parametro    
    char validarHashes(const std::string &nombre,const std::string &hash);
    
//valida si existe la version pasada por parametro    
    unsigned char validarVersion(const std::string &version);
    
//valida si existe el hash pasado por parametro    
    unsigned char validarHashExiste(const std::string &hash);
    
//devuelve si el elemento pasado por parametro corresponde a 
//un archivo o a un tag    
    bool soyArchivo(const std::string data);
    
//destructor del indice    
    virtual ~Indice();
};

#endif
