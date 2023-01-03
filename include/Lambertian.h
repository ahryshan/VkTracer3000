//
// Created by alex on 1/3/23.
//

#ifndef VKTRACER3000_LAMBERTIAN_H
#define VKTRACER3000_LAMBERTIAN_H

#include "Material.h"
#include "vec3.h"
#include "Hittable.h"

class Lambertian : public Material {
public:
  explicit Lambertian(const Color& albedo);
  virtual bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;

private:
  Color m_Albedo;
};


#endif //VKTRACER3000_LAMBERTIAN_H
