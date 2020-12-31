project(RayTracing)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(GTest REQUIRED)

add_executable(rt_tests
  src/tuple_test.cpp
  src/utility_test.cpp)
target_link_libraries(rt_tests GTest::GTest GTest::Main)
target_include_directories(rt_tests PUBLIC ${GTEST_INCLUDE_DIRS})

add_test(RayTracingTests rt_tests)