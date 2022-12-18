//
// Created by alex on 12/14/22.
//

#ifndef VKTRACER3000_COLOR_H
#define VKTRACER3000_COLOR_H

#include <iostream>

#include "Ray.h"
#include "Hittable.h"
#include "vec3.h"
#include "constants.h"

//void write_color(std::ostream& out, Color pixelColor, int samplesPerPixel) {
//  double r = pixelColor.x();
//  double g = pixelColor.y();
//  double b = pixelColor.z();
//
//  double scale = 1.0 / samplesPerPixel;
//
//  r *= scale;
//  g *= scale;
//  b *= scale;
//
//  out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
//      << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
//      << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
//}
#endif //VKTRACER3000_COLOR_H
