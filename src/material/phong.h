#ifndef D524A412_22F9_458A_B1A1_8B662656FE44
#define D524A412_22F9_458A_B1A1_8B662656FE44

#include <stdexcept>
#include "math/tuple.h"
#include "material.h"
#include "image/color.h"
#include "utility/utility.h"
#include "utility/log_helper.h"
#include "light/pointlight.h"

namespace RayTracer {
namespace Material {

class PhongMaterial : public Material {
public:
  PhongMaterial():
    _color(Color(1, 1, 1)),
    _ambient(0.1),
    _diffuse(0.9),
    _specular(0.9),
    _shininess(200.0)
  {}

  ~PhongMaterial() = default;

  const Color& color() override;
  double ambient() override;
  double diffuse() override;
  double specular() override;
  double shininess() override;

  const Color& color() const override;
  double ambient() const override;
  double diffuse() const override;
  double specular() const override;
  double shininess() const override;

  friend bool operator==(const PhongMaterial& lhs, const PhongMaterial& rhs);

  PhongMaterial& set_color(Color color) override;
  PhongMaterial& set_ambient(double ambient) override;
  PhongMaterial& set_diffuse(double diffuse) override;
  PhongMaterial& set_specular(double specular) override;
  PhongMaterial& set_shininess(double shininess) override;

  Color lighting(const Light::Light& light, const Point& position, const Vector& eyev, const Vector& normalv, bool in_shadow) override;

private:
  Color _color;
  double _ambient;
  double _diffuse;
  double _specular;
  double _shininess;
};

inline bool operator==(const PhongMaterial& lhs, const PhongMaterial& rhs) {
  return lhs._color == rhs._color &&
    lhs._ambient == rhs._ambient &&
    lhs._diffuse == rhs._diffuse &&
    lhs._specular == rhs._specular &&
    lhs._shininess == rhs._shininess;
}

inline bool operator!=(const PhongMaterial& lhs, const PhongMaterial& rhs) {
  return !(lhs == rhs);
}

}
}

#endif
