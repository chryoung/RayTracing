#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include <fstream>
#include <iostream>

#include "canvas.h"
#include "color.h"
#include "transform.h"
#include "tuple.h"

using namespace std;
using namespace RayTracer;

int main() {
  auto p = Tuple::make_point(1, 0, 0);
  double pi_6 = M_PI / 6.0;
  constexpr int IMAGE_SIZE = 500;
  constexpr double SCALE_SIZE = IMAGE_SIZE * 3.0 / 8.0;
  Canvas clock(IMAGE_SIZE, IMAGE_SIZE);
  const Color white(1, 1, 1);
  for (int i = 0; i < 12; i++) {
    Transform::TransformationBuilder tb;
    tb.rotate_y(i * pi_6)
      .scale(SCALE_SIZE, 0, SCALE_SIZE)
      .translate(IMAGE_SIZE / 2, 0, IMAGE_SIZE / 2);
    auto draw_point = tb.build() * p;
    int x = draw_point.x() + 0.5;
    int y = draw_point.z() + 0.5;
    cout << "Write at (" << x << ", " << y << ")" << endl;
    clock.write_pixel(x, y, white);
  }

  const char* ppm_file = "clock.ppm";
  fstream image(ppm_file, fstream::out | fstream::trunc);
  if (image.is_open()) {
    clock.to_ppm(image);
    image.close();
    cout << "Saved " << ppm_file << endl;
  } else {
    cerr << "Cannot open " << ppm_file << " to save.\n";
  }
}