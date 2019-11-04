cmake_minimum_required(VERSION 3.12)
project(minGL)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Graphics)
add_subdirectory(GUI)
add_subdirectory(test)

# target_include_directories(minGL PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/gdiplus> $<INSTALL_INTERFACE:include/gdiplus>)
