#pragma once

#include "Base3D/point.hpp"
#include "Base3D/vec3d.hpp"
#include "ray.hpp"

class Camera {
   public:
	   Camera() : Camera({ 0, 0, 0 }, { 0, 0, -1 }, { 0, 1, 0 }, 90, 16.0/9.0) {};
		Camera(const Point& look_from, const Point& look_at, const Vec3D& vup, double vfov=90, double aspect_ratio=16.0/9.0, double aperture=0, double focus_dist=1);
		Ray get_ray(double u, double v) const;
   private:
		double viewport_width, viewport_height, lens_radius;
		Vec3D horizontal, vertical, horziontal_unit, vertical_unit;
		Point origin;
		Point ll_corner;
};