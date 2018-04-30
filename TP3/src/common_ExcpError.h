#ifndef COMMON_EXCPERROR_H
#define COMMON_EXCPERROR_H

#include <exception>
#include <typeinfo>
#include <string>

class ExcpError : public std::exception {
private:
    std::string mensaje;
public:
    ExcpError(std::string &message, int line);
    virtual const char *what() const noexcept;
    virtual ~ExcpError() noexcept;
};

#endif

