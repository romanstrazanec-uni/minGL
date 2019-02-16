cmake_minimum_required(VERSION 3.12)
project(libgraphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(libgraphics
        main.cpp
        GUI/Window.h
        GUI/Window.cpp
        Graphics/Geometry/Point.cpp
        Graphics/Geometry/Point.h
        Graphics/Geometry/Edge.cpp
        Graphics/Geometry/Edge.h
        Graphics/Geometry/Circle.cpp
        Graphics/Geometry/Circle.h
        include.h
        Graphics/Geometry/Line.cpp
        Graphics/Geometry/Line.h
        Graphics/Colors/RGBColor.cpp
        Graphics/Colors/RGBColor.h
        Graphics/Colors/HSLColor.cpp
        Graphics/Colors/HSLColor.h
        Graphics/Geometry/geometry.h
        Graphics/Colors/colors.h
        Graphics/Pixel.cpp
        Graphics/Pixel.h
        Graphics/Canvas.cpp
        Graphics/Canvas.h)