#include "material.hpp"
#include "../Random.hpp"

const Color& Material::albedo() const
{
	return albedo_value;
}

Ray Lambertian::scatter(const Ray& ray_in, const HitRecord& hit_record) const
{
	Vec3D scatter_direction = Random::random_in_hemisphere(hit_record.normal);
	if (scatter_direction.approx_zero())  // randomly generated direction vector and normal vector are collinear
		scatter_direction = hit_record.normal;
	return { hit_record.hit_point, scatter_direction };
}

Ray Metal::scatter(const Ray& ray_in, const HitRecord& hit_record) const
{
	Vec3D scatter_direction = ray_in.direction().reflect(hit_record.normal) + fuzz * Random::random3d_in_unit_sphere();
	if (dot(scatter_direction, hit_record.normal) < 0)
		scatter_direction = Vec3D({ 0, 0, 0 });
	return { hit_record.hit_point, scatter_direction };
}

Ray Dielectric::scatter(const Ray& ray_in, const HitRecord& hit_record) const
{
	double ri = hit_record.ray_from_outside ? (1 / refraction_index) : refraction_index;
	double cos_theta = -ray_in.direction().normalize().dot(hit_record.normal.normalize());
	double sin_theta = std::sqrt(1 - cos_theta * cos_theta);
	double r0 = (1 - ri) / (1 + ri);
	r0 *= r0;
	double reflection_factor = r0 + (1 - r0) * std::pow(1 - cos_theta, 5);
	Vec3D scatter_direction;
	if (sin_theta * ri > 1 || reflection_factor > Random::random_double(0, 1)) { // total reflection
		scatter_direction = ray_in.direction().reflect(hit_record.normal);
	}
	else {
		scatter_direction = ray_in.direction().refract(hit_record.normal, ri);
	}
	return { hit_record.hit_point, scatter_direction };
}

