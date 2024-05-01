#pragma once
#include "Base3D/base3d.hpp"
#include "Base3D/Vec3d.hpp"

namespace Random
{
	double random_double(uint32_t& state, double max = 1);
	uint32_t xor_shift_32(uint32_t& state);
	Base3D random3d(double max, uint32_t& state);
	Base3D random3d_in_unit_sphere(uint32_t& state);
	Base3D random3d_in_unit_circle(uint32_t& state, char axis = 'z');  // generate a random 3d point in a circle around the given axis (the given coordinate will be 0)
	Vec3D random_unit_vector(uint32_t& state);
	Vec3D random_in_hemisphere(const Vec3D& normal, uint32_t& state);
}
