#include "../include/NetSocket.h"
#include "NetSocket.h"

NetSocket::NetSocket(std::string host, std::string port, bool blocking, int type) :
    host(host), port(port), blocking(blocking), type(type)
{
#ifdef _WIN32
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(EXIT_FAILURE);
    }

    if (LOBYTE(wsaData.wVersion) != 2 ||
    HIBYTE(wsaData.wVersion) != 2)
    {
        fprintf(stderr,"Version 2.2 of Winsock not available.\n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }  
#endif

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = type == 1 ? SOCK_STREAM : SOCK_DGRAM;
    if ((status = getaddrinfo(host.c_str(), port.c_str(), &hints, &res)) != 0) {

        fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(blocking){
        #ifdef _WIN32  
            u_long mode = 1;
            if (ioctlsocket(sockfd, FIONBIO, &mode) != 0) {
                printf("Failed to set non-blocking mode: %d\n", WSAGetLastError());
                closesocket(sockfd);
                WSACleanup();
                exit(EXIT_FAILURE);
            }
        #else
            fcntl(sockfd, F_SETFL, O_NONBLOCK);
        #endif
    }

    if(sockfd == -1 ){
        perror("unable to get socket\n");
        exit(EXIT_FAILURE);
    }
}

NetSocket::~NetSocket()
{    
    freeaddrinfo(res);
}

void *NetSocket::get_in_addr(sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int NetSocket::getSocketDescriptor()
{
    return sockfd;
}