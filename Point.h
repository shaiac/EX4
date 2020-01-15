//
// Created by shaiac on 14/01/2020.
//

#ifndef EX4_POINT_H
#define EX4_POINT_H


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

};


#endif //EX4_POINT_H
