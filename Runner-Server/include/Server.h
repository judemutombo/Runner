#include <string_view>
#include <thread>
#include "NetTcpServer.h"
#include "../externals/nlohmann/json.hpp"
#include <map>
#include <vector>
#include <atomic>

class Server
{
private:

    NetTcpServer* playerTcpserver;
    NetTcpServer* serverTcpserver;

    std::string_view fconfig;
    nlohmann::json jconfig;

    std::vector<std::thread> p_exchange_threads;
    std::vector<std::thread> ms_exchange_threads;


    void runPlayerServer(std::string_view host, std::string_view port);
    void runMiniServer(std::string_view host, std::string_view port);

    void newPlayer(int socket);
    void newMiniServer(int socket);

    void playerInteraction(int socket);
public:
    Server(std::string_view config);
    ~Server();
};


