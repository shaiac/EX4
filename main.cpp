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
    /**Matrix *matrix = new Matrix();
    vector<string> lines;
    string line;
    fstream file;
    file.open("Matrix50x50.txt", fstream::in);
    if (!file) {
        cerr << "Error in file creating, key doesn't exist" << endl;
    }
    while (getline(file, line)) {
        lines.push_back(line);
    }
    matrix->BuildMatrix(lines);
    DepthFirstSearch<Point *> *dfs = new DepthFirstSearch<Point *>();
    BestFirstSearch<Point *> *bestFS = new BestFirstSearch<Point *>();
    BreadthFirstSearch<Point *> *bfs = new BreadthFirstSearch<Point*>();
    AStar<Point *> *aStar = new AStar<Point*>();
    vector<State<Point *>*> vec_dfs = dfs->Search(matrix);
    vector<State<Point *> *> vec_bestfs = bestFS->Search(matrix);
    vector<State<Point *> *> vec_bfs = bfs->Search(matrix);
    vector<State<Point *> *> vec_Astar = aStar->Search(matrix);
    cout<< "BFS:: "<<endl;
    cout<< vec_bfs.size()<<endl;
    State<Point *>* state0 = vec_dfs.begin().operator*();
    cout << state0->getTrailCost() <<endl;
    cout<< "DFS:: "<<endl;
    cout<< vec_dfs.size()<<endl;
    State<Point *>* state1 = vec_dfs.begin().operator*();
    cout << state1->getTrailCost() <<endl;
    cout<< "Astar:: "<<endl;
    cout<< vec_Astar.size()<<endl;
    State<Point *>* state2 = vec_Astar.begin().operator*();
    cout << state2->getTrailCost() <<endl;
    cout<< "BestFS:: "<<endl;
    cout<< vec_bestfs.size()<<endl;
    State<Point *>* state3 = vec_bestfs.begin().operator*();
    cout << state3->getTrailCost() <<endl;*/
    BestFirstSearch<Point *> *bestfs = new BestFirstSearch<Point *>();
    DepthFirstSearch<Point *> *dfs = new DepthFirstSearch<Point*>();
    OA<Matrix*, Point*>* oa = new OA<Matrix*, Point*>(dfs);
    MyClientHandler *clientHandler = new  MyClientHandler(oa);
    MySerialServer *mss = new MySerialServer();
    mss->open(port, clientHandler);
    return 0;
}
