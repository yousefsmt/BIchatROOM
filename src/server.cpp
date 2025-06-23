#include <iostream>
#include "server.h"

int main() {
    Server server {};
    char *Msg;

    server.CreateSocket();
    server.ReceiveMessage(Msg);

    std::cout << Msg << '\n';
    
    return 0;
}