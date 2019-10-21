add_library(minGLgeometry Circle.hpp Circle.cpp Edge.hpp Edge.cpp Line.hpp Line.cpp Point.hpp Point.cpp geometry.hpp)

target_include_directories(minGLgeometry PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")