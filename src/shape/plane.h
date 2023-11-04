#include "basicshape.h"

namespace RayTracer {
namespace Shape {

class ShapeBuilder;

class Plane : public BasicShape {
 public:
  Vector local_normal_at(const Point& local_point) override;

  IntersectionCollection local_intersect(const Ray& local_test_ray) override;

  friend class ShapeBuilder;
 private:
  explicit Plane(std::uint64_t id, Matrix transform = Transform::id(), Material::MaterialPtr material = std::make_shared<Material::PhongMaterial>()):
    BasicShape{id, transform, material}
  {}
};
  
} /* Shape */ 
} /* RayTracer  */ 
