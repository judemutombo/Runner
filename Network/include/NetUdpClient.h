#ifndef NETUPDCLIENT_H
#define NETUPDCLIENT_H

#include "NetSocket.h"
#include "GamePacket.h"

class NetUdpClient : public NetSocket{

public:
    NetUdpClient();
    ~NetUdpClient();
    bool send(const Packet& pkt);
    std::string generateId() override;
private:
    char userInput[BUFFSIZE];
    char messages[BUFFSIZE];
};

#endif // NETUPDCLIENT_H