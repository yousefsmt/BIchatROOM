#include "handler.cpp"

int main() {
    pthread_t sendThread, recvThread;

    Create_ClientSocket();

    pthread_create(&sendThread, nullptr, &SendMessage_Client, nullptr);
    pthread_create(&recvThread, nullptr, &ReceiveMessage_Client, nullptr);

    pthread_join(sendThread, nullptr);
    pthread_join(recvThread, nullptr);

    
    return 0;
}