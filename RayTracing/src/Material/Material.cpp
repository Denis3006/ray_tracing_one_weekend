#include "material.hpp"
#include "../Utils.hpp"
#include <glm/geometric.hpp>

const Color::Color& Material::albedo() const
{
	return albedo_value;
}

Ray Lambertian::scatter(const Ray& ray_in, const HitRecord& hit_record, uint32_t& state) const
{
	const float EPSILON = 1e-8f;
	glm::vec3 scatter_direction = hit_record.normal + Random::random_in_hemisphere(hit_record.normal, state);
	if (glm::length(scatter_direction) < EPSILON)  // randomly generated direction vector and normal vector are collinear
		scatter_direction = hit_record.normal;
	return { hit_record.hit_point, scatter_direction };
}

Ray Metal::scatter(const Ray& ray_in, const HitRecord& hit_record, uint32_t& state) const
{
	glm::vec3 scatter_direction = glm::reflect(ray_in.direction(), hit_record.normal) + fuzz * Random::random3d_in_unit_sphere(state);
	if (glm::dot(scatter_direction, hit_record.normal) < 0)
		scatter_direction = glm::vec3(0);
	return { hit_record.hit_point, scatter_direction };
}

Ray Dielectric::scatter(const Ray& ray_in, const HitRecord& hit_record, uint32_t& state) const
{
	float ri = hit_record.ray_from_outside ? (1 / refraction_index) : refraction_index;
	float cos_theta = -glm::dot(glm::normalize(ray_in.direction()), glm::normalize(hit_record.normal));
	float sin_theta = glm::sqrt(1 - cos_theta * cos_theta);
	float r0 = glm::pow((1 - ri) / (1 + ri), 2);
	float reflection_factor = r0 + (1 - r0) * glm::pow(1 - cos_theta, 5);
	glm::vec3 scatter_direction(0);
	if (sin_theta * ri > 1 || reflection_factor > Random::random_float(state, 1)) { // total reflection
		scatter_direction = glm::reflect(ray_in.direction(), hit_record.normal);
	}
	else {
		scatter_direction = glm::refract(glm::normalize(ray_in.direction()), glm::normalize(hit_record.normal), ri);
	}
	return { hit_record.hit_point, scatter_direction };
}

