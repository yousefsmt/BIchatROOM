#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <pthread.h>
#include "server.h"
#include "client.h"

typedef struct handler
{
    Server server;
    Client client;
    char BufferServer[1024];
    char BufferClient[1024];
    char SendMsgServer[1024];
    char SendMsgClient[1024];
    std::string UserName_Server;
    std::string UserName_Client;
    
}HandlerParameters;

HandlerParameters HandleParam {};

bool CreateAll_Socket(void){

    if (!HandleParam.server.CreateSocket())
        std::cerr << "ERROR: Server socket didn't create\n";

    if (!HandleParam.client.CreateSocket())
        std::cerr << "ERROR: Client socket didn't create\n";

    return 1;
}

void* RunReceiveThread_Server(void* args){
    std::string ClientName {};
    pthread_setname_np(pthread_self(), "ReceiveServer");

    if (!HandleParam.server.ReceiveMessage(HandleParam.BufferServer))
        std::cerr << "ERROR: Server cannot receive message\n";

    ClientName = HandleParam.BufferServer;
    std::cout << "Client Connected... Client Name: " << ClientName << '\n';

    while (1)
    {
        if (!HandleParam.server.ReceiveMessage(HandleParam.BufferServer))
            std::cerr << "ERROR: Server cannot receive message\n";
        std::cout << "Server(" << ClientName << "): " << HandleParam.BufferServer << '\n';
    }
}

void* RunSendThread_Server(void* args){
    pthread_setname_np(pthread_self(), "SendServer");

    std::cin >> HandleParam.UserName_Server;

    if (!HandleParam.server.SendMessage((char *)&HandleParam.UserName_Server))
        std::cerr << "ERROR: Client cannot send message\n";

    while (1)
    {
        std::cout << "Own(" << HandleParam.UserName_Server << "): ";
        std::cin >> HandleParam.SendMsgServer;
        if (!HandleParam.server.SendMessage(HandleParam.SendMsgServer))
            std::cerr << "ERROR: Client cannot send message\n";
    }
}

void* RunReceiveThread_Client(void* args){
    std::string ServerName {};
    pthread_setname_np(pthread_self(), "ReceiveClient");

    if (!HandleParam.client.ReceiveMessage(HandleParam.BufferClient))
        std::cerr << "ERROR: Client cannot receive message\n";

    ServerName = HandleParam.BufferClient;
    std::cout << "Server Connected... Server Name: " << ServerName << '\n';

    while (1)
    {
        if (!HandleParam.client.ReceiveMessage(HandleParam.BufferClient))
            std::cerr << "ERROR: Client cannot receive message\n";
        std::cout << "Server(" << ServerName << "): " << HandleParam.BufferClient << '\n';
    }
}

void* RunSendThread_Client(void* args){
    pthread_setname_np(pthread_self(), "SendClient");
    
    std::cin >> HandleParam.UserName_Client;

    if (!HandleParam.client.SendMessage((char *)&HandleParam.UserName_Client))
        std::cerr << "ERROR: Client cannot send message\n";

    while (1)
    {
        std::cout << "Own(" << HandleParam.UserName_Client << "): ";
        std::cin >> HandleParam.SendMsgClient;
        if (!HandleParam.client.SendMessage(HandleParam.SendMsgClient))
            std::cerr << "ERROR: Client cannot send message\n";
    }
}

#endif // !HANDLER_HRunReceiveThread_Server