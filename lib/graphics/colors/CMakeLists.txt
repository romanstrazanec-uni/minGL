add_library(minGLcolors colors.hpp hslcolor.cpp hslcolor.hpp rgbcolor.cpp rgbcolor.hpp)

target_include_directories(minGLcolors PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
