#include "vkt3000_pch.h"

#include <iostream>
#include <fstream>
#include <thread>

#include "color.h"
#include "Hittable.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"


void write_image(const Camera& camera, const Hittable& hittable, int width, int height, int samplesPerPixel, const std::string& fileName);
void write_image_rand11(const Camera& camera, const Hittable& hittable, int width, int height, int samplesPerPixel, const std::string& fileName);

int main() {

  // Image
  constexpr double aspect_ratio    = 16.0 / 9.0;
  constexpr int    image_width     = 1920;
  constexpr int    image_height    = static_cast<int>(image_width / aspect_ratio);
  constexpr int    samplesPerPixel = 10;

  // World
  HittableList world;
  world.add(std::make_shared<Sphere>(0.5, point3(0.5, 0, -2)));
  world.add(std::make_shared<Sphere>(0.5, point3(-0.25, 0, -1)));

  // Camera
  Camera camera;

  std::cerr<<"Everything's done!";

  return 0;
}

void write_image(const Camera& camera, const Hittable& hittable, int width, int height, int samplesPerPixel, const std::string& fileName) {
  std::ofstream file(fileName);
  file << "P3\n" << width << " " << height << "\n255\n";

  std::cerr << "Starting the rendering process...\n" << "\tFile name: " << fileName << "\tWidth: " << width << "\n\tHeight: " << height << "\n";

  for (int j = height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < width; ++i) {
      Color    pixelColor{0.0, 0.0, 0.0};
      for (int s{0}; s < samplesPerPixel; s++) {
        auto u = (double(i) + randomDouble()) / (width - 1);
        auto v = (double(j) + randomDouble()) / (height - 1);
        Ray  r = camera.genRay(u, v);
        pixelColor += ray_color(r, hittable);
      }
      write_color(file, pixelColor, samplesPerPixel);
    }
  }

  std::cerr << "\nDone\n";
}

