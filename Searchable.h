//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <list>

#include "State.h"

template<typename T>
class Searchable {
    virtual State<T*>* getInitialState() = 0;

    virtual bool isGoalState(State<T*> state) = 0;

    virtual list<State<T*>*> GetAllPossibleStates(State<T*>* state) = 0;
};


#endif //EX4_SEARCHABLE_H
