#ifndef DB1E0476_45C3_4BB2_B83F_F11AF180E1E7
#define DB1E0476_45C3_4BB2_B83F_F11AF180E1E7

#include "tuple.h"

namespace RayTracer
{
class Environment {
public:
  Environment(const Tuple& gravity, const Tuple& wind): _gravity(gravity), _wind(wind) {}

  const Tuple& gravity() const { return _gravity; }
  const Tuple& gravity() { return _gravity; }

  const Tuple& wind() const { return _wind; }
  const Tuple& wind() { return _wind; }

  Environment& set_gravity(const Tuple& gravity) {
    _gravity = gravity;

    return *this;
  }

  Environment& set_wind(const Tuple& wind) {
    _wind = wind;

    return *this;
  }
private:
  Tuple _gravity;
  Tuple _wind;
};
} // namespace RayTracer


#endif /* DB1E0476_45C3_4BB2_B83F_F11AF180E1E7 */
