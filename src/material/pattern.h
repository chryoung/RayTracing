#ifndef D748DFC1_3B0F_4F96_BCDA_4D139E4794A6
#define D748DFC1_3B0F_4F96_BCDA_4D139E4794A6

#include "math/tuple.h"
#include "image/color.h"

namespace RayTracer {
class Pattern {
 public:
  Pattern() {}
  virtual ~Pattern() {}
  virtual Color color_at(const Point& p) = 0; 
  virtual Color color_at(const Point& p) const = 0; 
};
} // end of namespace RayTracer

#endif
