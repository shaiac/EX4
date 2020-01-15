//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include "Searchable.h"
#include "Point.h"
#include <list>
#include <cstring>

class Matrix : Searchable<Point> {
protected:
    list<list<State<Point*> *>> Tmatrix;
    State<Point*>* goalState;
    State<Point*>* startState;
    int Size = 0;
public:
    Matrix();

    void BuildMatrix(list<string> lines);

    State<Point*>* getInitialState();

    bool isGoalState(State<Point*>* currentState);

    list<State<Point*>> GetAllPossibleStates(State<Point> state);
};

#endif //EX4_MATRIX_H
