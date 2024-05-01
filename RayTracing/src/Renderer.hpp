#pragma once
#include <memory>

#include "Camera.hpp"
#include "Image.hpp"
#include "Hittable/hittable.hpp"


class Renderer
{
public:
	Renderer() = default;
	Renderer(std::shared_ptr<const HittableList> world, std::shared_ptr<const Camera> camera, int depth);

	void render(Image& result_image, int start_row, int end_row, unsigned int samples_per_pixel) const;
	void async_render(Image& result_image, unsigned int samples_per_pixel) const;
	int n_rays_rendered() const;
private:
	Color::Color ray_color(const Ray& ray, int depth, uint32_t& state) const;
	static Color::Color ambient_color(const Ray& ray);
	inline static int rays_rendered = 0;
	std::shared_ptr<const HittableList> world;
	std::shared_ptr<const Camera> camera;
	int max_depth;
};
