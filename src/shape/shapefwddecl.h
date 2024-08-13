#pragma once
#include <memory>

namespace RayTracer {
namespace Shape {
class BasicShape;
class Sphere;
class Plane;
using BasicShapePtr = std::shared_ptr<BasicShape>;
using ConstBasicShapePtr = std::shared_ptr<const BasicShape>;
}
}