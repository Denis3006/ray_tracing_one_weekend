#pragma once
#include <fstream>

class Base3D {
public:
	Base3D();
	Base3D(double x, double y, double z);
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

	bool approx_zero() const;

protected:
	double vec[3];

	double operator[](int i) const;
	double& operator[](int i);
};

Base3D operator+(double first, const Base3D& second);
Base3D operator*(double first, const Base3D& second);