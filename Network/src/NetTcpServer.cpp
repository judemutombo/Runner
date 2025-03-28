#include "../include/NetTcpServer.h"

NetTcpServer::NetTcpServer(std::string host, std::string port, bool blocking) :
    NetSocket(host, port, blocking, 1)
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

bool NetTcpServer::listening()
{
    if((status = listen(sockfd, acceptingClient)) != 0 ){
        fprintf(stderr, "unable to listen from socket : %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    printf("server is listening to port : %s\n", port.c_str());
    isListening = true;
    return isListening;
}

void NetTcpServer::accepting()
{
    if(!isBind || !isListening){
        fprintf(stderr, "the socket is either not binded or not listening");
        exit(EXIT_FAILURE);
    }


    addr_size = sizeof remote_addr;
    int numbytes;
    while (1)
    {
        int incomingSocket = accept(sockfd, (struct sockaddr *)&remote_addr, &addr_size);
        if(incomingSocket == -1){
            fprintf(stderr, "unable to accept incomming socket\n");
            continue;
        }
        inet_ntop(remote_addr.ss_family,get_in_addr((struct sockaddr *)&remote_addr), ipstr, sizeof ipstr);
        printf("server: got connection from %s\n", ipstr);

        char messages[BUFFSIZE];
        const char* notification = std::string("Message received").c_str();
        while(1){
            if((numbytes = recv(incomingSocket, messages, BUFFSIZE , 0)) == -1){
                fprintf(stderr, "Could't receive  message from  client.\n");
                break;
            }
            messages[numbytes-1] = '\0';
            printf("bytes received : %d \n", numbytes);
            printf("Message from client : %s\n", messages);
            if(send(incomingSocket, notification, strlen(notification), 0) == -1){
                perror("could not send message to socket\n");
                break;
            } 
        }
#ifdef _WIN32
        closesocket(incomingSocket);
#else
        close(incomingSocket);
#endif
    }
}

void NetTcpServer::setAcceptingClient(int value)
{
    acceptingClient = value;
}