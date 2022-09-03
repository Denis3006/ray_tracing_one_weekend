#include "point.hpp"
#include "vec3d.hpp"

double Point::x() const
{
	return vec[0];
}

double Point::y() const
{
	return vec[1];
}

double Point::z() const
{
	return vec[2];
}

void Point::set_x(double x)
{
	vec[0] = x;
}

void Point::set_y(double y)
{
	vec[1] = y;
}

void Point::set_z(double z)
{
	vec[2] = z;
}

double Point::distance_to(const Point& other) const
{
	return length_of(*this - other);
}

double distance(const Point& first, const Point& second)
{
	return first.distance_to(second);
}