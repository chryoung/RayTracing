#include "world.h"
#include <memory>

namespace RayTracer {

const Shape::BasicShapePtr World::object_at(int i) const {
  if (i < 0) {
    return nullptr;
  }

  auto iter = _objects.cbegin();
  for (; iter != _objects.cend() && i > 0; --i, ++iter)
    ;

  return (iter != _objects.cend()) ? *iter : nullptr;
}

IntersectionCollection World::intersect(const Ray& ray) const {
  IntersectionCollection union_intersection;
  for (auto& object : _objects) {
    auto xs = object->intersect(ray);
    for (auto&& x : xs) {
      union_intersection.insert(std::move(x));
    }
  }

  return union_intersection;
}

Color World::shade_hit(const Computation& comps) const {
  if (_light) {
    bool shadowed = is_shadowed(comps.over_point);

    return comps.object->material()->lighting(comps.object, *_light, comps.point, comps.eyev, comps.normalv, shadowed);
  }

  return Color::make_black();
}

Color World::color_at(const Ray& r) const {
  auto xs = intersect(r);
  if (!xs.hit()) {
    return Color::make_black();
  }

  auto comps = Computation::prepare_computations(*xs.hit(), r);

  return shade_hit(comps);
}

bool World::is_shadowed(const Point& point) const {
  if (_light) {
    auto v = _light->position() - point;
    auto distance = v.magnitude();
    auto direction = v;
    direction.normalize();

    Ray r{point, direction};
    auto intersections = this->intersect(r);
    auto h = intersections.hit();
    return (h && h->t() < distance);
  }

  return false;
}

} /* RayTracer  */ 
