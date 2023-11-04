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
  using value_type = Intersection;

  IntersectionCollection() {}

  IntersectionCollection(std::initializer_list<Intersection> intersections);

  void insert(Intersection&& i);

  size_t size() { return _intersections.size(); }
  size_t size() const { return _intersections.size(); }

  Intersection& operator[](size_t index);
  const Intersection& operator[](size_t index) const {
    return const_cast<IntersectionCollection&>(*this).operator[](index);
  }

  std::list<Intersection>::iterator begin() { return _intersections.begin(); }
  std::list<Intersection>::const_iterator cbegin() const { return _intersections.cbegin(); }
  std::list<Intersection>::iterator end() { return _intersections.end(); }
  std::list<Intersection>::const_iterator cend() const { return _intersections.cend(); }

  /**
   * Get the lowest nonnegative hit.
   * @return The lowest nonnegative hit. Or std::nullopt if not exists.
   */
  std::optional<Intersection> hit();

  /**
   * Get the lowest nonnegative hit.
   * @return The lowest nonnegative hit. Or std::nullopt if not exists.
   */
  std::optional<Intersection> hit() const { return const_cast<IntersectionCollection&>(*this).hit(); }

 private:
  std::list<Intersection> _intersections;
};
}  // namespace RayTracer

#endif /* DB4C6BD6_4EFF_4E71_AC37_8EE37D1D12D6 */
