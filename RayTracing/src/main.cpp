#include <fstream>
#include <cmath>
#include <memory>

#include "Base3D/vec3d.hpp"
#include "Base3D/color.hpp"
#include "Hittable/hittable.hpp"
#include "Hittable/sphere.hpp"
#include "Material/Material.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "Random.hpp"
#include "Renderer.hpp"

using namespace std;

HittableList random_scene()
{
	HittableList world;

	auto material_ground = make_shared<Lambertian>(Color{ 0.5, 0.5, 0.5 });
	auto material_center = make_shared<Dielectric>(1.5);
	auto material_left = make_shared<Lambertian>(Color{ 0.4, 0.2, 0.1 });
	auto material_right = make_shared<Metal>(Color{ 0.7, 0.6, 0.5 }, 0);

	world.add(make_shared<Sphere>(Point{0, -1000, 0}, 1000, material_ground));
	world.add(make_shared<Sphere>(Point{ -4, 1, 0 }, 1, material_left));
	world.add(make_shared<Sphere>(Point{ 0, 1, 0 }, 1, material_center));
	world.add(make_shared<Sphere>(Point{ 4, 1, 0 }, 1, material_right));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto rand_mat = Random::random_double();
			//auto rand_radius = random_double(0.1, 0.9);
			auto rand_radius = 0.2;
			Point rand_center(a + 0.9 * Random::random_double(), 0.2, b + 0.9 * Random::random_double());

			if (Vec3D(rand_center - Point(4, 0.2, 0)).length() > 0.9) {
				if (rand_mat < 0.75) {
					// matte material
					Color albedo(Random::random3d(0, 1));
					auto mat = make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(rand_center, rand_radius, mat));
				}
				else if (rand_mat < 0.9) {
					// metal
					Color albedo(Random::random3d(0.5, 1));
					double fuzz(Random::random_double(0, 0.5));
					auto mat = make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(rand_center, rand_radius, mat));
				}
				else {
					// glass
					double refraction_index = Random::random_double(1.3, 2.5);
					auto mat = make_shared<Dielectric>(refraction_index);
					world.add(std::make_shared<Sphere>(rand_center, rand_radius, mat));
				}
			}
		}
	}

	return world;
}

int main(int argc, const char* argv[])
{
	// Image
	const double aspect_ratio = 16.0 / 9.0;
	const double image_height = 400;
	const double image_width = round(image_height * aspect_ratio);
	const int samples_per_pixel = 16;
	const int depth = 8;
	double gamma = 2;

	Point look_from(13, 2, 3);
	Point look_at(0, 0, 0);
	double dist_to_focus = 10;
	double aperture = dist_to_focus / 100;
	double vfov = 20;
	Vec3D vup{0, 1, 0};

	Camera cam(look_from, look_at, vup, vfov, aspect_ratio, aperture, dist_to_focus);
	HittableList world = random_scene();
	Image result_image(image_width, image_height);
	Renderer renderer(std::make_shared<const HittableList>(world), std::make_shared<const Camera>(cam), depth);

	renderer.render(result_image, samples_per_pixel);
	result_image.gamma_correct(gamma);
	result_image.to_ppm("./ray_tracing.ppm");
}
