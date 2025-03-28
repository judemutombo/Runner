#include <fstream>
#include <iostream>
#include "externals/nlohmann/json.hpp"

using json = nlohmann::json;


int main(int argc, char** argv){

    std::ifstream f(argv[0]);
    if (!f) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }
    json data = json::parse(f);

    std::cout << data.dump(4) << std::endl;
}

