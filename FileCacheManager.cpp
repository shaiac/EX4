//
// Created by shaiac on 14/01/2020.
//

#include <cstring>
#include "FileCacheManager.h"

/**
 * constructor of the class.
 * @param capacity the capacity of the cache map.
 */
FileCacheManager::FileCacheManager(int capacity) {
    this->capacity = capacity;
}

/**
 * updating the last recently use list.
 * @param key the key.
 * @return
 */
string FileCacheManager::updateLRU(string key) {
    string oldKey;
    oldKey = lruKeys.back();
    this->lruKeys.pop_back();
    this->lruKeys.push_front(key);
    return oldKey;
}

/**
 * Checking if there is already solution for that problem in the files.
 * @param problem the problem.
 * @return
 */
bool FileCacheManager::isSolutionExist(string problem) {
    string hash = to_string(hashFunc(problem));
    fstream file(hash + ".txt", ios::in);
    if (this->cache.count(problem) == 1 || file.is_open()) {
        return true;
    }
    return false;
}
/**
 * Checking first if the solution exist in the cache if exist return it, if not exist in the cache
 * going to take the solution from the right file. we are mapping problem to file name by the hash function.
 * @param problem the problem.
 * @return solution represented by string.
 */
string FileCacheManager::getSolution(string problem) {
    string solution;
    if (this->cache.count(problem) == 1) {
        lruKeys.erase(this->cache[problem].second);
        this->lruKeys.push_front(problem);
        return this->cache[problem].first;
    } else {
        string file_name = to_string(hashFunc(problem));
        file_name += ".txt";
        fstream file;
        file.open(file_name, fstream::in);
        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);
        char *sol = new char[length];
        if (!file) {
            cerr << "Error in file creating, key doesn't exist" << endl;
        }
        file.read(sol, length);
        string solutionFromFile(sol);
        //updating him to be the last recently used, inserting him back to the cache.
        this->saveSolution(problem, solutionFromFile);
        file.close();
        return solutionFromFile;
    }
}

/**
 * saving the solution of a problem.
 * @param problem string of the problem.
 * @param solution string of the solution.
 */
void FileCacheManager::saveSolution(string problem, string solution) {
    list<string>::iterator it;
    pair<string, list<string>::iterator> pair;
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
    //mapping the problem to a number by hash function.
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