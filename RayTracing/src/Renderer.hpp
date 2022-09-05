#pragma once
#include "Camera.hpp"
#include "Image.hpp"
#include "Hittable/hittable.hpp"
#include <memory>


class Renderer
{
public:
	Renderer() = default;
	Renderer(std::shared_ptr<const HittableList> world, std::shared_ptr<const Camera> camera, int depth);

	void render(Image& result_image, unsigned int samples_per_pixel);
	void async_render(Image& result_image, unsigned int samples_per_pixel);
private:
	Color ray_color(const Ray& ray, int depth) const;
	static Color ambient_color(const Ray& ray);
	std::shared_ptr<const HittableList> world;
	std::shared_ptr<const Camera> camera;
	void test(unsigned int samples_per_pixel);
	int max_depth;
};
