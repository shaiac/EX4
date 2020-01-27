//
// Created by shaiac on 16/01/2020.
//

#include <zconf.h>
#include <sys/socket.h>
#include "MyClientHandler.h"
#include <vector>
#include <string>

/**
 * Constructor to the class, initializing with solver to use and the cache manager.
 * @param solver the solver.
 */
MyClientHandler::MyClientHandler(Solver<Matrix *, string> *solver) {
    this->solver = solver;
    fstream file("CacheOfMyClientHandler.txt", ios::in | ios::binary);
    this->cacheManager = new FileCacheManager(5);

}

/**
 * Reading from the client line by line of the matrix and the problem, creating a matrix and
 * solving the problem (a trail from the start point to the goal point). sending to the client the solution.
 * @param client_socket the client socket.
 */
void MyClientHandler::handleClient(int client_socket) {
    string partOfSol;
    int valread;
    Matrix *matrix = new Matrix();
    char buffer[1024] = {0};
    string solution;
    vector<string> lines;
    valread = read(client_socket, buffer, 1024);
    //reading until the end
    while (strstr(buffer, "end") == nullptr) {
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
