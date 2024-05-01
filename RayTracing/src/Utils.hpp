#pragma once
#include <glm/vec3.hpp>
#include <fstream>


using Point = glm::vec3;

namespace Color {
    using Color = glm::vec3;
    Color gamma_correct(const Color& color, double gamma);
    Color arithmetic_to_true_color(const Color& arithmetic);
    Color true_color_to_arithmetic(const Color& true_color);

    namespace Colors {
        const Color BLACK(0, 0, 0);
        const Color WHITE(1, 1, 1);
        const Color RED(1, 0, 0);
        const Color GREEN(0, 1, 0);
        const Color BLUE(0, 0, 1);
    }
}

namespace Random
{
    float random_float(uint32_t& state, float max = 1);
    uint32_t xor_shift_32(uint32_t& state);
    glm::vec3 random3d(float max, uint32_t& state);
    glm::vec3 random3d_in_unit_sphere(uint32_t& state);
    glm::vec3 random3d_in_unit_circle(uint32_t& state, char axis = 'z');  // generate a random 3d point in a circle around the given axis (the given coordinate will be 0)
    glm::vec3 random_unit_vector(uint32_t& state);
    glm::vec3 random_in_hemisphere(const glm::vec3& normal, uint32_t& state);
}



std::ostream& operator<<(std::ostream& out, const Color::Color& v);