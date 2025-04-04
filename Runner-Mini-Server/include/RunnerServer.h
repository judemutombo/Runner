#ifndef RunnerServer_H
#define RunnerServer_H
#include "../../Network/include/NetTcpServer.h"
#include "../../Network/include/NetUdpServer.h"
#include "../externals/nlohmann/json.hpp"
#include <string>
#include <vector>
#include <string_view>
#include <thread>
#define MAXPLAYER 10


class RunnerServer{
public : 
    RunnerServer(std::string_view config);
    ~RunnerServer();
    void setTcp(std::string_view host, std::string_view port);
    void setUdp(std::string_view host, std::string_view port);
    void newPlayer(u_int64 socket);
    void receivePosition(u_int64 socket, std::string_view message);

private :
    std::string_view tcphost;
    std::string_view tcpport;
    
    std::string_view udphost;
    std::string_view udpport;
    std::string_view fconfig;
    nlohmann::json jconfig;
    
    NetTcpServer* tcpserver;
    NetUdpServer* udpserver;
    bool raceStarted;

    std::vector<u_int64> tcp_sockets;

    std::thread tcp_thread;
    std::thread udp_thread;
};
#endif // RunnerServer_H