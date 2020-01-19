//
// Created by shaiac on 14/01/2020.
//

#include <assert.h>
#include <iostream>
#include "Matrix.h"

Matrix::Matrix() {

}

vector<string> split(string s) {
    vector<string> values;
    string str = "";
    int i;
    for (i = 0; i <= s.length(); i++) {
        if (s[i] == ',' || s[i] == '\n' || s[i] == '\000') {
            values.push_back(str);
            str = "";
            if (s[i] == '\n') {
                return values;
            }
        } else {
            str += s[i];
        }
    }
    return values;
}

template<typename T>
void pop_front(std::vector<T> &vec) {
    assert(!vec.empty());
    vec.erase(vec.begin());
}

vector<State<Point *> *> MakeVectorAsState(vector<string> line_str, double x) {
    vector<State<Point *> *> line_State;
    double i = 0;
    for (auto itr = line_str.begin(); itr != line_str.end(); itr++) {
        string tmp = *itr;
        Point *p = new Point(x, i);
        double val = stod(tmp);
        State<Point *> *stt = new State<Point *>(p, val);
        line_State.push_back(stt);
        i++;
    }
    return line_State;
}

void Matrix::setStartGoal(State<Point *> *start, State<Point *> *goal) {
    this->startState = start;
    this->goalState = goal;
}

void Matrix::BuildMatrix(vector<string> lines) {
    int i;
    vector<string>::iterator it;
    vector<Point *> start_end;
    int size = 0;
    bool s_e = false;
    for (it = lines.begin(); it != lines.end(); it++) {
        it++;
        string tmp = *(++it);
        it--;
        it--;
        if (tmp.find("end") != string::npos) {
            s_e = true;
        }
        if (!s_e) {
            vector<string> line_as_string = split(*it);
            this->Tmatrix.push_back(MakeVectorAsState(line_as_string, size));
            size++;
            continue;
        } else {
            for (i = 0; i < 2; i++) {
                vector<string> line_as_string = split(*it);
                double x = stod(line_as_string.front());
                pop_front(line_as_string);
                double y = stod(line_as_string.front());
                pop_front(line_as_string);
                Point *p = new Point(x, y);
                start_end.push_back(p);
                it++;
            }
            break;
        }
    }
    this->Size = size;
    Point *start = start_end.front();
    pop_front(start_end);
    Point *goal = start_end.front();
    this->setStartGoal(Tmatrix[start->getX()][start->getY()], Tmatrix[goal->getX()][goal->getY()]);
    this->Tmatrix[start->getX()][start->getY()]->setTrailCost(0);
}

State<Point *> *Matrix::getInitialState() {
    return this->startState;
}

bool Matrix::isGoalState(State<Point *> *currentState) {
    if (currentState->getState()->isEqual(*this->goalState->getState())) {
        return true;
    }
}

vector<State<Point *> *> Matrix::GetAllPossibleStates(State<Point *> *state) {
    Point *point = state->getState();
    double x = point->getX();
    double y = point->getY();
    int size = this->Size;
    vector<State<Point *> *> adjs;
    if (x + 1 < size) {
        State<Point *> *right = this->Tmatrix[x + 1][y];
        adjs.push_back(right);
    }

    if (y + 1 < size) {
        State<Point *> *up = this->Tmatrix[x][y + 1];
        adjs.push_back(up);
    }
    if (x - 1 >= 0) {
        State<Point *> *left = this->Tmatrix[x - 1][y];
        adjs.push_back(left);
    }
    if (y - 1 >= 0) {
        State<Point *> *down = this->Tmatrix[x][y - 1];
        adjs.push_back(down);
    }
    return adjs;
}

