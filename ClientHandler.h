//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
using namespace std;
#include "server_side.h"
#include <iostream>

class ClientHandler {
public:
    virtual void handleClient(int client_socket) = 0;
};


#endif //EX4_CLIENTHANDLER_H
