//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H
using namespace std;

namespace server_side {
    class Server {
    public:
        virtual void open(int port) = 0; //need to add clientHandler
        virtual void stop() = 0;
    };
}
#endif //EX4_SERVER_H
