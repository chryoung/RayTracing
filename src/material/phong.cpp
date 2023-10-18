#include <cmath>
#include "phong.h"
#include "math/util.h"
#include "utility/utility.h"

namespace RayTracer {
namespace Material {

const Color& PhongMaterial::color() { return _color; }
double PhongMaterial::ambient() { return _ambient; }
double PhongMaterial::diffuse() { return _diffuse; }
double PhongMaterial::specular() { return _specular; }
double PhongMaterial::shininess() { return _shininess; }

PhongMaterial& PhongMaterial::set_color(Color color) {
  _color = color;
  return *this;
}

PhongMaterial& PhongMaterial::set_ambient(double ambient) {
  if (is_double_gt(ambient, 1.0) || is_double_lt(ambient, 0.0)) {
    throw std::invalid_argument(CURRENT_LINE + "ambient should be between 0 and 1");
  }

  _ambient = ambient;

  return *this;
}

PhongMaterial& PhongMaterial::set_diffuse(double diffuse) {
  if (is_double_gt(diffuse, 1.0) || is_double_lt(diffuse, 0.0)) {
    throw std::invalid_argument(CURRENT_LINE + "diffuse should be between 0 and 1");
  }

  _diffuse = diffuse;

  return *this;
}

PhongMaterial& PhongMaterial::set_specular(double specular) {
  if (is_double_gt(specular, 1.0) || is_double_lt(specular, 0.0)) {
    throw std::invalid_argument(CURRENT_LINE + "specular should be between 0 and 1");
  }

  _specular = specular;

  return *this;
}

PhongMaterial& PhongMaterial::set_shininess(double shininess) {
  if (is_double_gt(shininess, 200.0) || is_double_lt(shininess, 10.0)) {
    throw std::invalid_argument(CURRENT_LINE + "shininess should be between 10 and 200");
  }

  _shininess = shininess;

  return *this;
}

Color PhongMaterial::lighting(const Light::PointLight& light, const Point& position, const Vector& eyev, const Vector& normalv) {
  Color effective_color = _color * light.intensity();

  Vector lightv = light.position() - position;
  lightv.normalize();

  Color ambient = effective_color * _ambient;

  double light_dot_normal = lightv.dot(normalv);

  Color diffuse;
  Color specular;

  if (light_dot_normal < 0) {
    diffuse = Color::make_black();
    specular = Color::make_black();
  } else {
    diffuse = effective_color * _diffuse * light_dot_normal;
    Vector reflectv = reflect(-lightv, normalv);
    double reflect_dot_eye = reflectv.dot(eyev);
    if (is_double_le(reflect_dot_eye, 0.0)) {
      specular = Color::make_black();
    } else {
      double factor = std::pow(reflect_dot_eye, _shininess);
      specular = light.intensity() * _specular * factor;
    }
  }

  return ambient + diffuse + specular;
}

}
}
