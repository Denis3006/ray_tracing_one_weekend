#include <corecrt_math_defines.h>
#include "Camera.hpp"
#include "Random.hpp"

Camera::Camera(const Point& look_from, const Point& look_at, const Vec3D& vup, double vfov, double aspect_ratio, double aperture, double focus_dist)
	: lens_radius(aperture / 2), origin(look_from)
{
	viewport_height = 2 * std::tan(M_PI / 180 * vfov / 2);
	viewport_width = viewport_height * aspect_ratio;

	Vec3D w = Vec3D(look_from - look_at).normalize();
	horziontal_unit = vup.cross(w).normalize();
	vertical_unit = w.cross(horziontal_unit);
	horizontal = focus_dist * viewport_width  * horziontal_unit;
	vertical = focus_dist * viewport_height * vertical_unit;
	ll_corner = Point(origin - horizontal / 2 - vertical / 2 - focus_dist * w);
}


Ray Camera::get_ray(double u, double v) const
{
	Vec3D aperture_offset = lens_radius * Random::random3d_in_unit_circle('z');
	Vec3D origin_with_offset = origin + horziontal_unit * aperture_offset.e1() + vertical_unit * aperture_offset.e2();  // transform into camera coordinates
	return { origin_with_offset, ll_corner + u * horizontal + v * vertical - origin_with_offset };
}