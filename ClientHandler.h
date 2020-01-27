//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H
using namespace std;

#include <iostream>
/**
 * Interface, the client handler in charge of handling what the client needs.
 */
class ClientHandler {
public:
    virtual void handleClient(int client_socket) = 0;
};


#endif //EX4_CLIENTHANDLER_H
