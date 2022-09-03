#include <iostream>
#include <fstream>
#include <cmath>
#include <corecrt_math_defines.h>
#include <memory>
#include <random>

#include "Base3D/vec3d.hpp"
#include "Base3D/color.hpp"
#include "Hittable/hittable.hpp"
#include "Hittable/sphere.hpp"
#include "Material/Material.hpp"
#include "ray.hpp"
#include "camera.hpp"

using namespace std;

double random_double(double min=0, double max=1)
{
	static std::uniform_real_distribution<double> distribution(0, 1);
	static std::default_random_engine gen;
	return distribution(gen);
}

Color ray_color(const Ray& ray, const HittableList& obj_list, int depth)
{
	const double EPSILON = 0.0001;
	if (depth <= 0)
		return Colors::BLACK; // no more light is gathered, ray bounce limit exceeded
	if (const auto record = obj_list.hit(ray, EPSILON, INFINITY); record) {
		Ray reflected_ray = record.value().material->scatter(ray, record.value());
		if (reflected_ray.direction().length() < EPSILON) {
			return Colors::BLACK;
		}
		return record.value().material->albedo() * ray_color(reflected_ray, obj_list, --depth);
	}
	double y_component = ray.direction().normalize().e2();
	double t = (1 + y_component) / 2;
	Color start_color = Colors::WHITE;
	Color end_color = arithmetic_to_true_color(Color(0.5, 0.7, 1.0));
	return (1 - t) * start_color + t * end_color;
}

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
			auto rand_mat = random_double();
			//auto rand_radius = random_double(0.1, 0.9);
			auto rand_radius = 0.2;
			Point rand_center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if (Vec3D(rand_center - Point(4, 0.2, 0)).length() > 0.9) {
				if (rand_mat < 0.75) {
					// matte material
					auto albedo(Color::random3d(0, 1));
					auto mat = make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(rand_center, rand_radius, mat));
				}
				else if (rand_mat < 0.9) {
					// metal
					auto albedo(Color::random3d(0.5, 1));
					double fuzz(random_double(0, 0.5));
					auto mat = make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(rand_center, rand_radius, mat));
				}
				else {
					// glass
					double refraction_index = random_double(1.3, 2.5);
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
	const double image_height = 1080;
	const double image_width = round(image_height * aspect_ratio);
	const int samples_per_pixel = 64;
	const int depth = 8;
	double gamma = 2;

	Point look_from(13, 2, 3);
	Point look_at(0, 0, 0);
	double dist_to_focus = 10;
	double aperture = dist_to_focus / 100;
	double vfov = 20;
	Vec3D vup{0, 1, 0};


	Camera cam(look_from, look_at, vup, vfov, aspect_ratio, aperture, dist_to_focus);

	// World
	auto material_ground = Lambertian({0.8, 0.8, 0});
	auto material_center = Lambertian({0.1, 0.2, 0.5});
	//auto material_left = Metal({ 0.8, 0.8, 0.8 }, 0.3);
	//auto material_center = Lambertian({ 0.1, 0.2, 0.5 });
	auto material_left = Dielectric(1.5);
	auto material_right = Metal({0.8, 0.6, 0.2}, 0.0);

	HittableList world = random_scene();
	//world.add(std::make_shared<Sphere>(Point(0, -100.5, -1), 100, material_ground));
	//world.add(std::make_shared<Sphere>(Point(0.0, 0.0, -1), 0.5, material_center));
	//world.add(std::make_shared<Sphere>(Point(-1, 0, -1), 0.5, material_left));
	//world.add(std::make_shared<Sphere>(Point(-1, 0, -1), -0.45, material_left));
	//world.add(std::make_shared<Sphere>(Point(1, 0, -1), 0.5, material_right));

	// Render
	ofstream file;
	file.open("./ray_tracing.ppm");
	file << "P3\n" << image_width << " " << image_height << endl << 255 << endl;

	double u = 0, v = 0;
	for (int i = image_height - 1; i >= 0; i--) {
		cout << "Scanlines remaining: " << i << endl;
		for (int j = 0; j < image_width; j++) {
			Color pixel;
			for (int s = 0; s < samples_per_pixel; s++) {
				u = (j + random_double()) / image_width;
				v = (i + random_double()) / image_height;
				Ray ray = cam.get_ray(u, v);
				pixel += ray_color(ray, world, depth);
			}
			Color gamma_corrected_pixel = true_color_to_arithmetic(pixel / samples_per_pixel).gamma_correct(gamma);
			file << arithmetic_to_true_color(gamma_corrected_pixel) << '\t';
		}
		file << endl;
	}
	file.close();
	cout << "Ready";
}
