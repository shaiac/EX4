//
// Created by shaiac on 16/01/2020.
//

#ifndef EX4_BREADTHFIRSTSEARCH_H
#define EX4_BREADTHFIRSTSEARCH_H


#include "Searcher.h"
#include <stack>
#include <list>
#include <queue>
#include <iostream>
#include "DSearcher.h"

using namespace std;

template<typename T>
class BreadthFirstSearch : public DSearcher<T> {
public:
    vector<State<T> *> Search(Searchable<T> *searchable) {
        list<State<T> *> search_in_past;
        queue<State<T> *> to_search;
        State<T> *check;
        to_search.push(searchable->getInitialState());
        int nodes = 0;
        while (!to_search.empty()) {
            check = to_search.front();
            to_search.pop();
            nodes++;
            if (this->IsInList(search_in_past, check)) {
                continue;
            }
            search_in_past.push_back(check);
            if (searchable->isGoalState(check)) {
                break;
            }
            vector<State<T> *> adj = searchable->GetAllPossibleStates(check);
            for (auto adj_itr = adj.begin(); adj_itr != adj.end(); adj_itr++) {
                State<T> *neigh = *adj_itr;
                if (neigh->GetCost() < 0) {
                    continue;
                }
                neigh->SetCameFrom(check);
                neigh->setTrailCost(check->getTrailCost() + neigh->GetCost());
                to_search.push(neigh);
            }
        }
        cout << "BFS Nodes:" << endl;
        cout << nodes << endl;
        return this->BuildPath(check);
    }
};


#endif //EX4_BREADTHFIRSTSEARCH_H
