#include <corecrt_math_defines.h>
#include <glm/geometric.hpp>
#include "Camera.hpp"

Camera::Camera(const Point& look_from, const Point& look_at, const glm::vec3& vup, float vfov, float aspect_ratio, float aperture, float focus_dist)
	: lens_radius(aperture / 2), origin(look_from)
{
	viewport_height = 2 * std::tan(M_PI / 180 * vfov / 2);
	viewport_width = viewport_height * aspect_ratio;

	glm::vec3 w = glm::normalize(look_from - look_at);
	horziontal_unit = glm::normalize(glm::cross(vup, w));
	vertical_unit = glm::cross(w, horziontal_unit);
	horizontal = focus_dist * viewport_width * horziontal_unit;
	vertical = focus_dist * viewport_height * vertical_unit;
	ll_corner = Point(origin - horizontal / 2.0f - vertical / 2.0f - focus_dist * w);
}


Ray Camera::get_ray(float u, float v, uint32_t& state) const
{
	glm::vec3 aperture_offset = lens_radius * Random::random3d_in_unit_circle(state, 'z');
	glm::vec3 origin_with_offset = origin + horziontal_unit * aperture_offset.x + vertical_unit * aperture_offset.y;  // transform into camera coordinates
	return { origin_with_offset, ll_corner + u * horizontal + v * vertical - origin_with_offset };
}