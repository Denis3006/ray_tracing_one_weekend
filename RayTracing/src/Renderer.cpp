#include "Renderer.hpp"

#include <future>
#include <iostream>

#include "Utils.hpp"
#include "Hittable/Hittable.hpp"
#include "Material/Material.hpp"


Renderer::Renderer(std::shared_ptr<const HittableList> world, std::shared_ptr<const Camera> camera, int depth) : world(std::move(world)), camera(std::move(camera)), max_depth(depth)
{}

void Renderer::render(Image& result_image, int start_row, int end_row, unsigned int samples_per_pixel) const
{
	float u = 0, v = 0;
	for (int y = start_row; y < end_row; y++) {
		uint32_t state = (y * 9781 + result_image.get_width() * 6271) | 1;
		//std::cout << "Rendering column " << x << " out of " << result_image.get_width() << std::endl;
		for (int x = 0; x < result_image.get_width(); x++) {
			Color::Color pixel_color(0);
			for (int s = 0; s < samples_per_pixel; s++) {
				u = (x + Random::random_float(state)) / result_image.get_width();
				v = (result_image.get_height() - y - 1 + Random::random_float(state)) / result_image.get_height();
				Ray ray = camera->get_ray(u, v, state);
				pixel_color += ray_color(ray, max_depth, state);
			}
			result_image.set_pixel(pixel_color / float(samples_per_pixel), x, y);
		}
	}
	std::cout << "Ready" << std::endl;
}


void Renderer::async_render(Image& result_image, unsigned int samples_per_pixel) const
{
	const auto n_available_threads = std::thread::hardware_concurrency();
	auto n_threads = n_available_threads;

	std::cout << "Using " << n_threads << " threads" << std::endl;
	std::vector<std::future<void>> result_futures;
	result_futures.reserve(n_threads);
	int row_step = result_image.get_height() / n_threads;
	for (unsigned int thread = 0; thread < n_threads; thread++) {
		int start_row = row_step * thread;
		int end_row = std::min(int(start_row + row_step), result_image.get_height());
		result_futures.push_back(std::async(&Renderer::render, *this, std::ref(result_image), start_row, end_row, samples_per_pixel));
	}

	for (auto& future : result_futures)
		future.get();
}

int Renderer::n_rays_rendered() const
{
	return rays_rendered;
}

Color::Color Renderer::ray_color(const Ray& ray, int depth, uint32_t& state) const
{
	const float EPSILON = 1e-4f;
	if (depth <= 0)
		return Color::Colors::BLACK; // no more light is gathered, ray bounce limit exceeded
	++rays_rendered;
	if (const auto record = world->hit(ray, EPSILON, INFINITY); record) { // ray hit something
		Ray reflected_ray = record.value().material->scatter(ray, record.value(), state);
		if (glm::length(reflected_ray.direction()) < EPSILON) {
			return Color::Colors::BLACK;
		}
		return record.value().material->albedo() * ray_color(reflected_ray, --depth, state);
	}
	return ambient_color(ray);  // ray didn't hit anything
}

Color::Color Renderer::ambient_color(const Ray& ray)
{
	float y_component = ray.direction().y / glm::length(ray.direction());
	float t = (1 + y_component) / 2;
	Color::Color start_color = Color::Colors::WHITE;
	Color::Color end_color(0.5, 0.7, 1.0);
	return (1 - t) * start_color + t * end_color;
}