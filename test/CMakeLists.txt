include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include)
enable_testing()
add_executable(rt_tests
    tuple_test.cpp
    utility_test.cpp
    color_test.cpp
    canvas_test.cpp
    matrix_test.cpp
    transform_test.cpp
    vector_test.cpp
    point_test.cpp
    ray_test.cpp
    intersection_test.cpp)

target_link_libraries(rt_tests gtest gtest_main rt_image rt_shape)
set_target_properties(rt_tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")
add_test(RayTracingTests rt_tests)
