#ifndef C1D37A2B_66FA_428E_AACF_03C888D2A1B7
#define C1D37A2B_66FA_428E_AACF_03C888D2A1B7

#include "image/color.h"
#include "math/tuple.h"

namespace RayTracer {
namespace Light {

class PointLight {
public:
  PointLight(const Color& intensity, const Point& position):
    _intensity(intensity),
    _position(position)
  {}
  ~PointLight() = default;

  const Color& get_intensity() { return _intensity; }
  const Point& get_position() { return _position; }
private:
  Color _intensity;
  Point _position;
};

}
}

#endif
