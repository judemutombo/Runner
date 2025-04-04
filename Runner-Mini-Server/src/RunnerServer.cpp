#include "../include/RunnerServer.h"
#include <fstream>

RunnerServer::RunnerServer(std::string_view config) :
    fconfig(config)
{
    std::ifstream f(std::string(fconfig).c_str(), std::ifstream::in);
    if (!f.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        exit(EXIT_FAILURE);
    }
    jconfig = nlohmann::json::parse(f);

    setTcp(std::string_view(std::string(jconfig["tcphost"])), std::string_view(std::string(jconfig["tcpport"])));
    setUdp(std::string_view(std::string(jconfig["udphost"])), std::string_view(std::string(jconfig["udpport"])));
    tcp_thread.join();
    udp_thread.join();
}

RunnerServer::~RunnerServer() 
{
    delete tcpserver;
    delete udpserver;
}

void RunnerServer::setTcp(std::string_view host, std::string_view port)
{
    tcphost = host;
    tcpport = port;
    tcpserver = new NetTcpServer(host, port, false);
    tcpserver->setAcceptingClient(MAXPLAYER);
    if(!tcpserver->listening()){
        std::cerr << "server unable to listen";
        exit(EXIT_FAILURE);
    }
    tcp_thread = std::thread(&NetTcpServer::accepting, tcpserver);
}

void RunnerServer::setUdp(std::string_view host, std::string_view port)
{
    udphost = host;
    udpport = port;
    udpserver = new NetUdpServer(host, port, false);
    udp_thread = std::thread(&NetUdpServer::receiving, udpserver);
}

void RunnerServer::newPlayer(u_int64 socket)
{
    tcp_sockets.push_back(socket);
}

void RunnerServer::receivePosition(u_int64 socket, std::string_view message)
{

}