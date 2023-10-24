#ifndef BCA943EF_21A1_4078_96EF_64102E5337C8
#define BCA943EF_21A1_4078_96EF_64102E5337C8

#include <list>
#include "shape/basicshape.h"
#include "light/light.h"
#include "ray/ray.h"
#include "ray/intersection_collection.h"

namespace RayTracer {
class World {
public:
  World() {}
  ~World() {}

  std::list<Shape::BasicShapePtr>& objects() { return _objects; }
  const std::list<Shape::BasicShapePtr>& objects() const { return _objects; }

  std::list<Light::LightPtr>& light_sources() { return _light_sources; }
  const std::list<Light::LightPtr>& light_sources() const { return _light_sources; }

  IntersectionCollection intersect(const Ray& ray);
private:
  std::list<Shape::BasicShapePtr> _objects;
  std::list<Light::LightPtr> _light_sources;
};

}

#endif
