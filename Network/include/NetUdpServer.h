#ifndef NetUdpServer_H
#define NetUdpServer_H

#include "NetSocket.h"
#include <iostream>
#include <string_view>


class NetUdpServer : public NetSocket{
public :
    NetUdpServer(std::string_view host, std::string_view port, bool blocking);
    void receiving();
private:
    bool isBind;
    bool isListening; 
};


#endif // NetUdpServer_H