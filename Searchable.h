//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <list>

#include "State.h"
#include <vector>
/**
 * Interface of the searchables.
 * @tparam T type of an object.
 */
template<typename T>
class Searchable {
public:
    virtual State<T>* getInitialState() = 0;

    virtual bool isGoalState(State<T>* state) = 0;

    virtual vector<State<T>*> GetAllPossibleStates(State<T>* state) = 0;
};


#endif //EX4_SEARCHABLE_H
