//
// Created by shaiac on 16/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "Searcher.h"
#include "Solver.h"
#include "DSearcher.h"

template<typename P, typename T>
class OA : public Solver<P,string> {
protected:
    DSearcher<T>* searcher;
public:
    OA(DSearcher<T>* searcher) {
        this->searcher = searcher;
    }

    string solve(P problem) {
        vector<State<T>*> solution = this->searcher->Search(problem);
        auto itr = solution.end();
        itr--;
        State<T>* first = *itr;
        itr--;
        string stringSolution="";
        while(itr != solution.begin()){
            State<T> * second = *itr;
            itr--;
            stringSolution += first->Direction(second->getState());
            first = second;
        }
        State<T> * second = *itr;
        itr--;
        stringSolution += first->Direction(second->getState());
        stringSolution = stringSolution.substr(0, stringSolution.length() - 2);
        return stringSolution;
    }
};



#endif //EX4_OA_H
