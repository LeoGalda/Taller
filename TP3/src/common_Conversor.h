#ifndef COMMON_CONVERSOR_H
#define COMMON_CONVERSOR_H

#include <string>

#include "common_Buffer.h"


class Conversor {
public:
    Conversor();
    std::string convertirAString(Buffer *buffer) const;
    virtual ~Conversor();
private:
};

#endif
