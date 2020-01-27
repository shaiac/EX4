//
// Created by shaiac on 16/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "Searcher.h"
#include "Solver.h"
#include "DSearcher.h"
/**
 * A class that connect between the solver and the searcher.
 * @tparam P The type of the problem.
 * @tparam T The type that we give to the searcher.
 */
template<typename P, typename T>
class OA : public Solver<P,string> {
protected:
    DSearcher<T>* searcher;
public:
    OA(DSearcher<T>* searcher) {
        this->searcher = searcher;
    }
    /**
     * solving the problem and creating a matching string for the solution to give back to the client.
     * @param problem the problem.
     * @return string the solution.
     */
    string solve(P problem) {
        string trailCost;
        vector<State<T>*> solution = this->searcher->Search(problem);
        auto itr = solution.end();
        itr--;
        State<T>* first = *itr;
        itr--;
        string stringSolution="";
        while(itr != solution.begin()){
            State<T> * second = *itr;
            itr--;
            trailCost = to_string(int(second->getTrailCost()));
            stringSolution += first->Direction(second->getState()) + "(" + trailCost + "), ";
            first = second;
        }
        State<T> * second = *itr;
        trailCost = to_string(int(second->getTrailCost()));
        stringSolution += first->Direction(second->getState()) + "(" + trailCost + ")";
        return stringSolution;
    }
};



#endif //EX4_OA_H
