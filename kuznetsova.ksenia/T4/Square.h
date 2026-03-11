<<<<<<< HEAD
#pragma once
=======
#ifndef SQUARE_H
#define SQUARE_H
>>>>>>> main

#include "Shape.h"

class Square : public Shape {
private:
    Point bottomLeft_;
    double side_;

public:
    Square(const Point& bottomLeft, double sideLength);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};
<<<<<<< HEAD
=======

#endif // SQUARE_H
>>>>>>> main
