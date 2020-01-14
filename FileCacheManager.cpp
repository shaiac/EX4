//
// Created by shaiac on 14/01/2020.
//

#include <cstring>
#include "FileCacheManager.h"

FileCacheManager::FileCacheManager(int capacity) {
    this->capacity = capacity;
}

string FileCacheManager::updateLRU(string key) {
    string oldKey;
    oldKey = lruKeys.back();
    this->lruKeys.pop_back();
    this->lruKeys.push_front(key);
    return oldKey;
}
bool FileCacheManager::isSolutionExist(string problem) {
    fstream file(to_string(hashFunc(problem)));
    if (this->cache.count(problem) == 1 || file) {
        return true;
    }
    return false;
}
string FileCacheManager::getSolution(string problem) {
    char* sol;
    string solution;
    if (this->cache.count(problem) == 1) {
        lruKeys.erase(this->cache[problem].second);
        this->lruKeys.push_front(problem);
        return this->cache[problem].first;
    } else {
        fstream file(to_string(hashFunc(problem)));
        if (!file) {
            cerr << "Error in file creating, key doesn't exist" << endl;
        }
        file.read(sol, solution.length());
        string solutionFromFile(sol);
        //updating him to be the last recently used, inserting him back to the cache.
        this->saveSolution(problem, solutionFromFile);
        file.close();
        return solutionFromFile;
    }
}

void  FileCacheManager::saveSolution(string problem, string solution) {
    list<string>::iterator it;
    pair <string, list<string>::iterator> pair;
    string oldKey;
    //If that key is already in the cache
    if (this->cache.count(problem) == 1) {
        this->cache.erase(problem);
        lruKeys.erase(this->cache[problem].second);
        this->lruKeys.push_front(problem);
    } else if (cache.size() == capacity) {
        oldKey = this->updateLRU(problem);
        this->cache.erase(oldKey);
    } else {
        this->lruKeys.push_front(problem);
    }
    string file_name = to_string(hashFunc(problem));
    file_name += ".txt";
    fstream file;
    file.open(file_name, fstream::out);
    if (!file) {
        cerr << "Error in file creating" << endl;
    }
    it = this->lruKeys.begin();
    pair.first = solution;
    pair.second = it;
    this->cache[problem] = pair;
    file.write(solution.c_str(), solution.length());
    file.close();
}