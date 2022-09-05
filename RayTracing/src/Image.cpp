#include "image.hpp"
#include <fstream>

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

const Color& Image::get_pixel(int x, int y) const
{
	return image_data[x + y * image_width];
}

