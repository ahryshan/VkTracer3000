//
// Created by alex on 12/15/22.
//
#include "vkt3000_pch.h"

#include "Sphere.h"

Sphere::Sphere(double radius, point3 center) : m_Radius(radius), m_Center(center) {}

bool Sphere::hit(const Ray& r, double minT, double maxT, HitRecord& rec) const {
  vec3 oc     = r.origin() - m_Center;
  auto a      = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c      = oc.length_squared() - m_Radius * m_Radius;

  auto discriminant = half_b*half_b - a*c;
  if(discriminant < 0) return false;
  auto sqrtD = std::sqrt(discriminant);

  auto root = (-half_b - sqrtD) / a;
  if(root < minT || root > maxT) {
    root = (-half_b + sqrtD) / a;
    if(root < minT || root > maxT) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(root);
  vec3 normal = (rec.p - m_Center) / m_Radius;
  rec.setFaceNormal(r, normal);

  return true;
}
