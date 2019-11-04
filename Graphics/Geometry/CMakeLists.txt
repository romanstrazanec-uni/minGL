add_library(minGLgeometry circle.hpp circle.cpp edge.hpp edge.cpp line.hpp line.cpp point.hpp point.cpp geometry.hpp)

target_include_directories(minGLgeometry PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
