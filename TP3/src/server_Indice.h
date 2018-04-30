#ifndef SERVER_INDICE_H
#define SERVER_INDICE_H

#include <map>
#include <string>
#include <vector>

class Indice {
private:
//    std::map<char, std::pair<std::string,std::vector<std::string>>> indice;
public:
    Indice();
    Indice(const Indice& orig);
    virtual ~Indice();
};

#endif