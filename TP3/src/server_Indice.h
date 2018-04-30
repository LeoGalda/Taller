#ifndef SERVER_INDICE_H
#define SERVER_INDICE_H

#include <map>
#include <string>
#include <vector>

#include "common_File.h"

class Indice {
private:
    std::map<char, std::pair<std::string,std::vector<std::string>>> indice;
    File file;
public:
    explicit Indice(char *ruta);    
    virtual ~Indice();
};

#endif