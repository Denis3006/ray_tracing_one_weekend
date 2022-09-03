#pragma once
#include "hittable.hpp"
#include <memory>

class Sphere : public Hittable {
public:
    Sphere(const Point& center, double radius, std::shared_ptr<const Material> material);

    const Point& center() const;
    double radius() const;
    virtual std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const override;

private:
    const Point C;
    const double r;
    std::shared_ptr<const Material> material;
};
