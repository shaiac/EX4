//
// Created by shaiac on 14/01/2020.
//
using namespace std;
#include "Point.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

void Point::SetX(double x) {
    this->x = x;
}

void Point::SetY(double y) {
    this->y = y;
}

void Point::SetPoint(double x, double y) {
    SetX(x);
    SetY(y);
}

double Point::getX() {
    return this->x;
}

double Point::getY() {
    return this->y;
}

bool Point::isEqual(Point p) {
    if (p.getX() != this->getX()) {
        return false;
    }
    if (p.getY() != this->getY()) {
        return false;
    }
    return true;
}

bool Point::operator==(Point &p) {
    return isEqual(p);
}

string Point::createString() {
    string point;
    string x = to_string(this->getX());
    string y = to_string(this->getY());
    point = "(" + x + "," + y + ")";
    return point;
}
string Point::operator>(Point &p) {
    bool x = this->getX() > p.getX();
    bool equalx = this->getX() == p.getX();
    bool y = this->getY() > p.getY();
    bool  eqauly = this->getY() == p.getY();
    if(x && y && !eqauly && !equalx){
        return "Up Left, ";
    }
    if(!x && !y && !eqauly && !equalx){
        return "Down Right, ";
    }
    if(eqauly && equalx){
        return "Same, ";
    }
    if(x && eqauly){
        return "Up, ";
    }
    if(y && equalx){
        return "Left, ";
    }
    if(!x && eqauly){
        return "Down, ";
    }
    if(!y && equalx){
        return "Right, ";
    }
    if(x && !y){
        return "Up Right, ";
    }
    if(!x && y){
        return "Down Left, ";
    }
}