//
// Created by alex on 12/15/22.
//

#include "Renderer.h"

#include <memory>
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include <functional>

#include "utils.h"
#include "Material.h"

constexpr int rayDepth{25};

struct Chunk {
  uint32_t Height;
  uint32_t Width;
  uint32_t XOffset;
  uint32_t YOffset;
  uint32_t FullImageHeight;
  uint32_t FullImageWidth;
  uint32_t Id;
  uint8_t* buffer{nullptr};

  Chunk() = default;
  Chunk(
      uint32_t height, uint32_t width,
      uint32_t xOffset, uint32_t yOffset,
      uint32_t fullImageHeight, uint32_t fullImageWidth,
      uint32_t id
  ) : Height(height), Width(width),
      XOffset(xOffset), YOffset(yOffset),
      FullImageHeight(fullImageHeight), FullImageWidth(fullImageWidth),
      Id(id) {
    buffer = new uint8_t[Size()];
  }

  Chunk(Chunk&& other) {
    Height          = other.Height;
    Width           = other.Width;
    XOffset         = other.XOffset;
    YOffset         = other.YOffset;
    FullImageWidth  = other.FullImageWidth;
    FullImageHeight = other.FullImageHeight;
    Id              = other.Id;
    buffer          = other.buffer;
    other.buffer = nullptr;
  }

  Chunk& operator=(Chunk&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    Height          = other.Height;
    Width           = other.Width;
    XOffset         = other.XOffset;
    YOffset         = other.YOffset;
    FullImageWidth  = other.FullImageWidth;
    FullImageHeight = other.FullImageHeight;
    Id              = other.Id;
    buffer          = other.buffer;
    other.buffer = nullptr;

    return *this;
  }

  ~Chunk() {
    delete[] buffer;
  }

  [[nodiscard]] inline uint32_t Size() const { return Width * Height * 3; }
};

void writePixel(Color color, uint8_t* pixelPtr, int samplesPerPixel) {
  double r = color.x();
  double g = color.y();
  double b = color.z();

  double scale = 1.0 / samplesPerPixel;
  r = std::sqrt(scale * r);
  g = std::sqrt(scale * g);
  b = std::sqrt(scale * b);

  *pixelPtr       = static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999));
  *(pixelPtr + 1) = static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999));
  *(pixelPtr + 2) = static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999));
}


