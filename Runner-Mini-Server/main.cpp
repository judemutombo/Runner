#include <iostream>
#include "include/RunnerServer.h"
#include "../Network/include/GamePacket.h"

using json = nlohmann::json;


int main(int argc, char** argv){

    /* if(argc != 2){
        std::cout << "usage example : miniserver.exe configpath";
        exit(EXIT_FAILURE);
    }

    RunnerServer server(argv[1]); */
    
    GamePacket pkt;
    pkt.push(7);
    pkt.push(23.4f);
    pkt.push("hello");
    pkt.push("gain");
    pkt.push("summarize");
    pkt.push(52);
    pkt.push(2.4);
    pkt.push(12);
    pkt.push(-78);

    std::cout << pkt.getSequence() << std::endl;
    std::cout << pkt.getTypeSequence() << std::endl;
}

