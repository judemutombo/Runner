#include "../include/NetClient.h"



NetClient::NetClient(std::string host, std::string port, bool blocking) :
    NetSocket(host, port, blocking, 1)
{
    isConnected = false;
}

NetClient::~NetClient()
{
#ifdef _WIN32
    closesocket(sockfd);
#else
    close(sockfd);
#endif
}

void NetClient::connection()
{
    if((status = connect(sockfd, res->ai_addr, res->ai_addrlen)) != 0){
        fprintf(stderr, "unable to connect socket : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    inet_ntop(res->ai_family,get_in_addr((struct sockaddr *)res->ai_addr), ipstr, sizeof ipstr);
    printf("Client is connected to :  %s\n", ipstr);
}