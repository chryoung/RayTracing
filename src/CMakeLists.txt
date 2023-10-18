include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(RT_SRC_FILES
    shape/shapebuilder.cpp
    image/canvas.cpp
    math/matrix.cpp
    ray/ray.cpp
    ray/intersection_collection.cpp
    geometry/transform.cpp
    shape/sphere.cpp
    material/phong.cpp)

add_library(rt ${RT_SRC_FILES})

add_executable(projenv_demo
        demo/projenv_demo.cpp math/matrix.cpp)
target_link_libraries(projenv_demo rt)

add_executable(transformation_demo
        demo/transformation_demo.cpp)
target_link_libraries(transformation_demo rt)

add_executable(sphere_demo
        demo/sphere_demo.cpp)
target_link_libraries(sphere_demo rt)

add_executable(sphere_with_material_demo
        demo/sphere_with_material_demo.cpp)
target_link_libraries(sphere_with_material_demo rt)
