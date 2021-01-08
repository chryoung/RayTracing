#include <fstream>
#include <iostream>
#include <string>

#include "canvas.h"
#include "color.h"
#include "environment.h"
#include "projectile.h"
#include "tuple.h"
#include "utility.h"

using namespace std;
using namespace RayTracer;

Projectile tick(const Environment& env, const Projectile& proj) {
  auto position = proj.postion() + proj.velocity();
  auto velocity = proj.velocity() + env.gravity() + env.wind();

  return Projectile(std::move(position), std::move(velocity));
}

void draw(Canvas& c, const Projectile& proj) {
  int y = c.height() - proj.postion().y() + 0.5;
  int x = proj.postion().x() + 0.5;
  if (y >= 0 && y < c.height() && x >= 0 && x < c.width()) {
    const Color red(0.9, 0, 0);
    c.write_pixel(x, y, red);
  }
}

int main() {
  Vector velocity(10, 1.8, 0);
  velocity.normalize();
  velocity = velocity * 11.25;
  Projectile p(Point(20, 10, 0), velocity);
  Environment e(Vector(0, -0.3, 0), Vector(-0.1, 0, 0));

  Canvas c = Canvas::create(900, 500);
  int count = 0;
  do {
    cout << "Tick " << count << ": ";
    count++;
    draw(c, p);
    p = tick(e, p);
    cout << "p.position == " << p.postion() << "; "
         << "p.velocity == " << p.velocity() << "\n";
  } while (is_double_gt(p.postion().y(), 0.0));

  const string image_file = "image.ppm";
  fstream image(image_file, fstream::out | fstream::trunc);
  if (image.is_open()) {
    c.to_ppm(image);
    cout << "Saved " << image_file << ".\n";
    image.close();
  } else {
    cout << "Cannot open " << image_file << " to write.\n";
  }
}