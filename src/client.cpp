#include "handler.cpp"

int main()
{
    pthread_t send_thread;
    pthread_t recv_thread;

    Create_ClientSocket();

    pthread_create(&send_thread, nullptr, &SendMessage_Client, nullptr);
    pthread_create(&recv_thread, nullptr, &ReceiveMessage_Client, nullptr);

    pthread_join(send_thread, nullptr);
    pthread_join(recv_thread, nullptr);

    return 0;
}