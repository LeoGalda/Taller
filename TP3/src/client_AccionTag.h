#ifndef CLIENT_ACCIONTAG_H
#define CLIENT_ACCIONTAG_H

#include <vector>
#include <string>
#include "common_Accion.h"

class AccionTag : public Accion {
private:
    std::string version;
    std::vector<std::string> hashes;
    std::vector<unsigned char> data;
public:
    explicit AccionTag(char *version);
    void ejecutar();
    void enviar(Socket *socket);
    void responder(Socket *socket);
    void agregarHash(char *hash);
    int getValorNumerico();
    int getTamanio();
    virtual ~AccionTag();
};

#endif

