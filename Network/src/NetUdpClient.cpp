#include "../include/NetUdpClient.h"



NetUdpClient::NetUdpClient(std::string host, std::string port, bool blocking) :
    NetSocket(host, port, blocking, 2)
{
    isConnected = false;
}

NetUdpClient::~NetUdpClient()
{
#ifdef _WIN32
    closesocket(sockfd);
#else
    close(sockfd);
#endif
}

bool NetUdpClient::send(const packet& pkt)
{
    return false;
}

std::string NetUdpClient::generateId()
{
    return "";
}