Color rayColor(const Ray& r, const Hittable& world, int depth) {
  HitRecord rec;

  if (depth <= 0) {
    return {0, 0, 0};
  }

  if (world.hit(r, 0.001, c_INFINITY, rec)) {
    Ray   scattered;
    Color attenuation;
    if (rec.material->scatter(r, rec, attenuation, scattered))
      return attenuation * rayColor(scattered, world, depth - 1);
    return {0.0, 0.0, 0.0};
  }
  vec3      unit_direction = unit_vector(r.direction());
  auto      t              = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

void renderChunk(const Camera& camera, const Hittable& hittable, int samplesPerPixel, Chunk& chunk) {
  std::stringstream ss;
  ss << "Rendering chunk_" << chunk.Id << " on thread " << std::this_thread::get_id() << ":"
     << "\n\tWidth: " << chunk.Width
     << "\n\tHeight: " << chunk.Height << "\n";
  std::cout << ss.str();
  ss.str(std::string());

  uint8_t* bufferPtr{&chunk.buffer[0]};

  for (uint32_t y{0}; y < chunk.Height; y++) {
    uint32_t      absY{chunk.FullImageHeight - (chunk.YOffset + y)};
    for (uint32_t x{0}; x < chunk.Width; x++) {
      uint32_t absX{chunk.XOffset + x};
      Color    pixel{0.0, 0.0, 0.0};
      for (int s{0}; s < samplesPerPixel; s++) {
        auto u = (double(absX) + randomDouble()) / (chunk.FullImageWidth - 1);
        auto v = (double(absY) + randomDouble()) / (chunk.FullImageHeight - 1);
        Ray  r = camera.genRay(u, v);
        pixel += rayColor(r, hittable, rayDepth);
      }
      writePixel(pixel, bufferPtr, samplesPerPixel);
      bufferPtr += 3;
    }
  }
  ss << "Done rendering chunk_" << chunk.Id << " on thread " << std::this_thread::get_id() << "\n";
  std::cout << ss.str();
}

void renderChunksSync(const Camera& camera, const Hittable& hittable, int samplesPerPixel, Chunk* chunks, uint32_t chunkCount) {
  for (Chunk* chunkPtr{chunks}; chunkPtr < chunks + chunkCount; chunkPtr++) {
    renderChunk(camera, hittable, samplesPerPixel, *chunkPtr);
  }
}

void renderChunksConcurrent(const Camera& camera, const Hittable& hittable, int samplesPerPixel, Chunk* chunks, uint32_t chunkCount) {
  auto     hardwareThreads = std::thread::hardware_concurrency();
  uint32_t num_threads{std::min(hardwareThreads != 0 ? hardwareThreads - 1 : 2, chunkCount)};

  std::vector<std::thread> threads(num_threads);
  std::atomic<uint32_t>    nextChunkIndex{0};

  for (auto& thread: threads) {
    thread = std::thread{[&]() {
      while (nextChunkIndex < chunkCount) {
        renderChunk(camera, hittable, samplesPerPixel, chunks[nextChunkIndex++]);
      }
    }};
  }

  for (auto& thread: threads) {
    thread.join();
  }
}

void write_color(std::ostream& out, Color pixel_color, int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Divide the color by the number of samples.
  auto scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void writeChunkBuffers(uint32_t horizontalChunkCount, uint32_t verticalChunkCount, Chunk* chunks, std::ofstream& file) {
  for (uint32_t yOffset{0}; yOffset < verticalChunkCount; yOffset++) {
    uint32_t      rowHeight{chunks[yOffset * horizontalChunkCount].Height};
    for (uint32_t innerY{0}; innerY < rowHeight; innerY++) {
      for (uint32_t xOffset{0}; xOffset < horizontalChunkCount; xOffset++) {
        const Chunk& chunk = chunks[yOffset * horizontalChunkCount + xOffset];
        for (uint32_t innerX{0}; innerX < chunk.Width; innerX++) {
          uint32_t basePixelOffset{(innerY * chunk.Width + innerX) * 3};
          file << (int)chunk.buffer[basePixelOffset] << ' ' << (int)chunk.buffer[basePixelOffset + 1] << ' ' << (int)chunk.buffer[basePixelOffset + 2] << ' ';
        }
      }
    }
  }
}

void Renderer::writeImage(const Camera& camera, const Hittable& hittable, uint32_t width, uint32_t height, int samplesPerPixel, const std::string& fileName) {
//  write_image(camera, hittable, (int)width, (int)height, samplesPerPixel, fileName);
//  return;
  constexpr uint16_t chunkBaseWidth{256};
  constexpr uint16_t chunkBaseHeight{256};

  uint32_t     chunkCount;
  unsigned int chunkHorizontalCount{(unsigned int)width / chunkBaseWidth};
  unsigned int chunkVerticalCount{(unsigned int)height / chunkBaseHeight};
  chunkHorizontalCount += width % chunkBaseWidth == 0 ? 0 : 1;
  chunkVerticalCount += height % chunkBaseHeight == 0 ? 0 : 1;
  chunkCount = chunkHorizontalCount * chunkVerticalCount;

  Chunk chunks[chunkCount];
  Chunk* chunkPtr{chunks};

  for (uint32_t vChunks{0}; vChunks < chunkVerticalCount; vChunks++) {
    uint32_t yOffset{vChunks * chunkBaseHeight};
    uint32_t chunkHeight{yOffset + chunkBaseHeight <= height ? chunkBaseHeight : height - yOffset};

    for (uint32_t hChunks{0}; hChunks < chunkHorizontalCount; hChunks++) {
      static uint32_t nextChunkId{1};
      uint32_t        xOffset{hChunks * chunkBaseWidth};
      uint32_t        chunkWidth{xOffset + chunkBaseWidth <= width ? chunkBaseWidth : width - xOffset};

      *chunkPtr = std::move(Chunk{chunkHeight, chunkWidth, xOffset, yOffset, height, width, nextChunkId++});

      chunkPtr++;
      xOffset += chunkWidth;
    }
    yOffset += chunkBaseHeight;
  }
  auto concurrency{std::thread::hardware_concurrency()};

  if (concurrency != 0)
    renderChunksConcurrent(camera, hittable, samplesPerPixel, chunks, chunkCount);
  else
    renderChunksSync(camera, hittable, samplesPerPixel, chunks, chunkCount);

  std::ofstream file{fileName};
  file << "P3\n" << width << ' ' << height << "\n255\n";

  writeChunkBuffers(chunkHorizontalCount, chunkVerticalCount, chunks, file);
}
