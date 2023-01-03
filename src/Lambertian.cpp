//
// Created by alex on 1/3/23.
//

#include "Lambertian.h"

Lambertian::Lambertian(const Color& albedo) : m_Albedo{albedo} {}

bool Lambertian::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const {
  vec3 scatterDirection = hitRecord.normal + random_in_hemisphere(hitRecord.normal);

  if (nearZeroVector(scatterDirection))
    scatterDirection = hitRecord.normal;

  scattered   = Ray(hitRecord.p, scatterDirection);
  attenuation = m_Albedo;
  return true;
}
