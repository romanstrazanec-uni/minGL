add_subdirectory(colors)
add_subdirectory(geometry)

add_library(minGLgraphics canvas.hpp canvas.cpp pixel.hpp pixel.cpp)
target_link_libraries(minGLgraphics PUBLIC minGLcolors)
target_link_libraries(minGLgraphics PUBLIC minGLgeometry)

target_include_directories(minGLgraphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
