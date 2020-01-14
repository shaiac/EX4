//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_CACHEMFROM2_H
#define EX4_CACHEMFROM2_H

using namespace std;

#include <unordered_map>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>

/**
 * The class fields are the max capacity of the map, an unordered map that has a string key,
 * pair of the object and iterator that save his place in the lru list (because we want to get
 * objects in o(1)), the list of the last recently used keys.
 */
template<typename T>
class CacheMfrom2 {
protected:
    unordered_map<string, pair<T, list<string>::iterator>> cache;
    list<string> lruKeys;
    int capacity;
public:
    CacheMfrom2(int capacity);

    string updateLRU(string key);

    void insert(string key, T obj, string name_of_file);

    T get(string key);

    void foreach(const function<void(T &)> func);
};

/**
 * Constructor for the class.
 * @tparam T the type.
 * @param capacity max capacity of the map.
 */
template<typename T>
CacheMfrom2<T>::CacheMfrom2(int capacity) {
    this->capacity = capacity;
}

template<typename T>
string CacheMfrom2<T>::updateLRU(string key) {
    string oldKey;
    oldKey = lruKeys.back();
    this->lruKeys.pop_back();
    this->lruKeys.push_front(key);
    return oldKey;
}

/**
 * Inserting an object to the map.
 * @tparam T the type
 * @param key string - the key of the object.
 * @param obj T - the object that we want to insert.
 */
template<typename T>
void CacheMfrom2<T>::insert(string key, T obj) {
    list<string>::iterator it;
    pair<T, list<string>::iterator> pair;
    string oldKey;
    //If that key is already in the cache
    if (this->cache.count(key) == 1) {
        this->cache.erase(key);
        lruKeys.erase(this->cache[key].second);
        this->lruKeys.push_front(key);
    } else if (cache.size() == capacity) {
        oldKey = this->updateLRU(key);
        this->cache.erase(oldKey);
    } else {
        this->lruKeys.push_front(key);
    }
    fstream file (obj.class_name + key, ios::out | ios::binary);
    if (!file) {
        cerr << "Error in file creating" << endl;
    }
    it = this->lruKeys.begin();
    pair.first = obj;
    pair.second = it;
    this->cache[key] = pair;
    file.write((char*)&obj, sizeof(obj));
    file.close();
}

/**
 * Getting an object from the cache by key in O(1).
 * @tparam T the type.
 * @param key the key.
 * @return the object for that key.
 */
template<typename T>
T CacheMfrom2<T>::get(string key) {
    T obj;
    if (this->cache.count(key) == 1) {
        lruKeys.erase(this->cache[key].second);
        this->lruKeys.push_front(key);
        return this->cache[key].first;
    } else {
        fstream file(T().class_name + key, ios::in | ios::binary);
        if (!file) {
            cerr << "Error in file creating, key doesn't exist" << endl;
        }
        file.read((char *) &obj, sizeof(obj));
        //updating him to be the last recently used, inserting him back to the cache.
        insert(key, obj);
        file.close();
        return obj;
    }
}

/**
 * Implementing a given function for each object in the cache.
 * @tparam T the type.
 * @param func the function.
 */
template<typename T>
void CacheMfrom2<T>::foreach(const function<void(T &)> func) {
    list<string>::iterator it;
    for (it = lruKeys.begin(); it != lruKeys.end(); it++) {
        func(this->cache[*it].first);
    }
}

#endif //EX4_CACHEMFROM2_H
