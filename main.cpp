#include <iostream>
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "SerialServer.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "DepthFirstSearch.h"
#include "BestFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "Astar.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"

int main(int argc, char *argv[]) {
    int port = atoi(argv[1]);
    AStar<Point *> *aStar = new AStar<Point *>();
    OA<Matrix *, Point *> *oa = new OA<Matrix *, Point *>(aStar);
    MyClientHandler *clientHandler = new MyClientHandler(oa);
    /**MySerialServer *mss = new MySerialServer();
    mss->open(port, clientHandler);*/
    MyParallelServer *parallelServer = new MyParallelServer();
    parallelServer->open(port, clientHandler);
    return 0;
}
