#include "Server.h"
#include <fstream>

Server::Server(std::string_view config) : fconfig(config)
{
    std::ifstream f(std::string(fconfig).c_str(), std::ifstream::in);
    if (!f.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        exit(EXIT_FAILURE);
    }
    jconfig = nlohmann::json::parse(f);

    runMiniServer(std::string(jconfig["miniHost"]), std::string_view(std::string(jconfig["miniPort"])));
    runPlayerServer(std::string(jconfig["playerHost"]), std::string_view(std::string(jconfig["playerPort"])));
}

Server::~Server()
{
    delete playerTcpserver;
    delete serverTcpserver;
}

void Server::runPlayerServer(std::string_view host, std::string_view port){
    playerTcpserver = new NetTcpServer();
    playerTcpserver->startListening(host, port);
    playerTcpserver->setAcceptingClient(50);
    if(!playerTcpserver->isListening()){
        std::cerr << "player server unable to listen";
        exit(EXIT_FAILURE);
    }
    playerTcpserver->incomingConnection.connect(this, &Server::newPlayer);
}

void Server::runMiniServer(std::string_view host, std::string_view port){
    serverTcpserver = new NetTcpServer();
    serverTcpserver->setAcceptingClient(15);
    serverTcpserver->startListening(host, port);
    if(!serverTcpserver->isListening()){
        std::cerr << "mini server unable to listen";
        exit(EXIT_FAILURE);
    }
    playerTcpserver->incomingConnection.connect(this, &Server::newMiniServer);
}

void Server::newPlayer(int socket)
{
    std::cout << "new player " << std::endl;
}

void Server::newMiniServer(int socket)
{
    std::cout << "new player " << std::endl;
}

void Server::playerInteraction(int socket)
{
    int numbytes;
    char messages[BUFFSIZE];
    while(1){
        if((numbytes = recv(socket, messages, BUFFSIZE - 1 , 0)) == -1){
            fprintf(stderr, "Could't receive  message from  client.\n");
            break;
        }
        messages[numbytes] = '\0';
        printf("bytes received : %d \n", numbytes);
        printf("Message from client : %s\n", messages);
        /* if(send(socket, notification, strlen(notification), 0) == -1){
            perror("could not send message to socket\n");
            break;
        }  */
    } 
#ifdef _WIN32
        closesocket(socket);
#else
        close(socket);
#endif
}
