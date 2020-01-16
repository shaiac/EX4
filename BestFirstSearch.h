//
// Created by shaiac on 15/01/2020.
//

#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H
#include "Searcher.h"
#include <queue>
#include <list>
#include <unordered_set>

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

    bool isInPriorityQueue(priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>>* pq, State<T> *finder) {
        list<State<T> *> holdOn;
        bool isIn = false;
        State<T> *check;
        while (!pq->empty()) {
            check = pq->top();
            pq->pop();
            if (check->getState() == finder->getState()) {
                isIn = true;
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
        unordered_set<State<T> *> search_in_past;
        vector<State<T> *> neighbors;
        State<T> *check;
        priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> pq;
        pq.push(searchable->getInitialState());
        int x = 0;
        while (!pq.empty()) {
            x++;
            check = pq.top();
            pq.pop();
            search_in_past.insert(check);
            if (searchable->isGoalState(check)) {
                cout << x << endl;
                return this->BuildPath(check);;
            }
            neighbors = searchable->GetAllPossibleStates(check);
            for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                State<T> *tmp = *it;
                if (tmp->GetCost() < 0) {
                    continue;
                }
                bool stateInPq = this->isInPriorityQueue(&pq, tmp);
                bool stateInPast = (search_in_past.find(tmp) == search_in_past.end());
                if (stateInPast && !stateInPq) {
                    tmp->setTrailCost(check->getTrailCost() + tmp->GetCost());
                    tmp->SetCameFrom(check);
                    pq.push(tmp);
                } else if (tmp->getTrailCost() > check->getTrailCost() + tmp->GetCost()) {
                    tmp->setTrailCost(check->getTrailCost() + tmp->GetCost());
                    tmp->SetCameFrom(check);
                    pq.push(tmp);
                    continue;
                } else if (stateInPq){
                    pq.push(tmp);
                }
            }
        }
        return this->BuildPath(check);
    }
};


#endif //EX4_BESTFIRSTSEARCH_H
