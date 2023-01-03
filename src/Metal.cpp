//
// Created by alex on 1/3/23.
//

#include "Metal.h"

Metal::Metal(const Color& albedo) : m_Albedo(albedo), m_Fuzz{0} {}

Metal::Metal(const Color& albedo, float fuzz) : m_Albedo{albedo}, m_Fuzz{fuzz} {}

bool Metal::scatter(const Ray& rayInput, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const {
  vec3 reflected = reflect(unit_vector(rayInput.direction()), hitRecord.normal);
  if (m_Fuzz == 0.f)
    scattered = Ray(hitRecord.p, reflected);
  else
    scattered = Ray(hitRecord.p, reflected + m_Fuzz * random_in_unit_sphere());

  attenuation = m_Albedo;
  return (dot(scattered.direction(), hitRecord.normal) > 0);
}
