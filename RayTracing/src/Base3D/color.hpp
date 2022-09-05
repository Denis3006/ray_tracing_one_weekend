#pragma once
#include "base3d.hpp"


class Color : public Base3D {
public:
    Color();
    Color(double x, double y, double z);
    Color(const Color& other) = default;
    Color(const Base3D& other);

    double r() const;
    double g() const;
    double b() const;

    void set_r(double r);
    void set_g(double g);
    void set_b(double b);

    Color gamma_correct(double gamma) const;
};

Color arithmetic_to_true_color(const Base3D& arithmetic);
Color true_color_to_arithmetic(const Base3D& true_color);

namespace Colors {
    const Color BLACK(0, 0, 0);
    const Color WHITE(1, 1, 1);
    const Color RED(1, 0, 0);
    const Color GREEN(0, 1, 0);
    const Color BLUE(0, 0, 1);
}