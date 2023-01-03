//
// Created by alex on 1/3/23.
//

#ifndef VKTRACER3000_MATERIAL_H
#define VKTRACER3000_MATERIAL_H

#include "Ray.h"
#include "vec3.h"
#include "Hittable.h"

class Material {
public:
  virtual bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const = 0;
};


#endif //VKTRACER3000_MATERIAL_H
