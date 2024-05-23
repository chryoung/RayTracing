#pragma once
#include <cstdint>
#include <memory>

#include "material/material.h"
#include "math/matrix.h"
#include "geometry/transform.h"
#include "material/phong.h"

namespace RayTracer {

class ShapeBuilder;
class Ray;
class IntersectionCollection;

namespace Shape {
class BasicShape : public std::enable_shared_from_this<BasicShape> {
 public:
  virtual ~BasicShape() = default;
  std::uint64_t id() { return _id; }
  std::uint64_t id() const { return _id; }

  const Matrix& transform() { return _transform; }
  const Matrix& transform() const { return _transform; }

  const Matrix& transform_inv() { return _transform_inv; }
  const Matrix& transform_inv() const { return _transform_inv; }

  BasicShape& set_transform(const Matrix& new_transform) {
    _transform = new_transform;
    _transform_inv = _transform.inverse();
    _transform_inv_t = _transform_inv.transpose();

    return *this;
  }

  Material::MaterialPtr material() { return _material; }
  const Material::MaterialPtr material() const { return _material; }

  BasicShape& set_material(const Material::MaterialPtr& material) {
    _material = material;

    return *this;
  }

  /**
   * Calculate the normal at the point on the object itself.
   * @param p The point on the object.
   */
  virtual Vector normal_at(const Point& p);

  /**
   * Calculate the normal at the point on the object itself.
   * @param p The point on the object.
   */
  virtual Vector normal_at (const Point& p) const;

  /**
   * Test if the object intersects with the test ray.
   * @param ray The test ray.
   * @return The collection of intersects
   */
  virtual IntersectionCollection intersect(const Ray& ray);


  /**
   * Test if the object intersects with the test ray.
   * @param ray The test ray.
   * @return The collection of intersects
   */
  virtual IntersectionCollection intersect(const Ray& ray) const;

  /**
   * Calculate normal in local space.
   */
  virtual Vector local_normal_at(const Point& local_point);

  /**
   * Test if the object intersects with the test ray in local space.
   */
  virtual IntersectionCollection local_intersect(const Ray& local_test_ray);

  friend class ShapeBuilder;

 protected:
  explicit BasicShape(std::uint64_t id, Matrix transform = Transform::id(), Material::MaterialPtr material = std::make_shared<Material::PhongMaterial>()) :
    _id(id),
    _transform(transform),
    _transform_inv(transform.inverse()),
    _transform_inv_t(_transform_inv.transpose()),
    _material(material) {}

 private:
  std::uint64_t _id;
  Matrix _transform;
  Matrix _transform_inv;
  Matrix _transform_inv_t;
  Material::MaterialPtr _material;
};

using BasicShapePtr = std::shared_ptr<BasicShape>;

inline bool operator==(const BasicShape& a, const BasicShape& b) { return a.id() == b.id(); }
inline bool operator!=(const BasicShape& a, const BasicShape& b) { return a.id() != b.id(); }
}  // namespace Shape

}  // namespace RayTracer

