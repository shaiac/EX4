//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

class MyClientHandler : public ClientHandler{
protected:
    CacheManager<string, string> *cacheManager;
    Solver<string, string > *solver;
public:
    void handleClient(int client_socket);
};


#endif //EX4_MYCLIENTHANDLER_H
