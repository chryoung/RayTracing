include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(rt_shape
    shape/shapebuilder.cpp)

add_library(rt_image
    image/canvas.cpp)

add_executable(projenv_demo
    demo/projenv_demo.cpp)
target_link_libraries(projenv_demo rt_image)

add_executable(transformation_demo
    demo/transformation_demo.cpp)
target_link_libraries(transformation_demo rt_image)
