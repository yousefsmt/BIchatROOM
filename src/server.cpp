#include <iostream>
#include <pthread.h>
#include "handler.cpp"

int main(){
    pthread_t sendThread, recvThread;

    Create_ServerSocket();

    pthread_create(&sendThread, nullptr, &SendMessage_Server, nullptr);
    pthread_create(&recvThread, nullptr, &ReceiveMessage_Server, nullptr);

    pthread_join(sendThread, nullptr);
    pthread_join(recvThread, nullptr);

    printf("55555555");

    close(HandleParam.ClientSocket);
    close(HandleParam.ServerSocket);

    return 0;
}