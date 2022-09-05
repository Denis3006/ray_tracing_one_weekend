#pragma once
#include "Base3D/base3d.hpp"
#include "Base3D/Vec3d.hpp"

namespace Random
{
	double random_double(double min = 0, double max = 1);

	Base3D random3d(double min, double max);
	Base3D random3d_in_unit_sphere();
	Base3D random3d_in_unit_circle(char axis = 'z');  // generate a random 3d point in a circle around the given axis (the given coordinate will be 0)
	Vec3D random_unit_vector();
	Vec3D random_in_hemisphere(const Vec3D& normal);
}
