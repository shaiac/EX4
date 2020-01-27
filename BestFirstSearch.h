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
class BestFirstSearch : public DSearcher<T> {
public:
    vector<State<T> *> Search(Searchable<T> *searchable) {
        unordered_set<State<T> *> search_in_past;
        vector<State<T> *> neighbors;
        State<T> *check;
        priority_queue<State<T> *, vector<State<T> *>, CustomCompare<T>> pq;
        pq.push(searchable->getInitialState());
        int nodes = 0;
        while (!pq.empty()) {
            check = pq.top();
            pq.pop();
            nodes++;
            search_in_past.insert(check);
            if (searchable->isGoalState(check)) {
                break;
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
                }
            }
        }
        cout<< "BESTFS Nodes:";
        cout<< nodes;
        cout<<" BESTFS Trial:";
        cout<<check->getTrailCost()<<endl;
        return this->BuildPath(check);
    }
};


#endif //EX4_BESTFIRSTSEARCH_H
