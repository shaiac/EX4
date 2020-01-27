//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_SERVER_SIDE_H
#define EX4_SERVER_SIDE_H

#include "ClientHandler.h"
#include "MyTestClientHandler.h"
using namespace std;
namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *clientH) = 0;

        virtual void stop() = 0;
    };
}
#endif //EX4_SERVER_SIDE_H
