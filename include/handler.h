#ifndef HANDLER_H
#define HANDLER_H

#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

typedef struct
{
    sockaddr_in server_address;
    sockaddr_in server_sent_addr;

    sockaddr_in client_sent_addr;

    socklen_t server_sent_addr_len;
    socklen_t client_sent_addr_len;

    int server_socket;
    int client_socket;
    int client_send_socket;

    char buffer_server[1024];
    char buffer_client[1024];

    std::string send_msg_server;
    std::string send_msg_client;

    std::string user_name_server;
    std::string user_name_client;

} HandlerParameters;

bool  Create_ServerSocket();
bool  Create_ClientSocket();
void* SendMessage_Server(void* args);
void* SendMessage_Client(void* args);
void* ReceiveMessage_Server(void* args);
void* ReceiveMessage_Client(void* args);

HandlerParameters handle_param{};

#endif // !HANDLER_H