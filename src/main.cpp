#include <iostream>

#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include "Renderer.h"

int main() {

  // Image
  const double aspect_ratio    = 16.0 / 9.0;
  const int    image_height    = 360;
  const int    image_width     = static_cast<int>(image_height * aspect_ratio);
  const int    samplesPerPixel = 50;

  // World
  HittableList world;
  world.add(std::make_shared<Sphere>(0.5, point3(0, 0, -1)));
  world.add(std::make_shared<Sphere>(100, point3(0, -100.5, -1)));

  // Camera
  Camera camera;

  Renderer::writeImage(camera, world, image_width, image_height, samplesPerPixel, "image.ppm");

  std::cerr << "Everything's done!";

  return 0;
}
