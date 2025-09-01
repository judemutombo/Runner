#include "NetTcpClient.h"
#include "Signal/Signal.h"


class Network
{
private:
    NetTcpClient* socketToMainServer;
    NetTcpClient* socketToMiniServer;

public:
    Network(/* args */);
    ~Network();

    bool requestParty();

};


