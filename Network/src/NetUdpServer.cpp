#include "../include/NetUdpServer.h"

NetUdpServer::NetUdpServer(std::string_view host, std::string_view port, bool blocking) :
    NetSocket(host, port, blocking, 2)
{
    isBind = false;
    isListening = false;
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
    std::cout << "waiting for data to read to port : " << port << std::endl;
    addr_size = sizeof remote_addr;
    char message[BUFFSIZE];
    int numbytes;
    while (true)
    {
        if((numbytes = recvfrom(sockfd, message, BUFFSIZE-1, 0, (struct sockaddr *)&remote_addr, &addr_size)) == -1){
            fprintf(stderr, "Couldn't receive  message from  client.\n");
            continue;
        }

        inet_ntop(remote_addr.ss_family,get_in_addr((struct sockaddr *)&remote_addr), ipstr, sizeof ipstr);
        printf("server: got message from %s\n", ipstr);

        message[numbytes] = '\0';
        printf("bytes received : %d \n", numbytes);
        printf("Message from client : %s\n", message);
    }
    
}
