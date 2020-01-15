//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H
using namespace std;

#include <string>

template<typename T>
class State {
protected:
    T state;
    double cost;
    State<T>* cameFrom;
public:
    State(T state, double cost);
    T getState();

};

template<typename T>
State<T>::State(T state, double cost) {
    this->state = state;
    this->cost = cost;
}

template<typename T>
T State<T>::getState() {
    return this->state;
}

#endif //EX4_STATE_H
