#ifndef NetClient_H
#define NetClient_H

#include "NetSocket.h"
#include "GamePacket.h"

class NetUdpClient : public NetSocket{

public:
    NetUdpClient(std::string host, std::string port, bool blocking);
    ~NetUdpClient();
    bool send(const GamePacket& packet);
    std::string generateId() override;
private:
    bool isConnected;
    char userInput[BUFFSIZE];
    char messages[BUFFSIZE];
};

#endif // NetClient_H