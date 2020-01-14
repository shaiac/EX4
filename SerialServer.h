//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_SERIALSERVER_H
#define EX4_SERIALSERVER_H
using namespace std;
#include <netinet/in.h>
#include "server_side.h"

class MySerialServer: public server_side::Server {
    bool toStop = false;
public:
    void start(int socketfd, sockaddr_in address,  ClientHandler *clientH);
    void open(int port, ClientHandler *clientH);
    void stop();
};

#endif //EX4_SERIALSERVER_H
