#ifndef DB4C6BD6_4EFF_4E71_AC37_8EE37D1D12D6
#define DB4C6BD6_4EFF_4E71_AC37_8EE37D1D12D6

#include <initializer_list>
#include <utility>
#include <vector>

#include "intersection.h"

namespace RayTracer {
class IntersectionCollection {
 public:
  IntersectionCollection() {}

  IntersectionCollection(std::initializer_list<Intersection> intersections) : _intersections{intersections} {
  }

  template<class T>
  void emplace_back(T &&i) {
    _intersections.emplace_back(std::forward<T>(i));
  }

  size_t size() { return _intersections.size(); }
  size_t size() const { return _intersections.size(); }

  Intersection &operator[](size_t index) { return _intersections[index]; }
  const Intersection &operator[](size_t index) const { return _intersections[index]; }

 private:
  std::vector<Intersection> _intersections;
};
}  // namespace RayTracer

#endif /* DB4C6BD6_4EFF_4E71_AC37_8EE37D1D12D6 */
