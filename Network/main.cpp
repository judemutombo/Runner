#include "include/NetTcpServer.h"
#include "include/GamePacket.h"
#include <iostream>

int main(){

    GamePacket pkt;
    pkt.push(45);
    pkt.push(23.4);
    pkt.push("hello");

    std::cout << pkt.getSequence() << std::endl;
}