//
// Created by shaiac on 15/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H


#include "Searcher.h"
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

template<typename T>
struct CustomCompare {
    bool operator()(State<T> *lhs, State<T> *rhs) {
        return lhs->GetCost() > rhs->GetCost();
    }
};

template<typename T>
class BestFirstSearch : public Searcher<T, vector<State<T> *>> {
public:

    State<T> *isInList(list<State<T> *> *checklist, State<T> *check) {
        for (auto itr = checklist->begin(); itr != checklist->end(); itr++) {
            State<T> *itrP = *itr;
            if (*(itrP->getState()) == *(check->getState())) {
                checklist->erase(itr);
                return *itr;
            }
        }
        return nullptr;

    }

    State<T> *
    PopFromPriorityQueue(priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> *pq, State<T> *finder) {
        list<State<T> *> holdOn;
        bool flag = false;
        State<T> *check;
        while (!pq->empty()) {
            check = pq->top();
            pq->pop();
            if (*(check->getState()) == *(finder->getState())) {
                flag = true;
                break;
            }
            holdOn.push_back(check);
        }
        while (!holdOn.empty()) {
            pq->push(holdOn.front());
            holdOn.pop_front();
        }
        if (flag) {
            return check;
        }
        return nullptr;
    }

    /**bool
    PopFromPriorityQueue(priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> pq, State<T> *finder) {
        list<State<T> *> holdOn;
        bool isIn = false;
        State<T> *check;
        while (!pq.empty()) {
            check = pq.top();
            pq.pop();
            if (check->getState() == finder->getState()) {
                isIn = true;
                break;
            }
            holdOn.push_back(check);
        }
        while (!holdOn.empty()) {
            pq.push(holdOn.front());
            holdOn.pop_front();
        }
        return isIn;
    }

    bool isInList(list<State<T> *> checklist, State<T> *check) {
        for (auto itr = checklist.begin(); itr != checklist.end(); itr++) {
            State<T> *itrP = *itr;
            if (*itrP->getState() == *check->getState()) {
                return true;
            }
        }
        return false;
    }*/

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

    vector<State<T> *> Search(Searchable<T> *searchable) {
        unordered_map<string, double> pathLength;
        list<State<T> *> search_in_past;
        vector<State<T> *> neighbors;
        State<T> *check;
        priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> pq;
        pq.push(searchable->getInitialState());
        int x = 0;
        while (!pq.empty()) {
            check = pq.top();
            x++;
            pq.pop();
            if (searchable->isGoalState(check)) {
                cout<<x<<endl;
                return this->BuildPath(check);;
            }
            search_in_past.push_front(check);
            neighbors = searchable->GetAllPossibleStates(check);
            for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                State<T> *tmp = *it;
                if (tmp->GetCost() < 0) {
                    continue;
                }
                State<T> *stateInPq = this->PopFromPriorityQueue(&pq, tmp);
                State<T> *stateInPast = isInList(&search_in_past, *it);
                if (stateInPq == nullptr && stateInPast == nullptr) {
                    tmp->setTrailCost(check->getTrailCost() + tmp->GetCost());
                    pq.push(tmp);
                } else {
                    if (stateInPq == nullptr) {
                        if (stateInPast->getTrailCost() > check->getTrailCost() + stateInPast->GetCost()) {
                            tmp->setTrailCost(check->getTrailCost() + tmp->GetCost());
                            pq.push(tmp);
                            //search_in_past.push_back(stateInPast);
                        } else {
                            search_in_past.push_back(stateInPast);
                        }
                    } else {
                        if (stateInPq->getTrailCost() > check->getTrailCost() + stateInPq->GetCost()) {
                            tmp->setTrailCost(check->getTrailCost() + tmp->GetCost());
                            pq.push(tmp);
                        } else {
                            pq.push(stateInPq);
                        }
                    }
                }
            }
        }
        return this->BuildPath(check);
    }
};


#endif //EX4_BESTFIRSTSEARCH_H
