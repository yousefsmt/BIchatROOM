#ifndef SERVER_H
#define SERVER_H

#include <sys/un.h>
#include <unistd.h>

typedef struct{
    sockaddr_un Address {};
    socklen_t AddressLen {};

}ServerParameters;

class Server{
    private:
        int CreationSocket_Server {};
        ServerParameters ServerParam {};
    public:
        bool CreateSocket();
        bool ReceiveMessage(char *RecvMessage);



};

#endif // !SERVER_H