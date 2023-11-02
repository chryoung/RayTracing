#include "computation.h"
#include "utility/utility.h"

namespace RayTracer {
Computation Computation::prepare_computations(const Intersection& i, const Ray& r) {
  Computation comps;

  comps.t = i.t();
  comps.object = i.object();
  comps.point = r.position(comps.t);
  comps.eyev = -r.direction();
  comps.normalv = comps.object->normal_at(comps.point);
  comps.inside = (comps.normalv.dot(comps.eyev) < 0.0);

  return comps;
}

} /* RayTracer  */ 
