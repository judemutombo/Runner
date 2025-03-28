#ifndef NetSocket_H
#define NetSocket_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <stdio.h>
    #include <Ws2tcpip.h>
#endif

#ifdef __linux__
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <fcntl.h>
#endif

#include <string>

#define BUFFSIZE 256


class NetSocket
{
public:
    NetSocket(std::string host, std::string port, bool blocking, int type);
    virtual ~NetSocket();    
    void *get_in_addr(struct sockaddr *sa);
    int getSocketDescriptor();

protected:
    struct sockaddr_storage remote_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
    int sockfd;
    int type;
    std::string port;
    std::string host;
    bool blocking; 
};


#endif // NetSocket_H