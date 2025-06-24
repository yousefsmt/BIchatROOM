#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <pthread.h>
#include "server.h"

void* RunReceiveThread(void* args){
    pthread_setname_np(pthread_self(), "Receive");
    Server server;
    char Buffer[1024] {0};

    if (!server.CreateSocket())
        std::cerr << "ERROR: Server socket didn't create\n";

    while (1)
    {
        if (!server.ReceiveMessage(Buffer))
            std::cerr << "ERROR: Server cannot receive message\n";
        std::cout << "This message receive: " << Buffer << '\n';
    }
}

#endif // !HANDLER_H