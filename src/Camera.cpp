//
// Created by alex on 12/15/22.
//

#include "Camera.h"
Camera::Camera(): Camera(2.0, 16.0 / 9.0, 1.0) {}

Camera::Camera(double viewportHeight, double aspectRatio, double focalLength) {
  auto viewportWidth = aspectRatio * viewportHeight;

  m_Origin          = point3(0, 0, 0);
  m_Horizontal      = vec3(viewportWidth, 0, 0);
  m_Vertical        = vec3(0, viewportHeight, 0);
  m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - vec3(0, 0, focalLength);
}

Ray Camera::genRay(double u, double v) const {
  return {m_Origin, m_LowerLeftCorner + u*m_Horizontal + v*m_Vertical - m_Origin};
}
