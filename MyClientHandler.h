//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "StringReverser.h"

class MyClientHandler : public ClientHandler{
protected:
    CacheManager*cacheManager;
    StringReverser *solver;
public:
     MyClientHandler();
    void handleClient(int client_socket);
};


#endif //EX4_MYCLIENTHANDLER_H
