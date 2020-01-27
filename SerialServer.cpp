#include "SerialServer.h"
#include <netinet/in.h>
#include <zconf.h>
#include "sys/socket.h"
#include <iostream>
#include <thread>

//
// Created by shaiac on 13/01/2020.
//

/**
 * Waiting to accept clients, there is a timeout of 60 sec if there is no clients close the socket.
 * @param socketfd the socket that we opened.
 * @param address the address.
 * @param clientH which client handle to use.
 */
void MySerialServer:: start(int socketfd, sockaddr_in address, ClientHandler *clientH) {
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
        clientH->handleClient(client_socket);
    }
    close(socketfd);
}

/**
 * opening the server for accepting clients.
 * @param port the port to listen.
 * @param clientH which client handle to use.
 */
void MySerialServer:: open(int port, ClientHandler *clientH) {
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
    thread start([this, socketfd, address, clientH] { this->start(socketfd, address, clientH); });
    start.join();
}

/**
 * For the main thread to call, say to stop accepting clients.
 */
void MySerialServer::stop() {
    this->toStop = true;
}
