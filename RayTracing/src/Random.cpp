#include "Random.hpp"
#include <cassert>
#include <corecrt_math_defines.h>
#include <random>

namespace Random
{
	double random_double(double min, double max)
	{
		static std::uniform_real_distribution<double> distribution(min, max);
		static std::default_random_engine gen;
		return distribution(gen);
	}


	Base3D random3d(double min, double max)
	{
		return { random_double(min, max), random_double(min, max), random_double(min, max) };
	}


	Base3D random3d_in_unit_sphere()
	{
		double r = std::pow(random_double(0, 1), 1 / 3);
		double theta = random_double(0, 2 * M_PI);
		double v = random_double(0, 1);
		double phi = std::acos(2 * v - 1);
		return { r * std::sin(phi) * std::cos(theta), r * std::sin(phi) * std::sin(theta), r * std::cos(phi) };
	}

	Base3D random3d_in_unit_circle(char axis)
	{
		static std::uniform_real_distribution distribution(0.0, 1.0);
		static std::default_random_engine re;
		double r = std::sqrt(distribution(re));
		double phi = 2 * M_PI * distribution(re);
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

	Vec3D random_unit_vector()
	{
		return Vec3D(random3d_in_unit_sphere()).normalize();
	}

	Vec3D random_in_hemisphere(const Vec3D& normal)
	{
		Vec3D rand_vec = random3d_in_unit_sphere();
		return rand_vec.dot(normal) > 0 ? rand_vec : -rand_vec;
	}
}