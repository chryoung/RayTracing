#pragma once
#include <memory>
#include "math/tuple.h"
#include "light/light.h"
#include "image/color.h"
#include "pattern.h"

namespace RayTracer {
namespace Shape {
class BasicShape;
} // end of namespace Shape

namespace Material {

class Material {
public:
  Material() {}
  /**
   * @brief The deconstructor
   */
  virtual ~Material() {}

  /**
   * Calculate the color when the light hit the material.
   * @param object the object to light.
   * @param light The light source.
   * @param position The position where the light hit.
   * @param eyev The eye vector.
   * @param normalv The normal vector of the object surface on the hit position.
   * @param in_shadow If the hit position is in the shadow.
   */
  virtual Color lighting(std::shared_ptr<Shape::BasicShape> object, const Light::Light& light, const Point& position, const Vector& eyev, const Vector& normalv, bool in_shadow) = 0;

  virtual const Color& color() = 0;
  virtual double ambient() = 0;
  virtual double diffuse() = 0;
  virtual double specular() = 0;
  virtual double shininess() = 0;
  virtual std::shared_ptr<Pattern> pattern() = 0;

  virtual const Color& color() const = 0;
  virtual double ambient() const = 0;
  virtual double diffuse() const = 0;
  virtual double specular() const = 0;
  virtual double shininess() const = 0;
  virtual std::shared_ptr<Pattern> pattern() const = 0;

  virtual Material& set_color(Color color) = 0;
  virtual Material& set_ambient(double ambient) = 0;
  virtual Material& set_diffuse(double diffuse) = 0;
  virtual Material& set_specular(double specular) = 0;
  virtual Material& set_shininess(double shininess) = 0;
  virtual Material& set_pattern(std::shared_ptr<Pattern> p) = 0;
};

using MaterialPtr = std::shared_ptr<Material>;

inline bool operator==(const Material& lhs, const Material& rhs) {
  return lhs.color() == rhs.color() &&
    lhs.ambient() == rhs.ambient() &&
    lhs.diffuse() == rhs.diffuse() &&
    lhs.specular() == rhs.specular() &&
    lhs.shininess() == rhs.shininess();
}

inline bool operator!=(const Material& lhs, const Material& rhs) {
  return !(lhs == rhs);
}

}
}

