//
// Created by shaiac on 14/01/2020.
//

#include <assert.h>
#include "Matrix.h"

Matrix::Matrix() {

}

/**
 * Getting a string and splitting him to a vector of string by ','.
 * @param s the string that we want to split.
 * @return the vector.
 */
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

/**
 * popping front element from vector.
 * @tparam T type of the object
 * @param vec the vector.
 */
template<typename T>
void pop_front(std::vector<T> &vec) {
    assert(!vec.empty());
    vec.erase(vec.begin());
}

/**
 * Getting a vector of strings and change him to be vector of states*.
 * @param line_str the vector of the strings.
 * @param x the x of point of the state.
 * @return the vector as state*.
 */
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

/**
 * Setting from the start and end points the start and goal states.
 * @param start the start point.
 * @param goal the goal point.
 * @param startCost the cost of the start point.
 */
void Matrix::setStartGoal(Point *start, Point *goal, double startCost) {
    this->startState = new State<Point *>(start, startCost);
    this->goalState = new State<Point *>(goal, 0);
}

/**
 * Creating a string of the matrix (the matrix is vectors of vectors of states*).
 * @return string of the matrix.
 */
string Matrix::matrixToString() {
    string matrixString = "";
    for (auto itr = this->Tmatrix.begin(); itr != this->Tmatrix.end(); itr++) {
        vector<State<Point *> *> line = *itr;
        for (auto it = line.begin(); it != line.end(); it++) {
            State<Point *> *state = *it;
            matrixString += to_string((int) state->GetCost());
            matrixString += ",";
        }
        matrixString += "\n";
    }
    return matrixString;
}

/**
 * getting vector of strings, each string is a line of the matrix from that data
 * creating the matrix vectors of vectors of states*. the 3 last lines are: the first one is the
 * start point, the second is the the goal state and the last line "end" indicate that the matrix finished.
 * @param lines The vector.
 */
void Matrix::BuildMatrix(vector<string> lines) {
    int i;
    string *splitLine;
    vector<string>::iterator it;
    vector<Point *> start_end;
    int size = 0;
    bool s_e = false;
    for (it = lines.begin(); it != lines.end(); it++) {
        it++;
        string tmp = *(++it);
        it--;
        it--;
        //if the line is end we got to the end of the matrix
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
    //setting the start and goal states.
    this->Size = size;
    Point *start = start_end.front();
    pop_front(start_end);
    Point *goal = start_end.front();
    double startCost = Tmatrix[start->getX()][start->getY()]->GetCost();
    this->setStartGoal(start, goal, startCost);
    this->Tmatrix[start->getX()][start->getY()]->setTrailCost(0);

}

/**
 * @return The start state.
 */
State<Point *> *Matrix::getInitialState() {
    this->startState->setTrailCost(this->startState->GetCost());
    return this->startState;
}

/**
 * Checking if a state is the goal state.
 * @param currentState the state that we want to check if goal.
 * @return true if the goal state, false otherwise.
 */
bool Matrix::isGoalState(State<Point *> *currentState) {
    if (currentState->getState()->isEqual(*this->goalState->getState())) {
        return true;
    }
}

/**
 * For a state, checking who are his neighbors that are all the states that we can move to them
 * if he is a neighbor push him to the possible states vector.
 * @param state the state that we search the neighbors for him.
 * @return vector of all the neighbors.
 */
vector<State<Point *> *> Matrix::GetAllPossibleStates(State<Point *> *state) {
    Point *point = state->getState();
    double x = point->getX();
    double y = point->getY();
    int size = this->Size;
    vector<State<Point *> *> adjs;
    if (y + 1 < size) {
        State<Point *> *up = this->Tmatrix[x][y + 1];
        adjs.push_back(up);
    }
    if (x + 1 < size) {
        State<Point *> *right = this->Tmatrix[x + 1][y];
        adjs.push_back(right);
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

