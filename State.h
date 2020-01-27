//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H
using namespace std;

#include <string>

/**
 * Generic class of a state.
 * @tparam T type of an object.
 */
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
/**
 * Constructor for the class, initializing the state, the cost of the state.
 * @tparam T object type.
 * @param state the state (can be point etc).
 * @param cost the cost.
 */
template<typename T>
State<T>::State(T state, double cost) {
    this->state = state;
    this->cost = cost;
    this->cameFrom = nullptr;
}
/**
 * @tparam T object type.
 * @return the state.
 */
template<typename T>
T State<T>::getState() {
    return this->state;
}
/**
 * @tparam T object type.
 * @return the cost of the state.
 */
template<typename T>
double State<T>::GetCost() {
    return this->cost;
}

/**
 * @tparam T object type.
 * @return from where which state we got to that state.
 */
template<typename T>
State<T> *State<T>::GetCameFrom() {
    return this->cameFrom;
}

/**
 * setting the state that we came from.
 * @tparam T object type.
 * @param cmf the state that we came from.
 */
template<typename T>
void State<T>::SetCameFrom(State<T> *cmf) {
    this->cameFrom = cmf;
}
/**
 * @tparam T object type.
 * @return the trail cost.
 */
template<typename T>
double State<T>::getTrailCost() {
    return this->trailCost;
}
/**
 * setting the trail cost (the cost that we pay to get to that state).
 * @tparam T object type.
 * @param trailCost the trailcost.
 */
template<typename T>
void State<T>::setTrailCost(double trailCost) {
    this->trailCost = trailCost;
}

/**
 * @tparam T object type.
 * @param second the other state.
 * @return the direction that we went.
 */
template<typename T>
string State<T>::Direction(T second) {
    return *(this->getState()) > (*second);
}


#endif //EX4_STATE_H
