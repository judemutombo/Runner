#ifndef NetTcpServer_H
#define NetTcpServer_H

#include "NetSocket.h"
#define BACKLOG 10

class NetTcpServer : public NetSocket{
public :
    NetTcpServer(std::string host, std::string port, bool blocking);
    bool listening();
    virtual void accepting();
    void setAcceptingClient(int value);
private:
    bool isBind;
    bool isListening; 
    int acceptingClient;
};


#endif // NetServer_H