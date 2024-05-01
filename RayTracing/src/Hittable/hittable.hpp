#pragma once
#include <optional>
#include <vector>
#include <memory>

#include "../Base3D/vec3d.hpp"
#include "../Base3D/point.hpp"
#include "../ray.hpp"

class Material;

struct HitRecord {
	Point hit_point;
	Vec3D normal;
	std::shared_ptr<const Material> material = nullptr;
	double t;
	bool ray_from_outside;

	void set_face_normal(const Ray& ray, const Vec3D& outward_normal) {
		ray_from_outside = ray.direction().dot(outward_normal) < 0;
		normal = ray_from_outside ? outward_normal : Vec3D(-outward_normal);
	}
};


class Hittable {
	public:
		virtual std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const = 0;
		virtual std::optional<double> get_t_if_hit(const Ray& ray, double t_min, double t_max) const = 0;
		virtual HitRecord get_hit_results(const Ray& ray, double t) const = 0;
};


class HittableList{
   public:
      HittableList() = default;
      HittableList(const std::shared_ptr<Hittable>);

      void add(const std::shared_ptr<Hittable>);
      void clear();
      std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const;
   private:
      std::vector<std::shared_ptr<Hittable>> list;
};