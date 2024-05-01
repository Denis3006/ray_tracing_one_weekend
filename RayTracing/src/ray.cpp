#include "ray.hpp"

Point Ray::at(float t) const
{
	return orig + (t * dir);
}

const Point& Ray::origin() const
{
	return orig;
}

const glm::vec3& Ray::direction() const
{
	return dir;
}