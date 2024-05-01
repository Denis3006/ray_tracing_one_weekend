#pragma once
#include "../Hittable/hittable.hpp"
#include "../Base3D/color.hpp"
#include "../ray.hpp"


class Material
{
	public:
		Material(const Color::Color& color) : albedo_value(color) {}
		virtual Ray scatter(const Ray& ray_in, const HitRecord& hit_record, uint32_t& state) const = 0;
		const Color::Color& albedo() const;
	private:
		const Color::Color albedo_value;
};


class Lambertian : public Material
{
	public:
		Lambertian(const Color::Color& color) : Material(color) {}
		Ray scatter(const Ray& ray_in, const HitRecord& hit_record, uint32_t& state) const override;
};

class Metal : public Material
{
	public:
		Metal(const Color::Color& color) : Metal(color, 0) {}
		Metal(const Color::Color& color, double fuzz) : Material(color), fuzz(fuzz) {};
		Ray scatter(const Ray& ray_in, const HitRecord& hit_record, uint32_t& state) const override;
	private:
		float fuzz;
};

class Dielectric : public Material
{
	public:
		Dielectric(const Color::Color& color, double refraction_index) : Material(color), refraction_index(refraction_index) {}
		Dielectric(double refraction_index) : Material({1, 1, 1}), refraction_index(refraction_index) {}
		Ray scatter(const Ray& ray_in, const HitRecord& hit_record, uint32_t& state) const override;
	private:
		float refraction_index;
};