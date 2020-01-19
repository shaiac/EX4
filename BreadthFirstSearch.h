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

using namespace std;

template<typename T>
class BreadthFirstSearch :public Searcher<T, vector<State<T> *>> {
public:
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
        list<State<T> *> search_in_past;
        queue<State<T> *> to_search;
        State<T> *check;
        to_search.push(searchable->getInitialState());
        int x = 0;
        while (!to_search.empty()) {
            check = to_search.front();
            to_search.pop();
            if (IsInList(search_in_past, check)) {
                continue;
            }
            x++;
            search_in_past.push_back(check);
            if (searchable->isGoalState(check)) {
                break;
            }
            vector<State<T> *> adj = searchable->GetAllPossibleStates(check);
            for (auto adj_itr = adj.begin(); adj_itr != adj.end(); adj_itr++) {
                to_search.push(*adj_itr);
            }
        }
        cout << x << endl;
        return BuildPath(check);
    }
};


#endif //EX4_BREADTHFIRSTSEARCH_H
