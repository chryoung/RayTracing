#include "image/canvas.h"

#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace RayTracer;

TEST(Canvas, WhenCreateACanvasExpectEveryPixelIsBlack) {
  Canvas c = Canvas::create(10, 20);
  EXPECT_EQ(c.width(), 10);
  EXPECT_EQ(c.height(), 20);
  Color black(0, 0, 0);
  for (int x = 0; x < c.width(); ++x) {
    for (int y = 0; y < c.height(); ++y) {
      EXPECT_EQ(black, c.pixel_at(x, y));
    }
  }
}

TEST(Canvas, WhenWriteAPixelExpectPixelOnCanvas) {
  Canvas c = Canvas::create(10, 20);
  Color red(1, 0, 0);
  c.write_pixel(2, 3, red);
  EXPECT_EQ(red, c.pixel_at(2, 3));
}

TEST(Canvas, WhenWriteACanvasToPPMExpectHeaderIsCorrect) {
  const Canvas c = Canvas::create(5, 3);
  stringstream ppm_stream;
  c.to_ppm(ppm_stream);
  string ppm = ppm_stream.str();
  string header = "P3\n5 3\n255\n";
  EXPECT_EQ(header, ppm.substr(0, header.size()));
}

TEST(Canvas, WhenWriteACanvasToPPMExpectContentIsCorrect) {
  Canvas c = Canvas::create(5, 3);
  c.write_pixel(0, 0, Color(1.5, 0, 0));
  c.write_pixel(2, 1, Color(0, 0.5, 0));
  c.write_pixel(4, 2, Color(-0.5, 0, 1));
  stringstream ppm_stream;
  string line;
  c.to_ppm(ppm_stream);
  string ppm = ppm_stream.str();
  int line_count = 0;
  size_t from = 0;
  size_t to = 0;

  // Skip the header.
  constexpr int NUMBER_HEADER_LINES = 3;
  while (line_count < NUMBER_HEADER_LINES) {
    to = ppm.find('\n', from);
    if (to == string::npos) {
      break;
    }
    from = to + 1;
    ++line_count;
  }

  EXPECT_EQ(NUMBER_HEADER_LINES, line_count);

  // Verify the content.
  constexpr int NUMBER_CONTENT_LINES = 3;
  string contents = 
      "P3\n"
      "5 3\n"
      "255\n"
      "255   0   0   0   0   0   0   0   0   0   0   0   0   0   0\n"
      "  0   0   0   0   0   0   0 128   0   0   0   0   0   0   0\n"
      "  0   0   0   0   0   0   0   0   0   0   0   0   0   0 255\n";

  EXPECT_EQ(contents, ppm);
}

TEST(Canvas, WhenALineIsLongerThan70InPpmExpectNewLineInPpm) {
  Canvas c = Canvas::create(10, 2);
  Color color(1, 0.8, 0.6);
  for (int x = 0; x < c.width(); x++) {
    for (int y = 0; y < c.height(); y++) {
      c.write_pixel(x, y, color);
    }
  }

  stringstream ppm_stream;
  string line;
  c.to_ppm(ppm_stream);
  string ppm = ppm_stream.str();
  int line_count = 0;
  size_t from = 0;
  size_t to = 0;

  // Skip the header.
  constexpr int NUMBER_HEADER_LINES = 3;
  while (line_count < NUMBER_HEADER_LINES) {
    to = ppm.find('\n', from);
    if (to == string::npos) {
      break;
    }
    from = to + 1;
    ++line_count;
  }

  EXPECT_EQ(NUMBER_HEADER_LINES, line_count);

  // Verify the content.
  constexpr int NUMBER_CONTENT_LINES = 4;
  string contents =
      "P3\n"
      "10 2\n"
      "255\n"
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n";

  EXPECT_EQ(contents, ppm);
}

