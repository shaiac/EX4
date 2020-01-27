//
// Created by shaiac on 16/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H
using namespace std;

#include "Searcher.h"
#include "BestFirstSearch.h"
#include <queue>
#include <list>
#include <unordered_map>
#include <limits>
#include <iostream>

template<typename T>
class AStar : public DSearcher<T> {
public:
    vector<State<T> *> Search(Searchable<T> *searchable) {
        unordered_map<State<T> *, double> destFromStart;
        list<State<T> *> past;
        vector<State<T> *> neighbors;
        priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> pq;
        destFromStart.insert(pair<State<T> *, double>(searchable->getInitialState(),
                searchable->getInitialState()->GetCost()));
        pq.push(searchable->getInitialState());
        State<T> *check;
        int nodes = 0;
        while (!pq.empty()) {
            nodes++;
            check = pq.top();
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
                    if (!this->isInPriorityQueue(&pq, neigh)) {
                        pq.push(neigh);
                    }
                }
            }


        }
        cout<< "ASTAR Nodes: ";
        cout<< nodes;
        cout<<" ASTAR Trial:";
        cout<<check->getTrailCost()<<endl;
        return this->BuildPath(check);
    }
};

#endif //EX4_ASTAR_H
