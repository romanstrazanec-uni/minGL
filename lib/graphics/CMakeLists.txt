add_library(minGLgraphics canvas.hpp canvas.cpp pixel.hpp pixel.cpp
        colors/colors.hpp colors/hslcolor.cpp colors/hslcolor.hpp colors/rgbcolor.cpp colors/rgbcolor.hpp
        geometry/circle.hpp geometry/circle.cpp geometry/edge.hpp geometry/edge.cpp geometry/line.hpp
        geometry/line.cpp geometry/point.hpp geometry/point.cpp geometry/geometry.hpp)

target_include_directories(minGLgraphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(minGLgraphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/colors")
target_include_directories(minGLgraphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/geometry")
