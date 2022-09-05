#pragma once
#include <vector>
#include <string>
#include "Base3D/color.hpp"

class Image
{
public:
	Image() = default;
	Image(int image_width, int image_height);

	const Color& get_pixel(int x, int y) const;
	int get_height() const;
	int get_width() const;
	void resize(int image_width, int image_height);
	void set_pixel(const Color& color, int x, int y);
	void gamma_correct(double gamma);
	void to_ppm(const std::string& filename) const;
private:
	int image_width, image_height;
	std::vector<Color> image_data;
};
