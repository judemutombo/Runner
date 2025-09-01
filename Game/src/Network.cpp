#include "../includes/Network.h"

Network::Network()
{
    socketToMainServer = new NetTcpClient("localhost", "5010", false);
    if(!socketToMainServer->isConnected()){
        std::cout << "socket not connected" << std::endl;
    }
}

Network::~Network()
{
    delete socketToMainServer;
    delete socketToMiniServer;
}

bool Network::requestParty()
{

    return false;
}
