//
// Created by shaiac on 18/01/2020.
//

#include "MyParallelServer.h"
#include <netinet/in.h>
#include <zconf.h>
#include "sys/socket.h"
#include <iostream>
#include <pthread.h>
#include <bits/sigthread.h>
#include <csignal>

void* clientHandle(void *threadid) {
    auto client = (ClientData*) threadid;
    client->clientHandler->handleClient(client->client_socket);
    pthread_exit(NULL);
}

void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler *clientH) {
    pthread_t thread;
    int client_socket;
    timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    while(!this->toStop) {
        if ((client_socket = accept(socketfd, (struct sockaddr *) &address,
                                    (socklen_t *) &address)) < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                cout << "Timeout, no more clients server closed" << endl;
                break;

            }
            cerr << "Error, during accepting client" << endl;
            exit(-4);
        }
        std::cout << "server is now connected to Client" << std::endl;
        auto client = new ClientData;
        client->clientHandler = clientH;
        client->client_socket = client_socket;
        if (pthread_create(&thread, nullptr, clientHandle, client) < 0) {
            cerr << "Error, during creating a thread" << endl;
            exit(1);
        }
        this->threadsList.push_front(thread);
        this->stop();
    }
    close(socketfd);
}

void MyParallelServer::open(int port, ClientHandler *clientH) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        exit(-1);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    //if we get the port number as an expression we are using the interpreter.
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
    list<pthread_t>::iterator itr;
    for (itr = this->threadsList.begin(); itr != this->threadsList.end(); itr++) {
        int ret = 0;
        pthread_t thread = *itr;
        /**if ((ret = pthread_kill(thread, 0) != 0)) {
            this->threadsList.erase(itr);
        }*/
    }
    if (this->threadsList.empty()) {
        this->toStop = false;
    }
}