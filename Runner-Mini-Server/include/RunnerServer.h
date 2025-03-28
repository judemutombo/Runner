#ifndef RunnerServer_H
#define RunnerServer_H
#include "../../Network/include/NetTcpServer.h"
#include "../../Network/include/NetUdpServer.h"
#include <string>

#define MAXPLAYER 10

class RunnerServer{
public : 
    RunnerServer(std::string config);
    ~RunnerServer();
    void setTcp(std::string host, std::string port);
    void setUdp(std::string host, std::string port);
private :
    std::string tcphost;
    std::string tcpport;
    
    std::string udphost;
    std::string udpport;
    std::string config;
    
    NetTcpServer* tcpserver;
    NetUdpServer* udpserver;
    bool raceStarted;
};
#endif // RunnerServer_H