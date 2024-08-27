#pragma once
#include <cstdint>
#include <memory>
#include <utility>
#include <concepts>
#include <mutex>

#include "basicshape.h"

namespace RayTracer {
namespace Shape {
class ShapeBuilder final {
 public:
  ShapeBuilder() = delete;
  template <class ShapeType, class... ParameterType>
    requires std::derived_from<ShapeType, BasicShape>
  static std::shared_ptr<ShapeType> build(ParameterType&&... parameters) {
    std::lock_guard<std::mutex> lock(_mutex);
    std::shared_ptr<ShapeType> s(new ShapeType(_total_id, std::forward<ParameterType>(parameters)...));
    _total_id++;
    return s;
  }

 private:
  static std::uint64_t _total_id;
  static std::mutex _mutex;
};
}  // namespace Shape
}  // namespace RayTracer

