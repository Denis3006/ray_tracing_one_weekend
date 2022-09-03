#pragma once
#include "base3d.hpp"

class Vec3D : public Base3D {
public:
    Vec3D() : Vec3D(0, 0, 0) {};
    Vec3D(double x, double y, double z) : Base3D(x, y, z) {};
    Vec3D(const Vec3D& other) = default;
    Vec3D(const Base3D& other) : Base3D(other) {};

    double e1() const;
    double e2() const;
    double e3() const;

    void set_e1(double e1);
    void set_e2(double e2);
    void set_e3(double e3);

    double distance_to(const Vec3D& other) const;
    double length() const;
    double dot(const Vec3D& other) const;
    Vec3D cross(const Vec3D& other) const;
    Vec3D normalize() const;
    bool is_unit() const;
    double length_squared() const;
    Vec3D reflect(const Vec3D& n) const;
    Vec3D refract(const Vec3D& n, double refraction_index) const;
};

double length_of(const Vec3D& vec);
double dot(const Vec3D& first, const Vec3D& second);
Vec3D cross(const Vec3D& first, const Vec3D& second);
Vec3D random_unit_vector();
Vec3D random_in_hemisphere(const Vec3D& normal);
Vec3D reflect(const Vec3D& v, const Vec3D& n);
Vec3D refract(const Vec3D& v, const Vec3D& n, double refraction_index);
