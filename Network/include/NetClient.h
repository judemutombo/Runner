#ifndef NetClient_H
#define NetClient_H

#include "NetSocket.h"

class NetClient : public NetSocket{

public:
    NetClient(std::string host, std::string port, bool blocking);
    ~NetClient();
    void connection();
private:
    bool isConnected;
    char userInput[BUFFSIZE];
    char messages[BUFFSIZE];
};

#endif // NetClient_H