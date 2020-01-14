//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H
using namespace std;
#include "CacheManager.h"
#include <list>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>
#include <functional>

class FileCacheManager : public CacheManager {
protected:
    hash<string> hashFunc;
    unordered_map<string, pair<string , list<string>::iterator>> cache;
    list<string> lruKeys;
    int capacity;

public:
    string updateLRU(string key);

    FileCacheManager(int capacity);

    bool isSolutionExist(string problem);

    string getSolution(string problem);

    void saveSolution(string problem, string solution);

};

#endif //EX4_FILECACHEMANAGER_H
