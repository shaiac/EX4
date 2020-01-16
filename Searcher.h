//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"

template<typename T, typename S>
class Searcher {
    virtual S Search(Searchable<T> *searchable) = 0;
};


#endif //EX4_SEARCHER_H
