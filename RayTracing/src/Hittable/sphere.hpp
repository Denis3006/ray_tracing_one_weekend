#pragma once
#include "hittable.hpp"
#include <memory>

class Sphere : public Hittable {
public:
    Sphere(const Point& center, float radius, std::shared_ptr<const Material> material);
    const Point& center() const;
    float radius() const;
    std::optional<HitRecord> hit(const Ray& ray, float t_min, float t_max) const override;
    float get_t_if_hit(const Ray& ray, float t_min, float t_max) const override;
    HitRecord get_hit_results(const Ray& ray, float t) const override;
private:
    const Point C;
    const float r;
    std::shared_ptr<const Material> material;
};
