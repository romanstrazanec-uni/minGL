add_subdirectory(Colors)
add_subdirectory(Geometry)

add_library(minGLgraphics Canvas.hpp Canvas.cpp Pixel.hpp Pixel.cpp)
target_link_libraries(minGLgraphics PUBLIC minGLcolors)
target_link_libraries(minGLgraphics PUBLIC minGLgeometry)

target_include_directories(minGLgraphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
