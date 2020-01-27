//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "StringReverser.h"

/**
 * Class that handle problem of string and solution is the revers string.
 */
class MyTestClientHandler : public ClientHandler{
protected:
    CacheManager* cacheManager;
    StringReverser *solver;
public:
     MyTestClientHandler();
    void handleClient(int client_socket);
};


#endif //EX4_MYTESTCLIENTHANDLER_H
