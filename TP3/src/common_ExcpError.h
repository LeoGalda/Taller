#ifndef COMMON_EXCPERROR_H
#define COMMON_EXCPERROR_H

#include <exception>
#include <typeinfo>
#include <string>

class ExcpError : public std::exception {
private:
    std::string mensaje;
public:
//constructor de la ExcpError    
    ExcpError(const std::string &message, int line);

//devuelve el mensaje de la excepcion    
    virtual const char *what() const noexcept;
    
//destructor de la excpError    
    virtual ~ExcpError() noexcept;
};

#endif

