//
// Created by shaiac on 16/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "Matrix.h"
#include "OA.h"
#include "FileCacheManager.h"

class MyClientHandler : public ClientHandler {
protected:
    CacheManager *cacheManager;
    Solver<Matrix *, string> *solver;
public:
    MyClientHandler(Solver<Matrix *, string> *solver);

    void handleClient(int client_socket);
};


#endif //EX4_MYCLIENTHANDLER_H
