#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include "vec3d.hpp"

Base3D::Base3D(double x, double y, double z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

double Base3D::operator[](int i) const
{
	return vec[i];
}

double& Base3D::operator[](int i)
{
	return vec[i];
}

Base3D& Base3D::operator+=(const Base3D& other)
{
	vec[0] += other[0];
	vec[1] += other[1];
	vec[2] += other[2];
	return *this;
}

Base3D& Base3D::operator-=(const Base3D& other)
{
	vec[0] -= other[0];
	vec[1] -= other[1];
	vec[2] -= other[2];
	return *this;
}

Base3D& Base3D::operator+=(double k)
{
	vec[0] += k;
	vec[1] += k;
	vec[2] += k;
	return *this;
}


Base3D& Base3D::operator-=(double k)
{
	vec[0] -= k;
	vec[1] -= k;
	vec[2] -= k;
	return *this;
}

Base3D& Base3D::operator/=(double k)
{
	vec[0] /= k;
	vec[1] /= k;
	vec[2] /= k;
	return *this;
}

Base3D& Base3D::operator=(const Base3D& other)
{
	vec[0] = other[0];
	vec[1] = other[1];
	vec[2] = other[2];
	return *this;
}

bool Base3D::near_zero() const
{
	const double EPSILON = 1e-8;
	return length_of(*this) < EPSILON;
}

Base3D& Base3D::operator*=(double k)
{
	vec[0] *= k;
	vec[1] *= k;
	vec[2] *= k;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Base3D& v)
{
	out << v[0] << ' ' << v[1] << ' ' << v[2];
	return out;
}


Base3D Base3D::operator-() const
{
	return *this * -1;
}

Base3D Base3D::operator-(const Base3D& other) const
{
	return {vec[0] - other[0], vec[1] - other[1], vec[2] - other[2]};
}

Base3D Base3D::operator-(const double other) const
{
	return {vec[0] - other, vec[1] - other, vec[2] - other};
}

Base3D Base3D::operator+(const Base3D& other) const
{
	return {vec[0] + other[0], vec[1] + other[1], vec[2] + other[2]};
}

Base3D Base3D::operator+(double other) const
{
	return {vec[0] + other, vec[1] + other, vec[2] + other};
}

Base3D Base3D::operator/(double other) const
{
	return {vec[0] / other, vec[1] / other, vec[2] / other};
}

Base3D Base3D::operator*(double other) const
{
	return {vec[0] * other, vec[1] * other, vec[2] * other};
}

Base3D Base3D::operator*(const Base3D& other) const
{
	return { vec[0] * other[0], vec[1] * other[1], vec[2] * other[2] };
}

Base3D operator+(double first, const Base3D& second)
{
	return second + first;
}

Base3D operator*(double first, const Base3D& second)
{
	return second * first;
}

Base3D Base3D::random3d(double min, double max)
{
	static std::uniform_real_distribution distribution(min, max);
	static std::default_random_engine re;
	return { distribution(re), distribution(re), distribution(re) };
}

Base3D Base3D::random3d_in_unit_sphere()
{
	static std::uniform_real_distribution distribution(0.0, 1.0);
	static std::default_random_engine re;
	double r = std::pow(distribution(re), 1/3);
	double theta = 2 * M_PI * distribution(re);
	double v = distribution(re);
	double phi = std::acos(2 * v - 1);
	return { r * sin(phi) * cos(theta), r * sin(phi) * sin(theta), r * cos(phi) };
}

Base3D Base3D::random3d_in_unit_circle(char axis)
{
	static std::uniform_real_distribution distribution(0.0, 1.0);
	static std::default_random_engine re;
	double r = std::sqrt(distribution(re));
	double phi = 2 * M_PI * distribution(re);
	switch (axis)
	{
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
