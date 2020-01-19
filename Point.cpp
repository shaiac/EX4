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