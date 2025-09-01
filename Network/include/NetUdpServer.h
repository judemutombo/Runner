#ifndef NetUdpServer_H
#define NetUdpServer_H

#include "NetSocket.h"
#include <iostream>
#include <string_view>
#include <vector>

typedef struct {
    struct sockaddr_storage addr;
    bool active;
    std::string id;

} ClientInfo;

class NetUdpServer : public NetSocket{
public :
    NetUdpServer();
    bool open(std::string_view host, std::string_view port);
    bool isNewClient(const struct sockaddr_storage& newaddr);
    std::string generateId() override;
    bool sendPacket(const Packet& pkt, int socket) override;

private:
    bool isBind;
    bool isListening; 
    std::vector<ClientInfo> clients;
    
    void receive();
};


#endif // NetUdpServer_H