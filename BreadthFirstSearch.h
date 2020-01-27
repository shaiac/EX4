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
        int nodes = 0;
        list<State<T> *> search_in_past;
        queue<State<T> *> to_search;
        State<T> *check;
        to_search.push(searchable->getInitialState());
        search_in_past.push_front(check);
        while (to_search.size() > 0) {
            check = to_search.front();
            to_search.pop();
            nodes++;
            if (searchable->isGoalState(check)) {
                break;
            }
            vector<State<T> *> adj = searchable->GetAllPossibleStates(check);
            for (auto adj_itr = adj.begin(); adj_itr != adj.end(); adj_itr++) {
                State<T> *neigh = *adj_itr;
                if (this->IsInList(search_in_past, neigh)) {
                    continue;
                }
                if (neigh->GetCost() < 0) {
                    continue;
                }
                neigh->SetCameFrom(check);
                neigh->setTrailCost(check->getTrailCost() + neigh->GetCost());
                to_search.push(neigh);
                search_in_past.push_front(neigh);
            }
        }
        cout << "BFS Nodes:";
        cout << nodes;
        cout<<" BFS Trial:";
        cout<<check->getTrailCost()<<endl;
        return this->BuildPath(check);
    }
};


#endif //EX4_BREADTHFIRSTSEARCH_H
