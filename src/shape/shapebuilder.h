#pragma once
#include <cstdint>
#include <memory>
#include <utility>

#include "basicshape.h"

namespace RayTracer {
namespace Shape {
class ShapeBuilder final {
 public:
  template <class ShapeType, class... ParameterType>
  static std::shared_ptr<ShapeType> build(ParameterType&&... parameters) {
    static_assert(std::is_base_of<BasicShape, ShapeType>::value, "Shape must be derived from BasicShape.");
    std::shared_ptr<ShapeType> s(new ShapeType(_total_id, std::forward<ParameterType&&>(parameters)...));
    _total_id++;
    return s;
  }

 private:
  ShapeBuilder() = default;
  static std::uint64_t _total_id;
};
}  // namespace Shape
}  // namespace RayTracer

