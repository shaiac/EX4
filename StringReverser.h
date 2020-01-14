//
// Created by shaiac on 13/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H
using namespace std;

#include <string>
#include "Solver.h"

class StringReverser : public Solver<string,string> {
public:
    string solve(string problem);
};


#endif //EX4_STRINGREVERSER_H
