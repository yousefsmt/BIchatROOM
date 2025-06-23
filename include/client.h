#ifndef CLIENT_H
#define CLIENT_H

#include <sys/un.h>
#include <unistd.h>

typedef struct{
    sockaddr_un Address {}, SentAddress {};
    socklen_t AddressLen {}, SentAddressLen {};

}ClientParameters;

class Client{
    private:
        int CreationSocket_Client {};
        ClientParameters ClientParam {};
    public:
        bool CreateSocket();
        bool SendMessage(const char *SendMessage);
        bool ReceiveMessage(char *RecvMessage);
};

#endif // !CLIENT_H