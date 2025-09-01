#ifndef NETTCPCLIENT_H
#define NETTCPCLIENT_H


#include <string_view>
#include "NetSocket.h"
#include "GamePacket.h"
#include "Signal/Signal.h"

class NetTcpClient : public NetSocket
{
public:
    NetTcpClient();
    ~NetTcpClient();
    bool sendPacket(const Packet& pkt, int socket) override;
    std::string generateId() override;
    bool bind(std::string_view host, std::string_view port);
    Signal<const GamePacket&> ByteAvailable;
private:
    void receive();
};

#endif // NETTCPCLIENT_H
