//
// Created by alex on 12/14/22.
//

#ifndef VKTRACER3000_RAY_H
#define VKTRACER3000_RAY_H

#include "vec3.h"

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

#endif //VKTRACER3000_RAY_H
