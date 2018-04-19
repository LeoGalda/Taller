#ifndef ACCIONTAG_H
#define ACCIONTAG_H

#include "Accion.h"

class AccionTag : public Accion {
private:    
public:
    AccionTag();
    AccionTag(const AccionTag& orig);
    virtual ~AccionTag();
};

#endif /* ACCIONTAG_H */

