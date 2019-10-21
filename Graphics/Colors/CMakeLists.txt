add_library(minGLcolors colors.hpp HSLColor.cpp HSLColor.hpp RGBColor.cpp RGBColor.hpp)

target_include_directories(minGLcolors PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
