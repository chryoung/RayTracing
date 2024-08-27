#include "shapebuilder.h"

#include <type_traits>

namespace RayTracer {
namespace Shape {

std::uint64_t ShapeBuilder::_total_id = 0;
std::mutex ShapeBuilder::_mutex;

}  // namespace Shape
}  // namespace RayTracer