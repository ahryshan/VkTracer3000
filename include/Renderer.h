//
// Created by alex on 12/15/22.
//

#ifndef VKTRACER3000_RENDERER_H
#define VKTRACER3000_RENDERER_H

#include <string>
#include "Camera.h"
#include "Hittable.h"


class Renderer {
public:
  static void writeImage(const Camera& camera, const Hittable& hittable, int width, int height, int samplesPerPixel, const std::string& fileName);
};


#endif //VKTRACER3000_RENDERER_H
