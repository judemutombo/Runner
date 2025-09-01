#include "../include/NetTcpClient.h"
#include "NetTcpClient.h"

NetTcpClient::NetTcpClient() :
    NetSocket(1)
{
    socket_thread = std::thread(NetTcpClient::receive, this);
    socket_thread.join();
}

NetTcpClient::~NetTcpClient(){
#ifdef _WIN32
    closesocket(sockfd);
#else
    close(sockfd);
#endif
}

bool NetTcpClient::sendPacket(const Packet& pkt, int socket)
{
    return false;
}

std::string NetTcpClient::generateId()
{
    return std::string();
}

bool NetTcpClient::bind(std::string_view host, std::string_view port)
{
    setup(host, port);
    return _isConnected;
}

void NetTcpClient::receive()
{
    int numbytes;
    char messages[BUFFSIZE];
    while(1){
        if((numbytes = recv(sockfd, messages, BUFFSIZE - 1 , 0)) == -1){
            fprintf(stderr, "Could't receive  message from  socket.\n");
            break;
        }
        messages[numbytes] = '\0';
        printf("bytes received : %d \n", numbytes);
        printf("Message from client : %s\n", messages);
    } 
#ifdef _WIN32
        closesocket(sockfd);
#else
        close(sockfd);
#endif
    
}
