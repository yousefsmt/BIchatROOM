#include "handler.h"
#include "server.h"

void init(){
    std::cout << "******** Welcome to BIchatROOM ********\n"
              << "Please set a username: ";
}

int main() {
    pthread_t ThreadSend, ThreadReceive;

    init();
    CreateAll_Socket();

    // pthread_create(&Thread_socket, nullptr, &CreateAll_Socket, nullptr);
    pthread_create(&ThreadSend, nullptr, &RunSendThread_Server, nullptr);
    pthread_create(&ThreadReceive, nullptr, &RunReceiveThread_Server, nullptr);

    // pthread_join(Thread_socket, nullptr);
    pthread_join(ThreadSend, nullptr);
    pthread_join(ThreadReceive, nullptr);
    
    return 0;
}