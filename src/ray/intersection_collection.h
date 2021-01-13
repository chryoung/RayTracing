#ifndef DB4C6BD6_4EFF_4E71_AC37_8EE37D1D12D6
#define DB4C6BD6_4EFF_4E71_AC37_8EE37D1D12D6

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
  IntersectionCollection() {}

  IntersectionCollection(std::initializer_list<Intersection> intersections) : _intersections{intersections} {
    _intersections.sort([](const Intersection& a, const Intersection& b) { return a.time() < b.time(); });
  }

  void insert(const Intersection& i) {
    auto iter = _intersections.begin();
    for (; iter != _intersections.end(); iter++) {
      if (iter->time() > i.time()) {
        break;
      }
    }

    _intersections.insert(iter, i);
  }

  size_t size() { return _intersections.size(); }
  size_t size() const { return _intersections.size(); }

  Intersection& operator[](size_t index) {
    auto iter = _intersections.begin();
    for (size_t i = 0; i < index && iter != _intersections.end(); i++, iter++)
      ;

    if (iter == _intersections.end()) {
      throw std::out_of_range(CURRENT_LINE + " operator[]: index is out of range.");
    }

    return *iter;
  }

  const Intersection& operator[](size_t index) const {
    return const_cast<IntersectionCollection&>(*this).operator[](index);
  }

  std::optional<Intersection> hit() {
    for (const auto& intersection : _intersections) {
      if (is_double_ge(intersection.time(), 0)) {
        return intersection;
      }
    }

    return std::nullopt;
  }

  std::optional<Intersection> hit() const { return const_cast<IntersectionCollection&>(*this).hit(); }

 private:
  std::list<Intersection> _intersections;
};
}  // namespace RayTracer

#endif /* DB4C6BD6_4EFF_4E71_AC37_8EE37D1D12D6 */
