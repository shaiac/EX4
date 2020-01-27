//
// Created by shaiac on 18/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H
using namespace std;
#include <netinet/in.h>
#include "server_side.h"
#include <list>

struct ClientData {
    int client_socket;
    ClientHandler * clientHandler;
};

class MyParallelServer: public server_side::Server {
    bool toStop = false;
public:
    void start(int socketfd, sockaddr_in address,  ClientHandler *clientH);
    void open(int port, ClientHandler *clientH);
    void stop();
    void clientHandle(ClientHandler *clientH, int client_socket);
};


#endif //EX4_MYPARALLELSERVER_H
