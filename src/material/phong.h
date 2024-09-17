#pragma once
#include "material.h"
#include "image/color.h"
#include "pattern.h"
#include "shape/shapefwddecl.h"

namespace RayTracer {
namespace Material {

class PhongMaterial : public Material {
public:
  PhongMaterial():
    _color(Color(1, 1, 1)),
    _ambient(0.1),
    _diffuse(0.9),
    _specular(0.9),
    _shininess(200.0),
    _reflective(0),
    _transparency(0),
    _refractive_index(1)
  {}

  ~PhongMaterial() = default;

  const Color& color() const override;
  double ambient() const override;
  double diffuse() const override;
  double specular() const override;
  double shininess() const override;
  double reflective() const override;
  double transparency() const override;
  double refractive_index() const override;
  std::shared_ptr<Pattern> pattern() const override;

  friend bool operator==(const PhongMaterial& lhs, const PhongMaterial& rhs);

  PhongMaterial& set_color(Color color) override;
  PhongMaterial& set_ambient(double ambient) override;
  PhongMaterial& set_diffuse(double diffuse) override;
  PhongMaterial& set_specular(double specular) override;
  PhongMaterial& set_shininess(double shininess) override;
  PhongMaterial& set_reflective(double reflective) override;
  PhongMaterial& set_pattern(std::shared_ptr<Pattern> p) override;
  PhongMaterial& set_transparency(double transparency) override;
  PhongMaterial& set_refractive_index(double refractive_index) override;

  Color lighting(Shape::ConstBasicShapePtr object, const Light::Light& light, const Point& position, const Vector& eyev, const Vector& normalv, bool in_shadow) const override;

private:
  std::shared_ptr<Pattern> _pattern;
  Color _color;
  double _ambient;
  double _diffuse;
  double _specular;
  double _shininess;
  double _reflective;
  double _refractive_index;
  double _transparency;
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

