#ifndef ACCIONPULL_H
#define ACCIONPULL_H

#include "client_Accion.h"

class AccionPull : public Accion {
private:    
public:
    AccionPull();
    AccionPull(const AccionPull& orig);
    virtual ~AccionPull();
};

#endif /* ACCIONPULL_H */

