//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H
using namespace std;

#include <string>
#include "CacheManager.h"

class FileCacheManager : public CacheManager {
protected:
    int capacity;

public:
    FileCacheManager(int capacity);

    bool isSolutionExist(string problem);

    char * getSolution(string problem);

    void saveSolution(string problem, string solution);

};

#endif //EX4_FILECACHEMANAGER_H
