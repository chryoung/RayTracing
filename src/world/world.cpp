#include "world.h"

namespace RayTracer {

Shape::BasicShapePtr World::object_at(int i) {
  if (i < 0) {
    return nullptr;
  }

  auto iter = _objects.begin();
  for (; iter != _objects.end() && i > 0; --i, ++iter)
    ;

  return (iter != _objects.end()) ? *iter : nullptr;
}

const Shape::BasicShapePtr World::object_at(int i) const {
  if (i < 0) {
    return nullptr;
  }

  auto iter = _objects.cbegin();
  for (; iter != _objects.cend() && i > 0; --i, ++iter)
    ;

  return (iter != _objects.cend()) ? *iter : nullptr;
}

IntersectionCollection World::intersect(const Ray& ray) {
  IntersectionCollection union_intersection;
  for (auto& object : _objects) {
    auto xs = object->intersect(ray);
    for (const auto& x : xs) {
      union_intersection.insert(x);
    }
  }

  return union_intersection;
}

Color World::shade_hit(const Computation& comps) {
  if (_light) {
    return comps.object->material()->lighting(*_light, comps.point, comps.eyev, comps.normalv);
  }

  return Color::make_black();
}

Color World::color_at(const Ray& r) {
  auto xs = intersect(r);
  if (!xs.hit()) {
    return Color::make_black();
  }

  auto comps = Computation::prepare_computations(*xs.hit(), r);

  return shade_hit(comps);
}

} /* RayTracer  */ 
