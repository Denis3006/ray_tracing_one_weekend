#pragma once
#include "hittable.hpp"
#include <memory>

class Sphere : public Hittable {
public:
    Sphere(const Point& center, double radius, std::shared_ptr<const Material> material);

    const Point& center() const;
    double radius() const;
    std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const override;
    std::optional<double> get_t_if_hit(const Ray& ray, double t_min, double t_max) const override;
    HitRecord get_hit_results(const Ray& ray, double t) const override;

private:
    const Point C;
    const double r;
    std::shared_ptr<const Material> material;
};
