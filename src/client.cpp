#include <iostream>
#include "client.h"

int main() {
    Client client;
    char SendMsg[] = "Send Message";

    if (!client.CreateSocket())
        std::cerr << "ERROR: Client socket didn't create\n";

    if (!client.SendMessage(SendMsg))
        std::cerr << "ERROR: Client cannot send message\n";
    
    return 0;
}