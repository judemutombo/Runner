#include <iostream>
#include "include/Server.h"

int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "usage example : server.exe configpath";
        exit(EXIT_FAILURE);
    }
    Server server(argv[1]);
    return 0;
}