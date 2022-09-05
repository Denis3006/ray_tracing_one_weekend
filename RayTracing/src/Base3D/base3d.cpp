#include "vec3d.hpp"

Base3D::Base3D(): Base3D(0, 0, 0)
{
}

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
