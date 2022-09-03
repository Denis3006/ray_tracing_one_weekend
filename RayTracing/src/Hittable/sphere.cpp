#include "sphere.hpp"

Sphere::Sphere(const Point& center, double radius, std::shared_ptr<const Material> material) : C(center), r(radius), material(material) {};

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
    Vec3D oc = ray.origin() - C;
    double a = ray.direction().dot(ray.direction());
    double half_b = ray.direction().dot(oc);
    double c = oc.length_squared() - r * r;
    double discriminant = half_b * half_b - a * c;
    HitRecord result;
    if (discriminant < 0) {
        return {};
    }
    else {
        double root = (- half_b - sqrt(discriminant) ) / a;
        if (root < t_min || root > t_max) {
            root = (- half_b + sqrt(discriminant)) / a;  // try another root
            if (root < t_min || root > t_max) {
                return {};
            }
        }
        result.t = root;
        result.hit_point = ray.at(result.t);
        result.material = material;
        auto outward_normal = Vec3D((result.hit_point - C)) / r;
        result.set_face_normal(ray, outward_normal);
        return result;
    }
}