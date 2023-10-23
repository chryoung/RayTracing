#ifndef DE42175B_5A7D_4059_8113_AC1894425874
#define DE42175B_5A7D_4059_8113_AC1894425874

#include <cstdint>
#include <memory>

#include "math/matrix.h"
#include "geometry/transform.h"
#include "material/phong.h"

namespace RayTracer {
namespace Shape {
class BasicShape {
 public:
  virtual ~BasicShape() = default;
  std::uint64_t id() { return _id; }
  std::uint64_t id() const { return _id; }

  const Matrix& transform() const { return _transform; }
  BasicShape& set_transform(const Matrix& new_transform) {
    _transform = new_transform;

    return *this;
  }

  const Material::MaterialPtr material() const { return _material; }
  Material::MaterialPtr material() { return _material; }
  BasicShape& set_material(const Material::MaterialPtr& material) {
    _material = material;

    return *this;
  }

  virtual Vector normal_at(const Point& p) {
    return Vector{0, 0, 1};
  }

 protected:
  explicit BasicShape(std::uint64_t id, Matrix transform = Transform::id()) : _id(id), _transform(transform) {}

 private:
  std::uint64_t _id;
  Matrix _transform;
  Material::MaterialPtr _material;
};

using BasicShapePtr = std::shared_ptr<BasicShape>;

inline bool operator==(const BasicShape& a, const BasicShape& b) { return a.id() == b.id(); }
}  // namespace Shape

}  // namespace RayTracer

#endif /* DE42175B_5A7D_4059_8113_AC1894425874 */
