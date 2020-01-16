//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_DEPTHFIRSTSEARCH_H
#define EX4_DEPTHFIRSTSEARCH_H

#include "Searcher.h"
#include <stack>
#include <list>
#include "DSearcher.h"

using namespace std;

template<typename T>
class DepthFirstSearch : public DSearcher<T> {
public:
    vector<State<T> *> Search(Searchable<T> *searchable) {
        list<State<T> *> search_in_past;
        stack<State<T> *> to_search;
        State<T> *check;
        to_search.push(searchable->getInitialState());
        while (!to_search.empty()) {
            check = to_search.top();
            to_search.pop();
            if (this->IsInList(search_in_past, check)) {
                continue;
            }
            search_in_past.push_back(check);
            if (searchable->isGoalState(check)) {
                break;
            }
            vector<State<T> *> adj = searchable->GetAllPossibleStates(check);
            for (auto adj_itr = adj.begin(); adj_itr != adj.end(); adj_itr++) {
                to_search.push(*adj_itr);
            }
        }
        return this->BuildPath(check);

    }
};


#endif //EX4_DEPTHFIRSTSEARCH_H