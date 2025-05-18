#ifndef NetSocket_H
#define NetSocket_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <Ws2tcpip.h>
#endif

#ifdef __linux__
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

#include <stdio.h>
#include <string>
#include <string_view>

#define BUFFSIZE 256


class NetSocket 
{
public:
    NetSocket(std::string_view host, std::string_view port, bool blocking, int type);
    virtual ~NetSocket();    
    void *get_in_addr(struct sockaddr *sa);
    int getSocketDescriptor();
    virtual std::string generateId() = 0;

protected:
    struct sockaddr_storage remote_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
    int sockfd;
    int type;
    std::string_view port;
    std::string_view host;
    bool blocking; 
};


#endif // NetSocket_H