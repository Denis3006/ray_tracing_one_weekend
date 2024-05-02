#include "Sphere.hpp"

Sphere::Sphere(const Point& center, float radius, std::shared_ptr<const Material> material) : C(center), r(radius), material(std::move(material)) {};

const Point& Sphere::center() const
{
	return C;
}

float Sphere::radius() const
{
	return r;
}

std::optional<HitRecord> Sphere::hit(const Ray& ray, float t_min, float t_max) const
{
    if (float t = get_t_if_hit(ray, t_min, t_max); t < INFINITY) {
        return get_hit_results(ray, t);
    }
    return {};
}

float Sphere::get_t_if_hit(const Ray& ray, float t_min, float t_max) const
{
    glm::vec3 co = C - ray.origin();
    float a = length_squared(ray.direction());
    float negative_half_b = glm::dot(ray.direction(), co);
    float c = length_squared(co) - r * r;
    float discriminant = negative_half_b * negative_half_b - a * c;
    if (discriminant >= 0) {
        float discriminant_sqrt = glm::sqrt(discriminant);
        float root = (negative_half_b - discriminant_sqrt) / a;
        if (root < t_min || root > t_max) {
            root = (negative_half_b + discriminant_sqrt) / a;  // try another root
            if (root < t_min || root > t_max) {
                return INFINITY;
            }
        }
        return root;
    }
    return INFINITY;
}

HitRecord Sphere::get_hit_results(const Ray& ray, float t) const
{
    HitRecord result;
    result.t = t;
    result.hit_point = ray.at(result.t);
    result.material = material;
    auto outward_normal = (result.hit_point - C) / r;
    result.set_face_normal(ray, outward_normal);
    return result;
}
