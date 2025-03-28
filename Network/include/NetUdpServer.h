#ifndef NetUdpServer_H
#define NetUdpServer_H

#include "NetSocket.h"
#include <iostream>
#define BACKLOG 10

class NetUdpServer : public NetSocket{
public :
    NetUdpServer(std::string host, std::string port, bool blocking);
    void receiving();
private:
    bool isBind;
    bool isListening; 
    int acceptingClient;
};


#endif // NetUdpServer_H