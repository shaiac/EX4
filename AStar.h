//
// Created by omer on 16.1.2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
#include <queue>
#include <list>
#include <unordered_map>
#include <limits>

template<typename T>

class AStar : public Searcher<T, vector<State<T> *>> {
public:

    bool IsInPQ(priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> *pq, State<T> *finder) {
        list<State<T> *> holdOn;
        bool flag = false;
        State<T> *check;
        while (!pq->empty()) {
            check = pq->top();
            pq->pop();
            if (*(check->getState()) == *(finder->getState())) {
                flag = true;
                holdOn.push_back(check);
                break;
            }
            holdOn.push_back(check);
        }
        while (!holdOn.empty()) {
            pq->push(holdOn.front());
            holdOn.pop_front();
        }
        return flag;
    }

    bool IsInList(list<State<T> *> checklist, State<T> *check) {
        for (auto itr = checklist.begin(); itr != checklist.end(); itr++) {
            State<T> *itrP = *itr;
            if (*itrP->getState() == *check->getState()) {
                return true;
            }
        }
        return false;

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
        unordered_map<State<T> *, double> destFromStart;
        list<State<T> *> past;
        vector<State<T> *> neighbors;
        priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> pq;
        destFromStart.insert(pair<State<T> *, double>(searchable->getInitialState(), 0));
        pq.push(searchable->getInitialState());
        State<T> *check;
        int x = 0;
        while (!pq.empty()) {
            x++;
            check = pq.top();
            past.push_back(check);
            pq.pop();
            if (searchable->isGoalState(check)) {
                break;
            }
            neighbors = searchable->GetAllPossibleStates(check);
            pair<State<T> *, double> checkInMap = *destFromStart.find(check);
            for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                State<T> *neigh = *it;
                if (neigh->GetCost() < 0) {
                    continue;
                }
                if (destFromStart.find(neigh) == destFromStart.end()) {
                    destFromStart.insert(pair<State<T> *, double>(neigh, numeric_limits<double>::infinity()));
                }
                pair<State<T> *, double> finder = *destFromStart.find(neigh);
                if (checkInMap.second + neigh->GetCost() < finder.second) {
                    neigh->SetCameFrom(check);
                    neigh->setTrailCost(checkInMap.second + neigh->GetCost());
                    destFromStart.at(neigh) = checkInMap.second + neigh->GetCost();
                    if (!IsInPQ(&pq, neigh)) {
                        pq.push(neigh);
                    }
                }
            }


        }
        cout << x << endl;
        return this->BuildPath(check);
    }

};


#endif //EX4_ASTAR_H
