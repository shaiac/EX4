//
// Created by shaiac on 16/01/2020.
//

#include <zconf.h>
#include <sys/socket.h>
#include "MyClientHandler.h"
#include <vector>
#include <string>
#include "pthread.h"

MyClientHandler::MyClientHandler(Solver<Matrix*,string >* solver) {
    this->solver = solver;
    this->cacheManager = new FileCacheManager(5);
}

void MyClientHandler::handleClient(int client_socket) {
    int valread;
    Matrix *matrix = new Matrix();
    char buffer[1024] = {0};
    string solution;
    vector<string> lines;
    valread = read(client_socket, buffer, 1024);
    while(strstr(buffer, "end") == nullptr) {
        lines.push_back(buffer);
                valread = read(client_socket, buffer, 1024);
    }
    lines.push_back("end\r\n");
    matrix->BuildMatrix(lines);
    if (!this->cacheManager->isSolutionExist(matrix->matrixToString())) {
        solution = this->solver->solve(matrix);
        this->cacheManager->saveSolution(matrix->matrixToString(), solution);
    } else {
        solution = this->cacheManager->getSolution(matrix->matrixToString());
    }
    int return_val;
    send(client_socket, solution.c_str(), solution.length(), 0);
}
