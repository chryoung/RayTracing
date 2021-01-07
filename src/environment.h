#ifndef DB1E0476_45C3_4BB2_B83F_F11AF180E1E7
#define DB1E0476_45C3_4BB2_B83F_F11AF180E1E7

#include "tuple.h"

namespace RayTracer
{
class Environment {
public:
  Environment(const Vector& gravity, const Vector& wind): _gravity(gravity), _wind(wind) {}

  const Vector& gravity() const { return _gravity; }
  const Vector& gravity() { return _gravity; }

  const Vector& wind() const { return _wind; }
  const Vector& wind() { return _wind; }

  Environment& set_gravity(const Vector& gravity) {
    _gravity = gravity;

    return *this;
  }

  Environment& set_wind(const Vector& wind) {
    _wind = wind;

    return *this;
  }
private:
  Vector _gravity;
  Vector _wind;
};
} // namespace RayTracer


#endif /* DB1E0476_45C3_4BB2_B83F_F11AF180E1E7 */
