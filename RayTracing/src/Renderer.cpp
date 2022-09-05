#include "Renderer.hpp"
#include "Random.hpp"
#include "Hittable/Hittable.hpp"
#include "Material/Material.hpp"

#include <future>
#include <iostream>

Renderer::Renderer(std::shared_ptr<const HittableList> world, std::shared_ptr<const Camera> camera, int depth) : world(world), camera(camera), max_depth(depth)
{}

void Renderer::render(Image& result_image, unsigned int samples_per_pixel)
{
	double u = 0, v = 0;
	for (int x = 0; x < result_image.get_width(); x++) {
		//std::cout << "Rendering column " << x << " out of " << result_image.get_width() << std::endl;
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
	std::cout << "Ready" << std::endl;
}

void Renderer::async_render(Image& result_image, unsigned int samples_per_pixel)
{
	const auto n_available_threads = std::thread::hardware_concurrency();
	auto n_threads = std::min(n_available_threads, samples_per_pixel);
	while (samples_per_pixel % n_threads != 0) {
		--n_threads;
	}
	std::cout << "Using " << n_threads << " threads" << std::endl;
	unsigned int samples_per_thread = samples_per_pixel / n_threads;

	std::vector<Image> result_images;
	std::vector<std::future<void>> result_futures;
	result_futures.reserve(n_threads);
	result_images.reserve(n_threads);
	for (unsigned int thread = 0; thread < n_threads; thread++) {
		result_images.emplace_back(Image{result_image.get_width(), result_image.get_height()});
		result_futures.push_back(std::async(&Renderer::render, *this, std::ref(result_images.back()), samples_per_thread));
	}
	for (auto& future : result_futures)
		future.get();
	result_image = Image::average_images(result_images);
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

void Renderer::test(unsigned int samples_per_pixel)
{
	auto x = 1;
}

