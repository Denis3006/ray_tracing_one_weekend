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

std::optional<HitRecord> HittableList::hit(const Ray& ray, double t_min, double t_max) const
{
   double closest_so_far = t_max;
   std::optional<HitRecord> result = std::nullopt;
   for (const auto& obj : list) {
      auto temp_result = obj->hit(ray, t_min, closest_so_far);
      if (temp_result) {
         result = temp_result;
         closest_so_far = result.value().t;
      }
   }
   return result;
}


