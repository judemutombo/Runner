#include <iostream>
#include "include/RunnerServer.h"


using json = nlohmann::json;


int main(int argc, char** argv){

    if(argc != 2){
        std::cout << "usage example : miniserver.exe configpath";
        exit(EXIT_FAILURE);
    }

    RunnerServer server(argv[1]);
    
    /* GamePacket pkt;
    pkt.push("hello gain summarize");
    pkt.push(7.3f);
    pkt.push(23.4f);
    pkt.push("hello gain summarize");
    pkt.push("hello gain summarize");
    pkt.push(2.4);
    pkt.push(-78);

    std::cout << pkt.getSequence() << std::endl;
    std::cout << pkt.getTypeSequence() << std::endl;
    
    auto val = pkt.pop();
    std::cout << val.type().name()<< ": " << std::any_cast<int>(val) << std::endl;

    auto val1 = pkt.pop();
    std::cout << val1.type().name()<< ": " << std::any_cast<double>(val1) << std::endl;

    auto val2 = pkt.pop();
    std::cout << val2.type().name()<< ": " << std::any_cast<std::string>(val2) << std::endl;

    std::cout << pkt.getSequence() << std::endl;
    std::cout << pkt.getTypeSequence() << std::endl; */

    return 0;
}

