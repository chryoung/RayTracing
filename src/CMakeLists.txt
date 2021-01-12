add_executable(projenv_demo
        canvas.cpp
        projenv_demo.cpp)

add_executable(transformation_demo
        canvas.cpp
        transformation_demo.cpp)

enable_testing()
add_executable(rt_tests
        tuple_test.cpp
        utility_test.cpp
        color_test.cpp
        canvas.cpp
        canvas_test.cpp
        matrix_test.cpp
        transform_test.cpp
        vector_test.cpp
        point_test.cpp
        ray_test.cpp
        shape/shapebuilder.cpp
        intersection_test.cpp)

target_link_libraries(rt_tests gtest gtest_main)

add_test(RayTracingTests rt_tests)