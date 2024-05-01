#pragma once
#include "Utils.hpp"
#include "ray.hpp"

class Camera {
public:
	Camera() : Camera({ 0, 0, 0 }, { 0, 0, -1 }, { 0, 1, 0 }, 90, 16.0 / 9.0) {};
	Camera(const Point& look_from, const Point& look_at, const glm::vec3& vup, float vfov = 90, float aspect_ratio = 16.0 / 9.0, float aperture = 0, float focus_dist = 1);
	Ray get_ray(float u, float v, uint32_t& state) const;
private:
	float viewport_width, viewport_height, lens_radius;
	glm::vec3 horizontal, vertical, horziontal_unit, vertical_unit;
	Point origin;
	Point ll_corner;
};