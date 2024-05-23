#pragma once
#include <memory>
#include "math/tuple.h"
#include "image/color.h"

namespace RayTracer {
namespace Light {

class Light {
public:
  Light() {}
  virtual ~Light() {}
  virtual const Color& intensity() = 0;
  virtual const Point& position() = 0;

  virtual const Color& intensity() const = 0;
  virtual const Point& position() const = 0;
};

using LightPtr = std::shared_ptr<Light>;
  
} /*  Light  */ 

} /* RayTracer */ 

