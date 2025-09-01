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
#include <thread>
#include "GamePacket.h"
#include "Signal/Signal.h"
#define BUFFSIZE 256


class NetSocket 
{
public:
    NetSocket(int type);
    virtual ~NetSocket();    
    void *get_in_addr(struct sockaddr *sa);
    int getSocketDescriptor();
    virtual std::string generateId() = 0;
    virtual bool sendPacket(const Packet& pkt, int socket) = 0;
    bool isConnected();
    bool setBlocking(bool b);
protected:
    void setup(std::string_view host, std::string_view port);
    struct sockaddr_storage remote_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
    int sockfd;
    int type;
    bool blocking; 
    bool _isConnected;

    std::thread socket_thread;
    
};


#endif // NetSocket_H