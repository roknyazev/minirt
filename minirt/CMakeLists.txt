cmake_minimum_required(VERSION 3.16)
project(minirt C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(LIBMLX ${CMAKE_SOURCE_DIR}/mlx/libmlx.a)

find_library(OPENGL OpenGL)
find_library(APPKIT AppKit)

include_directories(.)
#include_directories(libft)
include_directories(mlx)

#FILE(GLOB SOURCES *.c src/*.c)
add_executable(minirt main.c minirt.h linalg/linalg.h linalg/vecalg.c canvas/canvas.h canvas/color.c canvas/canvas.c scene/scene.h scene/scene_objects/objects.h scene/light.c scene/camera.c scene/scene.c scene/scene_objects/sphere.c render.c raytrace/raytrace.c scene/scene_objects/object.c raytrace/raytrace.h raytrace/ray.c)
#add_subdirectory(libft)
#target_link_libraries(minirt lib)
add_library(mlx STATIC IMPORTED)
set_property(TARGET mlx PROPERTY IMPORTED_LOCATION ${LIBMLX})
target_link_libraries(minirt mlx ${OPENGL} ${APPKIT})