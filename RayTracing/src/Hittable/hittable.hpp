#pragma once
#include <optional>
#include <vector>
#include <memory>

#include <glm/geometric.hpp>

#include "../Utils.hpp"
#include "../ray.hpp"

class Material;

struct HitRecord {
	bool valid;
	Point hit_point;
	glm::vec3 normal;
	std::shared_ptr<const Material> material = nullptr;
	float t;
	bool ray_from_outside;

	void set_face_normal(const Ray& ray, const glm::vec3& outward_normal) {
		ray_from_outside = glm::dot(ray.direction(), outward_normal) < 0;
		normal = ray_from_outside ? outward_normal : -outward_normal;
	}
};


class Hittable {
	public:
		virtual std::optional<HitRecord> hit(const Ray& ray, float t_min, float t_max) const = 0;
		virtual float get_t_if_hit(const Ray& ray, float t_min, float t_max) const = 0;
		virtual HitRecord get_hit_results(const Ray& ray, float t) const = 0;
};


class HittableList {
   public:
      HittableList() = default;
      HittableList(const std::shared_ptr<Hittable>);

      void add(const std::shared_ptr<Hittable>);
      void clear();
      std::optional<HitRecord> hit(const Ray& ray, float t_min, float t_max) const;
   private:
      std::vector<std::shared_ptr<Hittable>> list;
};