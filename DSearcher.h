//
// Created by shaiac on 16/01/2020.
//

#ifndef EX4_DSEARCHER_H
#define EX4_DSEARCHER_H

#include "Solver.h"
#include "State.h"
#include <vector>
#include <list>
#include <queue>

/**
 * Comparing between 2 states by the trail cost, we will use in in the priority queue to
 * which state has the priority.
 * @tparam T the type of the object.
 */
template<typename T>
struct CustomCompare {
    bool operator()(State<T> *lhs, State<T> *rhs) {
        return lhs->GetCost() + lhs->getTrailCost() > rhs->GetCost()+rhs->getTrailCost();
    }
};

/**
 * Generic class of the searchers, to prevent duplicated code to find path from start to destination.
 * @tparam T the type of the object.
 */
template<typename T>
class DSearcher : public Searcher<T, vector<State<T> *>> {
public:
    virtual  vector<State<T> *> Search(Searchable<T> *searchable) = 0;

    bool IsInList(list<State<T> *> checklist, State<T> *check) {
        for (auto itr = checklist.begin(); itr != checklist.end(); itr++) {
            State<T> *itrP = *itr;
            if (*itrP->getState() == *check->getState()) {
                return true;
            }
        }
        return false;

    }
    /**
     * Checking if a state is in the priority queue.
     * @param pq the priority queue.
     * @param finder state<T> *.
     * @return true if we found false otherwise.
     */
    bool isInPriorityQueue(priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>>* pq, State<T> *finder) {
        list<State<T> *> holdOn;
        bool isIn = false;
        State<T> *check;
        while (!pq->empty()) {
            check = pq->top();
            pq->pop();
            if (check->getState() == finder->getState()) {
                isIn = true;
                holdOn.push_back(check);
                break;
            }
            holdOn.push_back(check);
        }
        while (!holdOn.empty()) {
            pq->push(holdOn.front());
            holdOn.pop_front();
        }
        return isIn;
    }
    /**
     * Getting a sate and building a path from start to him, tracing his path by from where he
     * came from.
     * @param end the state
     * @return vector of the path.
     */
    vector<State<T> *> BuildPath(State<T> *end) {
        vector<State<T> *> rev_path;
        rev_path.push_back(end);
        State<T> *back = end->GetCameFrom();
        while (back != nullptr) {
            rev_path.push_back(back);
            back = back->GetCameFrom();
        }
        return rev_path;
    }
};


#endif //EX4_DSEARCHER_H
