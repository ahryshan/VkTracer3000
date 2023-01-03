//
// Created by alex on 12/14/22.
//

#ifndef VKTRACER3000_VEC3_H
#define VKTRACER3000_VEC3_H

#include <cmath>
#include <ostream>

#include "utils.h"

class vec3 {
public:
  inline static vec3 random() {
    return vec3(randomDouble(), randomDouble(), randomDouble());
  }

  inline static vec3 random(double min, double max) {
    return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
  }

  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double& operator[](int i) { return e[i]; }

  vec3& operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3& operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3& operator/=(const double t) {
    return *this *= 1 / t;
  }

  double length() const {
    return sqrt(length_squared());
  }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

public:
  double e[3];
};

using point3 = vec3;
using Color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
  return {u[0] + v[0], u[1] + v[1], u[2] + v[2]};
}

inline vec3 operator-(const vec3& u, const vec3& v) {
  return {u[0] - v[0], u[1] - v[1], u[2] - v[2]};
}

inline vec3 operator*(const vec3& u, const vec3& v) {
  return {u[0] * v[0], u[1] * v[1], u[2] * v[2]};
}

inline vec3 operator*(double t, const vec3& v) {
  return {t * v[0], t * v[1], t * v[2]};
}

inline vec3 operator*(const vec3& v, double t) {
  return t * v;
}

inline vec3 operator/(vec3 v, double t) {
  return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
  return u[0] * v[0]
         + u[1] * v[1]
         + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
  return vec3(
      u[1] * v[2] - u[2] * v[1],
      u[2] * v[0] - u[0] * v[2],
      u[0] * v[1] - u[1] * v[0]
  );
}

inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}

inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random();
    if (p.length_squared() >= 1) continue;
    return p;
  }
}

inline vec3 random_in_hemisphere(const vec3& normal) {
  vec3 inUnitSphere = random_in_unit_sphere();
  if (dot(random_in_unit_sphere(), normal) > 0.0)
    return inUnitSphere;
  else
    return -inUnitSphere;
}

inline bool nearZeroVector(vec3 vector) {
  const auto threshold = 1e-8;
  for (int   i{0}; i < 3; i++) {
    if (std::fabs(vector[i]) > threshold)
      return false;
  }
  return true;
}

inline vec3 reflect(const vec3& v, const vec3& normal) {
  return v - 2 * dot(v, normal) * normal;
}

inline vec3 refract(const vec3& uv, const vec3& normal, float refractionRatio) {
  float cosTheta         = std::fmin(dot(-uv, normal), 1.f);
  vec3  outPerpendicular = refractionRatio * (uv + cosTheta * normal);
  vec3  outParallel      = -std::sqrt(std::fabs(1.f - outPerpendicular.length_squared())) * normal;
  return outParallel + outPerpendicular;
}

#endif //VKTRACER3000_VEC3_H
