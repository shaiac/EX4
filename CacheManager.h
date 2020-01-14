//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

class CacheManager {
public:
    virtual bool isSolutionExist(string problem) = 0;
    virtual char * getSolution(string problem) = 0;
    virtual void saveSolution(string problem, string solution) = 0;
};


#endif //EX4_CACHEMANAGER_H
