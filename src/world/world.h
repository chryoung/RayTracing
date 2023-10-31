#ifndef BCA943EF_21A1_4078_96EF_64102E5337C8
#define BCA943EF_21A1_4078_96EF_64102E5337C8

#include <list>
#include <optional>
#include "shape/basicshape.h"
#include "light/light.h"
#include "ray/ray.h"
#include "ray/intersection_collection.h"

namespace RayTracer {
class Computation;

class World {
public:
  World() {}
  ~World() {}

  std::list<Shape::BasicShapePtr>& objects() { return _objects; }
  const std::list<Shape::BasicShapePtr>& objects() const { return _objects; }

  Shape::BasicShapePtr object_at(int i);
  const Shape::BasicShapePtr object_at(int i) const;

  Light::LightPtr light() { return _light; }
  const Light::LightPtr light() const { return _light; }

  World& set_light(Light::LightPtr light) {
    _light = light;

    return *this;
  }

  IntersectionCollection intersect(const Ray& ray);

  std::optional<Color> shade_hit(const Computation& comps);

  std::optional<Color> color_at(const Ray& r);
private:
  std::list<Shape::BasicShapePtr> _objects;
  Light::LightPtr _light;
};

}

#endif
