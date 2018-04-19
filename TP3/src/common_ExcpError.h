#ifndef EXCPERROR_H
#define EXCPERROR_H

#include <exception>
#include <typeinfo>
#include <string>

class ExcpError : std::exception {
private:
    std::string mensaje;
public:
    ExcpError(std::string &message, int line);
    virtual const char *what() const noexcept;
    virtual ~ExcpError() noexcept;
};

#endif

