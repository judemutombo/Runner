#include <iostream>
#include "include/RunnerServer.h"

using json = nlohmann::json;


int main(int argc, char** argv){

    if(argc != 2){
        std::cout << "usage example : miniserver.exe configpath";
        exit(EXIT_FAILURE);
    }

    RunnerServer server(argv[1]);

}

