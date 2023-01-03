//
// Created by alex on 12/15/22.
//

#include "Camera.h"

Camera::Camera(): Camera(point3{0.f, 0.f, 0.f}, point3{0.f, 0.f, -1.f}, vec3{0.f, 1.f, 0.f}, 120.f, 16.f / 9.f) {}

Camera::Camera(point3 lookFrom, point3 lookAt, vec3 upVector, float fov, float aspectRatio, float focalLength) {
  float theta = radians(fov);
  float h = std::tan(theta / 2);
  float viewportHeight = 2.0f * h;
  float viewportWidth = aspectRatio * viewportHeight;

  vec3 w = unit_vector(lookFrom - lookAt);
  vec3 u = unit_vector(cross(upVector, w));
  vec3 v = cross(w, u);

  m_Origin = lookFrom;
  m_Horizontal = viewportWidth * u;
  m_Vertical = viewportHeight * v;
  m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - w;
}


Ray Camera::genRay(double u, double v) const {
  return {m_Origin, m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin};
}
