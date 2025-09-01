#include "../include/NetTcpServer.h"
#include "NetTcpServer.h"


NetTcpServer::NetTcpServer() :
    NetSocket(1)
{
    isBind = false;
    _isListening = false;
    acceptingClient = BACKLOG;
    
}

NetTcpServer::~NetTcpServer()
{
    if(socket_thread.joinable())
        socket_thread.join();
}

bool NetTcpServer::startListening(std::string_view host, std::string_view port)
{
    setup(host, port);
    
    if(!_isConnected){
        return false;
    }

    int yes=1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(char*) &yes, sizeof(int));

    if((status = bind(sockfd, res->ai_addr, res->ai_addrlen)) != 0){
        fprintf(stderr, "unable to bind socket : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    isBind = true;    

    if((status = listen(sockfd, acceptingClient)) != 0 ){
        fprintf(stderr, "unable to listen from socket : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    std::cout << "server is listening to port : " << port << std::endl;
    _isListening = true;

    socket_thread = std::thread(NetTcpServer::accepting, this);
    return _isListening;
}

bool NetTcpServer::isListening() const
{
    return _isListening;
}

void NetTcpServer::accepting()
{
    
    std::cout << "start " << std::endl;
    if(!isBind || !_isListening){
        fprintf(stderr, "the socket is either not binded or not listening");
        exit(EXIT_FAILURE);
    }


    addr_size = sizeof remote_addr;
    while (1)
    {
        int incomingSocket = accept(sockfd, (struct sockaddr *)&remote_addr, &addr_size);
        if(incomingSocket == -1){
            fprintf(stderr, "unable to accept incomming socket\n");
            continue;
        }
        clients.push_back(incomingSocket);
        inet_ntop(remote_addr.ss_family,get_in_addr((struct sockaddr *)&remote_addr), ipstr, sizeof ipstr);
        printf("server: got connection from %s\n", ipstr);

        incomingConnection.emit(incomingSocket);
    }
    std::cout << "finished " << std::endl;
}

void NetTcpServer::setAcceptingClient(int value)
{
    acceptingClient = value;
}

std::string NetTcpServer::generateId()
{
    return "";
}

bool NetTcpServer::sendPacket(const Packet& pkt, int socket)
{
    
    if(send(socket,reinterpret_cast<const char*>(&pkt), sizeof(pkt), 0) == -1){
        perror("could not send message to socket\n");
        return false;
    } 
    return true;
}