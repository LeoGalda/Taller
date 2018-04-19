#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <stdexcept>
#include "ExcpError.h"

ExcpError::ExcpError(std::string &e_msg, int line){    
    std::stringstream msg;
    msg << "ERROR LA PUTA MADRE:" << e_msg << " - line: " <<line <<"\n";    
    this->mensaje = msg.str();
}

//ExcpError::ExcpError(const char* fmt, ...) noexcept{    
//    int _errno = errno;
//    va_list args;
//    va_start(args, fmt);
//    int s = vsnprintf(msg_error, BUF_LEN, fmt, args);
//    va_end(args);
//    strncpy(msg_error + s, strerror(_errno), BUF_LEN - s);
//    msg_error[BUF_LEN - 1] = 0;
//}
//
//char* ExcpError::enviarError(const char *mje, ...) {
//    int size = 0;
//    char *p = NULL;
//    va_list ap;
//
//    va_start(ap, mje);
//    size = vsnprintf(p, size, mje, ap);
//    va_end(ap);
//
//    if (size < 0)
//        return NULL;
//
//    size++;
//    p = (char*) malloc(size);
//    if (p == NULL)
//        return NULL;
//
//    va_start(ap, mje);
//    size = vsnprintf(p, size, mje, ap);
//    if (size < 0) {
//        free(p);
//        return NULL;
//    }
//    va_end(ap);
//
//    return p;
//
//}


const char *ExcpError::what() const noexcept{
    return this->mensaje.c_str();
}

ExcpError::~ExcpError() noexcept{
}

