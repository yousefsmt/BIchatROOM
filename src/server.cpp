#include <pthread.h>

#include <iostream>

#include "handler.cpp"

int main()
{
    pthread_t send_thread;
    pthread_t recv_thread;

    Create_ServerSocket();

    pthread_create(&send_thread, nullptr, &SendMessage_Server, nullptr);
    pthread_create(&recv_thread, nullptr, &ReceiveMessage_Server, nullptr);

    pthread_join(send_thread, nullptr);
    pthread_join(recv_thread, nullptr);

    printf("55555555");

    close(handle_param.client_socket);
    close(handle_param.server_socket);

    return 0;
}