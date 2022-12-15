//
// Created by alex on 12/15/22.
//

#ifndef VKTRACER3000_CAMERA_H
#define VKTRACER3000_CAMERA_H

#include "Ray.h"

class Camera {
public:
  Camera();
  Camera(double viewportHeight, double aspectRatio, double focalLength = 1.0);

  Ray genRay(double u, double v) const;

private:
  point3 m_Origin;
  point3 m_LowerLeftCorner;
  vec3 m_Horizontal;
  vec3 m_Vertical;
};


#endif //VKTRACER3000_CAMERA_H
