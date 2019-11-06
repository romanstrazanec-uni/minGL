# lib/CMakeLists.txt

set(fileglob *.*)
set(Dmingl "${CMAKE_CURRENT_SOURCE_DIR}/mingl")
set(Dgraphics "${Dmingl}/graphics")

# get all source files
file(GLOB DCmingl "${Dmingl}/${fileglob}")
file(GLOB DCgraphics "${Dgraphics}/${fileglob}")
file(GLOB DCgeometry "${Dgraphics}/geometry/${fileglob}")
file(GLOB DCcolors "${Dgraphics}/colors/${fileglob}")

# add minGL library
add_library(minGL ${DCmingl} ${DCgraphics} ${DCgeometry} ${DCcolors})
target_link_libraries(minGL PRIVATE gdiplus)
target_include_directories(minGL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# remove unused variables
unset(Dmingl)
unset(Dgraphics)
unset(DCmingl)
unset(DCgraphics)
unset(DCgeometry)
unset(DCcolors)
