cmake_minimum_required(VERSION 3.16)
project(minirt C)

set(CMAKE_C_STANDARD 99)
set(LIBMLX ${CMAKE_SOURCE_DIR}/mlx/libmlx.a)

find_library(OPENGL OpenGL)
find_library(APPKIT AppKit)

include_directories(.)
include_directories(mlx)

add_executable(minirt
        src/main.c
        includes/minirt.h
        includes/linalg.h
        src/vecalg1.c
        includes/canvas.h
        src/color.c
        src/canvas.c
        includes/scene.h
        includes/objects.h
        src/light.c
        src/camera.c
        src/scene.c
        src/sphere.c
        src/render.c
        src/raytrace.c
        src/object.c
        includes/raytrace.h
        src/ray.c
        src/intersection.c
        src/plane.c
        src/square.c
        src/cylinder.c
        src/triangle.c
        src/parse.c
        src/get_next_line.c
        includes/get_next_line.h
        src/get_next_line_utils.c
        src/parse_objects.c
        src/parse_utils_1.c
        src/bmp.c
        includes/bmp.h
        src/vecalg2.c
        src/parse_scene_elems.c
        src/parse_utils_2.c
        src/mlx_handle.c)

add_library(mlx STATIC IMPORTED)
set_property(TARGET mlx PROPERTY IMPORTED_LOCATION ${LIBMLX})
target_link_libraries(minirt mlx ${OPENGL} ${APPKIT})