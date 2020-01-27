//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_POINT_H
#define EX4_POINT_H
using namespace std;
#include <string>
/**
 * A point class.
 */
class Point {
protected:
    double x;
    double y;
public:
    Point();
    Point(double x, double y);
    void SetX(double x);
    void SetY(double y);
    double getX();
    double getY();
    void SetPoint(double x, double y);
    bool isEqual(Point p);
    bool operator==(Point& p);
    string operator>(Point& p);
    string createString();


};


#endif //EX4_POINT_H
