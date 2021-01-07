project(RayTracing)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

add_executable(projenv_demo
  src/canvas.cpp
  src/projenv_demo.cpp)

add_executable(transformation_demo
  src/canvas.cpp
  src/transformation_demo.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(rt_tests
  src/tuple_test.cpp
  src/utility_test.cpp
  src/color_test.cpp
  src/canvas.cpp
  src/canvas_test.cpp
  src/matrix_test.cpp
  src/transform_test.cpp)
target_link_libraries(rt_tests GTest::GTest GTest::Main)
target_include_directories(rt_tests PUBLIC ${GTEST_INCLUDE_DIRS})

add_test(RayTracingTests rt_tests)