# lib/CMakeLists.txt

set(fileglob *.*)
set(Dmingl "${CMAKE_CURRENT_SOURCE_DIR}/minglib")
set(Dgraphics "${Dmingl}/graphics")
set(Dgui "${Dmingl}/gui")
set(Dmessaging "${Dmingl}/messaging")

# get all source files
file(GLOB DCgraphics "${Dgraphics}/${fileglob}")
file(GLOB DCgeometry "${Dgraphics}/geometry/${fileglob}")
file(GLOB DCcolors "${Dgraphics}/colors/${fileglob}")
file(GLOB DCgui "${Dgui}/${fileglob}")
file(GLOB DCmessaging "${Dmessaging}/${fileglob}")

# add minGL library
add_library(minGL mingl ${DCgui} ${DCgraphics} ${DCgeometry} ${DCcolors} ${DCmessaging})
target_link_libraries(minGL PRIVATE gdiplus)
target_include_directories(minGL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# remove unused variables
unset(Dmingl)
unset(Dgraphics)
unset(Dgui)
unset(Dmessaging)

unset(DCgraphics)
unset(DCgeometry)
unset(DCcolors)
unset(DCgui)
unset(DCmessaging)
