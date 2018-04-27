#ifndef COMMON_VERSIONADO_H
#define COMMON_VERSIONADO_H

#include <map>
#include <string>

class Versionado {
private:
    std::map<std::string,std::string> version;
public:
    Versionado();
    Versionado(const Versionado& orig);
    virtual ~Versionado();


};

#endif

