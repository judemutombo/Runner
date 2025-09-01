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
    NetUdpServer(std::string_view host, std::string_view port, bool blocking);
    void receiving(/* void(*fn)(std::string_view, std::string_view) */);
    bool isNewClient(const struct sockaddr_storage& newaddr);
    std::string generateId() override;
    bool sendPacket(const packet& pkt, int socket) override;

private:
    bool isBind;
    bool isListening; 
    std::vector<ClientInfo> clients;
};


#endif // NetUdpServer_H