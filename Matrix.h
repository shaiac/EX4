//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include "Searchable.h"
#include "Point.h"
#include <vector>
#include <cstring>
#include <vector>

class Matrix : public Searchable<Point*> {
protected:
    vector<vector<State<Point*> *>> Tmatrix;
    State<Point*>* goalState;
    State<Point*>* startState;
    int Size = 0;
public:
    Matrix();

    void setStartGoal(State<Point*>* start, State<Point*>* goal);

    void BuildMatrix(vector<string> lines);

    State<Point*>* getInitialState() override;

    bool isGoalState(State<Point*>* currentState);

    vector<State<Point*>*> GetAllPossibleStates(State<Point*>* state);
};

#endif //EX4_MATRIX_H
