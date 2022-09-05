#include "Renderer.hpp"
#include "Random.hpp"
#include "Hittable/Hittable.hpp"
#include "Material/Material.hpp"

#include <iostream>

Renderer::Renderer(std::shared_ptr<const HittableList> world, std::shared_ptr<const Camera> camera, int depth) : world(world), camera(camera), max_depth(depth)
{}

void Renderer::render(Image& result_image, int samples_per_pixel) const
{
	double u = 0, v = 0;
	for (int x = 0; x < result_image.get_width(); x++) {
		std::cout << "Rendering column " << x << " out of " << result_image.get_width() << std::endl;
		for (int y = 0; y < result_image.get_height(); y++) {
			Color pixel_color;
			for (int s = 0; s < samples_per_pixel; s++) {
				u = (x + Random::random_double()) / result_image.get_width();
				v = (result_image.get_height() - y - 1 + Random::random_double()) / result_image.get_height();
				Ray ray = camera->get_ray(u, v);
				pixel_color += ray_color(ray, max_depth);
			}
			result_image.set_pixel(pixel_color / samples_per_pixel, x, y);
		}
	}
	std::cout << "Ready";
}

Color Renderer::ray_color(const Ray& ray, int depth) const
{
	const double EPSILON = 0.0001;
	if (depth <= 0)
		return Colors::BLACK; // no more light is gathered, ray bounce limit exceeded
	if (const auto record = world->hit(ray, EPSILON, INFINITY); record) { // ray hit something
		Ray reflected_ray = record.value().material->scatter(ray, record.value());
		if (reflected_ray.direction().length() < EPSILON) {
			return Colors::BLACK;
		}
		return record.value().material->albedo() * ray_color(reflected_ray, --depth);
	}
	return ambient_color(ray);  // ray didn't hit anything
}

Color Renderer::ambient_color(const Ray& ray)
{
	double y_component = ray.direction().normalize().e2();
	double t = (1 + y_component) / 2;
	Color start_color = Colors::WHITE;
	Color end_color(0.5, 0.7, 1.0);
	return (1 - t) * start_color + t * end_color;
}

