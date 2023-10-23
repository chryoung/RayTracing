#ifndef A95344E4_2D0E_4F61_AA9A_2CE2D5C2D916
#define A95344E4_2D0E_4F61_AA9A_2CE2D5C2D916

#include <memory>
#include "image/color.h"

namespace RayTracer {
namespace Material {

class Material {
public:
  Material() {}
  virtual Material() {}
  virtual Color lighting(const Light::PointLight& light, const Point& position, const Vector& eyev, const Vector& normalv) {
    return Color::make_black();
  }
};

using MaterialPtr = std::shared_ptr<Material>;

}
}

#endif