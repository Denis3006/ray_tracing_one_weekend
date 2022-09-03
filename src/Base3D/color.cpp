#include "color.hpp"
#include <cmath>

Color::Color(): Color(0, 0, 0)
{}

Color::Color(double x, double y, double z): Base3D(x, y, z)
{}

Color::Color(const Base3D& other) : Base3D(other)
{
	vec[0] = std::abs(vec[0]);
	vec[1] = std::abs(vec[1]);
	vec[2] = std::abs(vec[2]);
}

double Color::r() const
{
	return vec[0];
}

double Color::g() const
{
	return vec[1];
}

double Color::b() const
{
	return vec[2];
}

void Color::set_r(double r)
{
	vec[0] = r;
}

void Color::set_g(double g)
{
	vec[1] = g;
}

void Color::set_b(double b)
{
	vec[2] = b;
}

Color Color::gamma_correct(double gamma) const
{
	double gamma_power = 1 / gamma;
	return { std::pow(r(), gamma_power), std::pow(g(), gamma_power), std::pow(b(), gamma_power)};
}

Color arithmetic_to_true_color(const Base3D& arithmetic)
{
	return arithmetic * 255;
}

Color true_color_to_arithmetic(const Base3D& true_color)
{
	return true_color / 255;
}
