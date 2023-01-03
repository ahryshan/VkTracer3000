//
// Created by alex on 1/3/23.
//

#include "Dielectric.h"

Dielectric::Dielectric(float refractionCoefficient) : m_RefractionCoeff{refractionCoefficient}, m_Albedo(1.f, 1.f, 1.f) {}

Dielectric::Dielectric(float refractionCoefficient, Color albedo) : m_RefractionCoeff{refractionCoefficient}, m_Albedo{albedo} {}

bool Dielectric::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const {
  attenuation = Color{1.f, 1.f, 1.f};
  float refractionRatio = hitRecord.frontFace ? 1.f / m_RefractionCoeff : m_RefractionCoeff;

  vec3 unitDirection = unit_vector(rayInput.direction());

  float cosTheta = std::fmin(dot(-unitDirection, hitRecord.normal), 1.f);
  float sinTheta = std::sqrt(1.f - cosTheta * cosTheta);

  vec3 direction;

  if (refractionRatio * sinTheta > 1.f || reflectance(cosTheta, refractionRatio) > randomDouble())
    direction = reflect(unitDirection, hitRecord.normal);
  else
    direction = refract(unitDirection, hitRecord.normal, refractionRatio);

  scattered   = Ray(hitRecord.p, direction);
  attenuation = m_Albedo;
  return true;
}

float Dielectric::reflectance(float cos, float refractionRatio) {
  float r0 = (1.f - refractionRatio) / (1.f + refractionRatio);
  r0 *= r0;
  return r0 + (1.f - r0) * std::pow((1.f - cos), 5);
}
