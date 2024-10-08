#pragma once
#include <algorithm>
#include <initializer_list>
#include <list>
#include <optional>
#include <stdexcept>
#include <utility>

#include "intersection.h"
#include "utility/log_helper.h"
#include "utility/utility.h"

namespace RayTracer {
class IntersectionCollection {
 public:
  using value_type = Intersection;

  IntersectionCollection() {}

  IntersectionCollection(std::initializer_list<Intersection> intersections);

  void insert(Intersection&& i);

  size_t size() const { return _intersections.size(); }

  const Intersection& operator[](size_t index) const;

  bool empty() const { return _intersections.empty(); }

  std::list<Intersection>::iterator begin() { return _intersections.begin(); }

  std::list<Intersection>::const_iterator cbegin() const { return _intersections.cbegin(); }

  std::list<Intersection>::iterator end() { return _intersections.end(); }

  std::list<Intersection>::const_iterator cend() const { return _intersections.cend(); }

  /**
   * Get the lowest nonnegative hit.
   * @return The lowest nonnegative hit. Or std::nullopt if not exists.
   */
  std::optional<Intersection> hit() const;

 private:
  std::list<Intersection> _intersections;
};
}  // namespace RayTracer

