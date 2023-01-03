//
// Created by alex on 12/15/22.
//

#ifndef VKTRACER3000_HITTABLE_H
#define VKTRACER3000_HITTABLE_H

#include <memory>

#include "vec3.h"
#include "Ray.h"

class Material;

struct HitRecord {
  point3                    p;
  vec3                      normal;
  std::shared_ptr<Material> material;
  double                    t;
  bool                      frontFace;

  inline void setFaceNormal(const Ray& r, const vec3& outwardNormal) {
    frontFace = dot(r.direction(), outwardNormal) < 0;
    normal    = frontFace ? outwardNormal : -outwardNormal;
  }
};

class Hittable {
public :
  virtual bool hit(const Ray& r, double minT, double maxT, HitRecord& rec) const = 0;
};

#endif //VKTRACER3000_HITTABLE_H
