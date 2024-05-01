#include "Utils.hpp"
#include <cassert>
#include <corecrt_math_defines.h>
#include <random>
#include <cmath>

#include <glm/geometric.hpp>
#include <glm/exponential.hpp>

namespace Color {
	Color gamma_correct(const Color& color, double gamma)
	{
		glm::vec3 gamma_power(1 / gamma);
		return glm::pow(color, gamma_power);
	}

	Color arithmetic_to_true_color(const Color& arithmetic)
	{
		return arithmetic * 255.0f;
	}

	Color true_color_to_arithmetic(const Color& true_color)
	{
		return true_color / 255.0f;
	}
}

std::ostream& operator<<(std::ostream& out, const Color::Color& v)
{
	out << v[0] << ' ' << v[1] << ' ' << v[2];
	return out;
}

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

	float random_float(uint32_t& state, float max)
	{
		return max * (xor_shift_32(state) & 0xFFFFFF) / 16777216.0f;
	}

	glm::vec3 random3d(float max, uint32_t& state)
	{
		return { random_float(state, max), random_float(state, max), random_float(state, max) };
	}


	glm::vec3 random3d_in_unit_sphere(uint32_t& state)
	{
		float r = std::pow(random_float(state, 1), 1 / 3);
		float theta = random_float(state, 2 * M_PI);
		float v = random_float(state, 1);
		float phi = std::acos(2 * v - 1);
		return { r * std::sin(phi) * std::cos(theta), r * std::sin(phi) * std::sin(theta), r * std::cos(phi) };
	}

	glm::vec3 random3d_in_unit_circle(uint32_t& state, char axis)
	{
		float r = std::sqrt(random_float(state, 1));
		float phi = random_float(state, 2 * M_PI);
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

	glm::vec3 random_unit_vector(uint32_t& state)
	{
		float r = 1;
		float theta = random_float(state, 2 * M_PI);
		float v = random_float(state, 1);
		float phi = std::acos(2 * v - 1);
		return { r * std::sin(phi) * std::cos(theta), r * std::sin(phi) * std::sin(theta), r * std::cos(phi) };
	}

	glm::vec3 random_in_hemisphere(const glm::vec3& normal, uint32_t& state)
	{
		glm::vec3 rand_vec = random3d_in_unit_sphere(state);
		return glm::dot(rand_vec, normal) > 0 ? rand_vec : -rand_vec;
	}
}