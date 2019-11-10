# lib/CMakeLists.txt

set(fileglob *.*)
set(Dmingl "${CMAKE_CURRENT_SOURCE_DIR}/mingl")
set(Dgraphics "${Dmingl}/graphics")
set(Dgui "${Dmingl}/gui")

# get all source files
file(GLOB DCmingl "${Dmingl}/${fileglob}")
file(GLOB DCgraphics "${Dgraphics}/${fileglob}")
file(GLOB DCgeometry "${Dgraphics}/geometry/${fileglob}")
file(GLOB DCcolors "${Dgraphics}/colors/${fileglob}")
file(GLOB DCgui "${Dgui}/${fileglob}")

# add minGL library
add_library(minGL ${DCmingl} ${DCgui} ${DCgraphics} ${DCgeometry} ${DCcolors})
target_link_libraries(minGL PRIVATE gdiplus)
target_include_directories(minGL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# remove unused variables
unset(Dmingl)
unset(Dgraphics)
unset(Dgui)
unset(DCmingl)
unset(DCgraphics)
unset(DCgeometry)
unset(DCcolors)
unset(DCgui)
