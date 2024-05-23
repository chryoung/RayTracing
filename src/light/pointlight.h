#pragma once
#include "light.h"
#include "image/color.h"
#include "math/tuple.h"

namespace RayTracer {
namespace Light {

class PointLight : public Light {
public:
  PointLight(const Point& position, const Color& intensity):
    _position(position),
    _intensity(intensity)
  {}
  ~PointLight() = default;

  const Color& intensity() override { return _intensity; }
  const Point& position() override { return _position; }

  const Color& intensity() const override { return _intensity; }
  const Point& position() const override { return _position; }
private:
  Color _intensity;
  Point _position;
};

}
}

