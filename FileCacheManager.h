//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H
using namespace std;

#include <string>
#include "CacheManager.h"
template<typename P, typename S>
class FileCacheManager : public CacheManager<P , S> {
protected:
    int capacity;
public:
    FileCacheManager(int capacity);
    bool isSolutionExist(P problem);
    string getSolution(P problem);
    void saveSolution(P problem, S solution);
};

template<typename P, typename S> FileCacheManager<P,S> ::FileCacheManager(int capacity) {
    this->capacity = capacity;
}

#endif //EX4_FILECACHEMANAGER_H
