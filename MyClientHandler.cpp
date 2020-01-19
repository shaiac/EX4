//
// Created by shaiac on 14/01/2020.
//
#include <zconf.h>
#include <sys/socket.h>
#include <cstring>
#include "MyClientHandler.h"
#include "FileCacheManager.h"
#include "string"

MyClientHandler::MyClientHandler() {
    this->solver = new StringReverser();
    this->cacheManager = new FileCacheManager(5);
}

void MyClientHandler::handleClient(int client_socket) {
    int valread;
    char buffer[1024] = {0};
    string solution;
    valread = read(client_socket, buffer, 1024);
    if (!this->cacheManager->isSolutionExist(buffer)) {
        solution = this->solver->solve(buffer);
        this->cacheManager->saveSolution(buffer, solution);
    } else {
        solution = this->cacheManager->getSolution(buffer);
    }
    int return_val;
    //= send(client_socket,solution,solution.length(), 0);
    send(client_socket, solution.c_str(), solution.length(), 0);

}
