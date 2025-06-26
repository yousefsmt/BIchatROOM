#include "handler.h"
#include "client.h"

void init(){
    std::cout << "******** Welcome to BIchatROOM ********\n"
              << "Please set a username: ";
}

int main() {
    pthread_t ThreadSend, ThreadReceive;

    init();

    pthread_create(&ThreadSend, nullptr, &RunSendThread_Client, nullptr);
    pthread_create(&ThreadReceive, nullptr, &RunReceiveThread_Client, nullptr);

    pthread_join(ThreadSend, nullptr);
    pthread_join(ThreadReceive, nullptr);
    
    return 0;
}