#ifndef NetTcpServer_H
#define NetTcpServer_H

#include <vector>
#include "NetSocket.h"
#include <string_view>
#include <iostream>
#include <string.h>
#include <thread>

#define BACKLOG 6

class NetTcpServer : public NetSocket{
public :
    NetTcpServer();
    ~NetTcpServer();
    bool startListening(std::string_view host, std::string_view port);
    bool isListening() const;
    void setAcceptingClient(int value);
    std::string generateId() override;
    bool sendPacket(const Packet& pkt, int socket) override;

    Signal<int> incomingConnection;
private:
    bool isBind;
    bool _isListening; 
    int acceptingClient;
    std::vector<int> clients;
    std::thread socket_accepting_thread;
    
    void accepting();
};


#endif // NetServer_H