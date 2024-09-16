#pragma once
#include <list>
#include "shape/basicshape.h"
#include "light/light.h"
#include "ray/ray.h"
#include "ray/intersection_collection.h"
#include "ray/computation.h"

namespace RayTracer {

class World {
public:
  World() {}
  ~World() {}

  const std::list<Shape::BasicShapePtr>& objects() const { return _objects; }

  World& add_object(Shape::BasicShapePtr object) {
    _objects.emplace_back(object);

    return *this;
  }

  const Shape::BasicShapePtr object_at(int i) const;

  Light::ConstLightPtr light() const { return _light; }
  Light::LightPtr light() { return _light; }

  World& set_light(Light::LightPtr light) {
    _light = light;

    return *this;
  }

  IntersectionCollection intersect(const Ray& ray) const;

  Color shade_hit(const Computation& comps) const;

  /**
   * Calculate the color at the point in the world hit by the ray.
   * @param r The test ray.
   */
  Color color_at(const Ray& r) const;

  /**
   * Calculate if a point in the world is in the shadow.
   * @param p The point to be tested.
   */
  bool is_shadowed(const Point& p) const;

  /**
   * Calculate the reflected color
   * @param comps The computation of shape and ray
   */
  Color reflected_color(const Computation& comps) const;
private:
  std::list<Shape::BasicShapePtr> _objects;
  Light::LightPtr _light;
};

}

