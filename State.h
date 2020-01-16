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
    State<T> *cameFrom;
    double trailCost;
public:
    State(T state, double cost);

    T getState();

    double GetCost();

    State<T> *GetCameFrom();

    void SetCameFrom(State<T> *cmf);

    double getTrailCost();

    void setTrailCost(double trailCost);

    string Direction(T second);
};

template<typename T>
State<T>::State(T state, double cost) {
    this->state = state;
    this->cost = cost;
    this->cameFrom = nullptr;
}

template<typename T>
T State<T>::getState() {
    return this->state;
}

template<typename T>
double State<T>::GetCost() {
    return this->cost;
}

template<typename T>
State<T> *State<T>::GetCameFrom() {
    return this->cameFrom;
}

template<typename T>
void State<T>::SetCameFrom(State<T> *cmf) {
    this->cameFrom = cmf;
}

template<typename T>
double State<T>::getTrailCost() {
    return this->trailCost;
}

template<typename T>
void State<T>::setTrailCost(double trailCost) {
    this->trailCost = trailCost;
}

template<typename T>
string State<T>::Direction(T second) {
    return *(this->getState()) > (*second);
}


#endif //EX4_STATE_H
