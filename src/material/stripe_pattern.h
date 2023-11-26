#ifndef A88EBE07_4E64_4994_8F3F_2C327530C1B0
#define A88EBE07_4E64_4994_8F3F_2C327530C1B0

#include "pattern.h"
#include <cmath>

namespace RayTracer {
namespace Material {
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
    int floor;
    if (p.x() < 0) {
      floor = -static_cast<int>(std::ceil(-p.x()));
    } else {
      floor = static_cast<int>(p.x());
    }

    if (floor % 2 == 0) {
      return _a;
    }

    return _b;
  }

  /**
   * Stripe color at the object.
   * @param shape The object with stripe pattern. The caller MUST make sure it's not nullptr.
   * @param p The world point.
   */
  Color stripe_at_object(std::shared_ptr<Shape::BasicShape> shape, const Point& p);

  Color color_at(const Point& p) override {
    return stripe_at(p);
  }

  Color color_at(const Point& p) const override {
    return const_cast<StripePattern&>(*this).stripe_at(p);
  }

  Color color_at_object(std::shared_ptr<Shape::BasicShape> shape, const Point& p) override {
    return stripe_at_object(shape, p);
  }

  Color color_at_object(std::shared_ptr<Shape::BasicShape> shape, const Point& p) const override {
    return const_cast<StripePattern&>(*this).color_at_object(shape, p);
  }

 private:
  Color _a;
  Color _b;
};

} // end of namespace Material
} // end of namespace RayTracer
#endif
