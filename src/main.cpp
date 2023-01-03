#include <iostream>

#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include "Renderer.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

int main() {

  // Image
  const double aspect_ratio
                               = 16.0 / 9.0;
  const int    image_height    = 480;
  const int    image_width     = static_cast<int>(image_height * aspect_ratio);
  const int    samplesPerPixel = 25;

  // World
  HittableList world;

  auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto materialRight  = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
  auto materialCenterBack  = std::make_shared<Lambertian>(Color(0.3, 0.3, 0.7));
  auto materialCenter = std::make_shared<Dielectric>(1.5f);
  auto materialLeft   = std::make_shared<Dielectric>(1.5f);

  world.add(make_shared<Sphere>(100.0, point3(0.0, -100.5, -1.0), materialGround));
  world.add(make_shared<Sphere>(0.5, point3(0.0, 0.0, -1.0), materialCenter));
  world.add(make_shared<Sphere>(0.5, point3(0.0, 0.0, -5.0), materialCenterBack));
  world.add(make_shared<Sphere>(0.5, point3(-1.0, 0.0, -1.0), materialLeft));
  world.add(make_shared<Sphere>(0.5, point3(1.0, 0.0, -1.0), materialRight));

  // Camera
  Camera camera;

  Renderer::writeImage(camera, world, image_width, image_height, samplesPerPixel, "image.ppm");

  std::cerr << "Everything's done!";

  return 0;
}
