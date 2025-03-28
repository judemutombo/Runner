#include "include/NetServer.h"


int main(){

    NetServer server("localhost", "5001", false);
    server.listening();
    server.accepting();
}