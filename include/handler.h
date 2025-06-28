#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct handler
{
    sockaddr_in serverAddress;
    sockaddr_in ServerSentAddr;

    sockaddr_in clientAddress;
    sockaddr_in ClientSentAddr;

    socklen_t ServerSentAddrLen;
    socklen_t ClientSentAddrLen;
    
    int ServerSocket;
    int ClientSocket;

    char BufferServer[1024];
    char BufferClient[1024];

    std::string SendMsgServer;
    std::string SendMsgClient;

    std::string UserName_Server;
    std::string UserName_Client;
    
}HandlerParameters;

HandlerParameters HandleParam {};

bool Create_ServerSocket(){
    int isWork {};

    HandleParam.ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (HandleParam.ServerSocket < 0) {
        perror("socket failed");
        return 0;
    }

    
    HandleParam.ServerSentAddrLen = sizeof(HandleParam.ServerSentAddr);

    HandleParam.serverAddress.sin_family = AF_INET;
    HandleParam.serverAddress.sin_port = htons(9000);
    HandleParam.serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(HandleParam.ServerSocket, (sockaddr*)&HandleParam.serverAddress, sizeof(HandleParam.serverAddress)) < 0) {
        perror("bind failed");
        return 0;
    }

    listen(HandleParam.ServerSocket, 1);
    std::cout << "Server listening on port 9000...\n";

    int clientSocket = accept(HandleParam.ServerSocket, (sockaddr*)&HandleParam.ServerSentAddr, &HandleParam.ServerSentAddrLen);
    if (clientSocket < 0) {
        perror("accept failed");
        return 0;
    }

    return 1;
}

bool Create_ClientSocket(){
    int isWork {};

    HandleParam.ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (HandleParam.ClientSocket < 0) {
        perror("socket failed");
        return 0;
    }

    HandleParam.ClientSentAddr.sin_family = AF_INET;
    HandleParam.ClientSentAddr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &HandleParam.ClientSentAddr.sin_addr);

    if (connect(HandleParam.ClientSocket, (sockaddr*)&HandleParam.ClientSentAddr, sizeof(HandleParam.ClientSentAddr)) < 0) {
        perror("connect failed");
        return 0;
    }

    std::cout << "Connected to server!\n";
    
    return 1;
}

void SendMessage_Server(){}

void SendMessage_Client(){}

void ReceiveMessage_Server(){}

void ReceiveMessage_Client(){}

#endif // !HANDLER_H