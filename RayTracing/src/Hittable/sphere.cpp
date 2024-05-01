#include "Sphere.hpp"

Sphere::Sphere(const Point& center, double radius, std::shared_ptr<const Material> material) : C(center), r(radius), material(std::move(material)) {};

const Point& Sphere::center() const
{
	return C;
}

double Sphere::radius() const
{
	return r;
}

std::optional<HitRecord> Sphere::hit(const Ray& ray, double t_min, double t_max) const
{
    if (auto t = get_t_if_hit(ray, t_min, t_max); t.has_value()) {
        return get_hit_results(ray, t.value());
    }
    return {};
}

std::optional<double> Sphere::get_t_if_hit(const Ray& ray, double t_min, double t_max) const
{
    Vec3D co = C - ray.origin();
    double a = ray.direction().length_squared();
    double negative_half_b = ray.direction().dot(co);
    double c = co.length_squared() - r * r;
    double discriminant = negative_half_b * negative_half_b - a * c;
    if (discriminant >= 0) {
        double discriminant_sqrt = std::sqrt(discriminant);
        double root = (negative_half_b - discriminant_sqrt) / a;
        if (root < t_min) {
            root = (negative_half_b + discriminant_sqrt) / a;  // try another root
            if (root < t_min || root > t_max) {
                return {};
            }
        }
        return root;
    }
    return {};
}

HitRecord Sphere::get_hit_results(const Ray& ray, double t) const
{
    HitRecord result;
    result.t = t;
    result.hit_point = ray.at(result.t);
    result.material = material;
    auto outward_normal = Vec3D(result.hit_point - C) / r;
    result.set_face_normal(ray, outward_normal);
    return result;
}
