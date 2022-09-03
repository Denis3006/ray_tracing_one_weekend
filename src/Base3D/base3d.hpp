#pragma once
#include <fstream>


class Base3D {
	public:
		friend std::ostream& operator<<(std::ostream& out, const Base3D& v);

		Base3D operator-() const;
		Base3D operator-(const Base3D& other) const;
		Base3D operator-(double other) const;
		Base3D operator+(const Base3D& other) const;
		Base3D operator+(double other) const;
		Base3D operator*(double other) const;
		Base3D operator*(const Base3D& other) const;
		Base3D operator/(double other) const;

		Base3D& operator-=(const Base3D& other);
		Base3D& operator+=(const Base3D& other);
		Base3D& operator-=(double k);
		Base3D& operator+=(double k);
		Base3D& operator*=(double k);
		Base3D& operator/=(double k);
		Base3D& operator=(const Base3D& other);

		bool near_zero() const;

		static Base3D random3d(double min, double max);
		static Base3D random3d_in_unit_sphere();
		static Base3D random3d_in_unit_circle(char axis = 'z');  // generate a random 3d point in a circle around the given axis (the given coordinate will be 0)
	protected:
		Base3D() : Base3D(0, 0, 0) {};
		Base3D(double x, double y, double z);
		double vec[3];

		double operator[](int i) const;
		double& operator[](int i);
};

Base3D operator+(double first, const Base3D& second);
Base3D operator*(double first, const Base3D& second);