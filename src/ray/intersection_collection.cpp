#include "intersection_collection.h"

namespace RayTracer {
IntersectionCollection::IntersectionCollection(std::initializer_list<Intersection> intersections)
    : _intersections{intersections} {
  _intersections.sort([](const Intersection& a, const Intersection& b) { return a.t() < b.t(); });
}

void IntersectionCollection::insert(const Intersection& i) {
  auto iter = _intersections.begin();
  for (; iter != _intersections.end(); iter++) {
    if (iter->t() > i.t()) {
      break;
    }
  }

  _intersections.insert(iter, i);
}

Intersection& IntersectionCollection::operator[](size_t index) {
  auto iter = _intersections.begin();
  for (size_t i = 0; i < index && iter != _intersections.end(); i++, iter++)
    ;

  if (iter == _intersections.end()) {
    throw std::out_of_range(CURRENT_LINE + " operator[]: index is out of range.");
  }

  return *iter;
}

std::optional<Intersection> IntersectionCollection::hit() {
  for (const auto& intersection : _intersections) {
    if (is_double_ge(intersection.t(), 0)) {
      return std::optional<Intersection>(intersection);
    }
  }

  return std::nullopt;
}

}  // namespace RayTracer