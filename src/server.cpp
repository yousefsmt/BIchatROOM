#include <iostream>
#include <pthread.h>
#include "server.h"
#include "handler.h"


int main() {
    pthread_t thread;

    pthread_create(&thread, NULL, &RunReceiveThread, NULL);
    pthread_join(thread, NULL);
    
    return 0;
}