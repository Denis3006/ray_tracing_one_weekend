#include "vec3d.hpp"
#include <cassert>


double Vec3D::distance_to(const Vec3D& other) const
{
	return length_of(Vec3D(*this - other));
}

double Vec3D::length() const
{
	return std::sqrt(length_squared());
}

double Vec3D::dot(const Vec3D& other) const
{
	return vec[0] * other[0] + vec[1] * other[1] + vec[2] * other[2];
}

Vec3D Vec3D::cross(const Vec3D& other) const
{
	Vec3D result;
	result[0] = vec[1] * other[2] - vec[2] * other[1];
	result[1] = vec[2] * other[0] - vec[0] * other[2];
	result[2] = vec[0] * other[1] - vec[1] * other[0];
	return result;
}

Vec3D Vec3D::normalize() const
{
	if (length() == 0)
		return *this;
	return (*this) / (length());
}

bool Vec3D::is_unit() const
{
	return length() - 1.0 < std::numeric_limits<double>::epsilon();
}

double Vec3D::length_squared() const
{
	return (*this).dot(*this);
}

Vec3D Vec3D::reflect(const Vec3D& n) const
{
	return *this - 2 * this->dot(n) * n;
}

Vec3D Vec3D::refract(const Vec3D& n, double refraction_index) const
{
	auto v_norm = normalize();
	auto n_norm = n.normalize();
	double cos_theta = -v_norm.dot(n_norm);
	Vec3D r_rerp = refraction_index * (v_norm + cos_theta * n_norm);
	Vec3D r_parallel = -std::sqrt(std::abs(1 - r_rerp.length_squared())) * n_norm;
	return r_rerp + r_parallel;
}

double Vec3D::e1() const
{
	return vec[0];
}

double Vec3D::e2() const
{
	return vec[1];
}

double Vec3D::e3() const
{
	return vec[2];
}

void Vec3D::set_e1(double e1)
{
	vec[0] = e1;
}

void Vec3D::set_e2(double e2)
{
	vec[1] = e2;
}

void Vec3D::set_e3(double e3)
{
	vec[2] = e3;
}

double length_of(const Vec3D& vec)
{
	return vec.length();
}

double dot(const Vec3D& first, const Vec3D& second) {
	return first.dot(second);
}

Vec3D cross(const Vec3D& first, const Vec3D& second) {
	return first.cross(second);
}


Vec3D random_unit_vector()
{
	return Vec3D(Base3D::random3d_in_unit_sphere()).normalize();
}

Vec3D random_in_hemisphere(const Vec3D& normal)
{
	Vec3D rand_vec = Base3D::random3d_in_unit_sphere();
	return rand_vec.dot(normal) > 0 ? rand_vec : -rand_vec;
}

Vec3D reflect(const Vec3D& v, const Vec3D& n)
{
	return v - 2 * v.dot(n) * n;
}

Vec3D refract(const Vec3D& v, const Vec3D& n, double refraction_index)
{
	return v.refract(n, refraction_index);
}