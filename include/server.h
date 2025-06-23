#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/un.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

#define SERVER_PATH "/tmp/server"
#define CLIENT_PATH "/tmp/client"

typedef struct{
    sockaddr_un Address {};
    socklen_t AddressLen {};

}ServerParameters;

class Server{
    private:
        int CreationSocket_Server {};
        ServerParameters ServerParam {};
    public:
        bool CreateSocket();
        bool ReceiveMessage(char *RecvMessage);
};

bool Server::CreateSocket(){
    int isBind {};

    CreationSocket_Server = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (CreationSocket_Server == -1){
        perror("socket creation failed: ");
        return 0;
    }

    ServerParam.Address.sun_family = AF_UNIX;
    strncpy(ServerParam.Address.sun_path, SERVER_PATH, sizeof(ServerParam.Address.sun_path)-1);
    ServerParam.AddressLen = sizeof(ServerParam.Address);

    unlink(SERVER_PATH);

    isBind = bind(CreationSocket_Server,(sockaddr*)&ServerParam.Address, ServerParam.AddressLen);
    if (isBind == -1){
        perror("socket bind failed: ");
        return 0;
    }

    // ServerParam.SentAddress.sun_family = AF_UNIX;
    // strncpy(ServerParam.SentAddress.sun_path, SERVER_PATH, sizeof(ServerParam.SentAddress.sun_path)-1);
    // ServerParam.SentAddressLen = sizeof(ClientParam.SentAddress);

    return 1;
}

bool Server::ReceiveMessage(char *RecvMessage){
    int isReceive {};

    isReceive = recvfrom(CreationSocket_Server, RecvMessage, sizeof(RecvMessage), 0, nullptr, nullptr);
    if (isReceive == -1){
        perror("receive failed: ");
        return 0;
    }
        
    return 1;
}

#endif // !SERVER_H