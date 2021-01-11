#ifndef DF44B5A4_72C3_40F9_9A2B_196B97646C89
#define DF44B5A4_72C3_40F9_9A2B_196B97646C89

#include <cstdint>

#include "basicshape.h"

namespace RayTracer {
namespace Shape {
class ShapeBuilder final {
 public:
  template <class S>
  static S build() {
    static_assert(std::is_base_of<BasicShape, S>::value, "Shape must be derived from BasicShape.");
    S s(_total_id);
    _total_id++;
    return s;
  }

 private:
  ShapeBuilder() = default;
  static std::uint64_t _total_id;
};
}  // namespace Shape
}  // namespace RayTracer

#endif /* DF44B5A4_72C3_40F9_9A2B_196B97646C89 */
