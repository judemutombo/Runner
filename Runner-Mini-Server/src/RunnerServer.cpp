#include "../include/RunnerServer.h"

RunnerServer::RunnerServer(std::string config) :
    config(config)
{

}

RunnerServer::~RunnerServer() 
{
    delete tcpserver;
    delete udpserver;
}

void RunnerServer::setTcp(std::string host, std::string port)
{
    tcphost = host;
    tcpport = port;
    tcpserver = new NetTcpServer(host, port, true);
    tcpserver->setAcceptingClient(MAXPLAYER);
}

void RunnerServer::setUdp(std::string host, std::string port)
{
    udphost = host;
    udpport = port;
    udpserver = new NetUdpServer(host, port, true);
}