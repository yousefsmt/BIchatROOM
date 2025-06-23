#include <iostream>
#include "client.h"

int main() {
    Client client {};
    const char *Msg {"hello"};

    client.CreateSocket();
    client.SendMessage(Msg);
    
    return 0;
}