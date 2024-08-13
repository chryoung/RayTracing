include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(fmt REQUIRED)

set(RT_SRC_FILES
    shape/shapebuilder.cpp
    image/canvas.cpp
    math/matrix.cpp
    ray/ray.cpp
    ray/intersection_collection.cpp
    ray/computation.cpp
    geometry/transform.cpp
    shape/basicshape.cpp
    shape/sphere.cpp
    shape/plane.cpp
    material/phong.cpp
    material/pattern.cpp
    world/world.cpp
    camera/camera.cpp)

add_library(rt ${RT_SRC_FILES})
target_link_libraries(rt fmt::fmt)

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

add_executable(render_world_demo
        demo/render_world_demo.cpp)
target_link_libraries(render_world_demo rt)

add_executable(render_world_demo_2
        demo/render_world_demo_2.cpp)
target_link_libraries(render_world_demo_2 rt)
