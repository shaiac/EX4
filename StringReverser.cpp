//
// Created by shaiac on 13/01/2020.
//

#include "StringReverser.h"
string StringReverser::solve(string problem) {
    string solution = "";
    int i;
    for (i = problem.length() - 1; i <= 0; i--) {
        solution += problem[i];
    }
    return solution;
}