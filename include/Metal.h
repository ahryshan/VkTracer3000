//
// Created by alex on 1/3/23.
//

#ifndef VKTRACER3000_METAL_H
#define VKTRACER3000_METAL_H

#include "Material.h"
#include "vec3.h"

class Metal : public Material {
public:
  explicit Metal(const Color& albedo);
  Metal(const Color& albedo, float fuzz);
  virtual bool scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;

private:
  Color m_Albedo;
  float m_Fuzz;
};


#endif //VKTRACER3000_METAL_H
