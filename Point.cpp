//
// Created by shaiac on 14/01/2020.
//
using namespace std;
#include "Point.h"

/**
 * Empty constructor.
 */
Point::Point() {
    this->x = 0;
    this->y = 0;
}
/**
 * Constructor that getting the x,y of the point.
 * @param x double number.
 * @param y double number.
 */
Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

/**
 * Setting a x of a point.
 * @param x double number.
 */
void Point::SetX(double x) {
    this->x = x;
}

/**
 * Setting a y of a point.
 * @param y double number.
 */
void Point::SetY(double y) {
    this->y = y;
}

/**
 * @return The x of the point.
 */
double Point::getX() {
    return this->x;
}

/**
 * @return The y of the point.
 */
double Point::getY() {
    return this->y;
}

/**
 * Checking if two points are equal by there x and y.
 * @param p point to check if this point is equal to.
 * @return true if equal false if not.
 */
bool Point::isEqual(Point p) {
    if (p.getX() != this->getX()) {
        return false;
    }
    if (p.getY() != this->getY()) {
        return false;
    }
    return true;
}

/**
 * Overloading the == operator for two points
 * @param p a Point.
 * @return true if equal false if not.
 */
bool Point::operator==(Point &p) {
    return isEqual(p);
}

/**
 * Creating a string of a point.
 * @return the string.
 */
string Point::createString() {
    string point;
    string x = to_string(this->getX());
    string y = to_string(this->getY());
    point = "(" + x + "," + y + ")";
    return point;
}

/**
 * Overloading the > operator checking for 2 point the location over the other.
 * @param p the point.
 * @return the location.
 */
string Point::operator>(Point &p) {
    bool x = this->getX() > p.getX();
    bool equalx = this->getX() == p.getX();
    bool y = this->getY() > p.getY();
    bool  eqauly = this->getY() == p.getY();
    if(x && y && !eqauly && !equalx){
        return "Up Left ";
    }
    if(!x && !y && !eqauly && !equalx){
        return "Down Right ";
    }
    if(eqauly && equalx){
        return "Same ";
    }
    if(x && eqauly){
        return "Up ";
    }
    if(y && equalx){
        return "Left ";
    }
    if(!x && eqauly){
        return "Down ";
    }
    if(!y && equalx){
        return "Right ";
    }
    if(x && !y){
        return "Up Right ";
    }
    if(!x && y){
        return "Down Left ";
    }
}