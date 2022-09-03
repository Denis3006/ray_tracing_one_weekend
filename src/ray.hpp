#pragma once
#include "Base3D/point.hpp"
#include "Base3D/vec3d.hpp"

class Ray {
	public:
		Ray() = default;
		Ray(const Point& origin, const Vec3D& direction) : orig(origin), dir(direction) {}
		Point at(double t) const;
		const Point& origin() const;
		const Vec3D& direction() const;
	private:
		Point orig;
		Vec3D dir;
};