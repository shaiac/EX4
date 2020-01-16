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

int main() {
    //MyClientHandler *mch = new MyClientHandler();
    //MySerialServer *mss = new MySerialServer();
    //mss->open(7767, mch);
    double sum = 0;
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
    //vector<State<Point *>*> vec_dfs = dfs->Search(matrix);
    vector<State<Point *> *> vec_bestfs = bestfs->Search(matrix);
    //vector<State<Point *> *> vec_bfs = bfs->Search(matrix);
    //cout<< vec_dfs.size()<<endl;
    //cout << vec_bfs.size() << endl;
    cout<< vec_bestfs.size()<<endl;
    State<Point *>* state = vec_bestfs.begin().operator*();
    cout << state->getTrailCost() <<endl;
    /**for (auto itr = vec_bestfs.begin(); itr != vec_bestfs.end(); itr++ ) {
        State<Point*> *state = *itr;
        sum += state->GetCost();
    }
    cout <<sum << endl;*/
    return 0;
}
