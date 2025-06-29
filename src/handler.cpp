#include "handler.h"


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

    HandleParam.ClientSocket = accept(HandleParam.ServerSocket, (sockaddr*)&HandleParam.ServerSentAddr, &HandleParam.ServerSentAddrLen);
    if (HandleParam.ClientSocket < 0) {
        perror("accept failed");
        return 0;
    }

    return 1;
}

bool Create_ClientSocket(){
    int isWork {};

    HandleParam.ClientSendSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (HandleParam.ClientSendSocket < 0) {
        perror("socket failed");
        return 0;
    }

    HandleParam.ClientSentAddr.sin_family = AF_INET;
    HandleParam.ClientSentAddr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &HandleParam.ClientSentAddr.sin_addr);

    if (connect(HandleParam.ClientSendSocket, (sockaddr*)&HandleParam.ClientSentAddr, sizeof(HandleParam.ClientSentAddr)) < 0) {
        perror("connect failed");
        return 0;
    }

    std::cout << "Connected to server!\n";

    return 1;
}

void* SendMessage_Server(void* args){
    while (true) {
        std::cout << "You: ";
        std::getline(std::cin, HandleParam.SendMsgServer);
        send(HandleParam.ClientSocket, HandleParam.SendMsgServer.c_str(), HandleParam.SendMsgServer.size(), 0);
    }
}

void* SendMessage_Client(void* args){
    while (true) {
        std::cout << "You: ";
        std::getline(std::cin, HandleParam.SendMsgClient);
        send(HandleParam.ClientSendSocket, HandleParam.SendMsgClient.c_str(), HandleParam.SendMsgClient.size(), 0);
    }
}

void* ReceiveMessage_Server(void* args){
    while (true) {
        memset(HandleParam.BufferServer, 0, sizeof(HandleParam.BufferServer));
        int bytes = recv(HandleParam.ClientSocket, HandleParam.BufferServer, sizeof(HandleParam.BufferServer), 0);
        if (bytes <= 0) break;
        std::cout << "\nClient: " << HandleParam.BufferServer << std::endl;
    }
}

void* ReceiveMessage_Client(void* args){
    
    while (true) {
        memset(HandleParam.BufferClient, 0, sizeof(HandleParam.BufferClient));
        int bytes = recv(HandleParam.ClientSendSocket, HandleParam.BufferClient, sizeof(HandleParam.BufferClient), 0);
        if (bytes <= 0) break;
        std::cout << "\nServer: " << HandleParam.BufferClient << std::endl;
    }
}