#include "../include/NetUdpServer.h"

NetUdpServer::NetUdpServer(std::string host, std::string port, bool blocking) :
    NetSocket(host, port, blocking, 2)
{
    isBind = false;
    isListening = false;
    acceptingClient = BACKLOG;
    int yes=1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(char*) &yes, sizeof(int));

    if((status = bind(sockfd, res->ai_addr, res->ai_addrlen)) != 0){
        fprintf(stderr, "unable to bind socket : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    isBind = true;    
}

void NetUdpServer::receiving()
{
    if(!isBind){
        fprintf(stderr, "the socket was not binded");
        exit(EXIT_FAILURE);
    }
    std::cout << "waiting for data to read" << std::endl;
}
