#include "handler.h"

#define UNUSED(x) (void) (x)

bool Create_ServerSocket()
{
    int is_work{};

    handle_param.server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (handle_param.server_socket < 0)
    {
        perror("socket failed");
        return 0;
    }

    handle_param.server_sent_addr_len = sizeof(handle_param.server_sent_addr);

    handle_param.server_address.sin_family      = AF_INET;
    handle_param.server_address.sin_port        = htons(9000);
    handle_param.server_address.sin_addr.s_addr = INADDR_ANY;
    is_work                                     = bind(handle_param.server_socket,
                   (sockaddr*) &handle_param.server_address,
                   sizeof(handle_param.server_address));

    if (is_work < 0)
    {
        perror("bind failed");
        return 0;
    }

    listen(handle_param.server_socket, 1);
    std::cout << "Server listening on port 9000...\n";

    handle_param.client_socket = accept(handle_param.server_socket,
                                        (sockaddr*) &handle_param.server_sent_addr,
                                        &handle_param.server_sent_addr_len);
    if (handle_param.client_socket < 0)
    {
        perror("accept failed");
        return 0;
    }

    return 1;
}

bool Create_ClientSocket()
{
    int is_work{};

    handle_param.client_send_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (handle_param.client_send_socket < 0)
    {
        perror("socket failed");
        return 0;
    }

    handle_param.client_sent_addr.sin_family = AF_INET;
    handle_param.client_sent_addr.sin_port   = htons(9000);
    is_work = inet_pton(AF_INET, "127.0.0.1", &handle_param.client_sent_addr.sin_addr);
    is_work = connect(handle_param.client_send_socket,
                      (sockaddr*) &handle_param.client_sent_addr,
                      sizeof(handle_param.client_sent_addr));

    if (is_work < 0)
    {
        perror("connect failed");
        return 0;
    }

    std::cout << "Connected to server!\n";

    return 1;
}

void* SendMessage_Server(void* args)
{
    UNUSED(args);
    while (true)
    {
        std::cout << "You: ";
        std::getline(std::cin, handle_param.send_msg_server);
        send(handle_param.client_socket,
             handle_param.send_msg_server.c_str(),
             handle_param.send_msg_server.size(),
             0);
    }

    return nullptr;
}

void* SendMessage_Client(void* args)
{
    UNUSED(args);
    while (true)
    {
        std::cout << "You: ";
        std::getline(std::cin, handle_param.send_msg_client);
        send(handle_param.client_send_socket,
             handle_param.send_msg_client.c_str(),
             handle_param.send_msg_client.size(),
             0);
    }

    return nullptr;
}

void* ReceiveMessage_Server(void* args)
{
    UNUSED(args);
    while (true)
    {
        memset(handle_param.buffer_server, 0, sizeof(handle_param.buffer_server));
        ssize_t bytes = recv(handle_param.client_socket,
                             handle_param.buffer_server,
                             sizeof(handle_param.buffer_server),
                             0);
        if (bytes <= 0) break;
        std::cout << "\nClient: " << handle_param.buffer_server << std::endl;
    }

    return nullptr;
}

void* ReceiveMessage_Client(void* args)
{
    UNUSED(args);
    while (true)
    {
        memset(handle_param.buffer_client, 0, sizeof(handle_param.buffer_client));
        ssize_t bytes = recv(handle_param.client_send_socket,
                             handle_param.buffer_client,
                             sizeof(handle_param.buffer_client),
                             0);
        if (bytes <= 0) break;
        std::cout << "\nServer: " << handle_param.buffer_client << std::endl;
    }

    return nullptr;
}