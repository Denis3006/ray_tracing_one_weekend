#include "Random.hpp"
#include <cassert>
#include <corecrt_math_defines.h>
#include <random>

namespace Random
{
	uint32_t xor_shift_32(uint32_t& state)
	{
		uint32_t x = state;
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		state = x;
		return x;
	}

	double random_double(uint32_t& state, double max)
	{
		return max * (xor_shift_32(state) & 0xFFFFFF) / 16777216.0;
	}
	
	Base3D random3d(double max, uint32_t& state)
	{
		return { random_double(state, max), random_double(state, max), random_double(state, max) };
	}


	Base3D random3d_in_unit_sphere(uint32_t& state)
	{
		double r = std::pow(random_double(state, 1), 1 / 3);
		double theta = random_double(state, 2 * M_PI);
		double v = random_double(state, 1);
		double phi = std::acos(2 * v - 1);
		return { r * std::sin(phi) * std::cos(theta), r * std::sin(phi) * std::sin(theta), r * std::cos(phi) };
	}

	Base3D random3d_in_unit_circle(uint32_t& state, char axis)
	{
		double r = std::sqrt(random_double(state, 1));
		double phi = random_double(state, 2 * M_PI);
		switch (axis) {
		case 'x':
			return { 0, r * std::cos(phi), r * std::sin(phi) };
		case 'y':
			return { r * std::cos(phi), 0, r * std::sin(phi) };
		case 'z':
			return { r * std::cos(phi), r * std::sin(phi), 0 };
		default:
			assert(true);
			return { 0, 0, 0 };
		}
	}

	Vec3D random_unit_vector(uint32_t& state)
	{
		double r = 1;
		double theta = random_double(state, 2 * M_PI);
		double v = random_double(state, 1);
		double phi = std::acos(2 * v - 1);
		return { r * std::sin(phi) * std::cos(theta), r * std::sin(phi) * std::sin(theta), r * std::cos(phi) };
	}

	Vec3D random_in_hemisphere(const Vec3D& normal, uint32_t& state)
	{
		Vec3D rand_vec = random3d_in_unit_sphere(state);
		return rand_vec.dot(normal) > 0 ? rand_vec : -rand_vec;
	}
}