#pragma once
#include <vector>
#include <string>
#include "Base3D/color.hpp"

class Image
{
public:
	Image() = default;
	Image(int image_width, int image_height);

	static Image average_images(const std::vector<Image>& images);
	const Color& get_pixel(int x, int y) const;
	int get_height() const;
	int get_width() const;
	void resize(int image_width, int image_height);
	void set_pixel(const Color& color, int x, int y);
	void gamma_correct(double gamma);
	void to_ppm(const std::string& filename) const;
	void to_png(const std::string& filename) const;
	void to_jpg(const std::string& filename) const;
private:
	int image_width, image_height;
	std::vector<Color> image_data;
	std::vector<unsigned char> prepare_output() const;
};
