file(GLOB Dmingl "${CMAKE_CURRENT_SOURCE_DIR}/mingl/*.*")
file(GLOB Dgraphics "${CMAKE_CURRENT_SOURCE_DIR}/mingl/graphics/*.*")
file(GLOB Dgeometry "${CMAKE_CURRENT_SOURCE_DIR}/mingl/graphics/geometry/*.*")
file(GLOB Dcolors "${CMAKE_CURRENT_SOURCE_DIR}/mingl/graphics/colors/*.*")

add_library(minGL ${Dmingl} ${Dgraphics} ${Dgeometry} ${Dcolors})

target_link_libraries(minGL PRIVATE gdiplus)
target_include_directories(minGL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
