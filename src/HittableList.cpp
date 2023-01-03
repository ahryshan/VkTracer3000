//
// Created by alex on 12/15/22.
//

#include "HittableList.h"

void HittableList::clear() {
  m_Objects.clear();
}

void HittableList::add(const std::shared_ptr<Hittable>& object) {
  m_Objects.push_back(object);
}

bool HittableList::hit(const Ray& r, double minT, double maxT, HitRecord& rec) const {
  HitRecord temp_rec;
  bool hitAnything{false};
  double closestSoFar = maxT;

  for(const auto& object : m_Objects) {
    if(object->hit(r, minT, closestSoFar, temp_rec)) {
      hitAnything = true;
      closestSoFar = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hitAnything;
}
