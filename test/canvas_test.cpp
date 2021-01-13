#include "image/canvas.h"

#include <gtest/gtest.h>

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
  string contents[NUMBER_CONTENT_LINES]{
      "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
      "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0",
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255",
  };

  constexpr int TOTAL_LINES = NUMBER_HEADER_LINES + NUMBER_CONTENT_LINES;
  while (line_count < TOTAL_LINES) {
    to = ppm.find('\n', from);
    if (to == string::npos) {
      break;
    }
    line = ppm.substr(from, to - from);
    EXPECT_EQ(contents[line_count - NUMBER_HEADER_LINES], line);
    from = to + 1;
    ++line_count;
  }

  EXPECT_EQ(TOTAL_LINES, line_count);
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
  string contents[NUMBER_CONTENT_LINES]{
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
      "153 255 204 153 255 204 153 255 204 153 255 204 153",
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
      "153 255 204 153 255 204 153 255 204 153 255 204 153",
  };

  constexpr int TOTAL_LINES = NUMBER_HEADER_LINES + NUMBER_CONTENT_LINES;
  while (line_count < TOTAL_LINES) {
    to = ppm.find('\n', from);
    if (to == string::npos) {
      break;
    }
    line = ppm.substr(from, to - from);
    EXPECT_EQ(contents[line_count - NUMBER_HEADER_LINES], line);
    from = to + 1;
    ++line_count;
  }

  EXPECT_EQ(TOTAL_LINES, line_count);
}

TEST(Canvas, WhenBreakLinesExpectCorrectBreakLines) {
  string s1 = "0 0 0 0 0 0 0 0\n";
  string s2 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 0\n";
  string s3 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 0 0\n";
  string s4 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 0 0 0 0 0\n";
  string s5 =
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 255 "
      "204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 255 204 "
      "153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 255 204 153 "
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204\n";

  auto lines1 = Canvas::break_line(s1);
  auto lines2 = Canvas::break_line(s2);
  auto lines3 = Canvas::break_line(s3);
  auto lines4 = Canvas::break_line(s4);
  auto lines5 = Canvas::break_line(s5);

  vector<string> truth1{
      "0 0 0 0 0 0 0 0\n",
  };
  vector<string> truth2{
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
      "0\n",
  };
  vector<string> truth3{
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 0\n",
      "0\n",
  };
  vector<string> truth4{
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 0\n",
      "0 0 0 0\n",
  };
  vector<string> truth5{
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n",
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n",
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n",
      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n",
  };

  EXPECT_EQ(truth1, lines1);
  EXPECT_EQ(truth2, lines2);
  EXPECT_EQ(truth3, lines3);
  EXPECT_EQ(truth4, lines4);
  EXPECT_EQ(truth5, lines5);
}