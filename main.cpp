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

int main(int argc, char *argv[]) {
    int port = atoi(argv[1]);
    //MyTestClientHandler *mch = new MyTestClientHandler();
    //MySerialServer *mss = new MySerialServer();
    //mss->open(7767, mch);
    /**double sum = 0;
    Matrix *matrix = new Matrix();
    vector<string> lines;
    string line;
    fstream file;
    file.open("matrix_test.txt", fstream::in);
    if (!file) {
        cerr << "Error in file creating, key doesn't exist" << endl;
    }
    while (getline(file, line)) {
        lines.push_back(line);
    }
    matrix->BuildMatrix(lines);
    DepthFirstSearch<Point *> *dfs = new DepthFirstSearch<Point *>();
    BestFirstSearch<Point *> *bestfs = new BestFirstSearch<Point *>();
    BreadthFirstSearch<Point *> *bfs = new BreadthFirstSearch<Point*>();
    AStar<Point *> *aStar = new AStar<Point*>();
    //vector<State<Point *>*> vec_dfs = dfs->Search(matrix);
    vector<State<Point *> *> vec_bestfs = bestfs->Search(matrix);
    //vector<State<Point *> *> vec_bfs = bfs->Search(matrix);
    vector<State<Point *> *> vec_Astar = aStar->Search(matrix);
    //cout<< vec_dfs.size()<<endl;
    //cout << vec_bfs.size() << endl;
    cout<< "Astar:: "<<endl;
    cout<< vec_Astar.size()<<endl;
    State<Point *>* state = vec_Astar.begin().operator*();
    cout << state->getTrailCost() <<endl;
    cout<< "BestFS:: "<<endl;
    cout<< vec_bestfs.size()<<endl;
    State<Point *>* state1 = vec_bestfs.begin().operator*();
    cout << state1->getTrailCost() <<endl;**/
    BestFirstSearch<Point *> *bestfs = new BestFirstSearch<Point *>();
    OA<Matrix*, Point*>* oa = new OA<Matrix*, Point*>(bestfs);
    MyClientHandler *clientHandler = new  MyClientHandler(oa);
    MySerialServer *mss = new MySerialServer();
    mss->open(port, clientHandler);
    return 0;
}
