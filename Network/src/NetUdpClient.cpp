#include "../include/NetUdpClient.h"



NetUdpClient::NetUdpClient() :
    NetSocket(2)
{
    
}

NetUdpClient::~NetUdpClient()
{
#ifdef _WIN32
    closesocket(sockfd);
#else
    close(sockfd);
#endif
}

bool NetUdpClient::send(const Packet& pkt)
{
    return false;
}

std::string NetUdpClient::generateId()
{
    return "";
}