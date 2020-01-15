//
// Created by shaiac on 14/01/2020.
//

#include "Matrix.h"


list<string> split(string s) {
    list<string> values;
    string str = "";
    int i;
    for (i = 0; i < s.length(); i++) {
        if (s[i] == ',' || s[i] == '\n') {
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

list<State<Point *> *> MakeListAsState(list<string> line_str, double x) {
    list<State<Point *> *> line_State;
    double i = 0;
    for (auto itr = line_str.begin(); itr != line_str.end(); itr++) {
        string tmp = *itr;
        Point *p = new Point(x, i);
        double val = stod(tmp);
        State<Point *> *stt = new State<Point *>(p, val);
        line_State.push_back(stt);
    }
    return line_State;
}

void Matrix::BuildMatrix(list<string> lines) {
    string *splitLine;
    list<string>::iterator it;
    list<Point*> start_end;
    int size = 0;
    bool s_e = false;
    for (it = lines.begin(); it != lines.end(); it++) {
        string tmp = *((it++)++);
        if (tmp.find("end") != string::npos) {
            s_e = true;
        }
        if (!s_e) {
            list<string> line_as_string = split(*it);
            this->Tmatrix.push_back(MakeListAsState(line_as_string, size));
            size++;
            continue;
        } else {
            list<string> line_as_string = split(*it);
            double x = stod(line_as_string.front());
            line_as_string.pop_front();
            double y = stod(line_as_string.front());
            line_as_string.pop_front();
            Point *p = new Point(x, y);
            start_end.push_back(p);
        }

    }
    this->Size = size;
    Point *start = start_end.front();
    start_end.pop_front();
    Point *end = start_end.front();
}

State<Point *> *Matrix::getInitialState() {
    return this->startState;
}

bool Matrix::isGoalState(State<Point *> *currentState) {
    if (currentState->getState()->isEqual(*this->goalState->getState())) {
        return true;
    }
}