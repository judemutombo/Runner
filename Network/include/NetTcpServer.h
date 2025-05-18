#ifndef NetTcpServer_H
#define NetTcpServer_H

#include <vector>
#include "NetSocket.h"
#include <string_view>
#include <iostream>
#include <string.h>

#define BACKLOG 6

class NetTcpServer : public NetSocket{
public :
    NetTcpServer(std::string_view host, std::string_view port, bool blocking);
    bool listening();
    void accepting();
    void setAcceptingClient(int value);
    std::string generateId() override;

private:
    bool isBind;
    bool isListening; 
    int acceptingClient;
    std::vector<int> clients;
};


#endif // NetServer_H