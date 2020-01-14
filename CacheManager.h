//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

template<typename P, typename S>
class CacheManager {
public:
    virtual bool isSolutionExist(P problem) = 0;
    virtual S getSolution(P problem) = 0;
    virtual void saveSolution(P problem, S solution) = 0;
};


#endif //EX4_CACHEMANAGER_H
