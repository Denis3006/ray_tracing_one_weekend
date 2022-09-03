#include "ray.hpp"

Point Ray::at(double t) const
{
   return orig + (t * dir);
}

const Point& Ray::origin() const
{
   return orig;
}

const Vec3D& Ray::direction() const
{
   return dir;
}