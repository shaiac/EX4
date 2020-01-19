#include <iostream>
#include "StringReverser.h"
#include "MyClientHandler.h"
#include "SerialServer.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "DepthFirstSearch.h"
#include "BestFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "AStar.h"

int main() {
    //MyClientHandler *mch = new MyClientHandler();
    //MySerialServer *mss = new MySerialServer();
    //mss->open(7767, mch);
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
    cout<<"BESTFS:"<<endl;
    BestFirstSearch<Point *> *bestfs = new BestFirstSearch<Point *>();
    vector<State<Point *> *> vec_bestfs = bestfs->Search(matrix);
    cout << vec_bestfs.size() << endl;
    State<Point *>* state1 = vec_bestfs.begin().operator*();
    cout << state1->getTrailCost() <<endl;
    cout<<"ASTAR:"<<endl;
    AStar<Point *> *astar = new AStar<Point *>();
    vector<State<Point *> *> vec_str = astar->Search(matrix);
    cout << vec_str.size() << endl;
    State<Point *> *state = vec_str.begin().operator*();
    cout << state->getTrailCost();
    return 0;
}
