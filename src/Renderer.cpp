//
// Created by alex on 12/15/22.
//

#include "vkt3000_pch.h"
#include "Renderer.h"

#include <thread>
#include <fstream>
#include <cctype>

struct Chunk {
  uint32_t Width;
  uint32_t Height;
  uint32_t xOffset;
  uint32_t yOffset;
  uint8_t* buffer;

  uint64_t Size() {
    return Width * Height;
  }

  Chunk(uint32_t width, uint32_t height, uint32_t xOffset, uint32_t yOffset) : Width(width), Height(height), xOffset(xOffset), yOffset(yOffset) {
    buffer = new uint8_t[Size()];
  }

  ~Chunk() {
    delete[] buffer;
  }
};

void write_pixel(uint8_t* pixelPtr, Color pixelColor, int samplesPerPixel) {
  double r = pixelColor.x();
  double g = pixelColor.y();
  double b = pixelColor.z();

  double scale = 1.0 / samplesPerPixel;

  r *= scale;
  g *= scale;
  b *= scale;

  *pixelPtr = static_cast<int>(255.999 * clamp(r, 0.0, 0.999));
  pixelPtr++;
  *pixelPtr = static_cast<int>(255.999 * clamp(g, 0.0, 0.999));
  pixelPtr++;
  *pixelPtr = static_cast<int>(255.999 * clamp(b, 0.0, 0.999));
}

void write_buffer(const Camera& camera, const Hittable& hittable, int samplesPerPixel, Chunk& chunk) {
  uint8_t* bufferPtr;

}

void Renderer::writeImage(const Camera& camera, const Hittable& hittable, int width, int height, int samplesPerPixel, const std::string& fileName) {
  uint8_t buffer[width * height * 3];
  auto    concurrency = std::thread::hardware_concurrency();

  if (concurrency == 0) concurrency = 8;

  std::vector<Chunk>       chunks;
  std::vector<std::thread> threads;

  const int chunkBaseWidth{int(width / concurrency)};
  const int chunkBaseHeight{int(height / concurrency)};

  int w{0};
  int h{0};

  while (w < width) {
    while (h < height) {
      chunks.emplace_back(chunkBaseWidth, chunkBaseHeight, w, h);
      h += chunkBaseHeight;
    }
    w += chunkBaseWidth;
  }

  for (auto& chunk: chunks) {
    std::thread thread{[&]() {

    }};
  }

  for (auto& th: threads) {
    th.join();
  }
}
