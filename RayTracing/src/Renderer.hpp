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

	void render(Image& result_image, int samples_per_pixel) const;
private:
	Color ray_color(const Ray& ray, int depth) const;
	static Color ambient_color(const Ray& ray);
	std::shared_ptr<const HittableList> world;
	std::shared_ptr<const Camera> camera;
	int max_depth;
};
