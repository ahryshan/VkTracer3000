//
// Created by alex on 12/15/22.
//

#ifndef VKTRACER3000_HITTABLELIST_H
#define VKTRACER3000_HITTABLELIST_H


#include <vector>
#include <memory>
#include "Hittable.h"

class HittableList : public Hittable {
public:
  HittableList() = default;
  HittableList(std::initializer_list<std::shared_ptr<Hittable>> objects): m_Objects{objects} {}

  inline std::vector<std::shared_ptr<Hittable>> Objects() const { return m_Objects; }

  void clear();
  void add(const std::shared_ptr<Hittable>& object);

  virtual bool hit(const Ray& r, double minT, double maxT, HitRecord& rec) const override;

private:
  std::vector<std::shared_ptr<Hittable>> m_Objects;
};


#endif //VKTRACER3000_HITTABLELIST_H
