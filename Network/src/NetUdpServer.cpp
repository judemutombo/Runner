#include "../include/NetUdpServer.h"
#include <random>

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

void NetUdpServer::receiving(/* void(*fn)(std::string_view, std::string_view) */)
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

        if(isNewClient(remote_addr)){
            std::string id = generateId();
            ClientInfo info = {remote_addr, true, id};
            std::cout << "id : " << id <<std::endl;
            clients.push_back(info);
        }
    }
    
}

bool NetUdpServer::isNewClient(const sockaddr_storage &newaddr)
{
    for(auto& client : clients){
        if (client.addr.ss_family == newaddr.ss_family) {
            if (client.addr.ss_family == AF_INET) {
                // Compare IPv4 addresses and ports
                sockaddr_in *client_addr_in = reinterpret_cast<sockaddr_in*>(&client.addr);
                const sockaddr_in *new_addr_in = reinterpret_cast<const sockaddr_in*>(&newaddr);
                if (client_addr_in->sin_addr.s_addr == new_addr_in->sin_addr.s_addr &&
                    client_addr_in->sin_port == new_addr_in->sin_port) {
                    return false;  // Found an existing client, so it's not new
                }
            } 
        }
    }
    return true;
}

std::string NetUdpServer::generateId()
{

    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 35);

    const char *v = "0123456789abcdefghijklmnopqrstuvwxyz";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}
