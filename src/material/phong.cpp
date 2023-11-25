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
std::shared_ptr<Pattern> PhongMaterial::pattern() { return _pattern; }

const Color& PhongMaterial::color() const { return _color; }
double PhongMaterial::ambient() const { return _ambient; }
double PhongMaterial::diffuse() const { return _diffuse; }
double PhongMaterial::specular() const { return _specular; }
double PhongMaterial::shininess() const { return _shininess; }
std::shared_ptr<Pattern> PhongMaterial::pattern() const { return _pattern; }

PhongMaterial& PhongMaterial::set_color(Color color) {
  _color = color;
  return *this;
}

PhongMaterial& PhongMaterial::set_ambient(double ambient) {
  if (ambient > 1.0 || ambient < 0.0) {
    throw std::invalid_argument(CURRENT_LINE + "ambient should be between 0 and 1");
  }

  _ambient = ambient;

  return *this;
}

PhongMaterial& PhongMaterial::set_diffuse(double diffuse) {
  if (diffuse > 1.0 || diffuse < 0.0) {
    throw std::invalid_argument(CURRENT_LINE + "diffuse should be between 0 and 1");
  }

  _diffuse = diffuse;

  return *this;
}

PhongMaterial& PhongMaterial::set_specular(double specular) {
  if (specular > 1.0 || specular < 0.0) {
    throw std::invalid_argument(CURRENT_LINE + "specular should be between 0 and 1");
  }

  _specular = specular;

  return *this;
}

PhongMaterial& PhongMaterial::set_shininess(double shininess) {
  if (shininess > 200.0 || shininess < 10.0) {
    throw std::invalid_argument(CURRENT_LINE + "shininess should be between 10 and 200");
  }

  _shininess = shininess;

  return *this;
}

PhongMaterial& PhongMaterial::set_pattern(std::shared_ptr<Pattern> p) {
  _pattern = p;

  return *this;
}

Color PhongMaterial::lighting(const Light::Light& light, const Point& position, const Vector& eyev, const Vector& normalv, bool in_shadow) {
  Color color;

  if (_pattern != nullptr) {
    color = _pattern->color_at(position);
  } else {
    color = _color;
  }

  Color effective_color = color * light.intensity();

  Color ambient = effective_color * _ambient;

  if (in_shadow) {
    return ambient;
  }

  Vector lightv = light.position() - position;
  lightv.normalize();

  double light_dot_normal = lightv.dot(normalv);

  Color diffuse = Color::make_black();
  Color specular = Color::make_black();

  if (light_dot_normal > 0) {
    diffuse = effective_color * _diffuse * light_dot_normal;
    Vector reflectv = reflect(-lightv, normalv);
    double reflect_dot_eye = reflectv.dot(eyev);
    if (reflect_dot_eye < 0) {
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
