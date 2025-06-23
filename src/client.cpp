#include <iostream>
#include <sys/un.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>

#include "client.h"

#define SERVER_PATH "/tmp/server"
#define CLIENT_PATH "/tmp/client"

bool Client::CreateSocket(){
    int isBind {};

    CreationSocket_Client = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (CreationSocket_Client == -1){
        perror("socket creation failed: ");
        return 0;
    }

    ClientParam.Address.sun_family = AF_UNIX;
    strncpy(ClientParam.Address.sun_path, CLIENT_PATH, sizeof(ClientParam.Address.sun_path)-1);
    ClientParam.AddressLen = sizeof(ClientParam.Address);

    unlink(CLIENT_PATH);

    isBind = bind(CreationSocket_Client,(sockaddr*)&ClientParam.Address, ClientParam.AddressLen);
    if (isBind == -1){
        perror("socket bind failed: ");
        return 0;
    }

    ClientParam.SentAddress.sun_family = AF_UNIX;
    strncpy(ClientParam.SentAddress.sun_path, SERVER_PATH, sizeof(ClientParam.SentAddress.sun_path)-1);
    ClientParam.SentAddressLen = sizeof(ClientParam.SentAddress);

    return 1;
}

bool Client::ReceiveMessage(char *RecvMessage){
    int isReceive {};
    isReceive = recvfrom(CreationSocket_Client, RecvMessage, sizeof(RecvMessage), 0, nullptr, nullptr);
    if (isReceive == -1){
        perror("recv failed: ");
        return 0;
    }
    return 1;
}

bool Client::SendMessage(const char *SendMessage){
    int isSend {};
    isSend = sendto(CreationSocket_Client, SendMessage, strlen(SendMessage), 0, (sockaddr*)&ClientParam.SentAddress, ClientParam.SentAddressLen);
    if (isSend == -1){
        perror("send failed: ");
        return 0;
    }
    return 1;
}