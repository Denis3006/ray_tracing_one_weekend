#include "image.hpp"
#include <fstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../dependencies/stb/stb_image_write.h"

Image::Image(int image_width, int image_height) : image_width(image_width), image_height(image_height)
{
	image_data.resize(image_width * image_height);
}

int Image::get_height() const
{
	return image_height;
}

int Image::get_width() const
{
	return image_width;
}

void Image::resize(int new_width, int new_height)
{
	image_width = new_width;
	image_height = new_height;
	image_data.resize(image_width * image_height);
}

void Image::set_pixel(const Color& color, int x, int y)
{
	image_data[x + y  * image_width] = color;
}

void Image::gamma_correct(double gamma)
{
	for (auto& pixel : image_data)
		pixel = pixel.gamma_correct(gamma);
}

void Image::to_ppm(const std::string& filename) const
{
	std::ofstream file;
	file.open(filename);
	file << "P3\n" << image_width << " " << image_data.size() / image_width << std::endl << 255 << std::endl;
	int col = 0;
	for (const auto& pixel : image_data) {
		file << arithmetic_to_true_color(pixel) << '\t';
		++col;
		if (col % image_width == 0)
			file << '\n';
	}
	file.close();
}

void Image::to_png(const std::string& filename) const
{
	std::vector<unsigned char> data;
	int number_of_channels = 4;
	data.reserve(image_data.size() * number_of_channels);
	for (const auto& color : image_data) {
		Color pixel_color = arithmetic_to_true_color(color);
		data.push_back(static_cast<unsigned char>(pixel_color.r()));
		data.push_back(static_cast<unsigned char>(pixel_color.g()));
		data.push_back(static_cast<unsigned char>(pixel_color.b()));
		data.push_back(255);
	}
	stbi_write_png(filename.c_str(), image_width, image_height, number_of_channels, data.data(), number_of_channels * image_width);
}

void Image::to_jpg(const std::string& filename) const
{
	std::vector<unsigned char> data;
	int number_of_channels = 4;
	data.reserve(image_data.size() * number_of_channels);
	for (const auto& color : image_data) {
		Color pixel_color = arithmetic_to_true_color(color);
		data.push_back(static_cast<unsigned char>(pixel_color.r()));
		data.push_back(static_cast<unsigned char>(pixel_color.g()));
		data.push_back(static_cast<unsigned char>(pixel_color.b()));
		data.push_back(255);
	}
	stbi_write_jpg(filename.c_str(), image_width, image_height, number_of_channels, data.data(), number_of_channels * image_width);
}

Image Image::average_images(const std::vector<Image>& images)
{
	Image result(images[0].get_width(), images[0].get_height());
	for (const auto& image : images) {
		for (int i = 0; i < image.image_data.size(); i++) {
			result.image_data[i] += image.image_data[i] / images.size();
		}
	}
	return result;
}

const Color& Image::get_pixel(int x, int y) const
{
	return image_data[x + y * image_width];
}

