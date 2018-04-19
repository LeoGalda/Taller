#ifndef SOCKET_H
#define SOCKET_H

class Socket {
private:
    char *puerto;
    char *ip;
    struct addrinfo *ptr;
    int sock, peerskt;
public:
    Socket();
    Socket(char *puerto, char *ip);
    virtual ~Socket();
};

#endif /* SOCKET_H */

