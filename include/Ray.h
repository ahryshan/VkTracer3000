//
// Created by alex on 12/14/22.
//

#ifndef VKTRACER3000_RAY_H
#define VKTRACER3000_RAY_H

#include "vec3.h"
#include "Hittable.h"

class Ray {
public:
  Ray() = default;
  Ray(const point3& origin, const vec3& direction) : orig{origin}, dir{direction} {}
  inline point3 origin() const { return orig; }
  inline vec3 direction() const { return dir; }

  point3 at(double t) const {
    return orig + t * dir;
  }

private:
  point3 orig;
  vec3   dir;
};


Color ray_color(const Ray& r, const Hittable& world) {
  HitRecord rec;
  if (world.hit(r, 0, c_INFINITY, rec)) {
    return 0.5 * (rec.normal + Color(1, 1, 1));
  }

  vec3   unit_direction = unit_vector(r.direction());
  double t              = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Color(0, 0, 0) + t * Color(0.5, 0.7, 1.0);
}

#endif //VKTRACER3000_RAY_H
