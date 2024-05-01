#pragma once
#include <glm/vec3.hpp>

#include "Utils.hpp"

class Ray {
	public:
		Ray() : Ray({ 0, 0, 0 }, { 0, 0, 0 }) {}
		Ray(const Point& origin, const glm::vec3& direction) : orig(origin), dir(direction) {}
		Point at(float t) const;
		const Point& origin() const;
		const glm::vec3& direction() const;
	private:
		Point orig;
		glm::vec3 dir;
};