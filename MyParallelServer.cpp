//
// Created by shaiac on 18/01/2020.
//

#include "MyParallelServer.h"
#include <netinet/in.h>
#include <zconf.h>
#include "sys/socket.h"
#include <iostream>
#include <pthread.h>
#include <thread>
#include <bits/sigthread.h>
#include <csignal>


void MyParallelServer::clientHandle(ClientHandler *clientH, int client_socket) {
   clientH->handleClient(client_socket);
}

/**
 * Waiting to accept clients, there is a timeout of 60 sec if there is no clients close the socket.
 * each client sending to a thread to handle him and moving in the main thread to accept more clients
 * that way we can handle few clients parallel.
 * @param socketfd the socket that we opened.
 * @param address the address.
 * @param clientH which client handle to use.
 */
void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler *clientH) {
    int client_socket;
    timeval timeout;
    timeout.tv_sec = 120;
    timeout.tv_usec = 0;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    while(!this->toStop) {
        if ((client_socket = accept(socketfd, (struct sockaddr *) &address,
                                    (socklen_t *) &address)) < 0) {
            //we get to timeout
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                cout << "Timeout, no more clients server closed" << endl;
                break;

            }
            cerr << "Error, during accepting client" << endl;
            exit(-4);
        }
        std::cout << "server is now connected to Client" << std::endl;
        thread handle([this, clientH, client_socket] {this->clientHandle(clientH, client_socket); });
        handle.detach();
    }
    close(socketfd);
}

/**
 * opening the server for accepting clients.
 * @param port the port to listen.
 * @param clientH which client handle to use.
 */
void MyParallelServer::open(int port, ClientHandler *clientH) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        exit(-1);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        cerr << "Error, couldn't bind the socket to an IP" << endl;
        exit(-2);
    }
    if (listen(socketfd, 5) < 0) {
        cerr << "Error, during the listening command" << endl;
        exit(-3);
    }
    this->start(socketfd, address, clientH);
}

void MyParallelServer::stop() {
    this->toStop = true;
}