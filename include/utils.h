//
// Created by alex on 12/15/22.
//

#ifndef VKTRACER3000_UTILS_H
#define VKTRACER3000_UTILS_H

#include <cmath>
#include <random>

#include "Ray.h"
#include "Hittable.h"
#include "constants.h"

inline double radians(double degrees) {
  return degrees * c_PI / 180.0;
}

inline double randomDouble() {
  return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
  return min + (max-min)*std::rand();
}

inline double randomDouble11() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(mt);
}

inline double randomDouble11(double min, double max) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(min,  max);
  return dist(mt);
}

template<typename T>
inline T clamp(T value, T min, T max) {
  if(value < min) return min;
  if(value > max) return max;
  return value;
}

#endif //VKTRACER3000_UTILS_H
