#pragma once
#include "base3d.hpp"

class Point : public Base3D {
public:
    Point() : Point(0, 0, 0) {};
    Point(double x, double y, double z) : Base3D(x, y, z) {};
    Point(const Base3D& other) : Base3D(other) {};

    double x() const;
    double y() const;
    double z() const;

    void set_x(double x);
    void set_y(double y);
    void set_z(double z);

    double distance_to(const Point& other) const;
};

double distance(const Point& first, const Point& second);