find_package(GTest REQUIRED)
include(GoogleTest)
include_directories(${CMAKE_SOURCE_DIR}/src)
enable_testing()

set(RT_TESTS_SRC_FILES
    tuple_test.cpp
    utility_test.cpp
    color_test.cpp
    canvas_test.cpp
    matrix_test.cpp
    transform_test.cpp
    vector_test.cpp
    point_test.cpp
    ray_test.cpp
    sphere_test.cpp
    plane_test.cpp
    intersection_test.cpp
    shape_test.cpp
    light_test.cpp
    material_test.cpp
    world_test.cpp
    camera_test.cpp)

add_executable(rt_tests ${RT_TESTS_SRC_FILES})

target_link_libraries(rt_tests GTest::gtest_main rt)
set_target_properties(rt_tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")
gtest_discover_tests(rt_tests)
