#include "hittable.hpp"

HittableList::HittableList(const std::shared_ptr<Hittable> obj)
{
	add(obj);
}

void HittableList::add(const std::shared_ptr<Hittable> obj)
{
   list.emplace_back(obj);
}

void HittableList::clear()
{
   list.clear();
}

std::optional<HitRecord> HittableList::hit(const Ray& ray, float t_min, float t_max) const
{
	float closest_t_so_far = t_max;
	std::shared_ptr<Hittable> hit_obj = nullptr;
	for (const auto& obj : list) {
		auto temp_result = obj->get_t_if_hit(ray, t_min, closest_t_so_far);
		if (temp_result && temp_result.value() < closest_t_so_far) {
			closest_t_so_far = temp_result.value();
			hit_obj = obj;
		}
	}
	if (hit_obj != nullptr)
		return hit_obj->get_hit_results(ray, closest_t_so_far);
	return {};
}


