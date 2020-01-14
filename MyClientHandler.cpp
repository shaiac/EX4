//
// Created by shaiac on 14/01/2020.
//
#include <zconf.h>
#include "MyClientHandler.h"

void MyClientHandler::handleClient(int client_socket) {
    int valread;
    char buffer[1024] = {0};
    valread = read(client_socket, buffer, 1024);
    this->solver->solve(buffer);
}
