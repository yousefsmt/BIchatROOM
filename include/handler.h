#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct
{
    sockaddr_in serverAddress;
    sockaddr_in ServerSentAddr;

    sockaddr_in ClientSentAddr;

    socklen_t ServerSentAddrLen;
    socklen_t ClientSentAddrLen;
    
    int ServerSocket;
    int ClientSocket;
    int ClientSendSocket;

    char BufferServer[1024];
    char BufferClient[1024];

    std::string SendMsgServer;
    std::string SendMsgClient;

    std::string UserName_Server;
    std::string UserName_Client;
    
}HandlerParameters;

bool Create_ServerSocket();
bool Create_ClientSocket();
void* SendMessage_Server(void* args);
void* SendMessage_Client(void* args);
void* ReceiveMessage_Server(void* args);
void* ReceiveMessage_Client(void* args);

HandlerParameters HandleParam {};

#endif // !HANDLER_H