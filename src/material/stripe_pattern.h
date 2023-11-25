#ifndef A88EBE07_4E64_4994_8F3F_2C327530C1B0
#define A88EBE07_4E64_4994_8F3F_2C327530C1B0

#include "pattern.h"
#include "image/color.h"
#include "math/tuple.h"

namespace RayTracer {
class StripePattern : public Pattern {
 public:
  StripePattern():
    _a(Color::make_white()),
    _b(Color::make_black()) {
  }

  StripePattern(const Color& a, const Color& b):
    _a(a),
    _b(b) {
  }
  virtual ~StripePattern() {}

  Color a() { return _a; }
  Color a() const { return _a; }
  StripePattern& set_a(const Color& a) {
    _a = a;
    return *this;
  }

  Color b() { return _b; }
  Color b() const { return _b; }
  StripePattern& set_b(const Color& b) {
    _b = b;
    return *this;
  }

  Color stripe_at(const Point& p) {
    if (static_cast<int>(p.x()) % 2 == 0) {
      return _a;
    }

    return _b;
  }

  Color color_at(const Point& p) {
    return stripe_at(p);
  }

  Color color_at(const Point& p) const {
    return const_cast<StripePattern&>(*this).stripe_at(p);
  }

 private:
  Color _a;
  Color _b;
};
} // end of namespace RayTracer
#endif
