#pragma once
#include "../Hittable/hittable.hpp"
#include "../Base3D/color.hpp"
#include "../ray.hpp"


class Material
{
	public:
		Material(const Color& color) : albedo_value(color) {}
		virtual Ray scatter(const Ray& ray_in, const HitRecord& hit_record) const = 0;
		const Color& albedo() const;
	private:
		const Color albedo_value;
};


class Lambertian : public Material
{
	public:
		Lambertian(const Color& color) : Material(color) {}
		Ray scatter(const Ray& ray_in, const HitRecord& hit_record) const override;
};

class Metal : public Material
{
	public:
		Metal(const Color& color) : Metal(color, 0) {}
		Metal(const Color& color, double fuzz) : Material(color), fuzz(fuzz) {};
		Ray scatter(const Ray& ray_in, const HitRecord& hit_record) const override;
	private:
		double fuzz;
};

class Dielectric : public Material
{
public:
	Dielectric(double refraction_index) : Material({1, 1, 1}), refraction_index(refraction_index) {}
	Ray scatter(const Ray& ray_in, const HitRecord& hit_record) const override;
private:
	double refraction_index;
};