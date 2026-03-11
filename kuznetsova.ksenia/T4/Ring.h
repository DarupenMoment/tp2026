<<<<<<< HEAD
#pragma once
=======
#ifndef RING_H
#define RING_H
>>>>>>> main

#include "Shape.h"

class Ring : public Shape {
private:
    Point center_;
    double outR_;
    double inR_;

public:
    Ring(const Point& center, double outRad, double inRad);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};
<<<<<<< HEAD
=======

#endif // RING_H
>>>>>>> main
