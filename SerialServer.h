//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_SERIALSERVER_H
#define EX4_SERIALSERVER_H


using namespace std;
#include "Server.h"

class MySerialServer: public server_side::Server {
public:
    void open(int port);
    void stop();
};

#endif //EX4_SERIALSERVER_H
